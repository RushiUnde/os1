#!/bin/bash

# Factorial without recursion
num=$1
fact=1
for (( i=1; i<=num; i++ )); do
  fact=$((fact*i))
done
echo "Factorial of $num is $fact"

# Factorial with recursion
fact_recursion () {
  if [ $1 -eq 1 ]; then
    echo 1
  else
    local temp=$(($1-1))
    local result=$(fact_recursion $temp)
    echo $(($1*result))
  fi
}

result=$(fact_recursion $num)
echo "Factorial of $num using recursion is $result"

