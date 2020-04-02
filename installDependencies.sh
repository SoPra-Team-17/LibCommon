#!/usr/bin/env bash

# Setup
# Exit the script if any command fails
set -e


# spdlog
cd /tmp
git clone https://github.com/gabime/spdlog.git
cd spdlog
mkdir build && cd build
cmake ..
make -j$(nproc)
sudo make install


sudo ldconfig