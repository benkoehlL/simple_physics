import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

fig = plt.figure()
ax = plt.axes(xlim=(0, 1), ylim=(-1, 1))
line, = ax.plot([], [], lw=3)

def init():
    line.set_data([], [])
    return line,
def animate(i):
    x = np.linspace(0, 1, 100)
    y = []
    for j in range(len(x)):
        y.append(float((lines[i]).split('\t')[j]))
    line.set_data(x, y)
    return line,

#get data from file
data = open('advection.dat','r').read()
lines = data.split('\n')

plt.xlabel("x")
plt.ylabel("amplitude")

anim = animation.FuncAnimation(fig, animate, init_func=init,frames=200, interval=20, blit=True)
plt.show()
