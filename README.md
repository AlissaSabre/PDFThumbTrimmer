PDFThumbTrimmer
=========

A Windows Shell extension for better PDF thumbnail handling

What is this?
----

Alissa's PDF Thumbnail Trimmer (or PDFThumbTrimmer for short) is a small Windows program to improve the desktop thumbnails from PDF files by Adobe Reader or Acrobat used on Windows.

The Problem
----

Windows Explorer shows files on the desktop using thumbnails.  It also provides a thumbnail view for folder windows.

Windows has a nice feature to show thumbnails (small preview pictures) of files on the Desktop or other folder views.  Each thumbnail is provided by the corresponding application program for the file.  If it is a PDF file, and you have installed Adobe Reader or Acrobat on your PC as a default PDF viewer program, it generates a thumbnail for each PDF file behind the scenes.

Unfortunately, current Adobe Reader has two problems generating the thumbnail.  PDFThumbTrimmer fixes the issue.

- When the PDF's paper size is not a square (almost always it isn't), the generated thumbnail has extra white margins either on left and right or on top and bottom of the real thumbnail image so that the entire image is a square.  Alissa's PDF Thumbnail Trimmer removes them.  (So I call this program a "trimmer".)
- If your Windows is a 64 bit version (aka x64 edition), a PDF thumbnail doesn't appear soon on your folder views when it is created or copies.  (Or, it may seem never appearing.)  Alissa's PDF Thumbnail Trimmer makes sure the thumbnail appears on 64 bit Windows.
