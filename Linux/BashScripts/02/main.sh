#!/bin/bash

chmod +x research.sh
touch output.txt
bash research.sh > output.txt
cat output.txt
echo "Do you want to save the output to the file? [Y/N]"
read response
if [[ "$response" = "Y" || "$response" = "y" ]];
then
mv output.txt $(date +"%d_%m_%Y_%H_%M_%S").status
else
rm output.txt
fi