#!/usr/bin/python
import sys
import numpy as np
import matplotlib.pyplot as plt
import os.path as path


if len(sys.argv) < 2 or not sys.argv[1].endswith('.npy'):
	print(sys.argv)
	print('a .npy file must be given as argument.')
	exit(1)

a = np.load(sys.argv[1]) # .npy file
n = int(sys.argv[2]) if len(sys.argv) >= 3 else -1
dir = sys.argv[3] if len(sys.argv) >= 4 else 'img'
axes = plt.axes()
axes.xaxis.set_visible(False)
axes.yaxis.set_visible(False)

# Color
img = np.average(a[:n,:,:,:3], axis=0)
plt.imsave(path.join(dir, '01-color.png'), np.clip(img, 0, 1))

# Normal
img = np.average(a[:n,:,:,3:6], axis=0)
plt.imsave(path.join(dir, '02-normal.png'), (np.clip(img, -1, 1) + 1)/ 2)

# Distance
img = np.average(-np.clip(a[:n,:,:,6], 0, 50), axis=0)
plt.imsave(path.join(dir, '03-dist.png'), img, cmap='Greys_r')

# Sec Distance
img = np.average(-np.clip(a[:n,:,:,7], 0, 50), axis=0)
plt.imsave(path.join(dir, '04-dist2.png'), img, cmap='Greys_r')

# Mat rgb
img = np.average(a[:n,:,:,8:11], axis=0)
plt.imsave(path.join(dir, '05-matcolor.png'), img)

# Mat ka
img = np.average(a[:n,:,:,11], axis=0)
plt.imsave(path.join(dir, '06-matka.png'), img, cmap='Greys_r')

# Mat kd
img = np.average(a[:n,:,:,12], axis=0)
plt.imsave(path.join(dir, '07-matkd.png'), img, cmap='Greys_r')

# Mat ks
img = np.average(a[:n,:,:,13], axis=0)
plt.imsave(path.join(dir, '08-matks.png'), img, cmap='Greys_r')

# Mat kt
img = np.average(a[:n,:,:,14], axis=0)
plt.imsave(path.join(dir, '09-matkt.png'), img, cmap='Greys_r')

# Mat n
img = np.average(np.clip(a[:n,:,:,15], 0, 50), axis=0)
plt.imsave(path.join(dir, '10-matn.png'), img, cmap='Greys_r')

# Mat ir
img = np.average(np.clip(a[:n,:,:,16], 0, 50), axis=0)
plt.imsave(path.join(dir, '11-matir.png'), img, cmap='Greys_r')

# Mat is emissive
img = np.average(np.clip(a[:n,:,:,17], 0, 50), axis=0)
plt.imsave(path.join(dir, '12-matemissive.png'), img, cmap='Greys_r')

# Scene is emissive
img = np.average(np.clip(a[:n,:,:,18], 0, 50), axis=0)
plt.imsave(path.join(dir, '13-ispositive.png'), img, cmap='Greys_r')

# Mat ka, kd, ks
img = np.average(a[:n,:,:,11:14], axis=0)
plt.imsave(path.join(dir, '06-08-matkakdks.png'), img)
