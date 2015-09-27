#!/bin/bash
echo "doing devmake..."
gcc -B . `pkg-config --cflags gtk+-3.0` -o launcher main.c `pkg-config --libs gtk+-3.0`