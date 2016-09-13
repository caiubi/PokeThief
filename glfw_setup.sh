sudo apt-get install -y cmake unzip xorg-dev libglu1-mesa-dev
wget https://github.com/glfw/glfw/releases/download/3.2.1/glfw-3.2.1.zip
unzip glfw-3.2.1.zip
cd glfw-3.2.1
cmake -G "Unix Makefiles"
sudo make
sudo make install
cd ..
rm glfw-3.2.1.zip
rm -rf glfw-3.2.1
