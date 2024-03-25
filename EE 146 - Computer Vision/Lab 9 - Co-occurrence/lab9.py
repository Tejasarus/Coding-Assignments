import cv2
import numpy as np
from skimage.feature import graycomatrix, graycoprops
from skimage import data
import matplotlib.pyplot as plt
from numpy import asarray
from PIL import Image
import math
from skimage.io import imread


def co_occurrence(filename,m):
    img = imread(filename)
    #print(img)
    #img = Image.open(filename)
    
    frobenius_norm = np.linalg.norm(img, 'fro')
    arr = img / frobenius_norm
    
    new_arr = ((arr - arr.min()) * (1/(arr.max() - arr.min()) * 255)).astype('uint8')
    #print(new_arr)
    numpydata = asarray(img)
    c = math.sqrt((m[0]**2) + (m[1]**2))
    g = graycomatrix(img, [c], [math.tan(m[1]/m[0])], levels=255,normed=True, symmetric=True)
    

    energy = graycoprops(g,'energy')
    contrast = graycoprops(g, 'contrast')
    correlation = graycoprops(g, 'correlation')
    mask = np.ma.masked_equal(g / np.sum(g), 0)
    entropy = -np.sum(mask * np.log(mask))

    #print(g)
    print(m)
    print("energy:", energy)
    print("contrast:",contrast)
    print("correlation:",correlation)
    print("Entropy:", entropy)
    print("")

    g_reshaped = np.squeeze(g)
    plt.imshow(g_reshaped, cmap='gray')
    plt.title('Co-occurrence Matrix')
    plt.colorbar()
    plt.show()

co_occurrence('rice.png',[1,2])
co_occurrence('rice.png',[2,2])
co_occurrence('rice.png',[2,3])