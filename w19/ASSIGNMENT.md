**Week 19 - August 17th @7:00 '22**

Continuing our journey into file systems.  FSCK (File System ChecK) is about repairing file systems, and journaling is about recovery after a crash or hardware failure.

Reading:

- Ch. 42 FSCK And Journaling
- Ch. 43 Log-structured File System (LFS)

Homework:

- Ch. 42 & 43 Simulation homework

Resources:

- [ext3](https://en.wikipedia.org/wiki/Ext3), the popular Linux journaling file system
- [XFS](https://en.wikipedia.org/wiki/XFS), the file system built at Sun (not to be confused with [ZFS](https://en.wikipedia.org/wiki/ZFS), the popular NAS file system).  Xfs is also the file system that RAP uses (Comscore)
- [ZFS](https://en.wikipedia.org/wiki/ZFS) deserves its own section, it has many powerful features (snapshots, replication), and combines logical volume management and a file system (in Linux, this is separated into LVM and the file system on top of that). ZFS also has amazing data integrity features.
