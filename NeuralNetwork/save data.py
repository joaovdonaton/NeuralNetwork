from keras.datasets import mnist
import numpy as np

(x_train, y_train), (x_test, y_test) = mnist.load_data()

with open('x_test.txt', 'r') as f:
    print(f.read())

# with open("x_test.txt", 'w') as f:
#     for i in range(5000):
#         flat = x_test[i].flatten()
#         for j in range(flat.shape[0]): 
#             f.write(str(flat[j])+" ")
#         f.write('\n')

# with open("y_test.txt", 'w') as f:
#     for i in range(5000):
#         f.write(str(y_test[i])+'\n')