from keras.datasets import mnist, fashion_mnist
import numpy as np

#(x_train, y_train), (x_test, y_test) = mnist.load_data()

(x_train, y_train), (x_test, y_test) = fashion_mnist.load_data()

#with open('x_test.txt', 'r') as f:
#    print(f.read())

with open("x_train.txt", 'w') as f:
    for i in range(30000):
        flat = x_train[i].flatten()
        for j in range(flat.shape[0]): 
            f.write(str(flat[j])+" ")
        f.write('\n')

with open("y_train.txt", 'w') as f:
    for i in range(30000):
        f.write(str(y_train[i])+'\n')