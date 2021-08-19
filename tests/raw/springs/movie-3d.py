
import sys

import numpy
import matplotlib.pyplot
import matplotlib.animation

with open(sys.argv[1],'r') as F:
    D = list(map(lambda l: list(map(lambda x: float(x) if x != "" else x, l.split('\n')[0].split(','))), F.readlines()))

step = 1
N = int(len(D)/step)
M = int((len(D[0])-2)/9)

fig = matplotlib.pyplot.figure(figsize=(18,9))

# Position plots

pXs = [ D[i][9*j+1] for j in range(M) for i in range(len(D)) ]
pYs = [ D[i][9*j+2] for j in range(M) for i in range(len(D)) ]
pZs = [ D[i][9*j+3] for j in range(M) for i in range(len(D)) ]

## 3D view

ax_3d = fig.add_subplot(1, 2, 2, projection='3d')

ax_3d.set_xlim(min(pXs)-1, max(pXs)+1)
ax_3d.set_ylim(min(pYs)-1, max(pYs)+1)
ax_3d.set_zlim(min(pZs)-1, max(pZs)+1)

g_3d, = ax_3d.plot3D([], [], [], 'o')

## Projections

ax_pxy = fig.add_subplot(3, 6,  1)
ax_pxz = fig.add_subplot(3, 6,  7)
ax_pyz = fig.add_subplot(3, 6, 13)

ax_pxy.set_xlim(min(pXs)-1, max(pXs)+1)
ax_pxy.set_ylim(min(pYs)-1, max(pYs)+1)

ax_pxz.set_xlim(min(pXs)-1, max(pXs)+1)
ax_pxz.set_ylim(min(pZs)-1, max(pZs)+1)

ax_pyz.set_xlim(min(pYs)-1, max(pYs)+1)
ax_pyz.set_ylim(min(pZs)-1, max(pZs)+1)

g_pxy, = ax_pxy.plot([], [], 'o')
g_pxz, = ax_pxz.plot([], [], 'o')
g_pyz, = ax_pyz.plot([], [], 'o')

# Velocity projections

vXs = [ D[i][9*j+4] for j in range(M) for i in range(len(D)) ]
vYs = [ D[i][9*j+5] for j in range(M) for i in range(len(D)) ]
vZs = [ D[i][9*j+6] for j in range(M) for i in range(len(D)) ]

ax_vxy = fig.add_subplot(3, 6,  2)
ax_vxz = fig.add_subplot(3, 6,  8)
ax_vyz = fig.add_subplot(3, 6, 14)

ax_vxy.set_xlim(min(vXs)-1, max(vXs)+1)
ax_vxy.set_ylim(min(vYs)-1, max(vYs)+1)

ax_vxz.set_xlim(min(vXs)-1, max(vXs)+1)
ax_vxz.set_ylim(min(vZs)-1, max(vZs)+1)

ax_vyz.set_xlim(min(vYs)-1, max(vYs)+1)
ax_vyz.set_ylim(min(vZs)-1, max(vZs)+1)

g_vxy, = ax_vxy.plot([], [], 'o')
g_vxz, = ax_vxz.plot([], [], 'o')
g_vyz, = ax_vyz.plot([], [], 'o')

# Force projections

fXs = [ D[i][9*j+7] for j in range(M) for i in range(len(D)) ]
fYs = [ D[i][9*j+8] for j in range(M) for i in range(len(D)) ]
fZs = [ D[i][9*j+9] for j in range(M) for i in range(len(D)) ]

ax_fxy = fig.add_subplot(3, 6,  3)
ax_fxz = fig.add_subplot(3, 6,  9)
ax_fyz = fig.add_subplot(3, 6, 15)

ax_fxy.set_xlim(min(fXs)-1, max(fXs)+1)
ax_fxy.set_ylim(min(fYs)-1, max(fYs)+1)

ax_fxz.set_xlim(min(fXs)-1, max(fXs)+1)
ax_fxz.set_ylim(min(fZs)-1, max(fZs)+1)

ax_fyz.set_xlim(min(fYs)-1, max(fYs)+1)
ax_fyz.set_ylim(min(fZs)-1, max(fZs)+1)

g_fxy, = ax_fxy.plot([], [], 'o')
g_fxz, = ax_fxz.plot([], [], 'o')
g_fyz, = ax_fyz.plot([], [], 'o')

def animate(i):
    pX = numpy.array([ D[step*i][9*j+1] for j in range(M) ], dtype=numpy.float32)
    pY = numpy.array([ D[step*i][9*j+2] for j in range(M) ], dtype=numpy.float32)
    pZ = numpy.array([ D[step*i][9*j+3] for j in range(M) ], dtype=numpy.float32)
    vX = numpy.array([ D[step*i][9*j+4] for j in range(M) ], dtype=numpy.float32)
    vY = numpy.array([ D[step*i][9*j+5] for j in range(M) ], dtype=numpy.float32)
    vZ = numpy.array([ D[step*i][9*j+6] for j in range(M) ], dtype=numpy.float32)
    fX = numpy.array([ D[step*i][9*j+7] for j in range(M) ], dtype=numpy.float32)
    fY = numpy.array([ D[step*i][9*j+8] for j in range(M) ], dtype=numpy.float32)
    fZ = numpy.array([ D[step*i][9*j+9] for j in range(M) ], dtype=numpy.float32)

    g_3d.set_data(pX, pY)
    g_3d.set_3d_properties(pZ)
    ax_3d.view_init(elev=20. + 2. * numpy.sin(i/300.), azim=i/50.)

    g_pxy.set_data(pX,pY)
    g_pxz.set_data(pX,pZ)
    g_pyz.set_data(pY,pZ)

    g_vxy.set_data(vX,vY)
    g_vxz.set_data(vX,vZ)
    g_vyz.set_data(vY,vZ)

    g_fxy.set_data(fX,fY)
    g_fxz.set_data(fX,fZ)
    g_fyz.set_data(fY,fZ)

    return g_3d

anim = matplotlib.animation.FuncAnimation(fig, animate, frames=N, interval=100)
anim.save(sys.argv[2], writer=matplotlib.animation.FFMpegWriter(fps=10))

