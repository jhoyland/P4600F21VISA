# -*- coding: utf-8 -*-
"""
Created on Tue Oct 26 09:39:42 2021
Test out functions in python
@author: EPsajd
"""
# issue accepting python float values as argument 
# REMEMBER: in dll file make swig and make dll 

import datalink as dl 
import tkinter as tk
import numpy as np
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

root = tk.Tk() #creates root main window but does not start it 
root.wm_title("Scope/FG Control")

# we want the control frame to have buttons to: 
# Generate Resource manager and display Y/N in an uneditable box.
# Initialize scope and FG 
# set the channel (default to ch1?)
# Set the Frequency
# Autofocus the scope 
# collect and display sin data which includes:
# List of RMS, Average, Amplitude, Frequency vs. Amp Graph 

ctrlframe = tk.Frame(root)
ctrlframe.pack(side=tk.LEFT,anchor=tk.NW)

displayframe = tk.Frame(root)
displayframe.pack(side=tk.RIGHT, anchor=tk.NE)

terminalframe = tk.Frame(root)
terminalframe.pack(side=tk.RIGHT, anchor=tk.SE)

label_A = tk.Label(ctrlframe,text = "Initialize Devices", width=5)
# will check if resource manager is generated, 
# should have 3 displays for resource man, scope, FG 

label_B = tk.Label(ctrlframe,text = "Set Channel", width=5)
# label_C = tk.Label(ctrlframe,text = "Set Frequency", width=5)
# or should I set a range of frequencies? 
label_Cs =  tk.Label(ctrlframe,text = "Start Freq.", width=5)
label_Ce =  tk.Label(ctrlframe,text = "End Freq.", width=5)
label_Ci =  tk.Label(ctrlframe,text = "Intervals", width=5)


label_D = tk.Label(ctrlframe,text = "Autofocus Scope", width=5)
label_E = tk.Label(ctrlframe,text = "Display Data", width=5)

var_A = tk.StringVar(value="0")
var_B = tk.StringVar(value="0")
var_C = tk.StringVar(value="0")

tk.mainloop() #starts the window


