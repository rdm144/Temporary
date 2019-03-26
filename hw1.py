#!/usr/bin/env python
import numpy as np
import pandas
from sklearn import metrics
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from matplotlib import pyplot as plt

# load dataset
dataframe = pandas.read_csv("ENB2012_data.csv", delimiter=',', header=None)
dataset = dataframe.values

# split into input (X) and output (Y) variables
X = dataset[:,0:7]
Y1 = dataset[:,8]
Y2 = dataset[:,9]

# split data into training and testing data
xTrain, xTest, yTrain, yTest = train_test_split(X, Y1, test_size = 0.3, random_state = 0)

# Test the algorithm
lm = LinearRegression()
lm.fit(xTrain, yTrain)
yPred = lm.predict(xTest)

# Get info about algorithm test
print('Mean Absolute Error:', metrics.mean_absolute_error(yTest, yPred))
print('Mean Squared Error:', metrics.mean_squared_error(yTest, yPred))  
print('Root Mean Squared Error:', np.sqrt(metrics.mean_squared_error(yTest, yPred)))
print('Score:', lm.score(xTest, yTest))

# plot values
plt.scatter(yTest, yPred)
plt.xlabel("Actual Values")
plt.ylabel("Predicted Values")
plt.show()
