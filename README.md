# LedDriver (Test Driven Development for Embedded C) googletest

## How to use

### autotools

```
git clone --recursive https://github.com/tomoyuki-nakabayashi/TDDforEmbeddedC.git
cd TDDforEmbeddedC/
autoreconf -fi
./configure
make check
./test/gtest
```

### CMake

* requirements: cmake 2.8 or later

```
git clone https://github.com/tomoyuki-nakabayashi/TDDforEmbeddedC.git
cd TDDforEmbeddedC/
mkdir build
cd build
cmake ..
make
./unittest
```
