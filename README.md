mmapwrite
---------

Simple tool that creates a 50 MiB file, mmaps it, and rewrites it in a
loop in 1 MiB blocks.
One dot in the progress bar is one MiB, one line is 50 MiB.

Created to track down performance issues in in the kernel's FUSE
implementation.

Example output, testing against encfs on Linux 4.4:

```
$ mmapwrite /tmp/encfs-mnt/foo
  1 .................................................. 107.01 MB/s
  2 .................................................. 101.98 MB/s
[...]
 68 .................................................. 106.79 MB/s
 69 .................................................. 105.09 MB/s
 70 ..................................................   2.02 MB/s
 71 ..................................................   1.77 MB/s
 72 ..................................................   0.42 MB/s
 73 ....................................

```

Results by kernel version
-------------------------

```
4.0 ....... 140MB/s permanent
4.1 ....... 140MB/s permanent
4.2 ....... 100MB/s at the beginning, sudden slowdown to 1MB/s after ~5GB
4.3 ....... 100MB/s at the beginning, sudden slowdown to 1MB/s after ~1.5GB
4.4-rc4 ... 100MB/s at the beginning, slowly ramps down, 0.3MB/s after ~2GB
4.4 ....... 100MB/s at the beginning, sudden slowdown after ~3GB
```
