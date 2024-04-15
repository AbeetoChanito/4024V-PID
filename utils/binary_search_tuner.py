import tkinter as tk

window = tk.Tk()
window.geometry("400x200")
window.resizable(False, False)
window.title("Auto PID Tuner")

text_box = tk.Listbox()
text_box.pack() 

def stringify_mode(mode):
    return "kp" if mode == 0 else "kd"

def format_value(constants, mode):
    return f"current {stringify_mode(mode)} = {constants[mode]}"

def format_constants(constants):
    return f"kp = {constants[0]}, kd={constants[1]}"

def get_starting_constants():
    text_box.insert("end", "--- starting constants ---")

    confirmed = tk.BooleanVar(value=False)

    title = tk.Label(text="Start")        
    start_kp_entry = tk.Entry(text="Starting KP")
    start_kd_entry = tk.Entry(text="Starting KD")
    confirm_btn = tk.Button(text="Confirm", command=lambda: confirmed.set(True))

    confirm_btn.pack(before=text_box)
    start_kp_entry.pack(before=confirm_btn)
    start_kd_entry.pack(before=start_kp_entry)
    title.pack(before=start_kd_entry)

    confirm_btn.wait_variable(confirmed)

    constants = [float(start_kp_entry.get()), float(start_kd_entry.get())]
    
    title.destroy()
    start_kp_entry.destroy()
    start_kd_entry.destroy()
    confirm_btn.destroy()

    text_box.insert("end", format_constants(constants))

    return constants

def get_stage_2X(constants, mode):
    text_box.insert("end", f"--- stage 2X ({stringify_mode(mode)}) ---")

    stop = tk.BooleanVar(value=False)

    def low_update():
        constants[mode] *= 2 
        bottom_text_variable.set(format_value(constants, mode))
        text_box.insert("end", format_constants(constants))

    title = tk.Label(text=f"Stage 2X ({stringify_mode(mode)})")
    low_btn = tk.Button(text="Low", command=low_update)
    stop_btn = tk.Button(text="Stop", command=lambda: stop.set(True))
    bottom_text_variable = tk.StringVar(value=format_value(constants, mode))
    bottom_text = tk.Label(textvariable=bottom_text_variable)

    bottom_text.pack(before=text_box)
    stop_btn.pack(before=bottom_text)
    low_btn.pack(before=stop_btn)
    title.pack(before=low_btn)

    stop_btn.wait_variable(stop)

    constants[mode] /= 2

    title.destroy()
    low_btn.destroy()
    stop_btn.destroy()
    bottom_text.destroy()

    return constants

def get_stage_binary_search(constants, mode):
    text_box.insert("end", f"--- stage binary search ({stringify_mode(mode)}) ---")

    stop = tk.BooleanVar(value=False)

    last_low = constants[mode]
    last_high = constants[mode] * 2

    def change_constant(new_value):
        constants[mode] = new_value
        bottom_text_variable.set(format_value(constants, mode))
        text_box.insert("end", format_constants(constants))

    def low_update():
        last_constant = constants[mode]
        change_constant((constants[mode] + last_high) / 2)
        last_low = last_constant

    def high_update():
        last_constant = constants[mode]
        change_constant((constants[mode] + last_low) / 2)
        last_high = last_constant

    title = tk.Label(text=f"Stage Binary Search ({stringify_mode(mode)})")
    low_btn = tk.Button(text="Low", command=low_update)
    high_btn = tk.Button(text="High", command=high_update)
    stop_btn = tk.Button(text="Stop", command=lambda: stop.set(True))
    bottom_text_variable = tk.StringVar(value=format_value(constants, mode))
    bottom_text = tk.Label(textvariable=bottom_text_variable)

    bottom_text.pack(before=text_box)
    stop_btn.pack(before=bottom_text)
    high_btn.pack(before=stop_btn)
    low_btn.pack(before=high_btn)
    title.pack(before=low_btn)

    stop_btn.wait_variable(stop)

    title.destroy()
    low_btn.destroy()
    high_btn.destroy()
    stop_btn.destroy()
    bottom_text.destroy()

    return constants


constants = get_starting_constants()

while True:
    constants = get_stage_2X(constants, 0)
    constants = get_stage_binary_search(constants, 0)
    constants = get_stage_2X(constants, 1)
    constants = get_stage_binary_search(constants, 1)