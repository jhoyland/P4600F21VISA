# -*- coding: utf-8 -*-
"""
Created on Tue Oct 26 10:17:09 2021

@author: MYakovlev
"""



from datalink import OSC_setup,FG_setup,resource_manager_setup,data_loop
import numpy as np
import tkinter as tk
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from datetime import datetime
import threading
import time

global loader
loader=0
global endThread
endThread=threading.Event()
global EventA
EventA=threading.Event()
global LockThread
LockThread=threading.Lock()
global FG_channel
global OSC_channel
global freq_start
global freq_step
global freq_num
global v_offset
global FG_volt
global OSC_resol
global move_avg_size
global canvas
global fig
global graph
global big_s
global A_B_C
A_B_C="1"
global run_start
run_start=datetime.now()
global PARAmeters
PARAmeters=[0]*9

def save_data():
    global run_start
    dt_string = run_start.strftime("[%Y.%m.%d]-(%H_%M_%S)")
    title="DATA"+str(dt_string)+".csv" 
    try:
        if (big_s=="hi"):
            abra="cadabra"
        stringy="--- No Error ---\n\nData saved as: \t\t"+str(title)+"\n\n"
        Error_var.set("{:}".format(stringy))
        Error_label.config(fg="black")
        text_file = open(title, "wt")
        n = text_file.write(big_s)
        text_file.close()
    except:
        stringy="!!! There is no data to save !!!\n\n\n\n"
        Error_var.set("{:}".format(stringy))
        Error_label.config(fg="red")
        
def save_para():
    global run_start
    dt_string = run_start.strftime("[%Y.%m.%d]-(%H_%M_%S)")
    title="PARA"+str(dt_string)+".txt" 
    try:
        if (big_s=="hi"):
            abra="cadabra"
        stringy="--- No Error ---\n\nParameters saved as: \t\t"+str(title)+"\n\n"
        Error_var.set("{:}".format(stringy))
        Error_label.config(fg="black")
        text_file = open(title, "wt")
        para_para=str(PARAmeters[0])+"\n"+str(PARAmeters[1])+"\n"+str(PARAmeters[2])+"\n"+str(PARAmeters[3])\
        +"\n"+str(PARAmeters[4])+"\n"+str(PARAmeters[5])+"\n"+str(PARAmeters[6])+"\n"+str(PARAmeters[7])+"\n"+str(PARAmeters[8])
        n = text_file.write(para_para)
        text_file.close()
    except:
        stringy="!!! Start run before saving parameters !!!\n\n\n\n"
        Error_var.set("{:}".format(stringy))
        Error_label.config(fg="red")

def data_plot():
    global big_s
    global freq
    global amp
    global run_start
    global A_B_C
    global loader
    global FG_channel
    global OSC_channel
    global freq_start
    global freq_step
    global freq_num
    global v_offset
    global FG_volt
    global OSC_resol
    global move_avg_size
    abc=0
    stringy = "abc"
    if (loader==0):
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
            stringy="!!! Select the Function Generator Channel !!!\n\n\n\n"
        if (abc==2):
            stringy="!!! Select the Oscilloscope Channel !!!\n\n\n\n"
        if (abc==3):
            stringy="!!! Choose valid Starting Frequency !!!\n\n\n\n"
        if (abc==4):
            stringy="!!! Choose valid Frequency Step !!!\n\n\n\n"
        if (abc==5):
            stringy="!!! Choose valid number of Frequency Points !!!\n\n\n\n"
        if (abc==6):
            stringy="!!! Adjust frequecny parameters to lower Ending Frequency !!!\n\n\n\n"
        if (abc==7):
            stringy="!!! Choose valid DC Voltage Offset !!!\n\n\n\n"
        if (abc==8):
            stringy="!!! Choose valid Operating Voltage !!!\n\n\n\n"
        if (abc==9):
            stringy="!!! Choose valid Data Resolution size !!!\n\n\n\n"
        if (abc==10):
            stringy="!!! Choose valid Filter Window size !!!\n\n\n\n"   
        Error_var.set("{:}".format(stringy))
        Error_label.config(fg="red")
        LockThread.acquire()
        endThread.is_set
        LockThread.release()
    else:
        big_s="Frequency (Hz),Voltage Amplitude (V)\n"
        PARAmeters[0]=FG_channel
        PARAmeters[1]=OSC_channel
        PARAmeters[2]=freq_start
        PARAmeters[3]=freq_step
        PARAmeters[4]=freq_num
        PARAmeters[5]=v_offset
        PARAmeters[6]=FG_volt
        PARAmeters[7]=OSC_resol
        PARAmeters[8]=move_avg_size
        run_start=datetime.now()
        dt_string = run_start.strftime("[%Y.%m.%d] - (%H_%M_%S)")
        A_B_C="2"
        LockThread.acquire()
        freq=np.zeros(freq_num)
        amp=np.zeros(freq_num)
        i=0
        while (i<freq_num):
            if endThread.is_set():
                return
            freq[i]=freq_start+i*freq_step
            i=i+1
        EventA.set()
        LockThread.release()
        i=0
        while (i<freq_num):
            if endThread.is_set():
                stringy="--- No Error ---\n\nRun Title:\t\t"+str(dt_string)+"\n\nDATA GATHERING INTERUPTED"
                Error_var.set("{:}".format(stringy))
                Error_label.config(fg="black")
                return
            resource_manager=resource_manager_setup()
            functiongen_handle=FG_setup(resource_manager)
            scope_handle=OSC_setup(resource_manager)
            stringy="--- No Error ---\n\nRun Title:\t\t"+str(dt_string)+"\n\n"
            Error_var.set("{:}".format(stringy))
            Error_label.config(fg="black")
            LockThread.acquire()
            A_B_C=dt_string
            amp[i]=data_loop(functiongen_handle,scope_handle,FG_channel,OSC_channel,freq[i],v_offset,FG_volt,OSC_resol,move_avg_size)
            EventA.set()
            LockThread.release()
            big_s=big_s+str(freq[i])+","+str(amp[i])+"\n"
            #stringy="--- No Error ---\n\nRun Title:\t\t"+str(dt_string)+"\n\nOPEN TO INTERUPT"
            #Error_var.set("{:}".format(stringy))
            time.sleep(0.1)
            i=i+1        
        endThread.set()

def printss():
    global root
    global canvas
    global fig
    global graph
    global amp
    global A_B_C
    global freq
    while (1==1):
        if endThread.is_set():
            break
        LockThread.acquire()
        if EventA.is_set():
            title_="Run:     "+str(A_B_C)
            graph.clear()
            graph.plot(freq,amp)
            graph.set_title(title_)
            graph.set_xlabel("Freuqency (Hz)")
            graph.set_ylabel("Voltage Amplitude (V)")
            graph.grid()
            canvas.draw_idle()
            EventA.clear()
        LockThread.release()
        time.sleep(0.5)

def data_thread_start():

    endThread.clear()
    EventA.clear()
    thread_g=threading.Thread(target=printss)
    thread_g.start()
    thread_d=threading.Thread(target=data_plot)
    thread_d.start()
        
def data_thread_stop():
    endThread.set()
    
def loading_ui():
    global loader
    loader=0
    data_thread_start()
    
def loading_para():
    global loader
    try:
        file_title= str(LOAD_1_var.get())
        if (file_title[len(file_title)-1]=="t" and file_title[len(file_title)-2]=="x" and file_title[len(file_title)-3]=="t" and file_title[len(file_title)-4]=="."):
            abra="cadabra"
        else:
            file_title=file_title+".txt"
        global FG_channel
        global OSC_channel
        global freq_start
        global freq_step
        global freq_num
        global v_offset
        global FG_volt
        global OSC_resol
        global move_avg_size
        global loader
        loader=1
        with open(file_title) as f:
            lines = f.readlines()
        FG_channel=int(lines[0])
        OSC_channel=int(lines[1])
        freq_start=float(lines[2])
        freq_step=float(lines[3])
        freq_num=int(lines[4])
        v_offset=float(lines[5])
        FG_volt=float(lines[6])
        OSC_resol=int(lines[7])
        move_avg_size=int(lines[8])
        FG_ch.set("{:}".format(FG_channel))
        OSC_ch.set("{:}".format(OSC_channel))
        FG_41_var.set("{:}".format(freq_start))
        FG_42_var.set("{:}".format(freq_step))
        FG_43_var.set("{:}".format(freq_num))
        FG_2_var.set("{:}".format(v_offset))
        FG_3_var.set("{:}".format(FG_volt))
        OSC_2_var.set("{:}".format(OSC_resol))
        Avg_var.set("{:}".format(move_avg_size))
        ending_freq.set("{:}".format(float(FG_41_var.get())+float(FG_42_var.get())*(int(FG_43_var.get())-1)))
        data_thread_start()
    except:
        stringy="!!! File Reading Error !!!\n\nParameter File w/ Name:\t"+str(LOAD_1_var.get())+"\t is absent or does not qualify\n\n"
        Error_var.set("{:}".format(stringy))
        Error_label.config(fg="red")

root = tk.Tk()
FG_ch = tk.IntVar()
OSC_ch = tk.IntVar()
control_frame= tk.Frame(root)
control_frame.pack(side=tk.LEFT)
root.wm_title("LCR Frequency Sweep")

LOAD_0_label = tk.Label(control_frame,text="LOADER")
LOAD_1_label = tk.Label(control_frame,text="File Name:")
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
FG_43_label_ = tk.Label(control_frame,text="(>=3 points)")
FG_44_label = tk.Label(control_frame,text="Ending Frequency")
FG_44_label_ = tk.Label(control_frame,text="(<=25'000'000 Hz)")
OSC_0_label = tk.Label(control_frame,text="OSCILLOSCOPE")
OSC_1_label = tk.Label(control_frame,text="Operating Channel")
OSC_2_label = tk.Label(control_frame,text="Data Resolution")
OSC_2_label_ = tk.Label(control_frame,text="(1000 <--> 2500 points)")
Avg_label = tk.Label(control_frame,text="Filter Window")
Avg_label_ = tk.Label(control_frame,text="(2 <--> 100 points)")
Error_var = tk.StringVar(value="--- No Error ---\n\n\n\n")
Error_label = tk.Label(control_frame,textvariable=Error_var)
LOAD_1_var = tk.StringVar(value="file.txt")
LOAD_1_entry = tk.Entry(control_frame,textvariable=LOAD_1_var)
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
fig= Figure(figsize=(8,6),dpi=111)
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
OSC_0_label.grid(row=9,column=0,columnspan=3,padx=(5,0),pady=(20,5))
OSC_1_label.grid(row=10,column=0,rowspan=2,padx=(5,0))
OSC_select_1.grid(row=10,column=1,pady=(5,0))
OSC_select_2.grid(row=11,column=1,pady=(0,5))
OSC_2_label.grid(row=12,column=0,padx=(5,0),pady=(0,5))
OSC_2_entry.grid(row=12,column=1,padx=(5,10),pady=(0,5))
OSC_2_label_.grid(row=12,column=2,pady=(0,5))
Avg_label.grid(row=13,column=0,padx=(5,0),pady=(20,15))
Avg_entry.grid(row=13,column=1,padx=(5,10),pady=(3,15))
Avg_label_.grid(row=13,column=2,pady=(30,15))
LOAD_1_label.grid(row=14,column=0,padx=(5,0),pady=(20,15))
LOAD_1_entry.grid(row=14,column=1,columnspan=2,padx=(5,10),pady=(20,15))
Error_label.grid(row=18,column=0,columnspan=3,pady=(20,5))

Calculate_button=tk.Button(control_frame,text="Gather Data (UI Parameters)",fg="blue",command=loading_ui)
Calculate_button.grid(row=20,column=0,columnspan=3,sticky="ews",pady=(15,5))
Calculate_button=tk.Button(control_frame,text="Gather Data (Saved Parameters)",fg="blue",command=loading_para)
Calculate_button.grid(row=21,column=0,columnspan=3,sticky="ews",pady=(0,5))
Stop_button=tk.Button(control_frame,text="Interrupt",fg="red",command=data_thread_stop)
Stop_button.grid(row=22,column=0,columnspan=3,sticky="ews",pady=(0,5))
Save_button=tk.Button(control_frame,text="Save Data",fg="green",command=save_data)
Save_button.grid(row=23,column=0,columnspan=3,sticky="ews",pady=(0,5))
Save_button=tk.Button(control_frame,text="Save Parameter",fg="green",command=save_para)
Save_button.grid(row=24,column=0,columnspan=3,sticky="ews",pady=(0,5))
Quit_button=tk.Button(control_frame,text="Quit",fg="red",command=quit)
Quit_button.grid(row=33,column=0,columnspan=3,sticky="ews",pady=(0,5))

tk.mainloop()