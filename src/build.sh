mkdir -p ../build
pushd ../build
g++ -DLINUX -Wall -Werror -O3 -std=gnu++0x -Wno-attributes ../src/core/core.cpp

popd
