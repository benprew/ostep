**Week 11 - Tue May 24th @7:00 '22**

We're wrapping up the section on virtual memory (the 1st of the 3 easy pieces) by reading about a full implementation of a VM system.  Since there is no homework in the chapter for chapter 23, I was thinking we could write a (hopefully) simple program to investigate the linux vm system.

*Assignment:*

- Read chapters 23
- [Optional] Write a program to calculate USS (unique set size) for a pid

*Homework:*

Write a program that will calculate unique set size for a pid. USS is the amount of memory that a process is using that is not shared with any other process.

To do this, you'll be using some special files in the /proc directory:

- `/proc/$PID/pagemap` - Lets a userspace process find out which physical frame each virtual page is mapped to. It contains one 64-bit value for each virtual page.
- `/proc/$PID/maps` - Shows what process memory is mapped (so you can pread from the offset)
- `/proc/kpagecount` - This file contains a 64-bit count of the number of times each page is mapped, indexed by PFN.

*Algorithm:*

Use `/proc/$pid/maps` to determine which areas of memory are actually mapped and `lseek` to skip over unmapped regions.

1. Read `/proc/$pid/maps` to determine which parts of the memory space are mapped to what.
2. Select the maps you are interested in – in this case, all of them
3. Open `/proc/$pid/pagemap` and seek to the pages you would like to examine.
4. Read a u64 for each page from pagemap (see below for extracting th PFN from the pagemap entry).
5. Open `/proc/kpagecount`. For each PFN you just read, seek to that entry in the file, and tally up the number of pages that are only referenced once.

*ProcMapEntry*

Each row in `/proc/$PID/maps` describes a region of contiguous virtual memory in a process or thread. Each row has the following fields:

    address           perms offset  dev   inode   pathname
    08048000-08056000 r-xp 00000000 03:0c 64593   /usr/sbin/gpm

- address - This is the starting and ending address of the region in the process's address space
- permissions - This describes how pages in the region can be accessed. There are four different permissions: read, write, execute, and shared. If read/write/execute are disabled, a - will appear instead of the r/w/x. If a region is not shared, it is private, so a p will appear instead of an s. If the process attempts to access memory in a way that is not permitted, a segmentation fault is generated. Permissions can be changed using the mprotect system call.
- offset - If the region was mapped from a file (using mmap), this is the offset in the file where the mapping begins. If the memory was not mapped from a file, it's just 0.
- device - If the region was mapped from a file, this is the major and minor device number (in hex) where the file lives.
- inode - If the region was mapped from a file, this is the file number.
- pathname - If the region was mapped from a file, this is the name of the file. This field is blank for anonymous mapped regions. There are also special regions with names like [heap], [stack], or [vdso]. [vdso] stands for virtual dynamic shared object. It's used by system calls to switch to kernel mode. Here's a good article about it: "[What is linux-gate.so.1?](https://web.archive.org/web/20161122032625/http://www.trilithium.com/johan/2005/08/linux-gate/)"


*PageMapEntry:*

The pagemap entry contains the following data (from fs/proc/task_mmu.c, above pagemap_read):

        Bits 0-54 page frame number (PFN) if present
        Bits 0-4 swap type if swapped
        Bits 5-54 swap offset if swapped
        Bit 55 pte is soft-dirty (see Documentation/admin-guide/mm/soft-dirty.rst)
        Bit 56 page exclusively mapped (since 4.2)
        Bit 57 pte is uffd-wp write-protected (since 5.13) (see Documentation/admin-guide/mm/userfaultfd.rst)
        Bits 58-60 zero
        Bit 61 page is file-page or shared-anon (since 3.5)
        Bit 62 page swapped
        Bit 63 page present

*Sample Code*

- [Read from pagemap](https://github.com/cirosantilli/linux-kernel-module-cheat/blob/25f9913e0c1c5b4a3d350ad14d1de9ac06bfd4be/kernel_module/user/common.h)
