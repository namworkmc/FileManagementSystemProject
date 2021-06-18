#ifndef _NTFS_PARTITION_BOOT_SECTOR_
#define _NTFS_PARTITION_BOOT_SECTOR_

#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <iomanip>

void subB(BYTE sector[], int x, int y);

void subB_dec(BYTE sector[], int x, int y);

void subB_hex(BYTE sector[], int x, int y);

void asNTFS(BYTE s[512]);

#endif // !_NTFS_PARTITION_BOOT_SECTOR_
