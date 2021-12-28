# DisTream

What is this? Eh it's too early to tell...

## How to setup

Clone the repo locally:
```bash
git clone https://github.com/Yimura/DisTream.git --recursive
cd DisTream
```

Make sure you have the following development libraries installed:
    - boost
    - websocketpp

Install these through your package manager or any other way that works best for your use case.

The following libraries are included in the repo:
    - cpp-cryptlite
    - json

## Building the project

```bash
premake5 gmake2

# debug build
make

# release build
make config=release
```