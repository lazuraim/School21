#!/bin/bash

directory=$1

find_file() {
        find $directory -name $1 2>/dev/null | wc -l
}