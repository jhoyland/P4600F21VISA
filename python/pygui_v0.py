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
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

root = tk.Tk() #creates root main window but does not start it 
root.wm_title("Scope/FG Control")

scope_handle
fg_handle

# function to gen resource man, init scope and fg
var_ch = tk.StringVar(value="1")

def Initdevices():
    ch = float(var_ch.get())
    resource_manager = dl.resourceCreate()
    #if resource manager runs fine, complete scope and FG inits
    global scope_handle
    scope_handle = dl.initScope(resource_manager)
    global fg_handle
    fg_handle = dl.initFG(resource_manager)
    # set channels for both devices 
    dl.initCH(fg_handle, ch)
    dl.setSinWave(fg_handle)
    #dl.Scopeset()


var_fstart = tk.StringVar(value="0")
var_fend = tk.StringVar(value="0")
var_fint = tk.StringVar(value="0")

def CollectData():
    global fg_handle
    start = float(var_fstart.get())
    end = float(var_fend.get())
    interval = float(var_fint.get())
    ch = float(var_ch.get())
    
    # set amp, offset, etc, to zero 
    dl.setSinWave(fg_handle, ch, 0, 100, 0, 0)
    
    #array of frequencies
    frequencies = np.arange(start, end, interval, dtype=float)
    amplitudes = [0] * len(frequencies)
    
    for i in range(start, end, interval):
        #set the frequency 
        dl.setFreq(fg_handle, ch, i)
        #:SOUR1:FREQ 100
        #take a measurement
        #calculate amplitude
        #store amplitude 
    
    return frequencies, amplitudes
    

def DataGen():
    print("DataGen will generate the graph of freq vs amp")
# we want the control frame to have buttons to: 
# Generate Resource manager and display Y/N in an uneditable box.
# Initialize scope and FG 
# set the channel (default to ch1?)
# Set the Frequency
# Autofocus the scope 
# collect and display sin data which includes:
# List of RMS, Average, Amplitude, Frequency vs. Amp Graph 

ctrlframe = tk.Frame(root)
ctrlframe.pack(side=tk.LEFT,anchor=tk.NW)

displayframe = tk.Frame(root)
displayframe.pack(side=tk.RIGHT, anchor=tk.NE)

terminalframe = tk.Frame(root)
terminalframe.pack(side=tk.RIGHT, anchor=tk.SE)

label_init = tk.Label(ctrlframe,text = "Initialize Devices", width=5)
# will check if resource manager is generated, 
# should have 3 displays for resource man, scope, FG 

label_ch = tk.Label(ctrlframe,text = "Set Channel", width=5)
# label_C = tk.Label(ctrlframe,text = "Set Frequency", width=5)
# or should I set a range of frequencies? 
label_fstart =  tk.Label(ctrlframe,text = "Start Freq.", width=5)
label_fend =  tk.Label(ctrlframe,text = "End Freq.", width=5)
label_fint =  tk.Label(ctrlframe,text = "Intervals", width=5)
label_af = tk.Label(ctrlframe,text = "Autofocus Scope", width=5)
label_dat = tk.Button(ctrlframe,text = "Display Data", width=5, command = DataGen)

entry_ch = tk.Entry(ctrlframe, textvariable=var_ch, width=15)
entry_fstart = tk.Entry(ctrlframe, textvariable=var_fstart, width=15)
entry_fend = tk.Entry(ctrlframe, textvariable=var_fend, width=15)
entry_fint = tk.Entry(ctrlframe, textvariable=var_fint, width=15)
entry_af = tk.Entry(ctrlframe, textvariable=var_af, width=15)
entry_dat = tk.Entry(ctrlframe, textvariable=var_dat, width=15)


label_ch.grid(row=0,column=0)
label_fstart.grid(row=1,column=0)
label_fend.grid(row=2,column=0)
label_fint.grid(row=3,column=0,pady=(10,10))
label_af.grid(row=3,column=0,pady=(10,10))
label_dat.grid(row=3,column=0,pady=(10,10))


entry_ch.grid(row=0,column=1,padx=(0,10))
entry_fstart.grid(row=1,column=1,padx=(0,10))
entry_fend.grid(row=2,column=1,padx=(0,10))
entry_fint.grid(row=3,column=1,padx=(0,10))
entry_af.grid(row=4,column=1,padx=(0,10))
entry_dat.grid(row=5,column=1,padx=(0,10))


# if var_init = 1 then devices have been successfully initialized.

#var_fstart = tk.StringVar(value="0")
#var_Cs = tk.StringVar(value="0")
#var_Ce = tk.StringVar(value="0")
#var_Ci = tk.StringVar(value="0")
#var_D = tk.StringVar(value="0")


    #this function should generate:
    #List of RMS, Average, Amplitude, and a Frequency vs. Amp Graph

tk.mainloop() #starts the window


