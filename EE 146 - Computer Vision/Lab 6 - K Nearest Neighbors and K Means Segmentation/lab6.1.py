import pandas as pd
from matplotlib import pyplot as plt
from sklearn.neighbors import KNeighborsClassifier
import numpy as np
from sklearn import metrics

#Part 1: KNN Classification

#get values of train 1 and 2, show scatterplot
df = pd.read_excel('lab6_2Class_KNN_Data.xls', sheet_name = 0, header=None )

points_x = []
points_y = []
classes = []
len_zero = 0
for index, row in df.iterrows():
    row_values = list(row)
    
    points_x.append(row_values[0])
    points_y.append(row_values[1])
    len_zero += 1
    classes.append(0)

print(len_zero)
df = pd.read_excel('lab6_2Class_KNN_Data.xls', sheet_name = 2, header=None)
len_one = 0

for index, row in df.iterrows():
    row_values = list(row)
    
    points_x.append(row_values[0])
    points_y.append(row_values[1])
    len_one += 1
    classes.append(1)

plt.scatter(points_x,points_y, c=classes)
plt.show()

data = list(zip(points_x, points_y))
knn = KNeighborsClassifier(n_neighbors=5)
knn.fit(data, classes)

#predict first test set
df = pd.read_excel('lab6_2Class_KNN_Data.xls', sheet_name = 1,header=None)

train_zero = []
train_x_zero = []
train_y_zero = []
for index, row in df.iterrows():
    row_values = list(row)
    
    column1_value = row_values[0]
    column2_value = row_values[1]
    train_x_zero.append(column1_value)
    train_y_zero.append(column2_value)

    point = (column1_value, column2_value)
    train_zero.append(point)

prediction0 = knn.predict(train_zero)
print(prediction0)

plt.scatter(points_x,points_y, c=classes)
plt.scatter(train_x_zero,train_y_zero,color = 'r')

for i in range(len(prediction0)):
    x = train_x_zero[i]
    y = train_y_zero[i]
    z = prediction0[i]
    plt.text(x=x, y=y, s=f"c:{z}")

#predict second test set
df = pd.read_excel('lab6_2Class_KNN_Data.xls', sheet_name = 3,header=None)

train_one = []
train_x_one = []
train_y_one = []
for index, row in df.iterrows():
    row_values = list(row)
    
    column1_value = row_values[0]
    column2_value = row_values[1]
    train_x_one.append(column1_value)
    train_y_one.append(column2_value)

    point = (column1_value, column2_value)
    train_one.append(point)

prediction1 = knn.predict(train_one)
print(prediction1)

for i in range(len(prediction1)):
    x = train_x_one[i]
    y = train_y_one[i]
    z = prediction1[i]
    plt.text(x=x, y=y, s=f"c:{z}")

#show results
plt.scatter(points_x,points_y, c=classes)
plt.scatter(train_x_zero,train_y_zero,color = 'r')
plt.scatter(train_x_one,train_y_one,color = 'g')
plt.show()

#calculate accuracy
number = 0
for i in range(len(prediction0)):
    if prediction0[i] != 0:
        number += 1
    if prediction1[i] != 1:
        number += 1

accuracy = 100 - (number/(len(prediction0) * 2))
print("Accuracy:", accuracy, "%")

#get confusion matrix
zero_array = np.zeros((len(prediction0),), dtype=int)
one_array = np.ones((len(prediction1),), dtype=int)
actual = np.concatenate((zero_array, one_array))
zero_array = np.array(prediction0)
one_array = np.array(prediction1)
predicted = np.concatenate((zero_array,one_array))
print(actual)
print(predicted)
confusion_matrix = metrics.confusion_matrix(actual, predicted)

cm_display = metrics.ConfusionMatrixDisplay(confusion_matrix = confusion_matrix, display_labels = [False, True])

cm_display.plot()
plt.show()