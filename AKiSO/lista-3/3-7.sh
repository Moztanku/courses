#!/bin/bash
IFS="";
for f in ./*; do
    if [ -f $f ]; then
        mv -v $f `echo $f | tr '[A-Z]' '[a-z]'`;
    fi;
done;