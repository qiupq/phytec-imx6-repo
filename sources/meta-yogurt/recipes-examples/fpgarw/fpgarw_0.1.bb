
DESCRIPTION = "FPGA read and write recipe"

SECTION = "extras"

# must have License;or bitbake -s warning 
LICENSE = "MIT"
# Recipe file does not have license file information (LIC_FILES_CHKSUM) [license-checksum]
LIC_FILES_CHKSUM = "file://fpgarw.c;beginline=1;endline=17;md5=8427499345b4470a964370d7b65f695a"

PR = "r1"

SRC_URI = "file://fpgarw.c"

S = "${WORKDIR}"

do_compile () {
    ${CC} ${CFLAGS} -Wall ${LDFLAGS} \
        -o ${B}/fpgarw ${S}/fpgarw.c 
}

do_build () {
  echo "first: some shell script running as build"
}
