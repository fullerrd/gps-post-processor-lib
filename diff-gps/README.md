### How to use c++ diff-gps library

* Install dependecies for GPS Toolkit listed on their website
* Follow steps from either 'Working with pre-built library' or 'Building from Scratch'
* make all
* Run or link to binaries that are in the './build' folder


### Using GPSTk

#### Working with pre-built library

(This probably only works on 64-bit Ubuntu 12, the OS setup on the CU CSCI VM)

The source is included in the repo as a tarball to keep the size smaller. It
will need to be extracted for the include paths to work correctly. To extract it
to a `gpstk/` directory:
```
cd diff-gps/
tar xvzf gpstk-2.1.src.tar.gz
```
* `ls gpstk/` to list the contents and confirm the `tar` command worked

You must copy `libgpstk.so` into `/usr/lib`:

`sudo cp diff-gps/gpstk-build/libgpstk.so /usr/lib`

#### Building from Scratch

Directions adapted from [gpstk.org](http://www.gpstk.org/bin/view/Documentation/BuildingGPSTkUnderUnix).

Prerequisites:
* CMake; check with `cmake --version`. GPSTk docs don't specify a version.
* g++ version 4.7.3 (part of the [GNU Compiler Collection](http://gcc.gnu.org/)); check with `g++ --version`

```
cd diff-gps/
tar xvzf gpstk-2.1.src.tar.gz
mkdir gpstk-build/
cd gpstk/
mkdir build/
cd build/
cmake -DCMAKE_INSTALL_PREFIX:PATH=../../gpstk-build/ ../
make
make install
cp src/libgpstk.so ../../gpstk-build/
cd ../../
sudo cp gpstk-build/libgpstk.so /usr/lib/
```