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
import time
import pandas as pd
from datetime import datetime




root = tk.Tk()

root.wm_title("Main Window")

freq_range = [50.0, 25.0e6]
amp_range = [0.0, 5.0]
offset_range = [-2.5, 2.5]
phase_range = [0.0, 360.0]

error_code = 0.0
start = 0.0
stop = 0.0
incr = 0.0
amp = 0.0
offset = 0.0
phase = 0.0

endCalcThread = threading.Event()
endGraphThread = threading.Event()
closeProgram = threading.Event()
paramlock = threading.Lock()
graphlock = threading.Lock()
graphlock.acquire()

fig = Figure(figsize = (5,4), dpi = 100)
graph = fig.add_subplot()
graph.set_ylabel('Amplitude (Volts)')
graph.set_xlabel('Frequency (Hz)')
graph.set_title('Amplitude data')
canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT)

xAxis = []
yAxis = []
df = pd.DataFrame(columns=['Frequency', 'Amplitude'])

def check_parameters():
    global start, stop, incr, amp, offset, phase, error_code
    
    if start > freq_range[1] or start < freq_range[0]:
        print(start)
        endCalcThread.set()
        error_code = 1
    if stop > freq_range[1] or stop < freq_range[0]:
        print(stop)
        endCalcThread.set()
        error_code = 2
    if incr > abs(stop - start) or incr <= 0.0:
        print(incr)
        print((stop - start))
        endCalcThread.set() 
        error_code = 3
    if amp > amp_range[1] or amp < amp_range[0]:
        print(amp)
        endCalcThread.set()   
        error_code = 4
    if offset > offset_range[1] or offset < offset_range[0]:
        print(offset)
        endCalcThread.set() 
        error_code = 5
    if phase > phase_range[1] or phase < phase_range[0]:
        print(phase)
        endCalcThread.set() 
        error_code = 6
    if endCalcThread.is_set():
        print(error_code)


def stop_button_func():
    endCalcThread.set()
    
    
def switchButtonState():
    if (save_param_button['state'] == tk.NORMAL):
        save_param_button['state'] = tk.DISABLED
    else:
        save_param_button['state'] = tk.NORMAL
        
    if (save_data_button['state'] == tk.NORMAL):
        save_data_button['state'] = tk.DISABLED
    else:
        save_data_button['state'] = tk.NORMAL
        
    if (load_param_button['state'] == tk.NORMAL):
        load_param_button['state'] = tk.DISABLED
    else:
        load_param_button['state'] = tk.NORMAL
    
    
def runProg():
    global start, stop, incr, amp, offset, phase, xAxis, yAxis, label_readout
    while(1): 
        if endCalcThread.is_set():
            switchButtonState()
            break
        check_parameters() 
        if endCalcThread.is_set():
            switchButtonState()
            break
        switchButtonState()
        if start > stop:
            incr *= -1
        frequencies = np.arange(start, (stop + incr*0.1), incr)
        length = len(frequencies)
        lastFreq = frequencies[length-1]

        for i, freq in enumerate(frequencies):
            if i != 0:
                graphlock.acquire()
                
            if endCalcThread.is_set():
                break
                           
            ampvalue = 0.0
            label_readout['text'] = "Calculating amplitude"
            ampvalue = lcr.theController(freq, amp, offset, phase)
            
            if endCalcThread.is_set():
                break
                
            xAxis.append(freq)
            yAxis.append(ampvalue)
            graphlock.release()
            time.sleep(0.2)
            
            if(freq == lastFreq):
                endCalcThread.set()
                endGraphThread.set()
                switchButtonState()
                label_readout['text'] = "Waiting"
                time.sleep(0.2)
                
                          
def run():
    global start, stop, incr, amp, offset, phase, xAxis, yAxis
    paramlock.acquire()
    start = float(var_start_freq.get())
    stop = float(var_end_freq.get())
    incr = float(var_incr_freq.get())
    amp = float(var_amp.get())
    offset = float(var_offset.get())
    phase = float(var_phase.get())
    paramlock.release()
    xAxis = []
    yAxis = []

    endCalcThread.clear()
    endGraphThread.clear()
    thread = threading.Thread(target = runProg, args=())
    thread.start()  
    graphThread = threading.Thread(target = graphData, args=())
    graphThread.start()  
    
    
def graphData():
    global xAxis, yAxis, graph, label_readout
    
    while(1):
        graphlock.acquire()
        
        if endGraphThread.is_set():
            label_readout['text'] = "Waiting for input"
            break
        del graph #delete subplot
        graph = fig.add_subplot() #redefine subplot
        graph.set_ylabel('Amplitude (Volts)')
        graph.set_xlabel('Frequency (Hz)')
        graph.set_title('Amplitude data')
        graph.clear()
        
        graph.plot(xAxis,yAxis)
        
        canvas.draw_idle()
        graphlock.release()
        time.sleep(1.0)


def quitButton():
    endCalcThread.set()
    endGraphThread.set()
    closeProgram.set()
    if graphlock.locked() == True:
        graphlock.release()

    root.destroy()


def saveParam():
    global label_readout
    filenamesave = var_name_save.get()
    label_readout['text'] = "Saving parameters"
    parameters = var_start_freq.get()+", "+var_end_freq.get()+", "+var_incr_freq.get()+", "+var_amp.get()+", "+var_offset.get()+", "+var_phase.get() 

    if len(filenamesave) == 0:
        filenamesave = "saved_parameters_default.txt"
    if filenamesave.find(".txt") == -1:
        filenamesave = filenamesave + ".txt"
    f = open(filenamesave, "w")
    f.write(parameters)
    f.close()
    label_readout['text'] = "Parameters saved"
    
def checkfilename(filename):
    if len(filename) == 0:
        return -2        
    if filename.find(".txt") == -1:
        return -1
    
    return 0
    
    
def loadParam():
    global label_readout
    filenameload = var_name_load.get()
    label_readout['text'] = "Loading parameters"
    
    if len(filenameload) != 0:
        if filenameload.find(".txt") == -1:
            filenameload = filenameload + ".txt"
        try:
            f = open(filenameload, "r")
            parametersString = f.readline()
            parameters = parametersString.rsplit(", ")
            var_start_freq.set(parameters[0])
            var_end_freq.set(parameters[1])
            var_incr_freq.set(parameters[2])
            var_amp.set(parameters[3])
            var_offset.set(parameters[4])
            var_phase.set(parameters[5])
            f.close()
            label_readout['text'] = "Parameters loaded" 
        except:
            label_readout['text'] = "File not found"
        
    else:
        try:
            f = open("saved_parameters_default.txt", "r")
            parametersString = f.readline()
            parameters = parametersString.rsplit(", ")
            var_start_freq.set(parameters[0])
            var_end_freq.set(parameters[1])
            var_incr_freq.set(parameters[2])
            var_amp.set(parameters[3])
            var_offset.set(parameters[4])
            var_phase.set(parameters[5])
            f.close()
            label_readout['text'] = "Parameters loaded" 
        except:
            label_readout['text'] = "File not found"
       
    
def saveData():
    global label_readout
    if endCalcThread.is_set():
        label_readout['text'] = "Saving data"
        for x, y in zip(xAxis, yAxis):
            df.loc[len(df.index)] = [x, y]
        
        now = datetime.now() 
        date_time = now.strftime("__%m_%d_%Y__%H_%M_%S")
        name = "Amplitude_data_"+var_start_freq.get()+"_"+var_end_freq.get()+date_time+".xlsx"
        print(name)
        df.to_excel(name, index=False)
        endCalcThread.clear()
        label_readout['text'] = "Data saved"
            

control_frame = tk.Frame(root)
control_frame.pack(side=tk.LEFT)
label_func = tk.Label(control_frame, text="Function Generator Controls")
label_start_freq = tk.Label(control_frame, text="Start Frequency", width=15)
label_end_freq = tk.Label(control_frame, text="End Frequency", width=15)
label_incr_freq = tk.Label(control_frame, text="Frequency Increment", width=15)
label_amp = tk.Label(control_frame, text="Voltage Amplitude", width=15)
label_offset = tk.Label(control_frame, text="Voltage Offset", width=15)
label_phase = tk.Label(control_frame, text="Voltage Phase", width=15)

var_start_freq = tk.StringVar(value="5000.0")
var_end_freq = tk.StringVar(value="10000.0")
var_incr_freq = tk.StringVar(value="50.0")
var_amp = tk.StringVar(value="1.0")
var_offset = tk.StringVar(value="0.0")
var_phase = tk.StringVar(value="0.0")
var_name_save = tk.StringVar(value="")
var_name_load = tk.StringVar(value="")

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
label_readout = tk.Label(control_frame, text="Waiting for input")
label_name1 = tk.Label(control_frame, text="File name")
label_name2 = tk.Label(control_frame, text="File name")


label_func.grid(row=0, columnspan = 3, column=0)
label_start_freq.grid(row=3, column=0, padx=(0,10))
label_end_freq.grid(row=4, column=0, padx=(0,10))
label_incr_freq.grid(row=5, column=0, padx=(0,10))
label_amp.grid(row=6, column=0, padx=(0,10))
label_offset.grid(row=7, column=0, padx=(0,10))
label_phase.grid(row=8, column=0, padx=(0,10))
label_name1.grid(row=13, column=0, padx=(0,10))
label_name2.grid(row=15, column=0, padx=(0,10))

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
label_readout.grid(row=9, column=0, columnspan=3, pady=(30,30))

calc_button = tk.Button(control_frame, text="Run", width=20, command = run)
stop_button = tk.Button(control_frame, text="Stop", width=20, command = stop_button_func)
quit_button = tk.Button(control_frame, text="Quit", width=20, fg="red", command = quitButton)
save_param_button = tk.Button(control_frame, text="Save Parameters", width=20, command = saveParam)
entry_name_save = tk.Entry(control_frame, textvariable=var_name_save, width=20)
load_param_button = tk.Button(control_frame, text="Load Parameters", width=20, command = loadParam)
entry_name_load = tk.Entry(control_frame, textvariable=var_name_load, width=20)
save_data_button = tk.Button(control_frame, text="Save Data", width=20, command = saveData)

calc_button.grid(row=10, column=0, columnspan=3, pady=(3,3))
stop_button.grid(row=11, column=0, columnspan=3, pady=(3,3))
save_param_button.grid(row=12, column=0, columnspan=3, pady=(3,3))
entry_name_save.grid(row=13, column=1, pady=(5,5))
load_param_button.grid(row=14, column=0, columnspan=3, pady=(3,3))
entry_name_load.grid(row=15, column=1, pady=(5,5))
save_data_button.grid(row=16, column=0, columnspan=3, pady=(3,3))
quit_button.grid(row=25, column=0, columnspan=3, pady=(3,3))

tk.mainloop()
