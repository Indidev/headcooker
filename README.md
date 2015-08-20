# HeadCooker
A c++ GUI-based tool for managing chefkoch.de recipes.

## Compiling and dependencies ##

### Dependencies ###

#### libCurl ####
Before compiling make sure libcurl is installed:

**Linux:** (run as root or via sudo)
```
apt-get install libcurl3
```

**Windows:**

I'll check this later

#### QT5 ####
HeadCooker depents on QT5 so make sure QT5 is installed:
**Linux:** (run as root or via sudo)
```
apt-get install qt5-default qt5-qmake
```

**Windows:**

Check http://www.qt.io/download/

### Installation ###

Run following in your HeadCooker directory:
```
mkdir build
cd build
qmake ..
make
```

You can now run HeadCooker via ```./headcooker``` in your build directory
