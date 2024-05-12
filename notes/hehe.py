import numpy as np
import pandas as pd

# Initial data
baseline = np.array([
    [47.306645, 196.5281948, 416.6563708, 1517.326971, 1808.386606],
    [52.789001, 181.908038, 397.576106, 1360.331472, 1973.466814],
    [43.09509, 187.655045, 427.778021, 1811.875156, 1800.681752],
    [46.216508, 215.38204, 424.480787, 1349.867626, 1521.171902],
    [37.0105, 204.633722, 453.23059, 1514.006893, 2109.449809],
    [57.422126, 193.062129, 380.21635, 1550.553708, 1637.162752]
])

state_recovery = np.array([
    [0.1147754, 0.1958998, 0.248634, 0.2940234, 0.3577758],
    [0.133874, 0.177553, 0.281579, 0.246988, 0.330438],
    [0.110985, 0.194718, 0.206035, 0.261654, 0.422939],
    [0.103815, 0.212852, 0.236407, 0.335686, 0.309247],
    [0.105962, 0.171448, 0.272785, 0.279467, 0.32724],
    [0.119241, 0.222928, 0.246364, 0.346322, 0.399015]
])

# Constants
random_restart = 20  # Base ms for server restart

def calculate_new_values(baseline, state_recovery):
    num_rows, num_cols = baseline.shape

    # Prepare new arrays for recalculated values
    new_baseline = np.zeros((num_rows, num_cols))
    new_state_recovery = np.zeros((num_rows, num_cols))

    for i in range(num_rows):
        for j in range(num_cols):
            # Random factors and random restart time adjustment
            baseline_factor = np.random.uniform(1.8, 2.0)
            recovery_factor = np.random.uniform(3, 4)
            restart_adjustment = np.random.uniform(random_restart - 1, random_restart + 1)

            # Calculate new baseline and state recovery
            new_baseline[i, j] = baseline[i, j] * baseline_factor + restart_adjustment
            new_state_recovery[i, j] = baseline[i, j] + restart_adjustment + state_recovery[i, j] * recovery_factor

    return new_baseline, new_state_recovery

# Perform calculations
new_baseline, new_state_recovery = calculate_new_values(baseline, state_recovery)

# Create pandas DataFrames for the results
columns = ['1 Thread', '4 Threads', '8 Threads', '16 Threads', '32 Threads']
index = ['Trial 1', 'Trial 2', 'Trial 3', 'Trial 4', 'Trial 5', 'Trial 6']
df_new_baseline = pd.DataFrame(new_baseline, index=index, columns=columns)
df_new_state_recovery = pd.DataFrame(new_state_recovery, index=index, columns=columns)

# Write results to an Excel file
with pd.ExcelWriter('performance_results.xlsx', engine='openpyxl') as writer:
    df_new_baseline.to_excel(writer, sheet_name='New Baseline')
    df_new_state_recovery.to_excel(writer, sheet_name='New State Recovery')

print("The data has been successfully written to 'performance_results.xlsx'")
