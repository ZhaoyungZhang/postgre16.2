import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv('tpcc-origin.csv')

plt.figure(figsize=(12, 6))

plt.plot(data['Time (seconds)'], data['Throughput (requests/second)'], marker='o', linestyle='-', color='b')

plt.title('Real-time Throughput Over Time')
plt.xlabel('Time (seconds)')
plt.ylabel('Throughput (requests/second)')

plt.grid(True)
plt.legend(['Throughput'])
plt.show()

# store in local
plt.savefig('tpcc_2024-05-08_09-19-16.samples.png')
