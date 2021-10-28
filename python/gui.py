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

RM, FG, OS = initialize()
#initialFreq = getInitialfreq()


root = tk.Tk()
root.wm_title("Bob")

ctrlframe = tk.Frame(root)
ctrlframe.pack(side=tk.LEFT)

label_Channel = tk.Label(ctrlframe,text="Channel",width=10)
label_Freq = tk.Label(ctrlframe,text="Initial Freq",width=10)
label_endFreq = tk.Label(ctrlframe,text="Final Freq",width=10)
label_x = tk.Label(ctrlframe,text="x",width=5)

var_Channel = tk.StringVar(value="0")
var_Freq = tk.StringVar(value="0")
var_endFreq = tk.StringVar(value="0")
#var_x = tk.StringVar(value="0")
var_amp = tk.StringVar(value="AMP")





entry_Channel = tk.Entry(ctrlframe,text="Channel",textvariable=var_Channel,width=5)
entry_Freq = tk.Entry(ctrlframe,text="Freq",textvariable=var_Freq,width=5)
entry_endFreq = tk.Entry(ctrlframe,text="Final Freq",textvariable=var_endFreq,width=5)
#entry_x = tk.Entry(root,text="x",textvariable=var_x,width=15)

label_Channel.grid(row=0, column=0)
label_Freq.grid(row=1, column=0)
label_endFreq.grid(row=2, column=0)
#label_x.grid(row=3, column=0,pady(10,10))

entry_Channel.grid(row=0, column=1,padx=(0,10),pady=(0,10))
entry_Freq.grid(row=1, column=1,padx=(0,10),pady=(0,10))
entry_endFreq.grid(row=2, column=1,padx=(0,10),pady=(0,10))
#entry_x.grid(row=3, column=1,padx=(0,10),pady=(10,10))

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






def calc_poly():
    A = float(var_Channel.get())
    B = float(var_Freq.get())
    C = float(var_endFreq.get())
    #x = float(var_x.get())
    #calculation
    y = A*x*x+B*x+C
    #var_answer.set("{:}".format(y))    
    graph.clear()
    graph.plot(x,y)
    canvas.draw()
    
def calc_slider(a,b,c):
    calc_poly()
    
calc_button = tk.Button(ctrlframe,text="Calculate",command=calc_poly)
calc_button.grid(row=4,column=0,columnspan=2,sticky="ew")

#var_x.trace('w',calc_slider)


def getInitialfreq():
    freq = float(var_Freq.get())
    return freq

def initialize():
    RM = datalink.initRM()
    FG = datalink.initFG(RM)
    OS = datalink.initScope(RM)

    return (RM, FG, OS)

def getAMP():
    #do something
    
    return 0

tk.mainloop()