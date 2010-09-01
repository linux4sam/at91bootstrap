!if 0
Copyright (c) Microsoft Corporation.  All rights reserved.

Use of this source code is subject to the terms of the Microsoft end-user
license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
If you did not accept the terms of the EULA, you are not authorized to use
this source code. For a copy of the EULA, please see the LICENSE.RTF on your
install media.

Module Name:
    makefile.inc

!endif

BootImage:
!IF "$(NOLINK)" == ""
    romimage $(ROMIMAGE_FLAGS) FirstBoot.bib

!IF "$(WINCEREL)"=="1"
    copy $(_PLATFORMROOT)\$(_TGTPLAT)\target\$(_TGTCPU)\$(WINCEDEBUG)\FirstBoot.* $(_FLATRELEASEDIR)
!ENDIF
!ENDIF
