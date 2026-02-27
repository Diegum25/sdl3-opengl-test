## Get submodules (SDL3 & cglm)

```sh
git submodule update --init --recursive --depth 1
```
## Configure build folder (static SDL3 & cglm) and build
```sh
cmake -S . -B build -DSDL_SHARED=False -DSDL_STATIC=True
cmake --build build
```
## Run

```sh
./build/rmi
```

