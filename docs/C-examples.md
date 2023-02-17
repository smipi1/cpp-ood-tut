# Examples in ANSI C

See simple ANSI C example:
* [student.h](../src/ansi-c-oop-example/student.h)
* [student.c](../src/ansi-c-oop-example/student.c)
* [main.c](../src/ansi-c-oop-example/main.c)
* [CPP wrapper for compilation](../src/ansi-c-oop-example/ansi-c-oop-example.cpp)

---

## Linux file operations example:

Linux provides a virtual interface for each file-system to provide its own specific functions (methods):

The virtual interface is defined in [include/linux/fs.h](https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/include/linux/fs.h?h=v6.1.12)
```C
struct file_operations {
        loff_t (*llseek) (struct file *, loff_t, int);
        ssize_t (*read_iter) (struct kiocb *, struct iov_iter *);
        ssize_t (*write_iter) (struct kiocb *, struct iov_iter *);

        long (*unlocked_ioctl) (struct file *, unsigned int, unsigned long);

        int (*mmap) (struct file *, struct vm_area_struct *);

        int (*open) (struct inode *, struct file *);

        int (*fsync) (struct file *, loff_t, loff_t, int datasync);

}
```

A file-system can implement the interface by assigning its own functions.

For [UBIFS](https://en.wikipedia.org/wiki/UBIFS), this is done in [fs/ubifs/file.c](https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/fs/ubifs/file.c?h=v6.1.12)
```C
const struct file_operations ubifs_file_operations = {
	.llseek         = generic_file_llseek,
	.read_iter      = generic_file_read_iter,
	.write_iter     = ubifs_write_iter,
	.unlocked_ioctl = ubifs_ioctl,
	.mmap           = ubifs_file_mmap,

	.open		    = fscrypt_file_open,

	.fsync          = ubifs_fsync,
};
```

And when a UBIFS inode is allocated for kernel interactions, the inode is bound to the implemented interface in [fs/ubifs/dir.c](https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/fs/ubifs/dir.c?h=v6.1.12):
```C
struct inode *ubifs_new_inode(struct ubifs_info *c, struct inode *dir,
			      umode_t mode, bool is_xattr)
{

    inode->i_fop = &ubifs_file_operations;

}
```

## So let's open a file

Sequence of events:
1. Use `glibc` to perform the `fopen()` or `open()` call using [stdio.h](https://sourceware.org/git/?p=glibc.git;a=blob;f=usr/include/stdio.h;h=4d8ec49712edf020d0db28b69f7074b980d9eb3e;hb=HEAD):
   ```C
   extern FILE *fopen (const char *__restrict __filename,
                       const char *__restrict __modes)
   ```
2. `glibc` performs input validation and performs a system call
   - Excerpt from [libio/iofopen.c](https://sourceware.org/git/?p=glibc.git;a=blob;f=libio/iofopen.c;h=4d8ec49712edf020d0db28b69f7074b980d9eb3e;hb=HEAD):
      ```C
      versioned_symbol (libc, __new_fopen, fopen, GLIBC_2_1);
      strong_alias (_IO_new_fopen, __new_fopen)
      //...
      FILE *
      _IO_new_fopen (const char *filename, const char *mode)
      {
        return __fopen_internal (filename, mode, 1);
      }
      //...
      FILE *
      __fopen_internal (const char *filename, const char *mode, int is32)
      {
      // ...
          if(_IO_file_fopen ((FILE *) new_f, filename, mode, is32) != NULL)
      // ...
      }
      ```
   - Excerpt from [libio/fileops.c](https://sourceware.org/git/?p=glibc.git;a=blob;f=libio/fileops.c;h=4d8ec49712edf020d0db28b69f7074b980d9eb3e;hb=HEAD):
     ```C
     FILE *
     _IO_file_open (FILE *fp, const char *filename, int posix_mode, int prot,
                    int read_write, int is32not64)
     {
     // ...
         fdesc = __open_nocancel(filename,
                                 posix_mode | (is32not64 ? 0 : O_LARGEFILE), prot);
     // ...
     }
     ```
   - Excerpt from [sysdeps/unix/sysv/linux/open_nocancel.c](https://sourceware.org/git/?p=glibc.git;a=blob;f=sysdeps/unix/sysv/linux/open_nocancel.c;h=4d8ec49712edf020d0db28b69f7074b980d9eb3e;hb=HEAD):
     ```C
     int
     __open_nocancel (const char *file, int oflag, ...)
     {
     // ...
       return INLINE_SYSCALL_CALL (openat, AT_FDCWD, file, oflag, mode);
     }
     ```
3. Linux handles the system call using dynamic dispatch to call the right function for the `ubifs` file system:    
   - Excerpt from [fs/open.c](https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/fs/open.c?h=v6.1.12):
     ```C
     SYSCALL_DEFINE4(openat, int, dfd, const char __user *, filename, int, flags,
     		umode_t, mode)
     {
     // ...
         return do_sys_open(dfd, filename, flags, mode);
     }
     
     long do_sys_open(int dfd, const char __user *filename, int flags, umode_t mode)
     {
     // ...
     	return do_sys_openat2(dfd, filename, &how);
     }
     
     static long do_sys_openat2(int dfd, const char __user *filename,
     			   struct open_how *how)
     {
     // ...
         struct file *f = do_filp_open(dfd, tmp, &op);
     // ...
     }
     ```
   - Excerpt from [fs/namei.c](https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/fs/namei.c?h=v6.1.12):
     ```C
     struct file *do_filp_open(int dfd, struct filename *pathname,
     		const struct open_flags *op)
     {
     // ...
         filp = path_openat(&nd, op, flags);
     // ...
     }
     
     static struct file *path_openat(struct nameidata *nd,
     			const struct open_flags *op, unsigned flags)
     {
     // ...
         error = do_o_path(nd, flags, file);
     // ...
     }
     
     static int do_o_path(struct nameidata *nd, unsigned flags, struct file *file)
     {
     // ...
         error = vfs_open(&path, file);
     // ...
     }
     ```
   - Excerpt from [fs/open.c](https://git.kernel.org/pub/scm/linux/kernel/git/stable/linux.git/tree/fs/open.c?h=v6.1.12)
     ```C
     int vfs_open(const struct path *path, struct file *file)
     {
             file->f_path = *path;
             return do_dentry_open(file, d_backing_inode(path->dentry), NULL);
     }
     
     static int do_dentry_open(struct file *f,
                               struct inode *inode,
                               int (*open)(struct inode *, struct file *))
     {
     // ...
         f->f_op = fops_get(inode->i_fop);
     // ...
         open = f->f_op->open;
     // ...
         error = open(inode, f);
     // ...
     }
     ```
    
    
---

[Previous](./context.md) | [Top](../README.md) | [Next](./CPP-examples.md)