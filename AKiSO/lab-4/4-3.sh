#!/bin/bash

cat=`curl -s https://api.thecatapi.com/v1/images/search | jq -r '.[0].url | tostring'`;
chuck=`curl -s https://api.chucknorris.io/jokes/random | jq '.value'`
curl -s $cat > image;
catimg -H 90 image;
echo $chuck;
rm image;