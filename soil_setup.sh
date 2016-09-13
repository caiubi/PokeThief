wget http://www.lonesock.net/files/soil.zip
unzip soil.zip
cd "Simple OpenGL Image Library"
cd projects/makefile
cp makefile Makefile
mkdir obj
make
sudo make install
cd ../../../
rm soil.zip
rm -rf "Simple OpenGL Image Library"
