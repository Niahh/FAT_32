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
    void write_sector(int sec, sector to_write);
    void delete_sector(sector sec);
#ifdef __cplusplus
}
#endif

#endif /* HDD_READ_H */

