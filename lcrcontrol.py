# -*- coding: utf-8 -*-
"""
Created on Tue Oct 19 09:15:28 2021

@author: BMcClennon
"""

import tkinter as tk

from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np



root = tk.Tk()

root.wm_title("Main Window")

control_frame = tk.Frame(root)
control_frame.pack(side=tk.LEFT)

label_a = tk.Label(control_frame, text="A", width=5)
label_b = tk.Label(control_frame, text="B", width=5)
label_c = tk.Label(control_frame, text="C", width=5)
#label_x = tk.Label(control_frame, text="x", width=5)

var_a = tk.StringVar(value="0")
var_b = tk.StringVar(value="0")
var_c = tk.StringVar(value="0")
#var_x = tk.StringVar(value="0")

entry_a = tk.Entry(control_frame, textvariable=var_a, width=15)
entry_b = tk.Entry(control_frame, textvariable=var_b, width=15)
entry_c = tk.Entry(control_frame, textvariable=var_c, width=15)
#entry_x = tk.Entry(control_frame, textvariable=var_x, width=15)

#var_x = tk.DoubleVar(value=0.1)
#x_slide = tk.Scale(control_frame, variable=var_x, orient='horizontal', from_=0,to=5, resolution=0.1)
#x_slide.grid(row=3, column=1, padx=(0,10))

label_a.grid(row=0, column=0, padx=(0,10))
label_b.grid(row=1, column=0, padx=(0,10))
label_c.grid(row=2, column=0, padx=(0,10))
#label_x.grid(row=3, column=0, padx=(0,10))

entry_a.grid(row=0, column=1, padx=(0,10))
entry_b.grid(row=1, column=1, padx=(0,10))
entry_c.grid(row=2, column=1, padx=(0,10))
#entry_x.grid(row=3, column=1, padx=(0,10))

fig = Figure(figsize = (5,4), dpi = 100)
graph = fig.add_subplot()

canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT)

x = np.arange(-10, 10, 0.1)

def calc_poly():
    a = float(var_a.get())
    b = float(var_b.get())
    c = float(var_c.get())
#    x = float(var_x.get())
    
    y = a * x**2 + b * x + c
#    var_ans.set("{:}".format(y))
    graph.clear()
    graph.plot(x,y)
    canvas.draw()
        
    
def calc_slider(a, b, c):
    calc_poly()
    
    
calc_button = tk.Button(control_frame, text="Calculate", command=calc_poly)
calc_button.grid(row=4, column=0, columnspan=2, sticky="ew", padx=(0,10), pady=(3,3))

label_answer = tk.Label(control_frame, text="Answer", width=15)
label_answer.grid(row=5, column=0, sticky="ew", padx=(0,10), pady=(3,3))

var_ans = tk.StringVar(value="0")
entry_answer = tk.Entry(control_frame, textvariable=var_ans, width=5)
entry_answer.grid(row=5, column=1, columnspan=1,sticky="ew", padx=(10,10), pady=(3,3))

quitbutton = tk.Button(control_frame, text="Quit", fg="red", command = root.destroy)
quitbutton.grid(row=7, column=0, columnspan=2,sticky="ew", padx=(10,10), pady=(3,3))

#var_x.trace('w', calc_slider)

tk.mainloop()
