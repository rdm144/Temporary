#!/usr/bin/env python
import numpy as np
import pandas
from sklearn import metrics
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from matplotlib import pyplot as plt
from sklearn.linear_model import LogisticRegression
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import cross_val_predict
from sklearn.model_selection import KFold

# load dataset
dataframe = pandas.read_csv("ENB2012_data.csv", delimiter=',', header=None)
dataset = dataframe.values

# split into input (X) and output (Y) variables
X = dataset[:,0:8]
Y1 = dataset[:,8]
Y2 = dataset[:,9]

# split data into training and testing data
xTrain, xTest, yTrain, yTest = train_test_split(X, Y1, test_size = 0.3, random_state = 0)

# Test the algorithm
l1 = LinearRegression()
l1.fit(xTrain, yTrain)
yPred = l1.predict(xTest)

# Get info about algorithm test
print('------------Linear Regression Y1-----------')
print('Mean Absolute Error:', metrics.mean_absolute_error(yTest, yPred))
print('Mean Squared Error:', metrics.mean_squared_error(yTest, yPred))  
print('Root Mean Squared Error:', np.sqrt(metrics.mean_squared_error(yTest, yPred)))
print('Variance:', l1.score(xTest, yTest))

# plot values
plt.scatter(yTest, yPred)
plt.xlabel("Actual Y1")
plt.ylabel("Predicted Y1")
plt.title('Linear Regression:\nPredictied versus actual Y1 values')
plt.show()

# cross validation
print('Cross validation scores:', cross_val_score(l1, X, Y1, cv= 4))
k = KFold(n_splits = 4, random_state = None, shuffle = True)
crossPred = cross_val_predict(l1, X, Y1, cv = 4)
print('R^2 regression score:', metrics.r2_score(Y1, crossPred))
plt.scatter(Y1, crossPred)
plt.xlabel('Actual Y1')
plt.ylabel('Predicted Y1')
plt.title('Linear Regression:\nPredicted versus actual Y1 with 4-fold cross validation')
plt.show()

#####

# split data into training and testing data
xTrain, xTest, y2Train, y2Test = train_test_split(X, Y2, test_size = 0.3, random_state = 0)

# Test the algorithm
l1 = LinearRegression()
l1.fit(xTrain, y2Train)
y2Pred = l1.predict(xTest)

# Get info about algorithm test
print('------------Linear Regression Y2-----------')
print('Mean Absolute Error:', metrics.mean_absolute_error(y2Test, y2Pred))
print('Mean Squared Error:', metrics.mean_squared_error(y2Test, y2Pred))  
print('Root Mean Squared Error:', np.sqrt(metrics.mean_squared_error(y2Test, y2Pred)))
print('Variance:', l1.score(xTest, y2Test))

# plot values
plt.scatter(y2Test, y2Pred)
plt.xlabel("Actual Y2")
plt.ylabel("Predicted Y2")
plt.title('Linear Regression:\nPredictied versus actual Y2 values')
plt.show()

# cross validation
print('Cross validation scores:', cross_val_score(l1, X, Y2, cv= 4))
k = KFold(n_splits = 4, random_state = None, shuffle = True)
crossPred = cross_val_predict(l1, X, Y2, cv = 4)
print('R^2 regression score:', metrics.r2_score(Y2, crossPred))
plt.scatter(Y2, crossPred)
plt.xlabel('Actual Y2')
plt.ylabel('Predicted Y2')
plt.title('Linear Regression:\nPredicted versus actual Y2 with 4-fold cross validation')
plt.show()

#####################################################################

# split data into training and testing data
Y1 = [(10*round(x/10)) for x in Y1]
xTrain, xTest, yTrain, yTest = train_test_split(X, Y1, test_size = 0.3, random_state = 0)

# Test the algorithm
l1 = LogisticRegression(solver='liblinear', max_iter=100, multi_class='auto')
l1.fit(xTrain, yTrain)
yPred = l1.predict(xTest)

# Get info about algorithm test
print('------------Logistic Regression Y1-----------')
print('Mean Absolute Error:', metrics.mean_absolute_error(yTest, yPred))
print('Mean Squared Error:', metrics.mean_squared_error(yTest, yPred))  
print('Root Mean Squared Error:', np.sqrt(metrics.mean_squared_error(yTest, yPred)))
print('Variance:', l1.score(xTest, yTest))

# plot values
plt.scatter(yTest, yPred)
plt.xlabel("Actual Y1")
plt.ylabel("Predicted Y1")
plt.title('Logistic Regression:\nPredictied versus actual Y1 values')
plt.show()

# cross validation
print('Cross validation scores:', cross_val_score(l1, X, Y1, cv= 4))
k = KFold(n_splits = 4, random_state = None, shuffle = True)
crossPred = cross_val_predict(l1, X, Y1, cv = 4)
print('R^2 regression score:', metrics.r2_score(Y1, crossPred))
plt.scatter(Y1, crossPred)
plt.xlabel('Actual Y1')
plt.ylabel('Predicted Y1')
plt.title('Logistic Regression:\nPredicted versus actual Y1 with 4-fold cross validation')
plt.show()

#####

# split data into training and testing data
Y2 = [(10*round(x/10)) for x in Y2]
xTrain, xTest, yTrain, yTest = train_test_split(X, Y2, test_size = 0.3, random_state = 0)

# Test the algorithm
l1 = LogisticRegression(solver='liblinear', max_iter=100, multi_class='auto')
l1.fit(xTrain, yTrain)
yPred = l1.predict(xTest)

# Get info about algorithm test
print('------------Logistic Regression Y2-----------')
print('Mean Absolute Error:', metrics.mean_absolute_error(yTest, yPred))
print('Mean Squared Error:', metrics.mean_squared_error(yTest, yPred))  
print('Root Mean Squared Error:', np.sqrt(metrics.mean_squared_error(yTest, yPred)))
print('Variance:', l1.score(xTest, yTest))

# plot values
plt.scatter(yTest, yPred)
plt.xlabel("Actual Y2")
plt.ylabel("Predicted Y2")
plt.title('Logistic Regression:\nPredictied versus actual Y2 values')
plt.show()

# cross validation
print('Cross validation scores:', cross_val_score(l1, X, Y2, cv= 4))
k = KFold(n_splits = 4, random_state = None, shuffle = True)
crossPred = cross_val_predict(l1, X, Y2, cv = 4)
print('R^2 regression score:', metrics.r2_score(Y2, crossPred))
plt.scatter(Y2, crossPred)
plt.xlabel('Actual Y2')
plt.ylabel('Predicted Y2')
plt.title('Logistic Regression:\nPredicted versus actual Y2 with 4-fold cross validation')
plt.show()
