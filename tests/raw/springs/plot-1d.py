
import sys

import matplotlib.pyplot as plt

with open(sys.argv[1],'r') as F:
    D = list(map(lambda l: list(map(lambda x: float(x) if x != "" else x, l.split('\n')[0].split(','))), F.readlines()[1:]))

D = list(zip(*D))

(fig, axs) = plt.subplots(3,figsize=(18,12))

fig.suptitle('Springs 1D')

for i in range(int((len(D)-2)/3)):
    axs[0].plot(D[0], D[1+3*i], label='X[{}]'.format(i))
    axs[1].plot(D[0], D[2+3*i], label='V[{}]'.format(i))
    axs[2].plot(D[0], D[3+3*i], label='F[{}]'.format(i))

axs[0].set_xticks([])
axs[0].set_yticks([])
axs[1].set_xticks([])
axs[1].set_yticks([])
axs[2].set_xticks(range(int(D[0][- 1])))
axs[2].set_yticks([])

#plt.legend()

fig.savefig(sys.argv[2], dpi=180)

