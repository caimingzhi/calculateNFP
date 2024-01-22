import matplotlib.pyplot as plt

# Read the data from the file
with open('D:\workFile\levyDistribution.txt', 'r') as file:
    data = [float(line.strip()) for line in file]

# Create a plot
plt.plot(data)
plt.title('Data Plot')
plt.xlabel('Data Point Index')
plt.ylabel('Value')
plt.grid(True)

# Display the plot
plt.show()
