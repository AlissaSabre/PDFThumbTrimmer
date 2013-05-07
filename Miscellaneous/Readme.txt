Alissa's PDF Thumbnail Trmmer
                                   2013-5-7  Alissa Sabre


******************************************************************
*                                                                *
*  NOTE: If you keep seeing extra white borders around PDF       *
*  thumbnails after successful installation of Alissa's PDF      *
*  Thumbnail Trimmer, try clearing the Windows Thumbnail         *
*  Cache and restart the Windows.  See 2.2 below for a           *
*  detailed instruction.                                         *
*                                                                *
******************************************************************


CONTENTS:
1. About Alissa's PDF Thumbnail Trimmer
2. Precautions and Known Issues
2.1 Precautions
2.2 Known Issues
3. System Requirements
4. Installing and Uninstalling
4.1 Installing
4.2 Uninstalling
4.3 Upgrading Adobe Reader
4.4 Source Files
5. Envoi
5.1 Acknowledgements
5.2 Questions?

---

1. About Alissa's PDF Thumbnail Trimmer

Alissa's PDF Thumbnail Trimmer is a small Windows program to improve
Adobe Reader's PDF thumbnail display behaviour.

Windows has a nice feature to show thumbnails (small preview pictures)
of files on the Desktop or other folder views.  Each thumbnail is
provided by the corresponding application program for the file.  If it
is a PDF file, and you have installed Adobe Reader on your PC as a
default PDF viewer program, a component of the Reader generates a
thumbnail for each PDF file behind the scenes.

Unfortunately, current Adobe Reader (including at least versions 8.X 
through 11.0.2) has some problems generating the thumbnail.

Alissa's PDF Thumbnail Trimmer slightly modifies the behaviour of
Adobe Reader's thumbnail generation, solving the following two major
problems.

(1) When the PDF's paper size is not a square (almost always it
    isn't), the generated thumbnail has extra white margins either on
    left and right or on top and bottom of the real thumbnail image so
    that the entire image is a square.  Alissa's PDF Thumbnail Trimmer
    removes them.  (So I call this program a "trimmer".)

(2) If your Windows is a 64 bit version (aka x64 edition), a PDF
    thumbnail doesn't appear soon on your folder views when it is
    created or copies.  (Or, it may seem never appearing.)  Alissa's
    PDF Thumbnail Trimmer makes sure the thumbnail always appears
    on 64 bit Windows.

2. Precautions and Known Issues

2.1 Precautions

Alissa's PDF Thumbnail Trimmer is technically a set of Windows Shell
Extensions.  "Shell Extension" is something like a plug-in to Windows
itself.  Once installed it becomes a part of Windows.  A bug of a
Shell Extension can affect stability of entire Windows operations.

Alissa's PDF Thumbnail Trimmer is a program under development by an
individual as a hobby.  You can't expect high quality like a sold
commercial program.  It is very likely to have some bugs.  By using
Alissa's PDF Thumbnail Trimmer, you risk crushing of Windows and/or
loss of important data on the PC.

2.2 Known Issues

After installing Alissa's PDF Thumbnail Trmmer, thumbnails for
existing PDF files may keep appearing as before, i.e., with white
margines.  It is probably caused by the Windows Thumbnail Caches.  A
workaround is to clear the Thumbnail Cache manually and restart
Windows.  Go to Start Menu > All Programs > Accessories > System Tools > Disk Cleanup
Tool and choose the drive C: *and* the drive your PDF files reside.
Make sure "Thumbnails" is checked and click "OK".  After the 
cleanup completed, restart the Windows.

3. System Requirements

Alissa's PDF Thumbnail Trimmer runs on recent Windows.  I tested it on
the following:

Windows XP (SP3)
Windows 7 (pre-SP1 32 bit and SP1 64 bit)

It should work on Windows Vista 32/64 bit.  It *may* also work on
Windows XP SP2 or before, or Windows XP x64 Edition.

You need to install Adobe Reader version 9, 10, or 11 *before* 
installing Alissa's PDF Thumbnail Trimmer.  Adobe Reader version 8 
*may* work; I'm not sure.  (Adobe Reader version 8 is known to have 
some unfixed security bugs and not recommended.)  Adobe Acrobat may 
also work.

4. Installing and Uninstalling

4.1 Installing

Alissa's PDF Thumbnail Trimmer is provided as an executable installer
of name "PDFThumbTrimmer-*-setup.exe", where * is a versin number and
".exe" may not be visible depending on your Windows settings.

Running the installer, e.g., double clicking on the file, will install
the Alissa's PDF Thumbnail Trimmer on the PC.

If you are on Windows Vista or Windows 7, and UAC (User Account
Control) is enabled, Privileges Elevation will be requested when
running the installer.

The installer will ask you for a location (folder) where the files are
copied.  Alissa's PDF Thumbnail Trimmer needs to be installed on a 32
bit folder; i.e., you can't install it on "C:\Program Files" on 64 bit
Windows, but you need to install it on "C:\Program Files (x86)"
folder.  On 32 bit Windows, all folders are 32 bit, and you don't need
to worry about this point.

Alissa's PDF Thumbnail Trimmer is a small program; you only need less
than 200k bytes of free disk space.

4.2 Uninstalling

Use "Add or Remove Programs" (Windows XP) or "Programs and Features"
(Windows 7) on Control Panel to uninstall Alissa's PDF Thumbnail
Trimmer.

Alternatively, you can run a program "uninst.exe" under the
installation folder.

The installer creates several new registry entries and modifies some
existing entries.  You need to revert the registry changes.  Just
removing installed files is not sufficient.  It is not recommended
to uninstall it manually without invoking the uninstaller.

4.3 Upgrading Adobe Reader

If you upgrade your Adobe Reader, Alissa's PDF Thumbnail Trimmer may
stop working.  You need to run the installer again in the case.  You
don't need to uninstall it before the re-install.

4.4 Source Files

The source files of Alissa's PDF Thumbnail Trimmer is not included in
the binary distribution but is published separately.  As of this
writing, the source is hoted by Github, and you will find it on the
following URL:

    https://github.com/AlissaSabre/PDFThumbTrimmer

5. Envoi

5.1 Acknowledgements

This work was opened up by a comment to my MobiHandler program.  I
didn't even know PDF has a thumbnail handler before reading the
comment.

The installer is build using NSIS (Nullsoft Scriptable Install
System.)  It is an open source project available on:
http://nsis.sourceforge.net

The installer also uses LZMA compression module.  It is a part of
another open source project, 7-Zip, available on: http://www.7-zip.org
and distributed together with NSIS.

5.2 Questions?

Questions, as well as comments, on Alissa's PDF Thumbnail Trimmer can
be e-mailed to Alissa Sabre <alissa_sabre@yahoo.co.jp>.  Please write
in English or Japanese.  (Japanese preferred.)
