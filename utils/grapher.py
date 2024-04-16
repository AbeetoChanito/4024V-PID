import subprocess
import matplotlib.pyplot as plt

COMMAND = ["pros", "t"]

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

    print(stdout_line)
    plt.pause(50 / 1000) 

plt.show()

popen.stdout.close()