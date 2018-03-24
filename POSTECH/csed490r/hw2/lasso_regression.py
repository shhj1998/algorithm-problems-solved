import pandas as pd
import numpy as np
import numpy.linalg as lin
import matplotlib.pyplot as plt

def lasso(X, y, w, lmb):
    feature = X[0].size
    for d in range(feature):
        alpha = 0
        beta = 0
        for n in range(97) :
            alpha = alpha + X[n, d] * X[n, d]
        for n in range(97) :
            beta_sum = 0
            for k in range(feature) :
                if k == d :
                    continue
                beta_sum = beta_sum + X[n, k] * w[k, 0]

            beta = beta + (y[n, 0] - beta_sum) * X[n, d]

        if beta < -lmb :
            w[d, 0] = (beta + lmb) / alpha
        elif beta > lmb :
            w[d, 0] = (beta - lmb) / alpha
        else :
            w[d, 0] = 0

    return w

dataset = np.array(pd.read_csv('prostate.csv', sep = '\t'))
X = np.matrix(pd.DataFrame(dataset[:, 1:9]))
y = np.matrix(pd.DataFrame(dataset[:, 9]))
w_initial = np.dot(X.T, X)
w_initial = w_initial.astype(np.float32)
w_initial = np.dot(lin.inv(w_initial), np.dot(X.T, y))
w = []
x_range = range(1000)

for i in x_range :
    result = w_initial
    while True :
        check = lasso(X, y, result, i)
        conv = 0
        for j in range(8) :
            conv = conv + pow(check[j, 0] - result[j, 0], 2)
        conv = pow(conv, 0.5)
        if conv < 0.01 :
            break
        result = check
    put = []
    for i in range(8):
        put.append(result[i, 0])
    w.append(put)
w = np.array(w)
graph = plt.gca()
for i in range(X[0].size):
    graph.plot(x_range, w[:, i])
graph.set_xscale("log")
graph.set_xlim(graph.get_xlim()[::-1])
graph.legend(['lcavol', 'lweight', 'age', 'lbph', 'svi', 'lcp', 'gleason', 'pgg45'], loc='upper left')
plt.show()
