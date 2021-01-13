# ccalc

## Installation:

To build the `libccalc` shared library, open a terminal and enter the commands

```
git clone https://github.com/carsonaj/ccalc.git
cd ccalc
make build 
```

To install the `libccalc` shared library, enter the commands

```
sudo cp -i ./lib/libccalc.so /usr/local/lib/ccalc
sudo ldconfig
```