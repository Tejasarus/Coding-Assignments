import numpy as np
from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score

iris = datasets.load_iris()
x = iris.data[:, [2, 3]]
y = iris.target

x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.3, random_state=1, stratify=y)
sc = StandardScaler()
sc.fit(x_train)
x_train_std = sc.transform(x_train)
x_test_std = sc.transform(x_test)
model = LogisticRegression(max_iter=1000)
model.fit(x_train_std, y_train)

#predict and print accuracy
y_pred = model.predict(x_test_std)
accuracy = accuracy_score(y_test, y_pred)
print('Accuracy: %.2f' % (accuracy*100))

#print out weights and biases
weights = model.coef_[0]
bias = model.intercept_[0]
print('Separating line 1: %.2f * petal length + %.2f * petal width = %.2f' % (weights[0], weights[1], bias))
weights = model.coef_[1]
bias = model.intercept_[1]
print('Separating line 2: %.2f * petal length + %.2f * petal width = %.2f' % (weights[0], weights[1], bias))