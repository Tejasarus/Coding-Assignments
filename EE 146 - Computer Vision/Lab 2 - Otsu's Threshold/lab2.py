import cv2
import numpy as np
from matplotlib import pyplot as plt
import argparse

def Otsu(file_name):
    #grayscale image
    image = cv2.imread(file_name)
    grayscale = cv2.cvtColor(image,cv2.COLOR_BGR2GRAY)

    #get histogram
    histogram = cv2.calcHist([grayscale], [0], None, [256], [0, 256])

    #for between class variance
    b = []
    #mean tables
    k = len(histogram)
    u0 = {}
    u1 = {}
    n0 = 0
    s0 = 0

    for q in range(k):
        n0 += histogram[q]
        s0 += q*histogram[q]
        if n0 > 0:
            u0[q] = s0/n0
        else:
            u0[q] = -1

    N = n0
    n1 = 0
    s1 = 0
    u1[k-1] = 0

    for q in range(k - 2, -1, -1):
        n1 += histogram[q+1]
        s1 += (q+1)*histogram[q+1]
        if n1 > 0:
            u1[q] = s1/n1
        else:
            u1[q] = -1

    #rest of otsu
    o2_max = 0
    q_max = -1
    n0 = 0

    for q in range(k-2):
        n0 += histogram[q]
        n1 = N - n0
        if n0 > 0 and n1 > 0:
            o2_b = (1/(N ** 2)) * n0 * n1 * ((u0[q] - u1[q])**2)
            b.append(o2_b)
            if o2_b > o2_max:
                o2_max = o2_b
                q_max = q
        else:
            b.append(np.array([0], dtype=np.float32))

    ret, result = cv2.threshold(grayscale, q_max, 255, 0)
    foreground = np.cumsum(histogram)
    background = np.cumsum(histogram[::-1])[::-1]
    #show images
    cv2.imshow(file_name + ' Grayscale',grayscale)
    cv2.imshow(file_name + " threshold",result)

    #show histogram
    plt.plot(histogram, color='k',label = 'original histogram')
    plt.plot(b,color='r',label='between class variance')
    plt.plot(np.array(list(u0)),color='g',label='foreground variance')
    plt.plot(np.array(list(u1)),color='b',label='background variance')
    plt.title(file_name + " Histograms")
    plt.legend() 
    plt.show()

    #destroy the windows at key press
    cv2.waitKey(0)
    cv2.destroyAllWindows()

Otsu("textured1.png")
Otsu("texture2.jpeg")
Otsu("nontextured1.png")
Otsu("nontextured2.webp")