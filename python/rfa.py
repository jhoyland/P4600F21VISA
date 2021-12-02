# -*- coding: utf-8 -*-
"""
Created on Tue Oct 26 11:19:14 2021

@author: Dallas Collie
"""

import datalink as dl                        #imports C library
import tkinter as tk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np
import time
import threading          



root = tk.Tk()
root.wm_title("Resonance Frequency App")

ctrlframe = tk.Frame(root)
ctrlframe.pack(side=tk.LEFT, anchor = tk.NW)

#create labels
label_ENTER_FREQ = tk.Label(ctrlframe, text="ENTER FREQUENCIES", width = 20)
label_FROM = tk.Label(ctrlframe, text="FROM:", width = 5)
label_TO = tk.Label(ctrlframe, text="TO:", width = 5)
label_STEP = tk.Label(ctrlframe, text="STEP SIZE:", width = 10)

#position labels
label_ENTER_FREQ.grid(row=0, column=0)
label_FROM.grid(row=1, column=0)
label_TO.grid(row=2, column=0)
label_STEP.grid(row=3, column=0)

#create variables for default frequencies
var_FROM = tk.StringVar(value="23000")
var_TO = tk.StringVar(value="25000")
var_STEP = tk.StringVar(value="1000")

var_answer = tk.StringVar(value=" ")

#create entry boxes to capture user entry
entry_FROM = tk.Entry(ctrlframe, textvariable=var_FROM, width = 15)
entry_TO = tk.Entry(ctrlframe, textvariable=var_TO, width = 15)
entry_STEP= tk.Entry(ctrlframe, textvariable=var_STEP, width = 15)

#position entry boxes
entry_FROM.grid(row=1, column=1, padx=(0,10))
entry_TO.grid(row=2, column=1, padx=(0,10))
entry_STEP.grid(row=3, column=1, padx=(0,10))

#set up the graph
fig = Figure(figsize=(5,4),dpi=100)
graph = fig.add_subplot()
graph.set_title("Resonance Frequency")
graph.set_ylabel('Amplitude')
graph.set_xlabel('Frequencies')

canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT)

stopAquireEvent = threading.Event()             #creating a threading event for stopping aquiring data

def graph_reset():                              #resets the graph and relabels
    graph.clear()
    graph.set_title("Resonance Frequency")
    graph.set_ylabel('Amplitude')
    graph.set_xlabel('Frequencies')

def start_aquire():                             #start aquiring data        
    stopAquireEvent.clear()                     #clear the stopAquire event 
    t = threading.Thread(target = aquire_data)  #opens a new thread
    t.start()                                   #starts new thread
    
def stop_aquire():                              #stop aquiring data
    stopAquireEvent.set()                       #sets the stop aquire event
    
       
def aquire_data():
    var_answer.set(" ")                                         #clear any messages shown to user
    graph_reset()                                               #reset the graph
    canvas.draw_idle()                                          #draw an empty graph
    freq_from = float(var_FROM.get())                           #get the frequncy the user input
    freq_to = float(var_TO.get())                               #get the frequncy the user input
    freq_step = float(var_STEP.get())                           ##get the step frequncy the user input
    if freq_from <0 or freq_to < 0 or freq_step <0:             #error message for negative number entry
        var_answer.set("NO NEGATIVES")
    elif freq_from > freq_to:                                   #error message for inputting from and to number reversed
        var_answer.set("RANGE REVERSED")
    elif freq_from > 60e+06 or freq_to < 1e-06:                 #error message for outside of the frequency range of FG
        var_answer.set("RANGE 1 uHz - 60 MHz")
    else:
        frequencies = np.arange(freq_from,freq_to,freq_step)    #creates an array of frequencies using user input
        amplitudes = np.zeros(len(frequencies))                 #create an array the same size as the func array. 
        status, scope, funcGen = dl.openInstruments()           #connect to the oscilloscope and function gen. 
    
        for i,f in enumerate(frequencies):                      #loop to go through different freq and find the amplitude
            if stopAquireEvent.is_set():                        #if the tread detects a stop, break out of the loop
                break
            var_answer.set("AQUIRING DATA")                     #show status to user
            amplitudes[i] = dl.getAmplitude(f, scope, funcGen)  #get the amplitude associate with that this frequency
            time.sleep(0.25)                                    #small delay in case the 
        var_answer.set("DATA AQUIRE HAS FINISHED")              #show status to user
        graph_reset()                                           #resets graph
        graph.plot(frequencies, amplitudes, lw=2)               #makes plots with the data in freq. and ampl.
        canvas.draw_idle()                                      #draws the plots
           

calc_button = tk.Button(ctrlframe, text = "AQUIRE DATA", command=start_aquire)  #creates button for aquiring data
calc_button.grid(row=5, column=0, columnspan=2, sticky="ew")

stop_button = tk.Button(ctrlframe, text = "STOP", command=stop_aquire)          #creats a button for stop aquiring data
stop_button.grid(row=6, column=0, columnspan=2, sticky="ew")

label_answer = tk.Label(ctrlframe, textvariable=var_answer)                     #label for error warnings and status
label_answer.grid(row=9, column=0, columnspan=2, sticky="ew",pady=(10,10))


tk.mainloop()

