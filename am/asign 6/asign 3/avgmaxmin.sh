
#!/bin/bash

# Function to calculate average
average(){
  sum=0
  for num in "$@";
 do
    sum=$((sum+num))
 done
  
  echo $((sum/${#@}))
}

# Function to find maximum
max(){
  max=-999999999
  for num in "$@";
 do
    if [ $num -gt $max ]; 
then
      max=$num
    fi
  done
  
  echo $max
}

# Function to find minimum  
min(){
  min=999999999
  for num in "$@"; 
do
    if [ $num -lt $min ];
 then
      min=$num
    fi
  done
  
  echo $min
}

# Print average
echo "Average: $(average 10 20 30 40 50)"

# Print max
echo "Maximum: $(max 10 20 30 40 50)" 

# Print min
echo "Minimum: $(min 10 20 30 40 50)"



