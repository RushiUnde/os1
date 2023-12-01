#!/bin/bash

filename="$1"

# Check file type
if [ -f "$filename" ]; then
  echo "Regular file"
elif [ -d "$filename" ]; then
  echo "Directory"
else
  echo "Other type"
fi

# Check permission
permission=$(ls -ld "$filename" | cut -c1-10)
echo "Permissions: $permission"

