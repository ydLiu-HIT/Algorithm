#!/usr/bin/env python
# coding=utf-8
import numpy as np
import math

class Ann:
	def __init__(nn_input_dim,nn_output_dim,nn_hidden_dim):
		self.nn_input_dim = nn_input_dim
		self.nn_output_dim = nn_output_dim
		self.nn_hidden_dim = nn_hidden_dim

	def  calculate_predict(model,traindata):
		w1, b1, w2, b2 = model['w1'], model['b1'],model['w2'],model['b2']
		z1 = x.dot(w1) + b1
		a1 = 1/(1 + np.exp(z1))
		z2 = a1.dot(w2) + b2
		a2 = 1/(1 + np.exp(z2))

		return a2

	def calculate_loss(model):
		w1, b1, w2, b2 = model['w1'], model['b1'],model['w2'],model['b2']
		
