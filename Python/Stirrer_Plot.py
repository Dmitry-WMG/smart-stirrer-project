import csv, math
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style

style.use('ggplot')
fig, axs = plt.subplots(2, 2, figsize=(8, 4), constrained_layout=True)
i = 0

def animate(i):
    x_time = []
    R = []
    G = []
    B = []
    temp = []
    accelX = []
    accelY = []
    accelZ = []
    adc_1 = []

    with open('/Users/Dmitry/Documents/PythonProjects/test_csv_file.csv', 'r') as file:
        tryread = csv.reader(file)
        for row in tryread:
            x_time.append(float(row[0]))
            R.append(1.39*float(row[1]))
            G.append(float(row[2]))
            B.append(1.79*float(row[3]))
            temp.append(28+float(row[11])*0.0625)
            accelX.append(int(row[8])/2**16)
            accelY.append(int(row[9])/2**16)
            accelZ.append(int(row[10])/2**16)
            adc_1.append(69+(3000*int(row[7])/2**14-500)/10)

    axs[0][0].clear()
    axs[0][0].plot(x_time, R, color = 'r')
    axs[0][0].plot(x_time, G, color = 'g')
    axs[0][0].plot(x_time, B, color = 'b')
    axs[0][0].set_ylabel('Colour, RGB intensity')
    axs[0][0].set_xlim(left=max(0, x_time[i] - 20), right=x_time[i] + 40)
    axs[0][0].xaxis.set_visible(False)
    axs[1][0].clear()
    axs[1][0].plot(x_time, temp)
    axs[1][0].legend("lsm9ds1", fontsize=8)
    axs[1][0].set_xlim(left=max(0, x_time[i] - 20), right=x_time[i] + 40)
    axs[0][1].clear()
    axs[0][1].plot(x_time, accelX)
    axs[0][1].plot(x_time, accelY)
    axs[0][1].plot(x_time, accelZ)
    axs[0][1].xaxis.set_visible(False)
    axs[0][1].set_ylabel('Accelerometer, g')
    axs[0][1].set_xlim(left=max(0, x_time[i] - 20), right=x_time[i] + 40)
    axs[1][1].clear()
    axs[1][1].plot(x_time, adc_1, label='Blue stars')

    axs[1][1].grid(True, linestyle='-.')
    axs[1][1].tick_params(labelsize=8)

    axs[1][1].legend('Thermistor', fontsize=8)
    axs[1][1].set_xlim(left=max(0, x_time[i] - 20), right=x_time[i] + 40)



    axs[1][0].set_xlabel('time, s.')
    axs[1][1].set_xlabel('time, s.')

    i += 1

ani = animation.FuncAnimation(fig, animate, interval=1000)
plt.show()
#plt.tight_layout()