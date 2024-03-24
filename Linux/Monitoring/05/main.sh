#!/bin/bash

if [ $# != 1 ];
then
echo "Invalid input. One parameter expected."
elif [[ !($1 =~  ./$) ]];
then
echo "Invalid input. Parameter must end with '/'"
else 
chmod +x print.sh
bash print.sh $1
fi