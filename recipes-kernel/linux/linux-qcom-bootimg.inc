python __anonymous () {
    depends = d.getVar("DEPENDS", True)
    depends = "%s skales-native" % depends
    d.setVar("DEPENDS", depends)
}

QCOM_BOOTIMG_ROOTFS ?= "undefined"

# set output file names
DT_IMAGE_BASE_NAME = "dt-${PKGE}-${PKGV}-${PKGR}-${MACHINE}-${DATETIME}"
DT_IMAGE_BASE_NAME[vardepsexclude] = "DATETIME"

BOOT_IMAGE_BASE_NAME = "boot-${PKGE}-${PKGV}-${PKGR}-${MACHINE}-${DATETIME}"
BOOT_IMAGE_BASE_NAME[vardepsexclude] = "DATETIME"

do_deploy_append_dragonboard-410c() {

    dtbTool -o ${DEPLOYDIR}/${DT_IMAGE_BASE_NAME}.img -s 2048 ${B}/arch/${ARCH}/boot/dts/qcom/

    tmp="${SERIAL_CONSOLES}"
    baudrate=`echo $tmp | sed 's/\;.*//'`
    ttydev=`echo $tmp | sed -e 's/^[0-9]*\;//' -e 's/\s.*//' -e 's/\;.*//'`

    # mkbootimg requires an initrd file, make fake one that will be ignored
    # during boot
    echo "This is not an initrd" > ${B}/initrd.img

    mkbootimg --kernel ${B}/arch/${ARCH}/boot/Image \
              --ramdisk ${B}/initrd.img \
              --output ${DEPLOYDIR}/${BOOT_IMAGE_BASE_NAME}.img \
              --dt ${DEPLOYDIR}/${DT_IMAGE_BASE_NAME}.img \
              --pagesize 2048 \
              --base 0x80000000 \
              --cmdline \
              "root=/dev/${QCOM_BOOTIMG_ROOTFS} rw rootwait console=${ttydev},${baudrate}n8"

    cd ${DEPLOYDIR}
	ln -sf ${DT_IMAGE_BASE_NAME}.img dt-${MACHINE}.img
	ln -sf ${BOOT_IMAGE_BASE_NAME}.img boot-${MACHINE}.img
    cd -
}

do_deploy_append_ifc6410 () {

    tmp="${SERIAL_CONSOLES}"
    baudrate=`echo $tmp | sed 's/\;.*//'`
    ttydev=`echo $tmp | sed -e 's/^[0-9]*\;//' -e 's/\s.*//' -e 's/\;.*//'`

    # mkbootimg requires an initrd file, make fake one that will be ignored
    # during boot
    echo "This is not an initrd" > ${B}/initrd.img

    mkbootimg --kernel ${B}/arch/${ARCH}/boot/zImage \
              --ramdisk ${B}/initrd.img \
              --output ${DEPLOYDIR}/${BOOT_IMAGE_BASE_NAME}.img \
              --pagesize 2048 \
              --base 0x80200000 \
              --cmdline \
              "root=/dev/${QCOM_BOOTIMG_ROOTFS} rw rootwait console=${ttydev},${baudrate}n8"

    cd ${DEPLOYDIR}
	ln -sf ${BOOT_IMAGE_BASE_NAME}.img boot-${MACHINE}.img
    cd -
}
