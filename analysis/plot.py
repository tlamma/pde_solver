from simulation_results import results
import numpy as np
import matplotlib.pyplot as plt

data = results.states
frame_time = np.arange(data.shape[0]) * results.TIME_STEP * results.N_STEPS_PER_FRAME   
plt.figure()
plt.plot(frame_time, data[:, 0], label='x')
plt.plot(frame_time, data[:, 1], label='y')
plt.xlabel('Time')
plt.ylabel('Value')
plt.legend()
plt.show()

plt.figure()
plt.scatter(data[:, 0], data[:, 1])
plt.xlabel('x')
plt.ylabel('y')
plt.show()
