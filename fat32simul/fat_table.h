/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fat_table.h
 * Author: user
 *
 * Created on 26 juin 2017, 01:43
 */

#ifndef FAT_TABLE_H
#define FAT_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "fat32.h"
int get_next_cluster(fat32* fat, int cluster_number);
int get_next_empty_cluster(fat32* fat);
void add_to_table(fat32* fat, int cluster_begin, int cluster_following);
int realloc_directory(fat32* fat, int cluster_number);
void display_fat(fat32* fat);



#ifdef __cplusplus
}
#endif

#endif /* FAT_TABLE_H */

