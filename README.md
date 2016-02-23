# armadillo
A small ARM OS that implements the DOS API :p

# Setting up the environment
First, install the necessary tools: clang and gcc for
ARM. Then run (in the top dir of Armadillo):

	$ source script/load_env.sh

This will set up environment variables pointing to your
clang binary and your assembler. If you have installed any
of the above in a non-standard location, you will need to
set the environment variables `ASM` and `CC` to the
appropriate values yourself.

# Building the kernel
First, create a folder to hold the build artefacts:

	$ mkdir build

then change directory to that folder

	$ cd build

Make sure to have cmake installed and reachable in your
`PATH` and then run

	$ cmake ../

or

	$ cmake -DCMAKE_BUILD_TYPE=Debug ../

for a debug build.

This will generate makefiles so that you can in the next step run:

	$ make

If all goes well, armadillo should build and the resulting binary
should be in `kernel/armadillo`, relative to the `build` folder
created above.

To run qemu with the kernel, make sure to have qemu 
(specifically ARM systems) installed and run (once again in 
the `build` directory):

	$ ../script/run_qemu.sh

This will start an emulated ARM system and the kernel should now
boot.
