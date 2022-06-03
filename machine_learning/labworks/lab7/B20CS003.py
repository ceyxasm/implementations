# -*- coding: utf-8 -*-
"""lab_7.ipynb



#Question 1
"""

!pip3 install torch==1.2.0+cu92 torchvision==0.4.0+cu92 -f https://download.pytorch.org/whl/torch_stable.html
!pip install pandas
!pip install torch-summary

import torch #python #keras #tensorflow #pytorch
import torch.nn as nn
from torch.autograd import Variable

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt


from sklearn.utils import shuffle
from torchsummary import summary

device = "cuda" if torch.cuda.is_available() else "cpu"
print(f"Using {device} device")

import warnings

def fxn():
  warnings.warn('deprecated', DeprecationWarning)

with warnings.catch_warnings():
  warnings.simplefilter('ignore')
  fxn()

data= pd.read_csv('/content/abalone.data', names=['Sex', 'Length', 'Diameter', 'Heoght', 'Whole Weight', 'Shuckled Weight', 'Viscera Weight', 'Shell Weight', 'Rings'])
print(data.head())
print(data.info())

print( data['Rings'].value_counts())

from sklearn.preprocessing import LabelEncoder
lb_enc= LabelEncoder()

from sklearn.preprocessing import MinMaxScaler
scaler= MinMaxScaler()

drop=[]

for column in data:
  index=0
  for value in data[column]:
    if data[column].dtype=='object' and value.isnumeric()==True :
      drop.append(index)
    if data[column].dtype!='object' and isinstance(value, int)==False and isinstance(value, float)==False:
      drop.append(index)
    index+=1

data= data.drop( drop)

'''label encoding object columns;'''
data['Sex']= lb_enc.fit_transform( data['Sex'])

scaling_feat=[]
for columns in data:
  if columns!='Sex':
    scaling_feat.append( columns)

data[ scaling_feat]= scaler.fit_transform( data[scaling_feat])

'''further we binerize our data as the lest data is in that format'''

rings= np.array( data['Rings'])
from sklearn.preprocessing import KBinsDiscretizer
transform= KBinsDiscretizer( n_bins=3, encode= 'ordinal', strategy= 'uniform')
rings= np.ravel(transform.fit_transform( rings.reshape( len(rings), 1)))

data['Rings']= rings

'''this completes our preprocessing and now we can split the data'''
from sklearn.model_selection import train_test_split
train, test= train_test_split( data, test_size=0.3, random_state= 42)

X_train, y_train= train.iloc[:, :-1].values, train.iloc[:, -1].values
X_test, y_test= test.iloc[:, :-1].values, test.iloc[:, -1].values

def acc( batch_size, rings, logit):
  corrects= (torn.max( logit, 1)[1].view( target.size()).data== taregt.data).sum()
  acc= 100.0*corrects/batch_size
  return acc

'''lets make our model'''

class Network(torch.nn.Module):
    def __init__(self, num_inputs, size_hidden_1, size_hidden_2, n_output):
        super(Network, self).__init__()
        self.hidden_layer_1 = torch.nn.Linear(num_inputs, size_hidden_1)  
        self.activation_1 = torch.nn.Tanh()
        self.hidden_layer_2 = torch.nn.Linear(num_inputs, size_hidden_2)  
        self.activation_2 = torch.nn.Tanh() 
        
        self.output_layer = torch.nn.Linear(size_hidden_1, n_output) 
        self.output_act = torch.nn.Sigmoid()

    def forward(self, x):
        x1 = self.activation_1(self.hidden_layer_1(x)) 
        x2= self.activation_2(self.hidden_layer_2(x))      
        x3 = torch.add(x2,x1)
        res = self.output_act(self.output_layer(x3))    
        return res

batch_size = 32
num_epochs = 500
size_hidden_1 = 500
size_hidden_2 = 500
learning_rate = 0.05
num_classes = 5
batch_count = len(X_train)//batch_size
cols = X_train.shape[1]

net = Network(cols, size_hidden_1, size_hidden_2, num_classes)

optim_ = torch.optim.SGD(net.parameters(), lr=learning_rate)
loss_function = torch.nn.CrossEntropyLoss()

def get_accuracy(logit, target, batch_size):
    corrects = (torch.max(logit, 1)[1].view(target.size()).data == target.data).sum()
    accuracy = 100.0 * corrects/batch_size
    return accuracy.item()

# Commented out IPython magic to ensure Python compatibility.
losess = []
for epoch in range(500):
    X_train,y_train = shuffle(X_train, y_train)
    train_accuracy = 0.0
    run_time_loss = 0.0
    for i in range(batch_count):
        start = i * batch_size
        end = start + batch_size
        inputs = Variable(torch.FloatTensor(X_train[start:end]))
        labels = Variable(torch.LongTensor(y_train[start:end]))
        optim_.zero_grad()
        outputs = net(inputs)
        loss = loss_function(outputs, labels)
        loss.backward()
        optim_.step()
        run_time_loss += loss.item()
        acc = get_accuracy(outputs, labels, batch_size)
        train_accuracy += acc
    losess.append(run_time_loss/(i+1)) 
    print('Epoch: %d | Loss: %.4f | Train Accuracy: %.2f' \
#           %(epoch+1, run_time_loss / (i+1), train_accuracy/(i+1)))  
    run_time_loss = 0.0

epochs_ = range(1,501)
plt.figure(figsize=(10,10)) 
plt.plot(epochs_, losess, 'g', label='Training loss')
plt.title('Training loss vs epochs')
plt.xlabel('Epochs')
plt.ylabel('Loss')
plt.legend()
plt.show()

"""#Question 2

##Subpart a: Preprocess & visualize the data. Create train, val, and test splits
"""

import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

data=pd.read_csv('/content/drive/MyDrive/Colab Notebooks/data_sets/Dry_Bean_Dataset.csv')
data= data[['Area', 'Perimeter', 'MajorAxisLength', 'MinorAxisLength', 'roundness', 'AspectRation', 'ConvexArea', 'Class']]
#dropping un-necessary features

print(data.head())
print(data.info())

data=data.dropna(subset=['Class'])
#droppin datapoint for the corresponding missing class value

from sklearn.preprocessing import OrdinalEncoder
ordinal_encoder = OrdinalEncoder()

class_cat = data[["Class"]]
class_cat_encoded = ordinal_encoder.fit_transform(class_cat)
data['class']= class_cat_encoded.astype(int)
data=data.drop(["Class"], axis=1)
data.info()

'''with our data values available in suitable form and not dire need of scaling,
our data-preprocessing is therefore complete'''

"""###Visualization and drawing insights"""

#for better comparisons, lets plot a scatter matrix

from pandas.plotting import scatter_matrix
attributes = data.columns
scatter_matrix(data[attributes], figsize=(18, 12))

data.hist(bins=50, figsize=(20,15))
plt.show()

'''As we can see that data is skewed, we need to perform stratified sp[lits'''
print('skewness in data features')
print(data.skew())

print('\n\n\ncorrelation bw different features and class')
corr_matrix= data.corr()
print(corr_matrix['class'].sort_values(ascending= False))

"""'Area', 'MinorAisLength' and 'ConvexArea' are the most skewed features and yet their correlation with 'class' is almost similar with slight variation. For our case, we will stratify-fplit based on 'MinorAxisLength'.

> same was attempted but as The least populated class in MinorAxisLength, Area and ConvexArea has only 1 member, which is too few, we attempt this with 'class'
"""

from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler
from sklearn.preprocessing import LabelEncoder
scaler=MinMaxScaler()
label_encoder=LabelEncoder()
X=data.drop(['class'],axis=1)
y=data['class']
X=scaler.fit_transform(X)
y=label_encoder.fit_transform(y)
X_train,X_test,y_train,y_test=train_test_split(X,y,stratify=y,random_state=42)



##This procedure reduces sampling bais

"""##Subpart b: Implementing MLP from Scratch

###Activation functions
"""

def relu(x):
  if x<=0:
    return 0
  else:
    return x

def sigm(x):
  y=  1/(1+ np.exp(-x))  
  return y

def tanh(x):
  y = (np.exp(x)- np.exp(-x))/( np.exp(x) + np.exp(-x))
  return y

def i(x):
  return x

"""###forward propogation"""

class MLP:
  def __init___(self):
    self.network=[]
    self.layer_count= len(self.network)
    self.neuron_count= []
    self.weights= []
    self.biases= []
    self.activations= []


  def dense( self, neuron_count, active='i'):
    self.neuron_count.append( neuron_count)
    layer= np.zeros( (neuron_count, 1), dtype= float)
    self.network.append(layer)
    self.activations.append(active )
    self.layer_count= len(self.network)

  def init(self):
    for i in range(layer_count-1):
      self.biases.append( np.random.rand())
    
    for i in range(1, layer_count):
      matrix= np.random.randn( neuron_count[i], neuron_count[i-1])
      self.weights.append( matrix)

  def forward(self, x):
    self.network[0]= np.array(x)
    for i in range(1, layer_count):
      bias= np.rand()
      biases.append(bias)
      wx_b= np.array(self.weights[i-1] @ self.network[i-1]) + bias

      if activations[i]=='relu':
        self.network[i]= relu(wx_b)
      elif activations[i]== 'tanh':
        self.network[i]= tanh(wx_b)
      elif activation[i]== 'sigm':
        self.network[i]= sigm(wx_b)
      else:
        self.network[i]= i(wx_b)

      return network[self.layer_count-1]

# Initialize a network
from random import seed
from random import random


def init(n_inputs, hiddens, n_outputs,activ): 
  '''hiddens is a list
      where length of list is the number of hidden layer we have
      and value at each index is the number of neurons in that list'''
  network = []
  hidden_layer = [{'weights':[random() for i in range(n_inputs + 1)]} for i in range(hiddens[0] )] #last element in our weights list is actually the bias term
  hidden_layer.append({'activation': activ[0]})
  network.append(hidden_layer)
 
  for i in range(1, len(hiddens) ): # [1 2]:  i=1
    n_count= hiddens[i] #2
    w_count= hiddens[i-1]+1 #2
    hidden_layer=[] 
    for j in range( n_count): 
      weights=[]
      for k in range( w_count): 
        weights.append( random())
      hidden_layer.append({'weights': weights}) #<<<<<<
    hidden_layer.append({'activation':activ[i]})
    network.append( hidden_layer)

    # hidden_layer = [{'weights':[random() for k in range( hiddens[i-1] + 1)]} for j in range(hiddens[i])]
    # network.append( hidden_layer)

  output_layer = [{'weights':[random() for k in range(hiddens[-1] + 1)]} for j in range(n_outputs)]
  output_layer.append({'activation':activ[-1]})
  network.append(output_layer)
  return network
network = init(2, [1, 2], 2,['relu','relu','relu','relu'])
for layer in network:
  print(layer)

##for constant initializations

def init_k(n_inputs, hiddens, n_outputs,activ): 
  '''hiddens is a list
      where length of list is the number of hidden layer we have
      and value at each index is the number of neurons in that list'''
  k= random()
  network = []
  hidden_layer = [{'weights':[k for i in range(n_inputs + 1)]} for i in range(hiddens[0] )] #last element in our weights list is actually the bias term
  hidden_layer.append({'activation': activ[0]})
  network.append(hidden_layer)
 
  for i in range(1, len(hiddens) ): # [1 2]:  i=1
    n_count= hiddens[i] #2
    w_count= hiddens[i-1]+1 #2
    hidden_layer=[] 
    for j in range( n_count): 
      weights=[]
      for k in range( w_count): 
        weights.append( k)
      hidden_layer.append({'weights': weights}) #<<<<<<
    hidden_layer.append({'activation':activ[i]})
    network.append( hidden_layer)

    # hidden_layer = [{'weights':[k for k in range( hiddens[i-1] + 1)]} for j in range(hiddens[i])]
    # network.append( hidden_layer)

  output_layer = [{'weights':[k for k in range(hiddens[-1] + 1)]} for j in range(n_outputs)]
  output_layer.append({'activation':activ[-1]})
  network.append(output_layer)
  return network

##for 0 initialization

def init_zero(n_inputs, hiddens, n_outputs,activ): 
  '''hiddens is a list
      where length of list is the number of hidden layer we have
      and value at each index is the number of neurons in that list'''
  network = []
  hidden_layer = [{'weights':[0 for i in range(n_inputs + 1)]} for i in range(hiddens[0] )] #last element in our weights list is actually the bias term
  hidden_layer.append({'activation': activ[0]})
  network.append(hidden_layer)
 
  for i in range(1, len(hiddens) ): # [1 2]:  i=1
    n_count= hiddens[i] #2
    w_count= hiddens[i-1]+1 #2
    hidden_layer=[] 
    for j in range( n_count): 
      weights=[]
      for k in range( w_count): 
        weights.append( 0)
      hidden_layer.append({'weights': weights}) #<<<<<<
    hidden_layer.append({'activation':activ[i]})
    network.append( hidden_layer)

    # hidden_layer = [{'weights':[0 for k in range( hiddens[i-1] + 1)]} for j in range(hiddens[i])]
    # network.append( hidden_layer)

  output_layer = [{'weights':[0 for k in range(hiddens[-1] + 1)]} for j in range(n_outputs)]
  output_layer.append({'activation':activ[-1]})
  network.append(output_layer)
  return network

#firing of our neuron

def fire(weights, inputs):
  wx_b = weights[-1]
  # print(len(inputs))
  # print(len(weights))
  for i in range(len(weights)-1): ####
    wx_b += weights[i] * inputs[i]
  

  return wx_b

def forward_propagate(network, data):
	input = data
	for layer in network:
		new_input = []
		# print(layer)
		for neuron in layer[:-1]:
			# print(neuron)
			# print(len( neuron['weights']))
			# print(len(input))
			temp = fire( neuron['weights'], input)
			if layer[-1]['activation']=='relu':
				 neuron['output']= relu(temp)
			elif layer[-1]['activation']=='sigmoid':
				 neuron['output']= sigm(temp)
			elif layer[-1]['activation']=='tanh':
				 neuron['output']= tanh(temp)
			else:
				 neuron['output']= temp
			new_input.append(neuron['output'])
		input = new_input
	return input


def fire(weights, inputs):
  wx_b = weights[-1]
  # print(len(inputs))
  # print(len(weights))
  for i in range(len(weights)-1): ####
    wx_b += weights[i] * inputs[i]
  

  return wx_b

  
network= init( 2, [1, 3, 2], 3,['relu','relu','relu','relu','relu'])
output= forward_propagate( network, [2, 4])
print(output)

"""###Backward Propogation"""

def anti_activation(x, activation= 'i'):
  if activation=='relu':
    if x>0:
      return 1
    else: return 0 
  if activation=='tanh':
    return 1-x**2
  if activation=='sigm':
    return x*(1-x)
  else:
    return 1

def back_propagate(network, expected):
  for i in range( len(network)- 1, -1, -1):
    layer, error_layer = network[i], []
		
    if i != len(network)-1: #if it isnt the last layer, calculation of error is not staright forward
      for j in range(len(layer)-1):
        error_neuron = 0.0
        for neuron in network[i + 1][:-1]:
          error_neuron += (neuron['weights'][j] * neuron['delta'])
        error_layer.append(error_neuron)
    else: #if it is the last layer, calculation is rather straihtforward<<<<<<<<<<<<<<<<<<<<<
      for j in range(len(layer)-1):
        neuron = layer[j]
        error_layer.append(-neuron['output'] + expected[j])
    
    for j in range(len(layer)-1):
      neuron = layer[j]
      neuron['delta'] = error_layer[j] * anti_activation(neuron['output'],layer[-1]['activation']) 

network = init(2, [1, 2], 2,['relu','relu','relu','relu'])
expected= [1, 2, 3]

output= forward_propagate( network, [2, 4])
back_propagate( network, expected)
for layer in network:
  print(layer)


def anti_activation(x, activation= 'i'):
  if activation=='relu':
    if x>0:
      return 1
    else: return 0 
  if activation=='tanh':
    return 1-x**2
  if activation=='sigm':
    return x*(1-x)
  else:
    return 1


"""###Training"""

def update( network, feed, l):
  for i in range(len(network)):
    input= feed[: -1]
    if i!=0:
      # print('yes') #<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
      input= [neuron['output'] for neuron in network[i-1][:-1]]
    

    for neuron in network[i][:-1]:
      # print(input)
      # print(neuron['weights'])
      for j in range(len(input)): #1
        neuron['weights'][j]+= l*neuron['delta']*input[j]
      neuron['weights'][-1] += l*neuron['delta']
      # print( neuron['weights'])
      # print('\n\n\n')

def softmax(x):
  y=[]
  for i in x:
    y.append(sigm(i))
  return y

from sklearn.metrics import accuracy_score

def train( network, data, l, epochs, outputs):
	loss_list=[]
	acc_list=[]
	for epoch in range(epochs):
		loss=0
		y_pred=[]
		y_gt=[]
		for input in data:
			input= input.tolist()
			pred = forward_propagate( network, input)
			# print(pred)
			y_pred.append(np.argmax(pred))
			y_gt.append(int(input[-1]))
			pred= softmax(pred)
			output= []

			for i in range( outputs):
				output.append(0)
			output[ int(input[-1])]=1
			#print(pred)

			for i in range(len( pred )):
				loss+= ( pred[i]- output[i])**2
			# print(loss)

			back_propagate( network, output)
			update( network, input, l)
		acc=accuracy_score(y_pred,y_gt)
		loss_list.append(loss)
		acc_list.append(acc)
		print( '>>>>epoch: ', epoch, ', learning rate: ', l, ', accuracy: ',acc)  
	return [loss_list, acc_list ]

#n_input= dataset.shape[1]-1
#n_output= len( np.unique( data['class'] ) )
network= init( 8, [5], 6,['relu','relu','hi'])
metrics=train( network, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 20, 6)

"""###Accuracy"""

def accuracy(network):
  y_pred=[]
  y_gt=[]
  for input in np.hstack([X_test,np.array([y_test]).reshape(-1,1)]):
    input= input.tolist()
    pred = forward_propagate( network, input)
    y_pred.append(np.argmax(pred))
    y_gt.append(int(input[-1]))
  acc=accuracy_score(y_pred,y_gt)
  return acc

"""##Subpart C: experiment with different activation functions

###ReLU
"""

network_relu= init( 8, [5], 6,['relu','relu','hi'])
metrics_relu =train( network_relu, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 20, 6)
acc_relu= accuracy( network_relu)

"""###Sigmoid"""

network_sigm= init( 8, [5], 6,['sigm','sigm','hi'])
metrics_sigm =train( network_sigm, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 20, 6)
acc_sigm= accuracy( network_sigm)

"""###Tanh"""

network_tanh= init( 8, [5], 6,['tanh','tanh','hi'])
metrics_tanh =train( network_tanh, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 20, 6)
acc_tanh= accuracy( network_tanh)

def accuracy(network):
  y_pred=[]
  y_gt=[]
  for input in np.hstack([X_test,np.array([y_test]).reshape(-1,1)]):
    input= input.tolist()
    pred = forward_propagate( network, input)
    y_pred.append(np.argmax(pred))
    y_gt.append(int(input[-1]))
  acc=accuracy_score(y_pred,y_gt)
  return acc

"""###Comparison:"""

plt.plot( metrics_relu[0], label='relu')
plt.plot( metrics_sigm[0], label='sigmoid')
plt.plot( metrics_tanh[0], label='tanh')
plt.xlabel('epochs')
plt.ylabel('loss')
plt.legend()

plt.plot( metrics_relu[1], label='relu')
plt.plot( metrics_sigm[1], label='sigmoid')
plt.plot( metrics_tanh[1], label='tanh')
plt.xlabel('epochs')
plt.ylabel('accuracy')
plt.legend()

print('testing accuracies are: \n')
print('reLU :', acc_relu)
print('Sigmoid :', acc_sigm)
print('Tanh :', acc_tanh)

"""##Subpart d: Weight initializations

###Random initialization
"""

network_random= init( 8, [5], 6,['relu','relu','hi'])
metrics_random =train( network_random, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 50, 6)
acc_random= accuracy( network_random)

"""###Constant Initialization"""

network_k= init_k( 8, [5], 6,['relu','relu','hi'])
metrics_k =train( network_k, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 50, 6)
acc_k= accuracy( network_k)

"""###Zero Initialization"""

network_zero= init_zero( 8, [5], 6,['relu','relu','hi'])
metrics_zero =train( network_zero, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 50, 6)
acc_zero= accuracy( network_zero)

"""###Analysis"""

plt.plot( metrics_random[0], label='random')
plt.plot( metrics_zero[0], label='zero')
plt.plot( metrics_k[0], label='constant')
plt.xlabel('epochs')
plt.ylabel('loss')
plt.legend()

plt.plot( metrics_random[1], label='random')
plt.plot( metrics_zero[1], label='zero')
plt.plot( metrics_k[1], label='constant')
plt.xlabel('epochs')
plt.ylabel('accuracy')
plt.legend()

print('testing accuracies are: \n')
print('random :', acc_random)
print('zero :', acc_zero)
print('constant :', acc_k)

"""##Subpart e: neurons in the layers"""

neuron_count = [1, 3, 5, 8, 15]

metric_list=[]
acc_list=[]
for count in neuron_count:
  network= init( 8, [count], 6,['relu','relu','hi'])
  metrics =train( network, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 20, 6)
  acc= accuracy( network)
  metric_list.append( metrics)
  acc_list.append(acc )

for i in range( len( neuron_count)):
  plt.plot( metric_list[i][0], label= neuron_count[i])
plt.xlabel('epochs')
plt.ylabel('loss')
plt.legend()
plt.show()

for i in range( len( neuron_count)):
  plt.plot( metric_list[i][1], label= neuron_count[i])
plt.xlabel('accuracy')
plt.ylabel('epoch')
plt.legend()
plt.show()

for i in range( len( neuron_count)):
  print(' with ', neuron_count[i], ' test accuracy is :', acc_list[i])

"""##Subpart f: Save and Load network

###Saving our model
"""

import pickle 
model = network
with open('model', 'wb') as f: 
  pickle.dump(model, f)

"""###Loading model"""

my_model= '/content/my_model'
with open(my_model, 'rb') as f: 
  my_model = pickle.load(f)







"""##Subpart C: experiment with different activation functions

###ReLU
"""

network_relu= init( 8, [5], 6,['relu','relu','hi'])
metrics_relu =train( network_relu, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 20, 6)
acc_relu= accuracy( network_relu)

"""###Sigmoid"""

network_sigm= init( 8, [5], 6,['sigm','sigm','hi'])
metrics_sigm =train( network_sigm, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 20, 6)
acc_sigm= accuracy( network_sigm)

"""###Tanh"""

network_tanh= init( 8, [5], 6,['tanh','tanh','hi'])
metrics_tanh =train( network_tanh, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 20, 6)
acc_tanh= accuracy( network_tanh)

def accuracy(network):
  y_pred=[]
  y_gt=[]
  for input in np.hstack([X_test,np.array([y_test]).reshape(-1,1)]):
    input= input.tolist()
    pred = forward_propagate( network, input)
    y_pred.append(np.argmax(pred))
    y_gt.append(int(input[-1]))
  acc=accuracy_score(y_pred,y_gt)
  return acc

"""###Comparison:"""

plt.plot( metrics_relu[0], label='relu')
plt.plot( metrics_sigm[0], label='sigmoid')
plt.plot( metrics_tanh[0], label='tanh')
plt.xlabel('epochs')
plt.ylabel('loss')
plt.legend()

plt.plot( metrics_relu[1], label='relu')
plt.plot( metrics_sigm[1], label='sigmoid')
plt.plot( metrics_tanh[1], label='tanh')
plt.xlabel('epochs')
plt.ylabel('accuracy')
plt.legend()

print('testing accuracies are: \n')
print('reLU :', acc_relu)
print('Sigmoid :', acc_sigm)
print('Tanh :', acc_tanh)

"""##Subpart d: Weight initializations

###Random initialization
"""

network_random= init( 8, [5], 6,['relu','relu','hi'])
metrics_random =train( network_random, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 50, 6)
acc_random= accuracy( network_random)

"""###Constant Initialization"""

network_k= init_k( 8, [5], 6,['relu','relu','hi'])
metrics_k =train( network_k, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 50, 6)
acc_k= accuracy( network_k)

"""###Zero Initialization"""

network_zero= init_zero( 8, [5], 6,['relu','relu','hi'])
metrics_zero =train( network_zero, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 50, 6)
acc_zero= accuracy( network_zero)

"""###Analysis"""

plt.plot( metrics_random[0], label='random')
plt.plot( metrics_zero[0], label='zero')
plt.plot( metrics_k[0], label='constant')
plt.xlabel('epochs')
plt.ylabel('loss')
plt.legend()

plt.plot( metrics_random[1], label='random')
plt.plot( metrics_zero[1], label='zero')
plt.plot( metrics_k[1], label='constant')
plt.xlabel('epochs')
plt.ylabel('accuracy')
plt.legend()

print('testing accuracies are: \n')
print('random :', acc_random)
print('zero :', acc_zero)
print('constant :', acc_k)

"""##Subpart e: neurons in the layers"""

neuron_count = [1, 3, 5, 8, 15]

metric_list=[]
acc_list=[]
for count in neuron_count:
  network= init( 8, [count], 6,['relu','relu','hi'])
  metrics =train( network, np.hstack([X_train,np.array([y_train]).reshape(-1,1)]), 0.01, 20, 6)
  acc= accuracy( network)
  metric_list.append( metrics)
  acc_list.append(acc )

for i in range( len( neuron_count)):
  plt.plot( metric_list[i][0], label= neuron_count[i])
plt.xlabel('epochs')
plt.ylabel('loss')
plt.legend()
plt.show()

for i in range( len( neuron_count)):
  plt.plot( metric_list[i][1], label= neuron_count[i])
plt.xlabel('accuracy')
plt.ylabel('epoch')
plt.legend()
plt.show()

for i in range( len( neuron_count)):
  print(' with ', neuron_count[i], ' test accuracy is :', acc_list[i])

"""##Subpart f: Save and Load network

###Saving our model
"""

import pickle 
model = network
with open('model', 'wb') as f: 
  pickle.dump(model, f)

"""###Loading model"""

my_model= '/content/my_model'
with open(my_model, 'rb') as f: 
  my_model = pickle.load(f)

