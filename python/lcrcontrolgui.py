# -*- coding: utf-8 -*-
"""
Created on Tue Oct 19 09:15:28 2021

@author: BMcClennon
"""

import tkinter as tk

from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import numpy as np
import lcrcontrol as lcr
import threading


fig = Figure(figsize = (5,4), dpi = 100)
graph = fig.add_subplot()
endThread = threading.Event()

stop_var = 0
start_var = 0
start = 0.0
stop = 0.0
incr = 0.0
amp = 0.0
offset = 0.0
phase = 0.0

def stop_button_func():
    endThread.set()
    
def runProg():
    global thread, start_var, start, stop, incr, amp, offset, phase
    while(1):
        frequencies = np.arange(start, stop, incr)
        ampData = []
        
        for freq in frequencies:
            if endThread.is_set():
                return
            ampvalue = 0.0
            ampvalue = lcr.theController(freq, amp, offset, phase)
            ampData.append(ampvalue)
            
            x = frequencies[0:len(ampData)]
            y = ampData
            graph.clear()
            graph.plot(x,y)
                     
def run():    
    endThread.clear()
    thread = threading.Thread(target = runProg, args=())
    thread.start()
        


root = tk.Tk()

root.wm_title("Main Window")

control_frame = tk.Frame(root)
control_frame.pack(side=tk.LEFT)
label_func = tk.Label(control_frame, text="Function Generator Controls")
#label_func_ch = tk.Label(control_frame, text="Channel", width=15)
label_start_freq = tk.Label(control_frame, text="Start Frequency", width=15)
label_end_freq = tk.Label(control_frame, text="End Frequency", width=15)
label_incr_freq = tk.Label(control_frame, text="Frequency Increment", width=15)
label_amp = tk.Label(control_frame, text="Voltage Amplitude", width=15)
label_offset = tk.Label(control_frame, text="Voltage Offset", width=15)
label_phase = tk.Label(control_frame, text="Voltage Phase", width=15)

#var_func_ch = tk.StringVar(value="0")
#var_ch1 = tk.StringVar(value = "1")
#var_ch2 = tk.StringVar(value = "2")
var_start_freq = tk.StringVar(value="50.0")
var_end_freq = tk.StringVar(value="250.0")
var_incr_freq = tk.StringVar(value="50.0")
var_amp = tk.StringVar(value="1.0")
var_offset = tk.StringVar(value="0.0")
var_phase = tk.StringVar(value="0.0")

#radbutton_ch1 = tk.Radiobutton(control_frame, text = "1", variable = var_ch1, value = 1)
#radbutton_ch2 = tk.Radiobutton(control_frame, text = "2", variable = var_ch1, value = 2)
entry_start_freq = tk.Entry(control_frame, textvariable=var_start_freq, width=15)
entry_end_freq = tk.Entry(control_frame, textvariable=var_end_freq, width=15)
entry_incr_freq = tk.Entry(control_frame, textvariable=var_incr_freq, width=15)
entry_amp = tk.Entry(control_frame, textvariable=var_amp, width=15)
entry_offset = tk.Entry(control_frame, textvariable=var_offset, width=15)
entry_phase = tk.Entry(control_frame, textvariable=var_phase, width=15)


label_freq_min = tk.Label(control_frame, text="50Hz - 25MHz", width=15)
label_freq_max = tk.Label(control_frame, text="50Hz - 25MHz", width=15)
label_volt_max_min = tk.Label(control_frame, text="0.0 - 5.0")
label_volt_offset = tk.Label(control_frame, text="0.0 - 2.5")
label_volt_phase = tk.Label(control_frame, text="0.0 - 360")

label_func.grid(row=0, columnspan = 3, column=0)
#label_func_ch.grid(row=1, rowspan = 2, column=0, padx=(0,10))
label_start_freq.grid(row=3, column=0, padx=(0,10))
label_end_freq.grid(row=4, column=0, padx=(0,10))
label_incr_freq.grid(row=5, column=0, padx=(0,10))
label_amp.grid(row=6, column=0, padx=(0,10))
label_offset.grid(row=7, column=0, padx=(0,10))
label_phase.grid(row=8, column=0, padx=(0,10))

#radbutton_ch1.grid(row=1, column=1, padx=(0,10))
#radbutton_ch2.grid(row=2, column=1, padx=(0,10))
entry_start_freq.grid(row=3, column=1, padx=(0,10))
entry_end_freq.grid(row=4, column=1, padx=(0,10))
entry_incr_freq.grid(row=5, column=1, padx=(0,10))
entry_amp.grid(row=6, column=1, padx=(0,10))
entry_offset.grid(row=7, column=1, padx=(0,10))
entry_phase.grid(row=8, column=1, padx=(0,10))

label_freq_min.grid(row=3, column=2, padx=(0,10))
label_freq_max.grid(row=4, column=2, padx=(0,10))
label_volt_max_min.grid(row=6, column=2, padx=(0,10))
label_volt_offset.grid(row=7, column=2, padx=(0,10))
label_volt_phase.grid(row=8, column=2, padx=(0,10))


canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT)

stop_var = 0
start_var = 0
start = float(var_start_freq.get())
stop = float(var_end_freq.get())
incr = float(var_incr_freq.get())
amp = float(var_amp.get())
offset = float(var_offset.get())
phase = float(var_phase.get())


calc_button = tk.Button(control_frame, text="Run", width=20, command = run)
calc_button.grid(row=10, column=0, columnspan=3, pady=(3,3))

stop_button = tk.Button(control_frame, text="Stop", width=20, command = stop_button_func)
stop_button.grid(row=11, column=0, columnspan=3, pady=(3,3))

quit_button = tk.Button(control_frame, text="Quit", width=20, fg="red", command = root.destroy)
quit_button.grid(row=12, column=0, columnspan=3, pady=(3,3))

tk.mainloop()
