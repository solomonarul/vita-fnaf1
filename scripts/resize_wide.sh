rm -rf resized

mkdir resized

parallel magick {} -resize 1210x544! resized/{/} ::: *.png

pngquant resized/*.png

for f in resized/*-fs8.png; do
    # Remove "-fs8" from filename
    newname=$(basename "$f" | sed 's/-fs8//')

    # Copy to current folder (or "output" if you prefer)
    cp "$f" "./$newname"
done

rm -rf resized
