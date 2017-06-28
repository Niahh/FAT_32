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
    /**
     * the fat32 structure stores usefull informations to browse the filesystem
     */
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
    
    // Here are the functions used to format the disk before the beggining of the
    // programm
    
    /**
     * creates a mbr and volume id in the hdd variable.
     * @param disk_size the desired size of te disk
     * @param sec_per_clus the number of sectors per clusters.
     * @param sec_per_fat the number of sectors per fat.
     */
    void fat32_format(int disk_size, int sec_per_clus, int sec_per_fat);
    /**
     * creates a root directory with two files and a directory
     * @param fat
     */
    void create_root(fat32* fat);
    /**
     * initialise the fat32 structure by reading the mbr and the volume id.
     * @param fat
     */
    void fat32_init(fat32* fat);
    
    // Here are the functions used to browse into the filesystem.
    
    /**
     * get the root directory
     * @param fat : the fat32 structure
     * @return the adress of the first cluster of the root directory.
     */
    int get_root_dir(fat32* fat);
    /**
     * reads the volume id to get informations and store them in the fat32 
     * structure.
     * @param fat
     */
    void fat32_read_vol_id(fat32* fat);
    /**
     * Adds a file in a directory.
     * @param fat : the fat32 structure.
     * @param sec : the sector wic the file must be created into.
     * @param offset : the offset in the sector at wich the file must be created.
     * @param name : the name of the file to create
     */
    void add_file(fat32* fat, unsigned char* sec, int offset, char* name);
    /**
     * add a directory in a parent directory.
     * @param fat : the fat32 structure.
     * @param sec : the sector into wich the directory must be added.
     * @param cur_dir : the adress of the parent directory.
     * @param offset : the offset on wich the dir must be added.
     * @param name : the name of the new directory.
     */
    void add_dir(fat32* fat, unsigned char* sec, int cur_dir, int offset, char* name);
    /**
     * read the content of a file
     * @param fat : the fat32 structure.
     * @param sec : the sector containg the file.
     * @param offset : the offset of the file into the sector.
     * @return the content of the file 
     */
    unsigned char* read_file(fat32* fat, sector sec, int offset);
    /**
     * returns the adress of the cluster containing the content of the desired element
     * @param fat : the fat32 structure.
     * @param sec : the sector containing the file.
     * @param offset : the offset at wich the file is located.
     * @return the adress of the cluster containint the content of the element.
     */
    int get_dir_clus(fat32* fat, sector sec, int offset);
    /**
     * used for debbuging purpose, displays the elements in the given sector.
     * @param fat
     * @param sec
     */
    void display_sector_at(fat32* fat, int sec);
#ifdef __cplusplus
}
#endif

#endif /* FAT32_H */

