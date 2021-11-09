# -*- coding: utf-8 -*-
"""
Created on Tue Oct 26 09:39:42 2021
Test out functions in python
@author: EPsajd
"""
# issue accepting python float values as argument 
# REMEMBER: in dll file make swig and make dll 

import datalink as dl 
import tkinter as tk
import numpy as np
import time
import threading
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

root = tk.Tk() #creates root main window but does not start it 
root.wm_title("Scope/FG Control")

scope_handle = 0
fg_handle = 0


t = threading.Thread(target = Graph)
t.start()

# function to gen resource man, init scope and fg
var_ch = tk.StringVar(value="1")
#status for initialization of devices
var_status = tk.StringVar(value="Not Connected")

#create graphspace
fig= Figure(figsize=(5,4),dpi=100)

graph= fig.add_subplot()
graph.set_xlabel("Frequency")
graph.set_ylabel("Amplitude")
graph.set_title("Frequency vs. Amplitude")

canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT)


def quit():
    root.destroy()

def Initdevices():
    ch = int(var_ch.get())
    global var_status
    resource_manager = dl.resourceCreate()
    #if resource manager runs fine, complete scope and FG inits
    global scope_handle
    scope_handle = dl.initScope(resource_manager)
    global fg_handle
    fg_handle = dl.initFG(resource_manager)
    # set channels for both devices 
    dl.initCH(fg_handle, ch)
    dl.setSinWave(fg_handle, ch, 5, 100, 0, 0)
    #dl.setFreq(fg_handle, ch, 100)
    dl.Scopeset(scope_handle)
    var_status.set("Connected") 


var_fstart = tk.StringVar(value="1")
var_fend = tk.StringVar(value="50")
var_fint = tk.StringVar(value="5")
var_dat = tk.StringVar(value="0")

def Graph():
    global fg_handle
    global scope_handle
    start = int(var_fstart.get())
    end = int(var_fend.get())
    interval = int(var_fint.get())
    ch = int(var_ch.get())
    #create thread
    
    # set amp, offset, etc, to zero 
    dl.setSinWave(fg_handle, ch, 5, 100, 0, 0)
    
    #array of frequencies
    frequencies = np.arange(start, end, interval, dtype=int)
    amplitudes = [0] * len(frequencies)
    n = 0
    for i in range(start, end, interval):
        #set the frequency 
        dl.setFreq(fg_handle, ch, i)
        #autofocus the scope 
        dl.Scopeset(scope_handle)
        time.sleep(10)
        #take a measurement, calculate and store amplitude
        amplitudes[n] = dl.Ampget(scope_handle, ch) 
        n += 1
    
    #initialize graph
    graph.clear()
    graph.set_xlabel("Frequency")
    graph.set_ylabel("Amplitude")
    graph.set_title("Frequency vs. Amplitude")
    graph.plot(frequencies, amplitudes)
    canvas.draw()

#threading info for graph function
t = threading.Thread(target = Graph)
t.start()
    
def Auto():
    global scope_handle
    dl.Scopeset(scope_handle)

ctrlframe = tk.Frame(root)
ctrlframe.pack(side=tk.LEFT,anchor=tk.NW)

displayframe = tk.Frame(root)
displayframe.pack(side=tk.RIGHT, anchor=tk.NE)

terminalframe = tk.Frame(root)
terminalframe.pack(side=tk.RIGHT, anchor=tk.SE)

label_init = tk.Button(ctrlframe,text = "Initialize Devices", width=15, command = Initdevices)
label_status = tk.Label(ctrlframe,textvariable = var_status, width=15)

# will check if resource manager is generated, 
# should have 3 displays for resource man, scope, FG 

label_ch = tk.Label(ctrlframe,text = "Set Channel", width=15)
# label_C = tk.Label(ctrlframe,text = "Set Frequency", width=5)
# or should I set a range of frequencies? 
label_fstart =  tk.Label(ctrlframe,text = "Start Freq.", width=15)
label_fend =  tk.Label(ctrlframe,text = "End Freq.", width=15)
label_fint =  tk.Label(ctrlframe,text = "Intervals", width=15)
label_auto =  tk.Button(ctrlframe,text = "Autoset", width=30, command = Auto)
label_dat = tk.Button(ctrlframe,text = "Collect Data", width=30, command = Graph)
label_stop = tk.Button(ctrlframe,text = "Stop Collecting", width=30, command = EndGraph)
label_exit = tk.Button(ctrlframe,text = "Exit", width=30, command = quit)


entry_ch = tk.Entry(ctrlframe, textvariable=var_ch, width=15)
entry_fstart = tk.Entry(ctrlframe, textvariable=var_fstart, width=15)
entry_fend = tk.Entry(ctrlframe, textvariable=var_fend, width=15)
entry_fint = tk.Entry(ctrlframe, textvariable=var_fint, width=15)
#entry_dat = tk.Entry(ctrlframe, textvariable=var_dat, width=15)


label_init.grid(row=0,column=0)
label_ch.grid(row=1,column=0)
label_fstart.grid(row=2,column=0)
label_fend.grid(row=3,column=0)
label_fint.grid(row=4,column=0,pady=(10,10))
label_auto.grid(row=5,column=0,pady=(10,10))
label_dat.grid(row=6,column=0,pady=(10,10))
label_stop.grid(row=7,column=0,pady=(10,10))
label_exit.grid(row=8,column=0,pady=(10,10))


#status will change depending on if device is initialized or not
label_status.grid(row=0,column=1,padx=(0,10))
entry_ch.grid(row=1,column=1,padx=(0,10))
entry_fstart.grid(row=2,column=1,padx=(0,10))
entry_fend.grid(row=3,column=1,padx=(0,10))
entry_fint.grid(row=4,column=1,padx=(0,10))

tk.mainloop() #starts the window


