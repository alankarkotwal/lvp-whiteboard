#************************************************************************
# Virtual Whiteboard System Based on Image Processing
# Setup
#
# Author: Alankar Kotwal <alankarkotwal13@gmail.com>
#************************************************************************

# Make sure you're in the lvp-whiteboard directory

direc=${PWD##*/}

if [ "$direc" != "lvp-whiteboard" ]
then
	echo "Go to the lvp-whiteboard folder and execute the script."
	exit 0
else
	echo "Setting up..."
fi

#************************************************************************

# Get the  path of the repository in a file

mkdir code/opencv/build

path=`pwd`
echo 	"#define REPO_ROOT \"${path//\\/\\\\}\"" > \
	code/opencv/path.hpp

#************************************************************************

# Install Boost

sudo apt-get install libboost-all-dev 1>/dev/null

#************************************************************************

# Build the repo

cd code/opencv/build
cmake .. 1>/dev/null
make 1>/dev/null
cd ../../..

#************************************************************************

# Create a symbolic link to the executable in the root

ln -s code/opencv/build/Whiteboard ./Whiteboard

#****************************************************************

# Done!

echo "Done!"
