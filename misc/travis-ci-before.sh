#!/bin/bash
platform=$(uname | sed -e 's/_.*//' | tr '[:upper:]' '[:lower:]' | sed -e 's/\//_/g')
if [[ "$platform" == "linux" ]]; then
    sudo apt-get update -qq &> /dev/null
    sudo apt-get install -q -y libgl1-mesa-dev libsdl2-dev libfreetype6-dev mingw-w64 g++-mingw-w64 &> /dev/null
else
    brew update &> /dev/null
    brew install freetype &> /dev/null

fi

exit 0
