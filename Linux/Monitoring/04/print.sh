#!/bin/bash

source settings.conf 
. set_param.sh

define_name() {
        case $1 in 
        1) echo "white";;
        2) echo "red";;
        3) echo "green";;
        4) echo "blue";;
        5) echo "purple";;
        6) echo "black";;
        esac
}

define_num() {
        case $1 in
        [1-6]) echo "$1";;
        *) echo "default";;
        esac
}

echo 
echo "Column 1 background = $(define_num $column1_background) ($(define_name $c1_b))"
echo "Column 1 font color = $(define_num $column1_font_color) ($(define_name $c1_f))"
echo "Column 2 background = $(define_num $column2_background) ($(define_name $c2_b))"
echo "Column 2 font color = $(define_num $column2_font_color) ($(define_name $c2_f))"