# Binary resource integrator example

This example shows how to integrate binary resources into a exe file and extract them to the temporary directory.

## Goal

Some times applications written in Java or .NET require certain frameworks to be installed in order run. This project gives the user the ability to integrate installers into a single exectuable file, extract them and launch them after extraction. Afterwards the application can be extracted and launched by the same logic. The goal is to provide a boilerplate and show with the file `binres/test.bin` how it is integrated, recognized and extracted. This application is to be run on the Windows operating system.

## Restrictions

This is a very basic example with no icons, admin right requests or stuff like that. It should really just show how to integrate binary data into ones program and how to extract the code.

## Requrements

* [MSYS2](https://www.msys2.org) installed in `%LOCALAPPDATA%\Programs\Msys2` and environment variable `%MSYS2_HOME%` pointing to that directory. Msys2 also has to have gcc and gdb installed in order to build this application. `%MSYS2_HOME%` is required because the configuration scripts in the directory `.vscode` make use of it.

## Usage

### Add own resource.

1. Place the resource in the directory `binres`.
2. Change the file `.vscode/tasks.json`
   1. Look for the task with the label `Create binary object`.
   2. Go to the section `args` and change the last element of the array `binres\\test.bin` to whatever is required.
3. Evaluate the symbol names by using the command `nm` in the MSYS2 directory:

```
${env:MSYS2_HOME}\mingw64\bin\nm out\binary.o
0000000000000005 D _binary_binres_test_bin_end
0000000000000005 A _binary_binres_test_bin_size
0000000000000000 D _binary_binres_test_bin_start
```

4. Take the start, end and size names and change lines 6, 7 and 8 in the file `main.c` accordingly.
5. Build the application by running [CRTL]+[SHIFT]+[B]
6. Run the application `out/main.exe` and open the directory printed on the commandline.
7. You will find your bindary file in this directory.
