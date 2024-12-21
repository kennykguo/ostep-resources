#!/bin/bash

# Parameters
EXECUTABLE="./tlb"            # Path to your compiled program
OUTPUT_FILE="performance_data.csv"  # Output file for results
TRIALS=100                    # Fixed number of trials for reliable measurements
TOTAL_MEMORY=10000            # Total memory size (constant, bytes)
MAX_PAGES=$((TOTAL_MEMORY / 4)) # Maximum pages (4 bytes per int)
PAGESIZE=4                    # Starting page size (smallest valid page size in bytes)

# Check if the executable exists
if [ ! -x "$EXECUTABLE" ]; then
    echo "Error: Executable '$EXECUTABLE' not found or not executable."
    exit 1
fi

# Initialize output file with a header
echo "Page Size (bytes),Elapsed Time (seconds)" > "$OUTPUT_FILE"

# Loop through page sizes, doubling each iteration
while [ $PAGESIZE -le $MAX_PAGES ]; do
    echo "Running with page size: $PAGESIZE bytes"

    # Run the program and capture the elapsed time
    OUTPUT=$($EXECUTABLE $PAGESIZE $TRIALS 2>/dev/null)
    
    # Extract the time using regex or keyword search
    TIME=$(echo "$OUTPUT" | grep -oP "(?<=Time elapsed: )[0-9.]+")
    
    # Check if TIME is valid and append to output file
    if [ -n "$TIME" ]; then
        echo "$PAGESIZE,$TIME" >> "$OUTPUT_FILE"
    else
        echo "Warning: Failed to capture time for page size $PAGESIZE. Skipping..."
    fi

    # Increment page size (double each iteration)
    PAGESIZE=$((PAGESIZE * 2))
done

echo "Data collection complete. Results saved in '$OUTPUT_FILE'."
