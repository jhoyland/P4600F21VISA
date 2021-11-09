# -*- coding: utf-8 -*-
"""
Created on Tue Oct 26 10:17:09 2021

@author: MYakovlev
"""



from datalink import OSC_setup,FG_setup,resource_manager_setup,data_loop
import numpy as np
import tkinter as tk
from matplotlib.figure import Figure
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from datetime import datetime
import threading
import time

global endThread
endThread=threading.Event()



def data_plot():
    global big_s
    big_s=""
    abc=0
    stringy = "abc"
    FG_channel=int(FG_ch.get())
    if (FG_channel==0):
        abc=1
    OSC_channel=int(OSC_ch.get())
    if (OSC_channel==0):
        abc=2
    freq_start =float(FG_41_var.get())
    if (freq_start<0.000001):
        abc=3
    freq_step =float(FG_42_var.get())
    if (freq_step<0.000001):
        abc=4
    freq_num =int(FG_43_var.get())
    if (freq_num<1):
        abc=5
    if ((freq_num-1)*freq_step+freq_start>25000000):
        abc=6
    v_offset=float(FG_2_var.get())
    if (v_offset<-4.999 or v_offset>4.999):
        abc=7
    FG_volt=float(FG_3_var.get())
    if (FG_volt<0.002 or FG_volt>10):
        abc=8
    OSC_resol=int(OSC_2_var.get())
    if (OSC_resol<1000 or OSC_resol>2500):
        abc=9  
    move_avg_size=int(Avg_var.get())
    if (move_avg_size<2 or move_avg_size>100):
        abc=10
    ending_freq.set("{:}".format(float(FG_41_var.get())+float(FG_42_var.get())*(int(FG_43_var.get())-1)))
    if (abc!=0):
        if (abc==1):
            stringy="!!! Select the Function Generator Channel !!!"
        if (abc==2):
            stringy="!!! Select the Oscilloscope Channel !!!"
        if (abc==3):
            stringy="!!! Choose valid Starting Frequency !!!"
        if (abc==4):
            stringy="!!! Choose valid Frequency Step !!!"
        if (abc==5):
            stringy="!!! Choose valid number of Frequency Points !!!"
        if (abc==6):
            stringy="!!! Adjust frequecny parameters to lower Ending Frequency !!!"
        if (abc==7):
            stringy="!!! Choose valid DC Voltage Offset !!!"
        if (abc==8):
            stringy="!!! Choose valid Operating Voltage !!!"
        if (abc==9):
            stringy="!!! Choose valid Data Resolution size !!!"
        if (abc==10):
            stringy="!!! Choose valid Filter Window size !!!"   
        Error_var.set("{:}".format(stringy))
    else:
        stringy="--- No Error ---"
        Error_var.set("{:}".format(stringy))
        freq=np.zeros(freq_num)
        amp=np.zeros(freq_num)
        i=0
        while (i<freq_num):
            if endThread.is_set():
                return
            freq[i]=freq_start+i*freq_step
            i=i+1    
        #plt.figure()
        #plt.figure.clear()
        #plt.figure(freq,amp)
        #plt.show()
        i=0
        while (i<freq_num):
            if endThread.is_set():
                return
            resource_manager=resource_manager_setup()
            functiongen_handle=FG_setup(resource_manager)
            scope_handle=OSC_setup(resource_manager)
            stringy="--- No Error ---\nCLOSE TO INTERUPT"
            Error_var.set("{:}".format(stringy))
            amp[i]=data_loop(functiongen_handle,scope_handle,FG_channel,OSC_channel,freq[i],v_offset,FG_volt,OSC_resol,move_avg_size)
            #plt.figure.clear()
            #plt.figure(freq,amp)
            #plt.show()
            big_s=big_s+str(freq[i])+","+str(amp[i])+"\n"
            stringy="--- No Error ---\nOPEN TO INTERUPT"
            Error_var.set("{:}".format(stringy))

            time.sleep(3)
            i=i+1

def save_data():
    now = datetime.now()
    dt_string = now.strftime("%Y-%m-%d %H-%M-%S")
    title=str(dt_string)+".txt" 
    try:
        if (big_s=="hi"):
            abra="cadabra"
        stringy="--- No Error ---"
        Error_var.set("{:}".format(stringy))
        text_file = open(title, "wt")
        n = text_file.write(big_s)
        text_file.close()
    except:
        stringy="!!! There is no data to save !!!"
        Error_var.set("{:}".format(stringy))

def data_thread_start():
    endThread.clear()
    thread_=threading.Thread(target=data_plot)
    thread_.start()
    
def data_thread_stop():
    endThread.set()






root = tk.Tk()
FG_ch = tk.IntVar()
OSC_ch = tk.IntVar()



control_frame= tk.Frame(root)
control_frame.pack(side=tk.LEFT)
root.wm_title("LCR Frequency Sweep")



FG_0_label = tk.Label(control_frame,text="FUNCTION GENERATOR")
FG_1_label = tk.Label(control_frame,text="Operating Channel")
FG_2_label = tk.Label(control_frame,text="DC Voltage Offset")
FG_2_label_ = tk.Label(control_frame,text="(-4.999 <--> 4.999 V)")
FG_3_label = tk.Label(control_frame,text="Operating Voltage")
FG_3_label_ = tk.Label(control_frame,text="(0.002 <--> 10 Vpp)")
FG_41_label = tk.Label(control_frame,text="Starting Frequency")
FG_41_label_ = tk.Label(control_frame,text="(>=0.000'001 Hz)")
FG_42_label = tk.Label(control_frame,text="Frequency Step")
FG_42_label_ = tk.Label(control_frame,text="(>=0.000'001 Hz)")
FG_43_label = tk.Label(control_frame,text="Frequency Points")
FG_43_label_ = tk.Label(control_frame,text="(>=1 points)")
FG_44_label = tk.Label(control_frame,text="Ending Frequency")
FG_44_label_ = tk.Label(control_frame,text="(<=25'000'000 Hz)")
OSC_0_label = tk.Label(control_frame,text="OSCILLOSCOPE")
OSC_1_label = tk.Label(control_frame,text="Operating Channel")
OSC_2_label = tk.Label(control_frame,text="Data Resolution")
OSC_2_label_ = tk.Label(control_frame,text="(1000 <--> 2500 points)")
Avg_label = tk.Label(control_frame,text="Filter Window")
Avg_label_ = tk.Label(control_frame,text="(2 <--> 100 points)")
Error_var = tk.StringVar(value="--- No Error ---")
Error_label = tk.Label(control_frame,textvariable=Error_var)
FG_2_var = tk.StringVar(value="0")
FG_2_entry = tk.Entry(control_frame,textvariable=FG_2_var)
FG_3_var = tk.StringVar(value="1")
FG_3_entry = tk.Entry(control_frame,textvariable=FG_3_var)
FG_41_var = tk.StringVar(value="1000")
FG_41_entry = tk.Entry(control_frame,textvariable=FG_41_var)
FG_42_var = tk.StringVar(value="100")
FG_42_entry = tk.Entry(control_frame,textvariable=FG_42_var)
FG_43_var = tk.StringVar(value="10")
FG_43_entry = tk.Entry(control_frame,textvariable=FG_43_var)
Avg_var = tk.StringVar(value="10")
Avg_entry = tk.Entry(control_frame,textvariable=Avg_var)
OSC_2_var = tk.StringVar(value="2500")
OSC_2_entry = tk.Entry(control_frame,textvariable=OSC_2_var)
fig= Figure(figsize=(5,4),dpi=111)
graph = fig.add_subplot()
canvas = FigureCanvasTkAgg(fig,master=root)
canvas.get_tk_widget().pack(side=tk.RIGHT)
FG_select_1=tk.Radiobutton(control_frame, text="CH1",variable=FG_ch, value=1)
FG_select_2=tk.Radiobutton(control_frame, text="CH2",variable=FG_ch, value=2)
OSC_select_1=tk.Radiobutton(control_frame, text="CH1",variable=OSC_ch, value=1)
OSC_select_2=tk.Radiobutton(control_frame, text="CH2",variable=OSC_ch, value=2)
ending_freq = tk.StringVar(value="")
FG_44_entry=tk.Label(control_frame,textvariable=ending_freq)



FG_0_label.grid(row=0,column=0,columnspan=3,padx=(5,0),pady=(5,5))
FG_1_label.grid(row=1,column=0,rowspan=2,padx=(5,0))
FG_select_1.grid(row=1,column=1,pady=(5,0))
FG_select_2.grid(row=2,column=1,pady=(0,5))
FG_2_label.grid(row=3,column=0,padx=(5,0),pady=(0,5))
FG_2_entry.grid(row=3,column=1,padx=(5,10),pady=(0,5))
FG_2_label_.grid(row=3,column=2,pady=(0,5))
FG_3_label.grid(row=4,column=0,padx=(5,0),pady=(0,5))
FG_3_entry.grid(row=4,column=1,padx=(5,10),pady=(0,5))
FG_3_label_.grid(row=4,column=2,pady=(0,5))
FG_41_label.grid(row=5,column=0,padx=(5,0),pady=(0,5))
FG_41_entry.grid(row=5,column=1,padx=(5,10),pady=(0,5))
FG_41_label_.grid(row=5,column=2,pady=(0,5))
FG_42_label.grid(row=6,column=0,padx=(5,0),pady=(0,5))
FG_42_entry.grid(row=6,column=1,padx=(5,10),pady=(0,5))
FG_42_label_.grid(row=6,column=2,pady=(0,5))
FG_43_label.grid(row=7,column=0,padx=(5,0),pady=(0,5))
FG_43_entry.grid(row=7,column=1,padx=(5,10),pady=(0,5))
FG_43_label_.grid(row=7,column=2,pady=(0,5))
FG_44_label.grid(row=8,column=0,padx=(5,0),pady=(0,5))
FG_44_entry.grid(row=8,column=1,padx=(5,10),pady=(0,5))
FG_44_label_.grid(row=8,column=2,pady=(0,5))






    

OSC_0_label.grid(row=9,column=0,columnspan=3,padx=(5,0),pady=(30,5))
OSC_1_label.grid(row=10,column=0,rowspan=2,padx=(5,0))

OSC_select_1.grid(row=10,column=1,pady=(5,0))
OSC_select_2.grid(row=11,column=1,pady=(0,5))
OSC_2_label.grid(row=12,column=0,padx=(5,0),pady=(0,5))
OSC_2_entry.grid(row=12,column=1,padx=(5,10),pady=(0,5))
OSC_2_label_.grid(row=12,column=2,pady=(0,5))

Avg_label.grid(row=13,column=0,padx=(5,0),pady=(45,15))
Avg_entry.grid(row=13,column=1,padx=(5,10),pady=(45,15))
Avg_label_.grid(row=13,column=2,pady=(45,15))

Error_label.grid(row=14,column=0,columnspan=3,pady=(30,5))
    

Calculate_button=tk.Button(control_frame,text="Graph",command=data_thread_start)
Calculate_button.grid(row=21,column=0,columnspan=3,sticky="ews",pady=(30,5))

Stop_button=tk.Button(control_frame,text="Interrupt",command=data_thread_stop)
Stop_button.grid(row=22,column=0,columnspan=3,sticky="ews",pady=(10,5))

Save_button=tk.Button(control_frame,text="Save Data",command=save_data)
Save_button.grid(row=23,column=0,columnspan=3,sticky="ews",pady=(10,5))

Quit_button=tk.Button(control_frame,text="Quit",command=quit)
Quit_button.grid(row=24,column=0,columnspan=3,sticky="ews",pady=(10,5))

tk.mainloop()