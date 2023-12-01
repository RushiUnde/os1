echo "Enter array size"
read n
echo "enter array elements"
i=0
while [ $i -lt $n ]
do 
read nos[$i]
i=`expr $i + 1`
done

echo "Array elements"
i=0
while [ $i -lt $n ]
do
echo ${nos[$i]}
i=`expr $i + 1`
done

#Sorting of Numbers
for (( i = 0; i < n; i++ ))
do 
for (( j = $i; j < n; j++ ))
do
if [ ${nos[$i]} -gt ${nos[$j]} ];
then 
t=${nos[$i]}
nos[$i]=${nos[$j]}
nos[$j]=$t
fi
done
done
echo "sorted elements"
for (( i = 0; i < n; i++ ))
do
echo ${nos[$i]}
done

