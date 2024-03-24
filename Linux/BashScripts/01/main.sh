#!/bin/bash

regex='^[0-9]+$'

if [ -z "$1" ];
then
echo "Parameter 1 is empty"
elif [ $# != 1 ];
then
echo "Too many parameters. Should be one."
elif [[ $1 =~ $regex ]];
then
echo "Invalid input. Parameter should be text"
else
echo "$1"
fi