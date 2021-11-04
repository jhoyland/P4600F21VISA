# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import datalink
import tkinter as tk

from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

import numpy as np

def plot_AMP(FG, OS):
    channel, initialFreq, stepSize, finalFreq = getVariables()
    #x = float(var_x.get())
    x=np.arange(initialFreq, finalFreq, stepSize)
    y=[]
    datalink.setSinwave(FG, channel, initialFreq, 5.0, 0.0, 0.0)
    datalink.displayWave(FG, channel)  #output the signal
    #calculation
    for i in x: 
        #set freq on generator with i
        datalink.autosetScope(OS)
        datalink.setSinwave(FG, channel, i, 5.0, 0.0, 0.0)
        #get amp at i\
        amp = datalink.getAmplitude(OS,channel) 
        y.append(amp)

        #var_answer.set("{:}".format(y))    
        graph.clear()
        graph.plot(x[0:len(y)],y)
        canvas.draw()
    


def getVariables():
    channel = int(var_Channel.get())
    initialFreq = float(var_Freq.get())
    stepSize =  float(var_step.get())
    finalFreq = float(var_endFreq.get())
    return (channel, initialFreq, stepSize, finalFreq)

def init():
    RM = datalink.initRM()
    FG = datalink.initFG(RM)
    OS = datalink.initScope(RM)
    plot_AMP(FG, OS)
    


#------------------------------------------------------------------------------
root = tk.Tk()
root.wm_title("LRC")

ctrlframe = tk.Frame(root)
ctrlframe.pack(side=tk.LEFT)

label_Channel = tk.Label(ctrlframe,text="Channel (1 or 2)",width=15)
label_Freq = tk.Label(ctrlframe,text="Initial Freq (Hz)",width=15)
label_step = tk.Label(ctrlframe,text="Step size (Hz)",width=15)
label_endFreq = tk.Label(ctrlframe,text="Final Freq (Hz)",width=15)
#label_x = tk.Label(ctrlframe,text="x",width=5)

var_Channel = tk.StringVar(value="0")
var_Freq = tk.StringVar(value="0")
var_step = tk.StringVar(value="0")
var_endFreq = tk.StringVar(value="0")
var_amp = tk.StringVar(value="Get AMP")

entry_Channel = tk.Entry(ctrlframe,text="Channel",textvariable=var_Channel,width=10)
entry_Freq = tk.Entry(ctrlframe,text="Freq",textvariable=var_Freq,width=10)
entry_step = tk.Entry(ctrlframe,text="Step size",textvariable=var_step,width=10)
entry_endFreq = tk.Entry(ctrlframe,text="Final Freq",textvariable=var_endFreq,width=10)

label_Channel.grid(row=0, column=0)
label_Freq.grid(row=1, column=0)
label_step.grid(row=2, column=0)
label_endFreq.grid(row=3, column=0)

entry_Channel.grid(row=0, column=1,padx=(0,10),pady=(0,10))
entry_Freq.grid(row=1, column=1,padx=(0,10),pady=(0,10))
entry_step.grid(row=2, column=1,padx=(0,10),pady=(0,10))
entry_endFreq.grid(row=3, column=1,padx=(0,10),pady=(0,10))

#var_x = tk.DoubleVar(value=0.1)
#x_slide = tk.Scale(ctrlframe,variable=var_x,orient='horizontal',from_=0,to=1,resolution=0.1)
#x_slide.grid(row=3,column=1,padx=(0,10),pady=(10,10))

label_amp = tk.Label(ctrlframe,text="AMP",textvariable=var_amp)
label_amp.grid(row=5,column=0,columnspan=2,sticky="ew",pady=(10,10))

fig = Figure(figsize=(5,4),dpi=100)
graph = fig.add_subplot()

canvas = FigureCanvasTkAgg(fig,master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT)

x = np.arange(-10,10,0.1)

calc_button = tk.Button(ctrlframe,text="Calculate",command=init)
calc_button.grid(row=4,column=0,columnspan=2,sticky="ew")
#------------------------------------------------------------------------------

#RM, FG, OS = init()
#initialFreq = getInitialfreq()





tk.mainloop()