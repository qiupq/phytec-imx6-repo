======================
PHYTEC Yocto Linux BSP
======================

NOTE: For expert users who want to download our barebox and kernel only:
You can find all git repositories at:

  git://git.phytec.de

The barebox and kernel git repositories for this BSP are called
"barebox", "linux-mainline"  and "linux-ti". To find out which tag is
used for a specific board, run the buildinfo command:

 bitbake -c buildinfo [barebox/linux-mainline/linux-ti]

To find out which hardware is tested in the release, have a look at the
phytec webpage for a full list. You can also inspect the folder:

 meta-phytec/conf/machine/*.conf

for each release to find a description of the supported hardware.

=============
Documentation
=============

For further documentation, please visit the corresponding product page
at:

   http://www.phytec.de

You will find a BSP manual and a Yocto reference manual.
compile setup:
环境:ubuntu14.04-64bit
1.执行./phyLinux init
2.依次选择PD16.1.0;和4:phyboard-mira-imx6-7
3.source sources/poky/oe-init-build-env
4.bitbake phytec-qt5demo-image

