#!/usr/bin/env bash

# Setup
# Exit the script if any command fails
set -e

# libuuid
sudo apt install -y uuid-dev

# nlohmann json
cd /tmp
git clone --depth 1 --branch master https://github.com/nlohmann/json.git
cd json
git fetch origin 456478b3c50d60100dbb1fb9bc931f370a2c1c28
git checkout 456478b3c50d60100dbb1fb9bc931f370a2c1c28
mkdir build && cd build
cmake -DJSON_BuildTests=false ..
make -j$(nproc)
sudo make install


sudo ldconfig
