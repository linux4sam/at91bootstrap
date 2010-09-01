@echo off
set all_ek_list=9260 9261 9263 9rl 9g10 9g20 9g45 9m10 9g45ekes 9m10ekes
set all_mem_list=dataflash nandflash sdcard
set all_image_list=eboot cekernel uboot linuxkernel gettingstarted
set ek_list=""
set mem_list=""
set image_list=""

if "%3"=="" (
    echo Usage: build EK_TYPE MEMORY_TYPE IMAGE_TYPE
    echo        EK_TYPE: 9260 9261 9263 9rl 9g10 9g20 9g45 9m10 9g45ekes 9m10ekes all
    echo        MEMORY_TYPE: dataflash nandflash sdcard all
    echo        IMAGE_TYPE: eboot cekernel uboot linuxkernel gettingstarted all
    goto :EOF
)

:SELECT_EK
if %1==all (
    set ek_list=%all_ek_list%
    goto :SELECT_MEMORY
)

for %%i in (%all_ek_list%) do (
    if %1==%%i (
        set ek_list=%%i
    )
)

if %ek_list%=="" (
    echo select EK error!
    goto :EOF
)

:SELECT_MEMORY
if %2==all (
    set mem_list=%all_mem_list%
    goto :SELECT_IMAGE
)

for %%i in (%all_mem_list%) do (
    if %2==%%i (
        set mem_list=%%i
    )
)

if %mem_list%=="" (
    echo select memory error!
    goto :EOF
)

:SELECT_IMAGE
if %3==all (
    set image_list=%all_image_list%
    goto :BUILD
)

for %%i in (%all_image_list%) do (
    if %3==%%i (
        set image_list=%%i
    )
)

if %image_list%=="" (
    echo select image error!
    goto :EOF
)

:BUILD
set ek_mem_list=9260_dataflash 9260_nandflash 9261_dataflash 9261_nandflash 9263_dataflash 9263_nandflash 9263_sdcard 9rl_dataflash  9rl_nandflash  9rl_sdcard 9g10_dataflash 9g10_nandflash 9g10_sdcard 9g20_dataflash 9g20_nandflash 9g20_sdcard 9g45_dataflash 9g45_nandflash 9g45_sdcard 9m10_dataflash 9m10_nandflash 9m10_sdcard 9g45ekes_dataflash 9g45ekes_nandflash 9g45ekes_sdcard 9m10ekes_dataflash 9m10ekes_nandflash 9m10ekes_sdcard

for %%i in (%ek_list%) do (
    for %%j in (%mem_list%) do (
        for %%k in (%ek_mem_list%) do (
            if %%k==%%i_%%j (
                for %%m in (%image_list%) do (
                    echo %%i_%%j_%%m
                    if exist ..\image\obj\ARMV4I\retail\firstboot.nb0 del ..\image\obj\ARMV4I\retail\firstboot.nb0
                    call subbuild.bat goto %%i_%%j_%%m
                    copy ..\image\obj\ARMV4I\retail\firstboot.nb0 ..\output\%%i_%%j_%%m.nb0
                )
            )
        )
    )
)

:EOF