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
    
    unsigned char* read_name(sector sec, int offset, int size);
    int read_integer(sector sec, int offset, int size);
    void write_name(sector sec, char* name, int offset, int size);
    void write_integer(sector sec, int integer, int offset, int size);



#ifdef __cplusplus
}
#endif

#endif /* HELPER_H */

