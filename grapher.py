import subprocess
import matplotlib.pyplot as plt

COMMAND = ["pros", "t"]

try:
    popen = subprocess.Popen(COMMAND, stdout=subprocess.PIPE, universal_newlines=True)

    begin_reading = False

    while True:
        stdout_line = next(iter(popen.stdout.readline, "")).strip("\n")

        if stdout_line == "STOP":
            break

        if begin_reading is True:
            split_data = stdout_line.split(" ")
            plt.scatter(float(split_data[0]), float(split_data[1]), color="blue")
        
        if stdout_line == "START":
            begin_reading = True

        plt.pause(0.01) 

    plt.show()
except subprocess.CalledProcessError as e:
    print(f"Error: {e}")


popen.stdout.close()