
import sys

import numpy
import matplotlib.pyplot
import matplotlib.animation

with open(sys.argv[1],'r') as F:
    D = list(map(lambda l: list(map(lambda x: float(x) if x != "" else x, l.split('\n')[0].split(','))), F.readlines()))

step = 1
N = int(len(D)/step)
M = int((len(D[0])-2)/6)

fig = matplotlib.pyplot.figure()

Xs = [ D[i][6*j+1] for j in range(M) for i in range(len(D)) ]
Ys = [ D[i][6*j+4] for j in range(M) for i in range(len(D)) ]

matplotlib.pyplot.xlim(min(Xs)-1, max(Xs)+1)
matplotlib.pyplot.ylim(min(Ys)-1, max(Ys)+1)

Xs=None
Ys=None

graph, = matplotlib.pyplot.plot([], [], 'o')

def animate(i):
    graph.set_data( [ D[step*i][6*j+1] for j in range(M) ] , [ D[step*i][6*j+4] for j in range(M) ] )
    return graph

anim = matplotlib.animation.FuncAnimation(fig, animate, frames=N, interval=10)
anim.save(sys.argv[2], writer=matplotlib.animation.FFMpegWriter(fps=100))

