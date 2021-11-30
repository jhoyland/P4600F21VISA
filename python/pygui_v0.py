# -*- coding: utf-8 -*-
"""
Created on Tue Oct 26 09:39:42 2021
Test out functions in python
@author: EPsajd
"""
# REMEMBER: in dll file make swig and make dll 

import datalink as dl 
import tkinter as tk
import numpy as np
import time
import threading
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

root = tk.Tk() #creates root main window but does not start it 
root.wm_title("Scope/FG Control")

scope_handle = 0
fg_handle = 0
# function to gen resource man, init scope and fg
var_ch = tk.StringVar(value="1")
#status for initialization of devices
var_status = tk.StringVar(value="Not Connected")



"""
fig= Figure(figsize=(5,4),dpi=100)

graph= fig.add_subplot()
graph.set_xlabel("Frequency")
graph.set_ylabel("Amplitude")
graph.set_title("Frequency vs. Amplitude")

canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT)
"""

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
var_fint = tk.StringVar(value="10")
var_dat = tk.StringVar(value="0")

StopData = threading.Event()
StopGraph = threading.Event()
NewData = threading.Event()

frequencies = np.arange(0,100,1, dtype = int)
amplitudes = [0] * len(frequencies)

def GraphData():
    global fg_handle
    global scope_handle
    global StopData
    global frequencies
    global amplitudes
    start = int(var_fstart.get())
    end = int(var_fend.get())
    interval = int(var_fint.get())
    ch = int(var_ch.get())
    #clear stop
    StopData.clear()
    # set amp, offset, etc, to zero 
    dl.setSinWave(fg_handle, ch, 5, 100, 0, 0)
    
    #array of frequencies

    frequencies = np.arange(start, end, interval, dtype=int)
    amplitudes = [0] * len(frequencies)
    NewData.set()
    n = 0
    for i in range(start, end, interval):
        if (StopData.is_set()):
            break
        else:
            #set the frequency 
            dl.setFreq(fg_handle, ch, i)
            #autofocus the scope 
            dl.Scopeset(scope_handle)
            time.sleep(10)
            #take a measurement, calculate and store amplitude
            a = dl.Ampget(scope_handle, ch) 
            print(a)
            
            amplitudes[n] = a
            
            n += 1
            NewData.set()
        
    print("Loop Ended!")
    print(frequencies,amplitudes)

#create a function to call new thread for graph only 
#this thread will start running immediatly and then 
#update when neeeded
def Graph():
    global frequencies
    global amplitudes
    fig= Figure(figsize=(5,4),dpi=100)

     
    graph= fig.add_subplot()
    graph.set_xlabel("Frequency")
    graph.set_ylabel("Amplitude")
    graph.set_title("Frequency vs. Amplitude")

    canvas = FigureCanvasTkAgg(fig, master=root)
    canvas.get_tk_widget().pack(side=tk.RIGHT)
    #get frequencies and amplitudes to continuously update 
    while not StopGraph.is_set():
        if NewData.is_set():
            graph.clear()
            graph.set_xlabel("Frequency")
            graph.set_ylabel("Amplitude")
            graph.set_title("Frequency vs. Amplitude")
            graph.plot(frequencies, amplitudes)
            canvas.draw_idle()
            NewData.clear()

def SaveGraph():
    global frequencies 
    global amplitudes
    plt.plot(frequencies, amplitudes, color = 'blue', marker = 'o', linestyle = 'solid')
    plt.xlabel("Frequency")
    plt.ylabel("Amplitude")
    plt.title("Frequency Vs. Amplitude")
    plt.savefig('FvsA.png')
    
    file = open('Data.dat', 'w')
    file.write("Frequencies")
    file.write('\t')
    file.write("Amplitudes")
    file.write('\n')
    for i in range(0,len(frequencies),1):
            file.write(str(frequencies[i]))
            file.write('\t')
            file.write(str(amplitudes[i]))
            file.write('\n')
    file.close()
    
def SaveSettings():
    start = str(var_fstart.get())
    end = str(var_fend.get())
    interval = str(var_fint.get())
    ch = str(var_ch.get())
    file = open('Settings.dat','w')
    file.write(start)
    file.write("\n")
    file.write(end)
    file.write("\n")
    file.write(interval)
    file.write("\n")
    file.write(ch)
    file.close()
    
def LoadSettings():
    global var_fstart 
    global var_fend 
    global var_fint 
    global var_ch
    try:
        file = open('Settings.dat','r')
    except: 
        print("No Save File Exists")
    else:
        var_fstart.set(int(file.readline()))
        var_fend.set(int(file.readline()))
        var_fint.set(int(file.readline()))
        var_ch.set(int(file.readline()))
        file.close()
    

def StartGraph():
    global t1
    t1 = threading.Thread(target=Graph)
    t1.start()
    
def StopGraphfunc():
    global t1
    global StopGraph
    StopGraph.set() 

def Datathread(): 
    global t
    t = threading.Thread(target = GraphData)
    t.start()

def StopFunc(): 
    global t
    global StopData
    StopData.set() 
    
def Auto():
    global scope_handle
    dl.Scopeset(scope_handle)

StartGraph()

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
label_dat = tk.Button(ctrlframe,text = "Collect Data", width=30, command = Datathread)
label_stop = tk.Button(ctrlframe,text = "Stop Collecting", width=30, command = StopFunc)
label_save = tk.Button(ctrlframe,text = "Save Settings", width=30, command = SaveSettings)
label_load = tk.Button(ctrlframe,text = "Load Settings", width=30, command = LoadSettings)
label_savedata = tk.Button(ctrlframe,text = "Save Graph/Data", width=30, command = SaveGraph)
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
label_fint.grid(row=4,column=0)
label_auto.grid(row=5,column=0,pady=(10,0))
label_dat.grid(row=6,column=0)
label_stop.grid(row=7,column=0)
label_save.grid(row=8,column=0)
label_load.grid(row=9,column=0)
label_savedata.grid(row=10,column=0)
label_exit.grid(row=11,column=0)


#status will change depending on if device is initialized or not
label_status.grid(row=0,column=1,padx=(0,10))
entry_ch.grid(row=1,column=1,padx=(0,10))
entry_fstart.grid(row=2,column=1,padx=(0,10))
entry_fend.grid(row=3,column=1,padx=(0,10))
entry_fint.grid(row=4,column=1,padx=(0,10))

tk.mainloop() #starts the window


