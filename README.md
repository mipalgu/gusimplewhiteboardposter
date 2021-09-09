# gusimplewhiteboardposter

A simple POSIX whiteboard library poster.

## Prerequisites

You need a posix system a C/C++ compiler, [cmake](https://cmake.org),
and a build system supported by [cmake](https://cmake.org), such as
[Ninja](https://ninja-build.org) or
[gmake](https://www.gnu.org/software/make/).

### gusimplewhiteboard

## Building

To build, you simply create a build directory (e.g. `build.ninja`)
using [cmake](https://cmake.org), then use your build system to
build and install. Here is an example using
[Ninja](https://ninja-build.org):

	mkdir ../build.ninja
	cd ../build.ninja
	cmake -G Ninja ../gusimplewhiteboardposter
	ninja
	ninja install

If you require root permissions, run `ninja install` as root,
e.g. by using [sudo](https://www.sudo.ws):

	sudo ninja install
