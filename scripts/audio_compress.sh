#!/bin/bash

for f in *.wav; do
    ffmpeg -i "$f" -ar 44100 -ac 2 -q:a 2 "${f%.wav}.mp3"
done