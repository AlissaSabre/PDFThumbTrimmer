purge is a Windows command line tool that purges the thumbnail caches.
The installer of Alissa's PDF Thumbnail Trimmer will use it so that
the users see the new thumbnails immediately after the installation.

This command invokes the system's standard Disk Cleanup Handler for
desktop thumbnails to discard the persistent caches on all fixed
drives, then calls SHChangeNotify to let shell discard its on-memory
caches.  This two step process ensures that the newly installed
thumbnail handler is called and that the users see the updated
thumbnails soon.

