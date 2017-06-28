/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   helper.h
 * Author: user
 *
 * Created on 26 juin 2017, 15:25
 */

#ifndef HELPER_H
#define HELPER_H

#ifdef __cplusplus
extern "C" {
#endif
#include "hdd_read.h"
#include <stdio.h>
#include <stdlib.h>
    /**
     * reads a string at a specific offset in the byte array.
     * @param sec : the sector/byte array 
     * @param offset the offset of the string.
     * @param size : the size of the string.
     * @return the string found.
     */
    unsigned char* read_name(sector sec, int offset, int size);
    /**
     * read an integer at a specific offset in the byte array. (Big endian)
     * @param sec : the sector/byte array
     * @param offset : the offset of the integer.
     * @param size : the size in bytes of the integer.
     * @return the integer
     */
    int read_integer(sector sec, int offset, int size);
    /**
     * Writes a string in the sector.
     * @param sec : the sector.
     * @param name : the string to write.
     * @param offset : the offset to write at.
     * @param size : the size of the string.
     */
    void write_name(sector sec, char* name, int offset, int size);
    /**
     * writes an integer in the sector.
     * @param sec : the sector.
     * @param integer : the integer to write.
     * @param offset : the offset to write at.
     * @param size : the size of the integer.
     */
    void write_integer(sector sec, int integer, int offset, int size);

#ifdef __cplusplus
}
#endif

#endif /* HELPER_H */

