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

RM, FG, OS =  initialize()
getVolt(OS, 1)

root = tk.Tk()
root.wm_title("Bob")

ctrlframe = tk.Frame(root)
ctrlframe.pack(side=tk.LEFT)

label_A = tk.Label(ctrlframe,text="A",width=5)
label_B = tk.Label(ctrlframe,text="B",width=5)
label_C = tk.Label(ctrlframe,text="C",width=5)
label_x = tk.Label(ctrlframe,text="x",width=5)

var_A = tk.StringVar(value="0")
var_B = tk.StringVar(value="0")
var_C = tk.StringVar(value="0")
#var_x = tk.StringVar(value="0")
var_answer = tk.StringVar(value="Answer")

entry_A = tk.Entry(ctrlframe,text="A",textvariable=var_A,width=15)
entry_B = tk.Entry(ctrlframe,text="B",textvariable=var_B,width=15)
entry_C = tk.Entry(ctrlframe,text="C",textvariable=var_C,width=15)
#entry_x = tk.Entry(root,text="x",textvariable=var_x,width=15)

label_A.grid(row=0, column=0)
label_B.grid(row=1, column=0)
label_C.grid(row=2, column=0)
#label_x.grid(row=3, column=0,pady(10,10))

entry_A.grid(row=0, column=1,padx=(0,10),pady=(0,10))
entry_B.grid(row=1, column=1,padx=(0,10),pady=(0,10))
entry_C.grid(row=2, column=1,padx=(0,10),pady=(0,10))
#entry_x.grid(row=3, column=1,padx=(0,10),pady=(10,10))

#var_x = tk.DoubleVar(value=0.1)
#x_slide = tk.Scale(ctrlframe,variable=var_x,orient='horizontal',from_=0,to=1,resolution=0.1)
#x_slide.grid(row=3,column=1,padx=(0,10),pady=(10,10))

label_answer = tk.Label(ctrlframe,text="Answer",textvariable=var_answer)
label_answer.grid(row=5,column=0,columnspan=2,sticky="ew",pady=(10,10))

fig = Figure(figsize=(5,4),dpi=100)
graph = fig.add_subplot()

canvas = FigureCanvasTkAgg(fig,master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT)

x = np.arange(-10,10,0.1)






def calc_poly():
    A = float(var_A.get())
    B = float(var_B.get())
    C = float(var_C.get())
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


def getVolt(OS, channel):
    datalink.getScopevolts(OS, channel)

def initialize():
    RM = datalink.initRM()
    FG = datalink.initFG(RM)
    OS = datalink.initScope(RM)

    return RM, FG, OS


tk.mainloop()