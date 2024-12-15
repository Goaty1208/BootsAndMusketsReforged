rm -rf ./build/bin/debug/
cmake -S . -B build
cmake --build build
cp -a ./src/build/. ./build/bin/debug/
cd ./build/bin/debug/
./untitled_fighting_game
cd ..
cd ..