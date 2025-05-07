#!/bin/bash

# compile
echo "[+] Compiling..."
g++ ascii_player.cpp -o ascii_player `pkg-config --cflags --libs opencv4`
if [ $? -ne 0 ]; then
    echo "[!] compile error!"
    exit 1
fi

if [ ! -d "frames" ] || [ -z "$(ls -A frames)" ]; then
    echo "[+] Frames extracting (ffmpeg)..."
    mkdir -p frames
    ffmpeg -i bad_apple.mp4 -vf scale=120:60 -r 15 frames/frame_%04d.png
fi

if [ ! -f "bad_apple.mp3" ]; then
    echo "[+] Sound..."
    ffmpeg -i bad_apple.mp4 -q:a 0 -map a bad_apple.mp3
fi

printf '\e[8;67;240t'

echo "[+] Starting..."
./ascii_player

killall -q mpg123
