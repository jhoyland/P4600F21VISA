# -*- coding: utf-8 -*-
"""
Created on Tue Oct 26 11:19:14 2021

@author: Dallas Collie
"""

import datalink as dl

import tkinter as tk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np

root = tk.Tk()
root.wm_title("Resonance Frequency App")

ctrlframe = tk.Frame(root)
ctrlframe.pack(side=tk.LEFT, anchor = tk.NW)

label_ENTER_FREQ = tk.Label(ctrlframe, text="ENTER FREQUENCIES", width = 20)
label_FROM = tk.Label(ctrlframe, text="FROM:", width = 5)
label_TO = tk.Label(ctrlframe, text="TO:", width = 5)
label_STEP = tk.Label(ctrlframe, text="STEP SIZE:", width = 10)

var_FROM = tk.StringVar(value="18000")
var_TO = tk.StringVar(value="25000")
var_STEP = tk.StringVar(value="1000")

entry_FROM = tk.Entry(ctrlframe, textvariable=var_FROM, width = 15)
entry_TO = tk.Entry(ctrlframe, textvariable=var_TO, width = 15)
entry_STEP= tk.Entry(ctrlframe, textvariable=var_STEP, width = 15)

label_ENTER_FREQ.grid(row=0, column=0)
label_FROM.grid(row=1, column=0)
label_TO.grid(row=2, column=0)
label_STEP.grid(row=3, column=0)

entry_FROM.grid(row=1, column=1, padx=(0,10))
entry_TO.grid(row=2, column=1, padx=(0,10))
entry_STEP.grid(row=3, column=1, padx=(0,10))

fig = Figure(figsize=(5,4),dpi=100)
graph = fig.add_subplot()
graph.set_title("Resonance Frequency")
graph.set_ylabel('Amplitude')
graph.set_xlabel('Frequencies')

canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT)

def graph_reset():
    graph.clear()
    graph.set_title("Resonance Frequency")
    graph.set_ylabel('Amplitude')
    graph.set_xlabel('Frequencies')
    
def neg_error():
    var_answer = tk.StringVar(value="NO NEGATIVES")
    label_answer = tk.Label(ctrlframe, textvariable=var_answer)
    label_answer.grid(row=6, column=0, columnspan=2, sticky="ew",pady=(10,10))

def range_reversed():
    var_answer = tk.StringVar(value="RANGE REVERSED")
    label_answer = tk.Label(ctrlframe, textvariable=var_answer)
    label_answer.grid(row=6, column=0, columnspan=2, sticky="ew",pady=(10,10))

def range_exceeded():
    var_answer = tk.StringVar(value="RANGE 1 uHz - 60 MHz")
    label_answer = tk.Label(ctrlframe, textvariable=var_answer)
    label_answer.grid(row=6, column=0, columnspan=2, sticky="ew",pady=(10,10))
    
def message_reset():
    var_answer = tk.StringVar(value=" ")
    label_answer = tk.Label(ctrlframe, textvariable=var_answer)
    label_answer.grid(row=6, column=0, columnspan=2, sticky="ew",pady=(10,10))

def aquire_data():
    message_reset()
    graph_reset()
    canvas.draw()
    freq_from = float(var_FROM.get())
    freq_to = float(var_TO.get())
    freq_step = float(var_STEP.get())
    if freq_from <0 or freq_to < 0 or freq_step <0:
        neg_error()
    elif freq_from > freq_to:
        range_reversed()
    elif freq_from > 60e+06 or freq_to < 1e-06:
        range_exceeded()
    else:
        frequencies = np.arange(freq_from,freq_to,freq_step)
        amplitudes = np.zeros(len(frequencies))
        status, scope, funcGen = dl.openInstruments()
    
        for i,f in enumerate(frequencies):
            amplitudes[i] = dl.getAmplitude(f, scope, funcGen)
            print(f, amplitudes[i])
            
        graph_reset()
        graph.plot(frequencies, amplitudes, lw=2)
        canvas.draw()
        
    

calc_button = tk.Button(ctrlframe, text = "AQUIRE DATA", command=aquire_data)
calc_button.grid(row=5, column=0, columnspan=2, sticky="ew")


tk.mainloop()

