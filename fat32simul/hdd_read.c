/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "hdd_read.h"
#include <stdlib.h>
#include <stdio.h>

void write_sector(int sec, sector to_write){
    for (int i = 0;i<512;i++){
         *(hdd+sec*512+i)= *(to_write+i);
    }
}
void delete_sector(sector sec){
    free(sec);
}
sector read_sector(int sec){
    sector ret = malloc(512*sizeof(unsigned char));
    for (int i = 0;i<512;i++){
        *(ret+i) = *(hdd+sec*512+i);
    }
    return ret;
}
