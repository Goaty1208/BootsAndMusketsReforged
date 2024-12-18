cmake -S . -B build
cmake --build build
cp -a ./src/build/. ./build/bin/debug/
cd ./build/bin/
./bootsAndMuskets
cd ..
cd ..