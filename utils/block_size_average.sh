#!/bin/bash

RPC_URL="http://127.0.0.1:34568/json_rpc"
MAX_RETRIES=3
SLEEP_BETWEEN_REQUESTS=0.1
BLOCK_RANGE_SIZE=10000
OUTPUT_FILE="average_block_sizes.txt"

# Get current blockchain height
get_current_height() {
    local retry=0
    while [[ $retry -lt $MAX_RETRIES ]]; do
        response=$(curl -s -X POST $RPC_URL -d '{"jsonrpc":"2.0","id":"0","method":"get_block_count"}' -H 'Content-Type: application/json')
        if [[ $? -eq 0 ]]; then
            height=$(echo "$response" | jq -r '.result.count')
            if [[ -n "$height" && "$height" != "null" ]]; then
                echo $((height - 1)) # Return 0-based height
                return 0
            fi
        fi
        ((retry++))
        sleep $SLEEP_BETWEEN_REQUESTS
    done
    echo "Error: Failed to get blockchain height after $MAX_RETRIES attempts" >&2
    exit 1
}

# Get block sizes for a range
get_block_sizes() {
    local start=$1
    local end=$2
    local retry=0
    
    while [[ $retry -lt $MAX_RETRIES ]]; do
        response=$(curl -s -X POST $RPC_URL -d "{\"jsonrpc\":\"2.0\",\"id\":\"0\",\"method\":\"get_block_headers_range\",\"params\":{\"start_height\":$start,\"end_height\":$end}}" -H 'Content-Type: application/json')
        if [[ $? -eq 0 ]]; then
            sizes=$(echo "$response" | jq -r '.result.headers[].block_size')
            if [[ -n "$sizes" ]]; then
                echo "$sizes"
                return 0
            fi
        fi
        ((retry++))
        sleep $SLEEP_BETWEEN_REQUESTS
    done
    echo "Error: Failed to get blocks $start-$end after $MAX_RETRIES attempts" >&2
    return 1
}

main() {
    current_height=$(get_current_height)
    echo "Current blockchain height: $current_height"
    
    ranges=$((current_height / BLOCK_RANGE_SIZE))
    echo "Processing $ranges ranges of $BLOCK_RANGE_SIZE blocks each..."
    
    echo -n "[" > "$OUTPUT_FILE"
    first_range=true
    
    for ((i=0; i<=ranges; i++)); do
        start=$((i * BLOCK_RANGE_SIZE))
        end=$((start + BLOCK_RANGE_SIZE - 1))
        
        # Cap the end at current height
        if [[ $end -gt $current_height ]]; then
            end=$current_height
        fi
        
        # Status update every 1000 blocks within the range
        for ((j=start; j<=end; j+=1000)); do
            checkpoint=$((j + 1000 - 1))
            if [[ $checkpoint -gt $end ]]; then
                checkpoint=$end
            fi
            echo "Processing blocks $j to $checkpoint ..."
        done
        
        sizes=$(get_block_sizes $start $end)
        if [[ $? -ne 0 ]]; then
            continue
        fi
        
        # Calculate average
        count=0
        sum=0
        for size in $sizes; do
            sum=$((sum + size))
            ((count++))
        done
        
        if [[ $count -gt 0 ]]; then
            average=$((sum / count))
            if [[ "$first_range" = false ]]; then
                echo -n ", " >> "$OUTPUT_FILE"
            fi
            echo -n "$average" >> "$OUTPUT_FILE"
            first_range=false
        fi
        
        sleep $SLEEP_BETWEEN_REQUESTS
    done
    
    echo "]" >> "$OUTPUT_FILE"
    echo "Done! Averages saved to $OUTPUT_FILE"
}

main
