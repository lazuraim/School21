#!/bin/bash

if [ -f "settings.conf" ];
then
source settings.conf
else 
echo "Config file is not found."
exit 1
fi

chmod +x set_param.sh
. set_param.sh

if [[ $c1_b = $c1_f || $c2_b = $c2_f ]];
then
echo "Matching values for background and font. Try to edit settings.conf and call the script again."
else 
chmod +x research.sh
bash research.sh ${background[$c1_b]} ${font[$c1_f]} ${background[$c2_b]} ${font[$c2_f]}
chmod +x print.sh
bash print.sh
fi