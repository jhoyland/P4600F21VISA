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
    
def runProg():
    global start, stop, incr, amp, offset, phase, xAxis, yAxis
    while(1):

        if endCalcThread.is_set():
            break
        switchButtonState()
        
        frequencies = np.arange(start, (stop + incr*0.1), incr)
        length = len(frequencies)
        lastFreq = frequencies[length-1]

        for i, freq in enumerate(frequencies):
            if i != 0:
                graphlock.acquire()
                
            if endCalcThread.is_set():
                break
                           
            ampvalue = 0.0
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
    global xAxis, yAxis
    
    while(1):
        graphlock.acquire()
        
        if endGraphThread.is_set():
            break
        
        graph.clear()
        graph.plot(xAxis,yAxis)
        
        canvas.draw_idle()
        
        graphlock.release()
        time.sleep(0.5)


def quitButton():
    endCalcThread.set()
    endGraphThread.set()
    closeProgram.set()
    if graphlock.locked() == True:
        graphlock.release()

    root.destroy()

#def SavingThread():
#    while(closeProgram.is_set() == False):
#        time.sleep(2)
#        if saveParameters.is_set():
#            paramlock.acquire()
#            parameters = var_start_freq.get()
#            f = open("saved_parameters.txt", "w")
#            f.write(parameters)
#            f.close()
#            saveParameters.clear()
#            paramlock.release()
#        
#        if saveData.is_set():
#            df.to_excel("Amplitude_data_",start,"_",stop,".xlsx")
#            saveData.clear()

def saveParam():
        
    print("saving parameters")
    parameters = var_start_freq.get()+", "+var_end_freq.get()+", "+var_incr_freq.get()+", "+var_amp.get()+", "+var_offset.get()+", "+var_phase.get() 
    f = open("saved_parameters.txt", "w")
    f.write(parameters)
    f.close()
    

def saveData():
    if endCalcThread.is_set():
        print("saving data")
        for x, y in zip(xAxis, yAxis):
            df.loc[len(df.index)] = [x, y]
        
        now = datetime.now() 
        date_time = now.strftime("__%m_%d_%Y__%H_%M_%S")
        name = "Amplitude_data_"+var_start_freq.get()+"_"+var_end_freq.get()+date_time+".xlsx"
        print(name)
        df.to_excel(name, index=False)
        endCalcThread.clear()
            
    
    



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


calc_button = tk.Button(control_frame, text="Run", width=20, command = run)
stop_button = tk.Button(control_frame, text="Stop", width=20, command = stop_button_func)
quit_button = tk.Button(control_frame, text="Quit", width=20, fg="red", command = quitButton)
save_param_button = tk.Button(control_frame, text="Save Parameters", width=20, command = saveParam)
save_data_button = tk.Button(control_frame, text="Save Data", width=20, command = saveData)
calc_button.grid(row=10, column=0, columnspan=3, pady=(3,3))
stop_button.grid(row=11, column=0, columnspan=3, pady=(3,3))
save_param_button.grid(row=12, column=0, columnspan=3, pady=(3,3))
save_data_button.grid(row=13, column=0, columnspan=3, pady=(3,3))
quit_button.grid(row=14, column=0, columnspan=3, pady=(3,3))

tk.mainloop()
