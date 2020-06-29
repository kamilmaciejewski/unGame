#!/bin/bash
sudo apt-get install gcc libxext-dev libsdl2-dev libsdl2-ttf-dev libboost-all-dev default-jre mc libncurses-dev valgrind

wget http://www.ferzkopp.net/Software/SDL2_gfx/SDL2_gfx-1.0.4.tar.gz
tar xzvf SDL2_gfx-1.0.4.tar.gz
rm SDL2_gfx-1.0.4.tar.gz

cd SDL2_gfx-1.0.4
./autogen.sh
./configure 
make
sudo make install
cd ..
rm -rf SDL2_gfx-1.0.4
