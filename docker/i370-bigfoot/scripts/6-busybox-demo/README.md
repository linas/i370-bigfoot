Demo of BusyBox
---------------
BusyBox provides several shells and a collection of basic OS tools. For
this demo, the `ash` shell (alternately, the `hush` shell) is used in
place of `/sbin/init` and thus provides an interactive user environment.

To compile BusyBox, the provided `defconfig` is recommended; otherwise
compilation can be a bit dicey. In addition, the present-day (Sept 2024)
BusyBox makes some minor assumptions about the modernity of the kernel,
breaking our old kernel. Thus, the patch in `busybox.patch` must be
applied first, in order to build. Its a tiny patch.

To summarize:
```
cd busybox
cp ../busbox-demo/defconfig .config
patch -p1 < ../busbox-demo/busybox.patch
make
```

Once built, copy `busybox` to `root-disk` (the pre-configured root
filesystem in the directory below), and set the linux `cmd_line` to
`init=/busybox ash -i`. Upon booting, this will start the `ash` shell
in interactive mode. The very first thing you will need to do will be:
```
busybox mount -t proc foo /proc
```
The name `foo` doesn't matter. This will mount the `proc` filesystem
onto the directory `/proc`. Make sure your root disk has this directory
defined. Failing to mount `/proc` will make busybox a little harder to
use than normal: many commands will have to be explicitly launched by
saying `busybox command-name`.  A list of available commands can be
obtained with `help`. After this, you can get busy and punch away.

Suggested:
```
ls
ls -la
ps
ls -la /proc
ls -la /proc/self/*
PS1='my-i370:\w # '
echo "hullo, file\n" > my-file
cat my-file
```
