# meta-qcom

## Introduction

OpenEmbedded/Yocto Project layer for Qualcomm based platforms.

This layer depends on:

```
URI: git://github.com/openembedded/oe-core.git
layers: meta
branch: master
revision: HEAD
```

## EULA

Some SoC depends on firmware and/or packages that are covered by
Qualcomm EULA. To have the right to use those binaries in your images
you need to read and accept the EULA available as:

conf/eula/$MACHINE, e.g. conf/eula/dragonboard-410c

In order to accept it, you should add, in your local.conf file:

ACCEPT_EULA_$MACHINE = "1", e.g.: ACCEPT_EULA_dragonboard-410c = "1"

If you do not accept the EULA the generated image will be missing some
components and features.

## Contributing

If you want to contribute changes, you can send Github pull requests at
https://github.com/ndechesne/meta-qcom/pulls.

Alternatively you can send patches to openembedded@lists.linaro.org, in which
case, please: 

* When creating patches, please use something like:

`git format-patch -s --subject-prefix='meta-qcom][PATCH' origin`

* When sending patches, please use something like:

`git send-email --to openembedded@lists.linaro.org <generated patch>`

You can discuss about this layer, on `#linaro` on FreeNode IRC network.

## Reporting issues

Please report any issue on https://github.com/ndechesne/meta-qcom/issues

## Maintainer(s)

Nicolas Dechesne <nicolas.dechesne@linaro.org>
