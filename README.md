# HeadCooker
A C++ GUI-based tool for managing chefkoch.de recipes.

![HeadCooker](http://indidude.de/stuff/headcooker.gif)

<!-- [toc] -->
## Table of Contents

   * [Compilation and dependencies](#compilation-and-dependencies)
     * [Dependencies](#dependencies)
       * [libCurl](#libcurl)
       * [QT5](#qt5)
       * [SQLite3](#sqlite3)
     * [Compilation](#compilation)
   * [Credits](#credits)
     * [Unicode Parsing](#unicode-parsing)

<!-- [toc] -->
## Compilation and dependencies ##

### Dependencies ###

#### libCurl ####
Before compiling make sure libcurl is installed:

**Linux:** (run as root or via sudo)
``` bash
apt-get install libcurl3
```

**Windows:**

I'll check this later

#### QT5 ####
HeadCooker depents on QT5 so make sure QT5 is installed:

**Linux:** (run as root or via sudo)
``` bash
apt-get install qt5-default qt5-qmake
```

**Windows:**

Check http://www.qt.io/download/

#### SQLite3 ####
SQLite is required for storing the recipes on your local computer.

**Linux:** (run as root or via sudo)
``` bash
apt-get install libsqlite3-dev
```

**Windows:**

I'll check this later...

### Compilation ###

Run following in your HeadCooker directory:
``` bash
mkdir build
cd build
qmake ..
make
```

You can now run HeadCooker via ```./headcooker``` in your build directory

## Credits ##

### Unicode Parsing ###
This credit goes to [Jan Düpmeier](https://github.com/jduepmeier) for part of his project ["easy json"](https://github.com/jduepmeier/easy_json), thanks dude.
