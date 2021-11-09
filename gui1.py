# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import numpy as np
import tkinter as tk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

x=np.arange(-13,13,0.05)


root = tk.Tk()

control_frame= tk.Frame(root)
control_frame.pack(side=tk.LEFT)
root.wm_title("LCR Frequency Sweep")

A_label = tk.Label(control_frame,text="A")
B_label = tk.Label(control_frame,text="B")
C_label = tk.Label(control_frame,text="C")
#X_label = tk.Label(control_frame,text="X")


A_var = tk.StringVar(value="0")
B_var = tk.StringVar(value="0")
C_var = tk.StringVar(value="0")
#X_var = tk.StringVar(value="0")
Answer_var = tk.StringVar(value="Answer")

A_entry = tk.Entry(control_frame,textvariable=A_var)
B_entry = tk.Entry(control_frame,textvariable=B_var)
C_entry = tk.Entry(control_frame,textvariable=C_var)
#X_entry = tk.Entry(root,textvariable=X_var)

A_label.grid(row=0,column=0,padx=(10,10),pady=(10,5))
A_entry.grid(row=0,column=1,padx=(10,10),pady=(10,5))
B_label.grid(row=1,column=0,padx=(10,10),pady=(5,5))
B_entry.grid(row=1,column=1,padx=(10,10),pady=(5,5))
C_label.grid(row=2,column=0,padx=(10,10),pady=(5,5))
C_entry.grid(row=2,column=1,padx=(10,10),pady=(5,5))
#X_label.grid(row=3,column=0,padx=(10,10),pady=(5,10))
#X_entry.grid(row=3,column=1,padx=(10,10),pady=(5,10))
#X_var=tk.DoubleVar(value=0)
#X_slide=tk.Scale(control_frame,variable=X_var,orient='horizontal',from_=0,to=10,resolution=0.05)
#X_slide.grid(row=3,column=1,padx=(10,10),pady=(5,5))


fig= Figure(figsize=(5,4),dpi=111)
graph = fig.add_subplot()

canvas = FigureCanvasTkAgg(fig,master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT)

def calc_poly():
    A = float(A_var.get())
    B = float(B_var.get())
    C = float(C_var.get())
    #X = float(X_var.get())
    y=A*x*x+B*x+C
    Answer_var.set("{:}".format(y))
    graph.clear()
    graph.plot(x,y)
    canvas.draw()

def calc_slider(a,b,c):
    calc_poly()

Calc_button=tk.Button(control_frame,text="Calculate",command=calc_poly)
Calc_button.grid(row=4,column=0,columnspan=2,sticky="ews")

Quit_button=tk.Button(control_frame,text="Quit",command=quit)
Quit_button.grid(row=6,column=0,columnspan=2,sticky="ews",pady=(20,5))



Answer_label = tk.Label(control_frame,textvariable=Answer_var)
Answer_label.grid(row=5,column=0,columnspan=2,sticky="ews")

#X_var.trace('w',calc_slider)

tk.mainloop()