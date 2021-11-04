# -*- coding: utf-8 -*-
"""
Created on Tue Oct 26 11:19:14 2021

@author: texas
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


label_ENTER_RANGE = tk.Label(ctrlframe, text="ENTER FREQUENCIES", width = 20)
label_FROM = tk.Label(ctrlframe, text="FROM:", width = 5)
label_TO = tk.Label(ctrlframe, text="TO:", width = 5)
label_STEP = tk.Label(ctrlframe, text="STEP SIZE:", width = 10)


var_FROM = tk.StringVar(value="0")
var_TO = tk.StringVar(value="0")
var_STEP = tk.StringVar(value="0.1")

entry_FROM = tk.Entry(ctrlframe, textvariable=var_FROM, width = 15)
entry_TO = tk.Entry(ctrlframe, textvariable=var_TO, width = 15)
entry_STEP= tk.Entry(ctrlframe, textvariable=var_STEP, width = 15)

label_ENTER_RANGE.grid(row=0, column=0)
label_FROM.grid(row=1, column=0)
label_TO.grid(row=2, column=0)
label_STEP.grid(row=3, column=0)

entry_FROM.grid(row=1, column=1, padx=(0,10))
entry_TO.grid(row=2, column=1, padx=(0,10))
entry_STEP.grid(row=3, column=1, padx=(0,10))

freq_from = float(var_FROM.get())
freq_to = float(var_TO.get())
freq_step = float(var_STEP.get())


fig = Figure(figsize=(5,4),dpi=100)
graph = fig.add_subplot()
graph.set_title("Resonance Frequency")
graph.set_ylabel('Amplitude')
graph.set_xlabel('Frequencies')

canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT)

#scope, funcGen = dl.openInstruments()

frequencies = np.arange(freq_from,freq_to,freq_step)

def aquire_data():
    var_answer = tk.StringVar(value="AQUIRING DATA")
    label_answer = tk.Label(ctrlframe, textvariable=var_answer)
    label_answer.grid(row=5, column=0, columnspan=2, sticky="ew",pady=(10,10))
    
    #amplitudes = dl.getAmplitude(frequencies, scope, funcGen)
    #graph.plot(frequencies, amplitudes, lw=2)

calc_button = tk.Button(ctrlframe, text = "AQUIRE DATA", command=aquire_data())
calc_button.grid(row=4, column=0, columnspan=2, sticky="ew")


tk.mainloop()

