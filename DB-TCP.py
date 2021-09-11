# -*- coding: utf-8 -*-
"""DB-TCP.ipynb

Automatically generated by Colaboratory.

Original file is located at
    https://colab.research.google.com/drive/1SqQpabNkEbgCZ8JN0ILjQDTf6R1feB0p
"""

import tensorflow as tf
from tensorflow import keras
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import os
from google.colab import files 
print(tf.__version__)

!pip install -q pyyaml h5py

uoloaded=files.upload()

training_set = pd.read_csv('input.txt', delim_whitespace=True)

training_eval = pd.read_csv('eval_input.txt', delim_whitespace=True)

print(training_set.head())

print(training_eval.head())

column=training_set["diff"]
print(column.max())
print(column.min())
column=column/1759
print(column[100])

column1=training_eval["diff"]
print(column1.max())
print(column1.min())
column1=column1/1759
print(column1[100])

training_set["diff"]=column
print(training_set)

training_eval["diff"]=column1
print(training_eval)

training_output=training_set.pop("output")

training_eval_output=training_eval.pop("output")

training_input=training_set

training_eval_input=training_eval

print(training_output)
print(training_input)

print(training_eval_output)
print(training_eval_input)

training_input.rtt.hist(bins=20)

training_input.tmp.hist(bins=20)

training_input.targetedvscwnd.hist(bins=20)

training_x=np.array(training_input)
training_y=np.array(training_output)


training_eval_x=np.array(training_eval_input)
training_eval_y=np.array(training_eval_output)

print(training_x.shape)
print(training_y.shape)


print(training_eval_x.shape)
print(training_eval_y.shape

training_x=training_x.reshape(len(training_x),5,1)
training_y=training_y.reshape(len(training_y))

print(training_x.shape)
print(training_y.shape)


training_eval_x=training_eval_x.reshape(len(training_eval_x),5,1)
training_eval_y=training_eval_y.reshape(len(training_eval_y))

print(training_eval_x.shape)
print(training_eval_y.shape

model=tf.keras.Sequential([
    tf.keras.layers.Flatten(input_shape=(5, 1)),
      tf.keras.layers.Dense(20, activation='relu', kernel_initializer=keras.initializers.GlorotNormal()),
      keras.layers.Dropout(rate=0.2),
      tf.keras.layers.Dense(25, activation='relu',  kernel_initializer=keras.initializers.GlorotNormal()),
      keras.layers.Dropout(rate=0.2),
      tf.keras.layers.Dense(20, activation='relu',  kernel_initializer=keras.initializers.GlorotNormal()),
      keras.layers.Dropout(rate=0.2),
      tf.keras.layers.Dense(3,activation='softmax' ), 
  ])
 
 model.compile(
      loss='sparse_categorical_crossentropy',
      optimizer='adam',
      metrics='accuracy')

model.fit(training_x,training_y,epochs=987)
          #,   callbacks=[callbacks])
model.save('DTCP')

model.evaluate(training_eval_x,training_eval_y)

model.layers[4].weights

print(model.trainable_variables)

x=np.array([0.0540525,	0.407113,	0.2552,	931	,0.0754249	])
x=x.reshape(1,5,1)
print(model.predict(x))
print(np.argmax(model.predict(x)))