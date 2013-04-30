Alissa's PDF Thumbnail Trimmer -- source files

PDF Thumbnail Trimmer is written in C++.  I used Microsoft Visual C++
Express 2010 and Windows SDK 7.1 to create distribution binaries.  Any
other standard C++ compilers for Windows should work, too.

The VC++ Solution file PDFThumbTrimmer.sln contains three projects.
PDFThumbTrimmer project is the 32 bit DLL and PDFThumbTrimmer64
project is the 64 bit DLL.  test32 is a small test program and its
product is not included in the binary distribution.

Note that 32 bit DLL and 64 bit DLL shares same set of source files.
The subdirectory PDFThumbTrimmer contains all C++ (.cpp/.h) files.

One more file, comdll.def is used to linking the DLLs.  It is not
added to the project, because VC++ Express disallows it.  comdll.def
is in Miscellaneous.

Choose "Release" configuration and "Mixed Platforms" platform to build
a set of distributable binaries.

NSIS script to generate the installer is in Miscellaneous, as well as
distribution Readme files.

The Miscellaneous folder contains two more files: Makefile.mingw and
iid.cpp.  They are for building with the MinGW-w64 toolchain.  The
former is a sample Makefile, and iid.cpp is a supplementary source
file needed in MinGW.

Please feel free to use these source files in any way for any purpose.

Have fun!
                Alissa Sabre
