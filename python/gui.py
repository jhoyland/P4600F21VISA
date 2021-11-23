# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import datalink
import tkinter as tk
import numpy as np
import time
import csv
import threading

from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg


endThread = threading.Event()
lockThread = threading.Lock()

dataReady = threading.Event()

x=[]
y=[]

def plot_AMP(FG, OS):
    channel, initialFreq, stepSize, finalFreq = getVariables()


    global x
    global y
    x = np.arange(initialFreq, finalFreq, stepSize)
    y = []
    datalink.setSinwave(FG, channel, initialFreq, 5.0, 0.0, 0.0)
    datalink.displayWave(FG, channel)  #output the signal
    datalink.autosetScope(OS)       #autoset
    time.sleep(3)
    
    #calculation
    for i in x: 
        #set freq on generator with i
        datalink.setSinwave(FG, channel, i, 5.0, 0.0, 0.0)
        datalink.autosetScope(OS)
        time.sleep(4)
        #get amp at i\
        amp = datalink.getAmplitude(OS,channel) 
        
        lockThread.acquire()     
        y.append(amp)
        lockThread.release()
        
        if endThread.is_set():          #if stop button is pressed show graph.
            dataReady.set()                 #stop button doesnt crash the program
            break
        
    dataReady.set()                     #when loop is done data is ready
    
    plotGraph()
    #graph doesnt plot when loop is done


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
    #plot_AMP(FG, OS)
    label_status.config(text="RUNNING...")
    endThread.clear()
    dataReady.clear()
    t=threading.Thread(target=plot_AMP, args=(FG,OS))
    t.start()

#-------------------------------------------------------------------------------
#threading
def stopIt():
    endThread.set()
        
        
def plotGraph():
    
    global x
    global y 
    global label_status
    
    if dataReady.is_set():
        graph.clear()
        lockThread.acquire()
        graph.plot(x[0:len(y)],y)
        lockThread.release()
        
        canvas.draw_idle()
        label_status.config(text="DONE")    
        dataReady.clear()
        
        
def saveData():
    global x
    global y
    with open('data.txt', 'w') as f:
        writer = csv.writer(f, delimiter='\t')
        writer.writerows(zip(x,y))
    
    f.close()

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

var_Channel = tk.StringVar(value="1")
var_Freq = tk.StringVar(value="500")
var_step = tk.StringVar(value="100")
var_endFreq = tk.StringVar(value="1000")


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

label_status = tk.Label(ctrlframe,text="READY")
label_status.grid(row=6,column=0,columnspan=2,sticky="ew",pady=(10,10))

fig = Figure(figsize=(5,4),dpi=100)
graph = fig.add_subplot()


canvas = FigureCanvasTkAgg(fig,master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT)

#x = np.arange(-10,10,0.1)

calc_button = tk.Button(ctrlframe,text="Calculate",command=init)
calc_button.grid(row=4,column=0,columnspan=2,sticky="ew")

stop_button = tk.Button(ctrlframe,text="Stop",command=stopIt)
stop_button.grid(row=5,column=0,columnspan=2,sticky="ew")

save_button = tk.Button(ctrlframe, text="Save Data", command=saveData)
save_button.grid(row=7,column=0,columnspan=2,sticky="ew")

#------------------------------------------------------------------------------
#Start a plotting thread on its own in the background running continuously 
#plotGraph checks if data is ready to be graphed
plotThread = threading.Thread(target=plotGraph)
plotThread.start()



tk.mainloop()