# ccalc

## Installation:

To download and build, open a terminal and enter the following commands:

```
git clone https://github.com/carsonaj/ccalc.git
cd ccalc
make build 
```

To install, enter the following command:

```
make install
```

To uninstall, enter the following command:

```
make uninstall
```

## Usage:

To compile and link a program `prog.c` that includes functionality from `array.h`, enter the following command:

```
gcc prog.c -I/usr/local/include/ccalc -L/usr/local/lib/ccalc -lccalc -o prog
```

To run the binary `prog`, enter the following command:

```
./prog
```