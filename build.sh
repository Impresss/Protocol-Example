mkdir -p Bin

cd Server
mkdir build
cd build
cmake ..
make
cp Server ../../Bin/

cd ../../

cd Client
mkdir build
cd build
cmake ..
make
cp Client ../../Bin/
cd ../../