#!/bin/bash

# Define a list variable as an array
list=("item1" "item2" "item3")

# Loop through each item in the list
for item in "${list[@]}"; do
  echo "$item"
done

