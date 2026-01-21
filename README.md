## Get submodules (SDL3)

```sh
git submodule update --init --recursive
```
## Configure build folder and build
```sh
cmake -S . -B build
cmake --build build
```
## Run

```sh
./build/hello
```

