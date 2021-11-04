import datalink as dl
import tkinter as tk

resource_manager = dl.rm()
print(resource_manager)
fun_generator= dl.findgen(resource_manager, 1)
scope_handle = dl.findscope(resource_manager,1)

root = tk.Tk()
root.wm_title("Function Generator & Oscilloscope")
ctrlframe = tk.Frame(root)
ctrlframe.pack(side=tk.LEFT)

label_A = tk.Label(ctrlframe, text="Amplitude",width=5)
label_B = tk.Label(ctrlframe, text="Freqency Start",width=5)
label_C = tk.Label(ctrlframe, text="Freqency End",width=5)

for x in range(9, 100):
    amp = dl.findamp(1,10,x,fun_generator,scope_handle)
    print(amp)
