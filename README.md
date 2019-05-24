# Nonio - Tool for exploration of compiler flags

An extensible tool for exploration of sequences of compiler flags with support for phase ordering (i.e., exploration of sequences of compilation steps taking the order into account).
Can be used to improve a function/kernel (e.g., performance, energy consumption, code size), taking into account a specific target.
The target can be the host computer (e.g., host CPUs) or, in the context of cross-compilation, an external device (e.g., an embedded computing board) or a simulation environment.
The current version works with C/C++ code compilation using GCC (phase selection only) and Clang+LLVM.
However, it is possible to extend the tool to support other source languages and/or compiler tool-chains.

## Supported Metrics

Compiler sequences for improvement of execution time and code size is supported for all targets.
Energy consumption is supported as an optimization metric when compiling to Intel CPUs (Haswell and later) and the Odroid-XU single computer board.

## Setup Nonio

Nonio requires a Java virtual machine (version 10 or greater), and the [Clava](https://github.com/specs-feup/clava/) C/C++ source-to-source compiler.

Clone this repository (`clone https://github.com/specs-feup/nonio`) to where you want Nonio to be installed.
Add `export PATH=~/PATHTONONIO/bin:$PATH` to your `.bashrc` file. Open a new shell session, or reload the shell settings (`source .bashrc`).

## Preparing a Function/Kernel

Isolate the function/kernel to be the subject of phase ordering exploration in a single file (e.g., `kernel_nussinov.c`) and create a file with a `main()` function which calls the former with representative arguments (for the previous kernel, file must be named `kernel_nussinov_main.c`).
Verification of correctness of the binaries compiled with specialized phase selections/orders is accomplished by comparing the output of executing those binaries with outputs known to be correct (e.g., generated with the version resulting from compilation without specialized phase selections/orderings).
Verification is expected to return `10` if everything is OK and `1` if there is a problem.
Code performing verification can be on the same `main()` or in a different file (`isVerificationSeparated = true`).
For the previous kernel, the file must be named `kernel_nussinov_verify.c`.

## How to Use

Create an `arguments.properties` file such as the following.

```
sourceFile = 'kernel_nussinov.c'
compiler = 'gcc'		# default: gcc
nsteps = 10				# default: 1000
language = 'c'			# default: c
target = 'host-intel'	# default: host-intel
algo = 'sa'				# default: sa
seqlen = 32				# default: 32
nexec = 30				# default: 1
# used for the reference fitness and for the final reported value for the phase ordering
minimumExecForReporting = 30	# default: 30
clean = 1				# default: 1
passes = ''				# default: ''
percent = 2				# default: 2
append = ''				# default: false
metrics = ['performance']		#default: performance; available: performance, energy, size
alreadyInstrumented = false 	#default: false
isVerificationSeparated = true	# default: false
#log = 'log.gz' # if enabled, stores the log files in a compressed file
```

Start exploration by executing:
```
nonio arguments.properties
```

## Ongoing Work

- Adding support for fine-grain control of some of the individual compiler phases.
- Automatization of the steps mentioned in "Preparing a Function/Kernel", i.e., extraction of the function/kernel, generation of `main()` file, selection of input arguments for the function/kernel, and generation of verification code.
- Integration with Makefile and CMake.

## Authors

- Ricardo Nobre   - rjfn@fe.up.pt
https://web.fe.up.pt/~pro11012/index.php?lang=en

- João Bispo      - jbispo@fe.up.pt
http://jbispo.eu/

## License

This software is published under the GNU Lesser General Public License (LGPL) version 3.
