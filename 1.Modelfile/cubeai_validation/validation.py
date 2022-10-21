import numpy as np




test_x = np.load('../model/testData.npy')
test_x = test_x.reshape(len(test_x), 90*3)

# test_x = test_x[0:50]
np.savetxt("testx_cubeai.csv", test_x, delimiter=",")

test_y = np.load('../model/groundTruth.npy')
# test_y = test_y[0:50]
np.savetxt("testy_cubeai.csv", test_y, delimiter=",")