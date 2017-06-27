/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fat32.h
 * Author: user
 *
 * Created on 24 juin 2017, 15:02
 */

#ifndef FAT32_H
#define FAT32_H
#include "hdd_read.h"
#include <stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

    typedef struct fat32 {
        unsigned long Partition_LBA_Begin;
        unsigned long Number_of_Reserved_Sectors;
        unsigned long Number_of_FATs;
        unsigned long BPB_SecPerClus;
        unsigned long BPB_RootClus;
        unsigned long Sectors_Per_FAT;
        unsigned long fat_begin_lba;
        unsigned long cluster_begin_lba;
    } fat32;
    
void fat32_init(fat32* fat) ;

int get_root_dir(fat32* fat);
void fat32_read_vol_id(fat32* fat);
void fat32_format(int disk_size, int sec_per_clus, int sec_per_fat);
void create_root(fat32* fat);
void add_file(fat32* fat, unsigned char* sec, int offset, char* name);
void add_dir(fat32* fat, unsigned char* sec, int cur_dir, int offset, char* name);

unsigned char* read_file(fat32* fat, sector sec, int offset);
int get_dir_clus(fat32* fat, sector sec, int offset);
void display_sector_at(fat32* fat, int sec) ;
#ifdef __cplusplus
}
#endif

#endif /* FAT32_H */

