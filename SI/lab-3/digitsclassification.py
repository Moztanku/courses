import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

path = r'/home/most/Dokumenty/mnist/'
files = os.listdir(path)

print("Number of files: {}".format(len(files)))
images = np.ndarray(shape=(len(files), 48, 48), dtype=np.uint8)

for i in range(len(files)):
    print("Loading file: {}".format(files[i]))
    images[i] = cv2.resize(cv2.imread(path + files[i], 0), (48, 48))

f, ax = plt.subplots(6, 5, figsize=(10, 10))
for i in range(images.shape[0]):
    print("Creating subplot: {}".format(i))
    x = i // 5
    y = i % 5
    ax[x, y].imshow(images[i], cmap='gray')
    ax[x, y].axis('off')

# Remove space between subplots
plt.subplots_adjust(wspace=0, hspace=0)
# Set background color to black
f.patch.set_facecolor('black')
plt.show()
