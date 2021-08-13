
import sys

import numpy
import matplotlib.pyplot
import matplotlib.animation

#with open(sys.argv[1],'r') as F:
#    D = list(map(lambda l: list(map(lambda x: float(x) if x != "" else x, l.split('\n')[0].split(','))), F.readlines()[1:]))
#
#D = list(zip(*D))

x = numpy.arange(10)
y = numpy.random.random(10)

fig = matplotlib.pyplot.figure()
matplotlib.pyplot.xlim(0, 10)
matplotlib.pyplot.ylim(0, 1)
graph, = matplotlib.pyplot.plot([], [], 'o')

def animate(i):
    graph.set_data(x[:i+1], y[:i+1])
    return graph

anim = matplotlib.animation.FuncAnimation(fig, animate, frames=10, interval=200)
anim.save(sys.argv[2], writer=matplotlib.animation.FFMpegWriter(fps=60))
