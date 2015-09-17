#!/bin/bash
echo "doing devmake..."
gcc `pkg-config --cflags gtk+-3.0` -o test main.c `pkg-config --libs gtk+-3.0`