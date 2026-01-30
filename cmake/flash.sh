
if [ ! -f "$1" ]; then
    echo "Passed in file does not exist"
    exit 1
fi

# Assumes that the SD card is partition in exfat or fat32
disk_file=$(mount | awk '/^\/dev\/disk/ && /(msdos|exfat)/ {print $1}')

disk_mount_point=$(mount | awk '/^\/dev\/disk/ && /(msdos|exfat)/ {print $3}')

if [ -n "$disk_mount_point" -a -n "$disk_file" ]; then
    echo "Writing $1 to $disk_mount_point/BUILD.bin"
    cp "$1" "$disk_mount_point/BUILD.bin" && \
    diskutil eject "$disk_file"
else
    echo "Could not find disk file or mount point"
    exit 1
fi
