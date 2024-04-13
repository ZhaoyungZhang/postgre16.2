import matplotlib.pyplot as plt
import numpy as np

# Simulated data
thread_counts = ['1 Thread', '4 Threads', '8 Threads', '16 Threads', '32 Threads']
baseline_times = [
    np.mean([47.306645, 52.789001, 43.09509, 46.216508, 37.0105, 57.422126]),
    np.mean([196.5281948, 181.908038, 187.655045, 215.38204, 204.633722, 193.062129]),
    np.mean([416.6563708, 397.576106, 427.778021, 424.480787, 453.23059, 380.21635]),
    np.mean([1517.326971, 1360.331472, 1811.875156, 1349.867626, 1514.006893, 1550.553708]),
    np.mean([1808.386606, 1973.466814, 1800.681752, 1521.171902, 2109.449809, 1637.162752])
]
recovery_times = [
    np.mean([0.1147754, 0.133874, 0.110985, 0.103815, 0.105962, 0.119241]),
    np.mean([0.1958998, 0.177553, 0.194718, 0.212852, 0.171448, 0.222928]),
    np.mean([0.248634, 0.281579, 0.206035, 0.236407, 0.272785, 0.246364]),
    np.mean([0.2940234, 0.246988, 0.261654, 0.335686, 0.279467, 0.346322]),
    np.mean([0.3577758, 0.330438, 0.422939, 0.309247, 0.32724, 0.399015])
]


# Create figure and axis
fig, ax1 = plt.subplots()

# Plot baseline times
ax1.set_xlabel('Number of Threads')
ax1.set_ylabel('Baseline Time (ms)', color='tab:blue')
ax1.plot(thread_counts, baseline_times, color='tab:blue', marker='o', label='Baseline Time')
ax1.tick_params(axis='y', labelcolor='tab:blue')

# Create another axis for recovery times sharing the same x-axis
ax2 = ax1.twinx()
ax2.set_ylabel('State Recovery Time (ms)', color='tab:red')
ax2.plot(thread_counts, recovery_times, color='tab:red', marker='o', label='State Recovery Time')
ax2.tick_params(axis='y', labelcolor='tab:red')

# Set legends
ax1.legend(loc='upper left')
ax2.legend(loc='upper right')

# Set the title
plt.title('Baseline and State Recovery Times')

# Display the plot
plt.savefig('my_plot.png')
