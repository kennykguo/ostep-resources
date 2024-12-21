import matplotlib.pyplot as plt
import csv

# Read data from the output file
page_sizes = []
times = []
with open('performance_data.csv', 'r') as file:
    reader = csv.reader(file)
    next(reader)  # Skip the header
    for row in reader:
        page_sizes.append(int(row[0]))
        times.append(float(row[1]))

# Create the plot
plt.figure(figsize=(10, 6))
plt.plot(page_sizes, times, marker='o')
plt.xscale('log')  # Logarithmic scale for x-axis
plt.yscale('log')  # Logarithmic scale for y-axis
plt.title('Page Size vs. Access Time')
plt.xlabel('Page Size (bytes)')
plt.ylabel('Elapsed Time (seconds)')
plt.grid(True, which="both", linestyle='--', linewidth=0.5)
plt.savefig('performance_plot.png')  # Save the plot
plt.show()
