Alissa's PDF Thumbnail Trimmer -- source files Readme

PDF Thumbnail Trimmer is written in C++.  I used Microsoft Visual C++
Express 2010 and Windows SDK 7.1 to create the distribution binaries.
However, any other standard C++ compilers for Windows, e.g. MinGW gcc,
should work, too.

Source Organization

The source files are divided into four subdirectories:
PDFThumbTrimmer, PDFThumbTrimmer64, test32, and Miscellaneous.

PDFThumbTrimmer is the main source file directory and also is a VC++
project folder for the 32 bit DLL.  PDFThumbTrimmer64, which is almost
empty, is a VC++ project folder for the 64 bit DLL.

test32 contains a small test program.

Miscellaneous subdirectory contains miscellaneous files (:-), i.e.,
files that are needed to complete PDF Thumbnail Trimmer but are not
considered as a part of the VC++ solution.

VC++ Solution

The VC++ Solution file PDFThumbTrimmer.sln contains three projects.
PDFThumbTrimmer project is for the 32 bit DLL and PDFThumbTrimmer64
project is for the 64 bit DLL.  test32 project is for a small test
program and its product is not included in the binary distribution.

Note that 32 bit DLL and 64 bit DLL share the same set of source
files.  The subdirectory PDFThumbTrimmer contains all C++ (.cpp/.h)
files, and PFThumbTrimmer64 project contains links to them.  The
source code differences between 32 bit and 64 bit versions are
distinguished by "#if _M_IX86" directives.

One more file, comdll.def, a custom module definition, is required
when producing the DLLs.  It is not included as a member of VC++
projects and does not appear on the Solution Explorer, because VC++
Express disallows it.  comdll.def is in Miscellaneous subdirectory and
referred to from the "Configuration Properties | Linker | Input |
Module Definition File" setting on the project property.

Choose "Release" configuration and "Mixed Platforms" platform to build
a set of distributable binaries containing both 32 bit and 64 bit
DLLs.

Installer

The binary distribution comes in a single .EXE installer file produced
by NSIS (Nullsoft Scriptable Install System).

NSIS script to generate the installer is in Miscellaneous
subdirectory, as well as distribution Readme files.

The installer building step is not a part of the VC++ solution,
because the feature is disabled in Express edition.  I run makensis
command manually...

Yet More Files

The Miscellaneous folder contains two more files: Makefile.mingw and
iid.cpp.  They are for building PDF Thumbnail Trimmer using the
MinGW-w64 toolchain.  The former is a sample Makefile, and iid.cpp is
a supplementary source file needed to build under MinGW.  They are the
files I was using in a past, but they are not maintained any more.
They may or may not work.

Conclusion

Please feel free to use these source files in any way for any purpose.

Have fun!
                Alissa Sabre
