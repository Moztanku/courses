#!/bin/bash

IFS=","
string=" "
for f in `find $1 -type f -printf '%p,'`; do
    size=$(wc -c $f | cut -d " " -f 1);
    sum=$(sha256sum $f | cut -d " " -f 1);
    name=$f;
    string="${string}
    ${size};${sum};${name}"
done;


echo $string | sort -t, -nk2 | awk -F ";" '{print +a[$2] " " $1 " " $2 " " $3; a[$2]++}' | awk '{if($1!=0) print $4}'; #+a[$0]

# function iterate(){
#     IFS="";
#     dir="$1/*";
#     for f in $dir;do
#         if [ -f $f  ]; then
#             sum=`sha256sum $f | cut -d " " -f 1`;
#             size=`wc -c $f | awk '{print $1}'`;
#             hashArr+=($sum);
#             sizeArr+=($size);
#             nameArr+=($f);
#             arrSize=$((arrSize+1));
#         elif [ -d $f ]; then
#             iterate $f;
#         fi;
#     done;
# }

# function countHash(){
#     hashVal=$1;
#     count=-1;
#     for((i=0; i<arrSize;i++)); do
#         if [ $hashVal = ${hashArr[$i]}  ]; then
#             count=$((count+1));
#         fi;
#         if (( $count > 0 )); then
#             break;
#         fi;
#     done;
#     echo $count;
# }

# hashArr=();
# sizeArr=();
# nameArr=();
# arrSize=0;
# iterate $1;

# string="";
# for(( i=0; i<arrSize; i++ )); do
#     if (( $(countHash ${hashArr[$i]}) > 0  )); then
#         string="$string
#         \"${nameArr[$i]}\",${sizeArr[$i]}";
#     fi;
# done;
# echo $string | sort -t, -nk2;