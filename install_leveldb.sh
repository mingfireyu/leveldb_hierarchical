make clean && make
sudo cp -r include/leveldb /usr/include
sudo cp out-shared/libleveldb.so.1.19 /usr/lib
sudo cp out-static/libleveldb.a /usr/local/lib
cp out-static/libleveldb.a ./
cd /usr/lib
sudo rm libleveldb.so.1
sudo rm libleveldb.so
sudo ln -fs libleveldb.so.1.19 libleveldb.so.1
sudo ln -fs libleveldb.so.1 libleveldb.so
sudo ldconfig
