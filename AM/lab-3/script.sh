file_array=(
"data/xqf131.tsp"
"data/xqg237.tsp"
"data/pma343.tsp"
"data/pka379.tsp"
"data/bcl380.tsp"
"data/pbl395.tsp"
"data/pbk411.tsp"
"data/pbn423.tsp"
"data/pbm436.tsp"
"data/xql662.tsp"
"data/xit1083.tsp"
"data/icw1483.tsp"
"data/djc1785.tsp"
"data/dcb2086.tsp"
"data/pds2566.tsp"
)

for file in "${file_array[@]}"
do
    ./main "$file" 8 1>> results/memes
done