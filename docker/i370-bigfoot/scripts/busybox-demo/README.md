Demo of BusyBox
---------------
BusyBox provides several shells and a collection of basic OS tools. For
this demo, the `ash` shell (alternately, the `hush` shell) is used in
place of `/sbin/init` and thus provides an interactive user environment.

To compile BsyBox, the provided `defconfig` is recommended; otherwise
compilation can be a bit dicey. In addition, the present-day (Sept 2024)
BusyBox makes some minor assumptions about the modernity of the kernel,
breaking out old kernel. Thus, the patch in `busybox.patch` must be
applied, in order to build.

To summarize:
```
cd busybox
cp ../busbox-demo/defconfig .config
patch -p1 < ../busbox-demo/busybox.patch
make
```
