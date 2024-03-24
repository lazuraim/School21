#!/bin/bash

directory=$1

chmod +x functions.sh
. functions.sh $directory

start=$(date +%s.%N)
echo "Total number of folders (including all nested ones) = $(find $directory* 2>/dev/null -type d | wc -l)"
echo "TOP 5 folders of maximum size arranged in descending order (path and size): "
du $directory -h 2>/dev/null | sort -hr | head -n 5 | awk '{printf "- %s, %sB\n", $2, $1}' | nl
echo "Total number of files = $(find $directory -type f 2>/dev/null | wc -l)"
echo "Number of:"
echo "Configuration files (with the .conf extension) = $(find_file "*.conf")"
echo "Text files = $(find_file "*.txt")"
echo "Executable files = $(find $directory -type f -executable 2>/dev/null | wc -l)"
echo "Log files (with the extension .log) = $(find_file "*.log")"
echo "Archive files = $(find $directory -name *.zip -o -name *.tar -o -name *.rar -o -name *.7z -o -name *.gz 2>/dev/null | wc -l)"
echo "Symbolic links = $(find $directory -type l 2>/dev/null | wc -l)"
echo "TOP 10 files of maximum size arranged in descending order (path, size and type):"
find $directory -type f -exec du -h {} + 2>/dev/null | sort -hr | head -n 10 | awk '{printf "- %s, %sB\n", $2, $1}' | nl
echo "TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file)"
find $directory -type f -executable -exec du -h {} + 2>/dev/null | sort -hr | head -n 10 | awk '{printf "- %s, %sB\n", $2, $1}' | nl
end=$(date +%s.%N)
exec_time=$(echo "$end - $start" | bc )
echo "Script execution time (in seconds) = $(printf "%.2f" $exec_time)"