#!/bin/bash

FOLDER_NAME=$(basename "$PWD")
FILES=(*.png)

if [ ${#FILES[@]} -eq 0 ]; then
    echo "No PNG files found in this folder."
    exit 1
fi

FILTER=""
INPUTS=""
COUNT=0
FIRST_WIDTH=$(identify -format "%w" "${FILES[0]}")

for FILE in "${FILES[@]}"; do
    INPUTS+="-i \"$FILE\" "
    FILTER+="[$COUNT:v]scale=${FIRST_WIDTH}:-1[img$COUNT];"
    COUNT=$((COUNT+1))
done

VSTACK=""
for i in $(seq 0 $((COUNT-1))); do
    VSTACK+="[img$i]"
done
FILTER+="$VSTACK vstack=inputs=$COUNT"

eval ffmpeg $INPUTS -filter_complex "\"$FILTER\"" merged.png > /dev/null

pngquant --quality=65-80 --output "$FOLDER_NAME.png" merged.png

rm merged.png
