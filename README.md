## Get submodules (SDL3)

```sh
git submodule update --init --recursive
```
## Configure build folder (statically linking SDL3) and build
```sh
cmake -S . -B build -DSDL_SHARED=False -DSDL_STATIC=True
cmake --build build
```
## Run

```sh
./build/hello
```

