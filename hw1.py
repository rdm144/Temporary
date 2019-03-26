#!/usr/bin/python
import numpy
import pandas
from keras.models import Sequential
from keras.layers import Dense
from keras.wrappers.scikit_learn import KerasRegressor
from sklearn.model_selection import cross_val_score
from sklearn.model_selection import KFold
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import Pipeline

# load dataset
dataframe = pandas.read_csv("ENB2012_data.csv", delimiter=',', header=None)
dataset = dataframe.values
# split into input (X) and output (Y) variables
X = dataset[:,0:7]
Y1 = dataset[:,8]
Y2 = dataset[:,9]
print("End!")