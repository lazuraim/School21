#!/bin/bash

background=(0 107 41 42 44 45 40)
font=(0 97 31 32 34 35 30)

set_values() {
        c1_b=${column1_background}
        c1_f=${column1_font_color}
        c2_b=${column2_background}
        c2_f=${column2_font_color}
}

set_values

set_default() {
        c1_b=${c1_b:=1}
        c1_f=${c1_f:=2}
        c2_b=${c2_b:=3}
        c2_f=${c2_f:=4}
}
set_default