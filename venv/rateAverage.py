file_path = 'E:\\tmp\\groupMessage\\Group70\\rateCache.txt'

# Variables to calculate the sum and count of rates
rate_sum = 0
rate_count = 0

# Open the file for reading
with open(file_path, 'r') as file:
    # Read each line in the file
    for line in file:
        # Split the line into key-value pairs
        pairs = line.strip().split(' ')

        # Create a dictionary to store the data
        data = {}

        # Parse each key-value pair and store it in the dictionary
        for pair in pairs:
            key, value = pair.split(':')
            data[key.strip()] = value.strip()

        # Access the values using the keys
        group_id = int(data['groupID'])
        rate = float(data['rate'])
 
        # Check if groupID is between 7 and 17
        if 0 <= group_id < 71:
            # Add the rate to the sum and increment the count
            rate_sum += rate
            rate_count += 1

# Calculate the average rate
average_rate = rate_sum / rate_count if rate_count > 0 else 0

print(f"The average rate for all groups : {average_rate}")
