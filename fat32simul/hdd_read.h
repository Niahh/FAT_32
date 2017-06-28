/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hdd_read.h
 * Author: user
 *
 * This file is used to emulate the Read/Write sector interuptions availables in
 * the protected mode.
 * these two functions are the only ways the explorer will access the hdd variable.
 * 
 * Created on 24 juin 2017, 14:44
 */

#ifndef HDD_READ_H
#define HDD_READ_H
#define SECTOR_INIT malloc(512*sizeof(unsigned char)))

#ifdef __cplusplus
extern "C" {
#endif
    unsigned char* hdd;
    typedef unsigned char* sector;
    /**
     * emulates a function tha could use the int13h bios interuption to write the
     * content of a sector into memory and returns a pointer to it.
     * @param sec : the adress (LBA) of the sector to write.
     * @return 
     */
    sector read_sector(int sec);
    /**
     * writes the values of the given sector at the desired place in the disk.
     * @param sec : the LBA adress of the sector to write.
     * @param to_write : the array of bytes to write.
     */
    void write_sector(int sec, sector to_write);
    /**
     * frees the array containg the bytes.
     * @param sec
     */
    void delete_sector(sector sec);
#ifdef __cplusplus
}
#endif

#endif /* HDD_READ_H */

