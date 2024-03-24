#!/bin/bash

background=(0 107 41 42 44 45 40)
font=(0 97 31 32 34 35 30)
regex='^[1-6]$'

if [ $# != 4 ];
then
echo "Invalid number of arguments. Expected 4."
elif [[ !($1 =~ $regex) || !($2 =~ $regex) || !($3 =~ $regex) || !($4 =~ $regex) ]];
then
echo "Invalid input. Expected 1-6."
elif [[ $1 = $2 || $3 = $4 ]];
then
echo "Matching values for background and font. Try to call the script again."
else 
chmod +x research.sh
bash research.sh ${background[$1]} ${font[$2]} ${background[$3]} ${font[$4]}
fi