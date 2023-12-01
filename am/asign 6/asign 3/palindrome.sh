^C

#!/bin/bash

string="$1"
reverse=$(echo $string | rev)

if [ "$string" = "$reverse" ]; then
  echo "String is palindrome"
else
  echo "String is not palindrome"
fi

