import pandas as pd
from matplotlib import pyplot as plt
from sklearn.neighbors import KNeighborsClassifier
import numpy as np
from sklearn import metrics

points_x = [3.56,4.12,2.85,5.19,4.32,1.14,0.73,1.07,6.16,6.12,6.18,6.19,6.08]
points_y = [2.33,4.29,5.2,3.96,4.17,0.28,0.58,0.91,8.09,8.15,8.14,8.18,8.19]
classes = [1,1,1,1,1,2,2,2,3,3,3,3,3]

data = list(zip(points_x, points_y))
knn = KNeighborsClassifier(n_neighbors=3)
knn.fit(data, classes)

point = [(0.5, 0.5),(3.5,4.5),(6,7)]
prediction = knn.predict(point)
print(prediction)