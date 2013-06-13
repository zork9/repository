#!/bin/sh

echo "brew : Starting build..."
cd src;
gcc -I/usr/include/GNUstep -I../include -c *.m
cd ..;
echo "brew : Build Done."
