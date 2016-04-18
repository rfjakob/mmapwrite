mmapwrite
---------

Simple tool that creates a 50 MiB file, mmaps it, and rewrites it in a
loop in 1 MiB blocks.
One dot in the progress bar is one MiB, one line is 50 MiB.

Created to track down performance issues in in the kernel's FUSE
implementation: (linux-kernel thread)[https://lkml.org/lkml/2016/3/16/260],
(patch that fixes the issue)[https://patchwork.kernel.org/patch/8554181/]

Use `./encfs-test.sh` to automatically mount an encfs filesystem into
a temporary directory and run the test.

Or you can call mmapwrite manually:
```
Usage: mmapwrite FILENAME
```

Example output, testing against Linux 4.4.6:

```
mmapwrite$ ./encfs-test.sh 
gcc -std=gnu99 -Wall mmapwrite.c -o mmapwrite
  1 ..................................................  92.72 MB/s
  2 ..................................................  90.10 MB/s
  3 .................................................. 114.73 MB/s
  4 ..................................................  88.48 MB/s
[...]
 69 .................................................. 115.62 MB/s
 70 ..................................................  91.83 MB/s
 71 .................................................. 112.83 MB/s
 72 ..................................................  91.09 MB/s
 73 .................................................. 113.84 MB/s
 74 ..................................................  91.59 MB/s
 75 .................................................. 117.75 MB/s
 76 ................ [hangs]

```

Results by kernel version
-------------------------

```
4.0 ....... 140MB/s permanent
4.1 ....... 140MB/s permanent
4.2 ....... hangs after ~5GB
4.3 ....... hangs after ~1.5GB
4.4-rc4 ... hangs after ~2GB
4.4 ....... hangs after ~3GB
4.6-rc3-182-gb9f5dba ... hangs after ~6GB
```
