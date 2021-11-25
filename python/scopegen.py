import datalink as dl
import tkinter as tk
import threading
import time

from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

import numpy as np

resource_manager = dl.rm()
print(resource_manager)
fun_generator= dl.findgen(resource_manager, 1)
scope_handle = dl.findscope(resource_manager,1)

root = tk.Tk()
root.wm_title("Function Generator & Oscilloscope")

stopCalcEvent = threading.Event()
dataLock= threading.Lock()

ctrlframe = tk.Frame(root)
ctrlframe.pack(side=tk.LEFT)

label_A = tk.Label(ctrlframe, text="Start Frequency",width=15)
label_B = tk.Label(ctrlframe, text="End Freqency",width=15)
label_C = tk.Label(ctrlframe, text="Number of Steps",width=15)


var_A = tk.StringVar(value="100")
var_B = tk.StringVar(value="200")
var_C = tk.StringVar(value="10")

entry_A = tk.Entry(ctrlframe, textvariable=var_A, width=10)
entry_B = tk.Entry(ctrlframe, textvariable=var_B, width=10)
entry_C = tk.Entry(ctrlframe, textvariable=var_C, width=10)

label_A.grid(row=0,column=1)
label_B.grid(row=1,column=1)
label_C.grid(row=2,column=1)


fig = Figure(figsize=(5,4),dpi=100)
graph = fig.add_subplot()
fig.suptitle("Freqency Vs Amplitude")


canvas = FigureCanvasTkAgg(fig,master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT)

entry_A.grid(row=0,column=2,padx=(0,10))
entry_B.grid(row=1,column=2,padx=(0,10))
entry_C.grid(row=2,column=2,padx=(0,10))

def freqency_range():
    A=int(var_A.get())
    B=int(var_B.get())
    C=int(var_C.get())
    freq = np.linspace(A,B,C)
    amp = np.zeros_like(freq)
    for i,x in enumerate(freq):
        if stopCalcEvent.is_set():
            break
        dataLock.acquire()
        amp[i] = dl.findamp(1,10,x,fun_generator,scope_handle)
        dataLock.release()
        time.sleep(0.25)
    graph.clear()
    graph.plot(freq,amp)
    canvas.draw_idle()
        

def startCalculation():
    stopCalcEvent.clear()
    t = threading.Thread(target = freqency_range)
    t.start()

def stopf():
    stopCalcEvent.set()


calc_button = tk.Button(ctrlframe,text="Start",command=startCalculation)
calc_button.grid(row=3,column=1,columnspan=2,sticky="ews")
stop_button = tk.Button(ctrlframe,text="stop",command=stopf)
stop_button.grid(row=4,column=1,columnspan=2,sticky="ews")
quit_button = tk.Button(ctrlframe,text="Quit",command=quit)
quit_button.grid(row=5,column=1,columnspan=2,sticky="ews")


tk.mainloop()