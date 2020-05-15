#!/usr/bin/env bash

# Setup
# Exit the script if any command fails
set -e

# libuuid
sudo apt install -y uuid-dev

# nlohmann json
cd /tmp
git clone --depth 1 https://github.com/nlohmann/json.git
cd json
mkdir build && cd build
cmake -DJSON_BuildTests=false ..
make -j$(nproc)
sudo make install


sudo ldconfig
