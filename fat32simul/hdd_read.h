/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hdd_read.h
 * Author: user
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
    unsigned char*  read_name(sector sec, int offset, int size);
    int read_integer(sector sec, int offset, int size);
    sector read_sector(int sec);
    void write_sector(int sec, sector to_write);
    void write_integer(sector sec, int integer, int offset, int size);
    void write_name(sector sec, char* name, int offset, int size);
    void delete_sector(sector sec);
#ifdef __cplusplus
}
#endif

#endif /* HDD_READ_H */

