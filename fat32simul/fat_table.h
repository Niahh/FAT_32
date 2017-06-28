/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   fat_table.h
 * Author: user
 * this file contains functions to use the fat, reconstitute directories/files by following 
 * the cluster chains.
 * Created on 26 juin 2017, 01:43
 */

#ifndef FAT_TABLE_H
#define FAT_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "fat32.h"
    
    /**
     * returns the next cluster for a given element.
     * @param fat : the fat32 structure.
     * @param cluster_number : the adress of the cluster of the element.
     * @return the next cluster.
     */
    int get_next_cluster(fat32* fat, int cluster_number);
    /**
     * returns the number of the next unused cluster.
     * @param fat : the fat32 structure.
     * @return the adress of the next unused cluster.
     */
    int get_next_empty_cluster(fat32* fat);
    /**
     * add a cluster to an element in the table
     * @param fat : the fat32 structure.
     * @param cluster_begin : the adress of the last cluster of the element.
     * @param cluster_following : the desired 
     * adress of the next cluster of the element.
     */
    void add_to_table(fat32* fat, int cluster_begin, int cluster_following);
    /**
     * increase the size of the current element.
     * @param fat : the fat32 structure.
     * @param cluster_number : the adress of the last cluster of the element.
     * @return the adress of the next cluster of the element.
     */
    int realloc_directory(fat32* fat, int cluster_number);
    /**
     * used for debugging purposes.
     * displays the 32bits values int the file allocation table.
     * @param fat : the fat32 table.
     */
    void display_fat(fat32* fat);



#ifdef __cplusplus
}
#endif

#endif /* FAT_TABLE_H */

