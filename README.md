# sdl3-opengl-test

Building instructions at [BUILDING.md](BUILDING.md).

Structs are defined as RMI_NameOfStruct

And functions are defined as RMINameOfFunction()

idk

## Build containers

`build.sh`

## Run containers

`x11.sh`, `wayland.sh` if youre using a normal gpu.

or `x11-nvidia.sh`, `wayland-nvidia.sh` if youre using an nvidia one.

> [!NOTE]  
> You can run both if you're on a wayland session.

> [!IMPORTANT]  
> For the X containers you're gonna need xorg-host
>
> For the nvidia containers you're gonna need to run `sudo nvidia-ctk runtime configure --runtime=docker`

# Container issues

* For some weird reason a docker proccess is sometimes kept open and it uses a lot of cpu. it may have to do with running both at the same time.
* The wayland ones use a lot more cpu.
* The image build prossess recompiles the whole thing every time.

## Licenses

[**SDL**](https://github.com/libsdl-org/SDL) - Zlib license

[**cglm**](https://github.com/recp/cglm/) - [MIT license](cglm/LICENSE)

**[stb](https://github.com/nothings/stb/)** - Public Domain