import matplotlib.pyplot as plt
import numpy as np

# Data
cache_sizes = [10, 50, 100, 250, 500]
fifo_faults = [9916, 9515, 9018, 7534, 5130]
lru_faults = [9915, 9510, 9029, 7532, 5207]
second_chance_faults = [9915, 9510, 9022, 7526, 5178]

# Calculating hit rates
fifo_hit_rates = [(10000 - faults) / 10000 for faults in fifo_faults]
lru_hit_rates = [(10000 - faults) / 10000 for faults in lru_faults]
second_chance_hit_rates = [(10000 - faults) / 10000 for faults in second_chance_faults]

# Create bar graph
bar_width = 0.25
index = np.arange(len(cache_sizes))

plt.figure(figsize=(12, 10))

# Bar graph
plt.subplot(2, 1, 1)  # Subplot for bar graph
plt.bar(index, fifo_hit_rates, bar_width, label='FIFO')
plt.bar(index + bar_width, lru_hit_rates, bar_width, label='LRU')
plt.bar(index + 2 * bar_width, second_chance_hit_rates, bar_width, label='Second Chance')

plt.xlabel('Cache Size')
plt.ylabel('Hit Rate')
plt.title('Hit Rates of Page Replacement Algorithms')
plt.xticks(index + bar_width, cache_sizes)
plt.legend()
plt.grid(True)

# Table
plt.subplot(2, 1, 2)  # Subplot for table
plt.axis('off')  # Hide axes

data = [cache_sizes, fifo_hit_rates, lru_hit_rates, second_chance_hit_rates]
columns = ['Cache Size', 'FIFO Hit Rate', 'LRU Hit Rate', 'Second Chance Hit Rate']  # Corrected column labels

# Creating table
table = plt.table(cellText=data, colLabels=columns, loc='center', cellLoc='center', colColours=['lightgray']*4)
table.auto_set_font_size(False)
table.set_fontsize(12)
table.scale(1.5, 1.5)  # Scale table for better readability

plt.tight_layout()
plt.savefig('hit_rates_combined.png')
plt.show()

