/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "helper.h"
unsigned char* read_name(sector sec, int offset, int size){
    unsigned char* name = malloc(size *sizeof(int));
    for (int i =0;i<size;i++){
        name[i]=sec[i+offset];
    }
    return name;
}
int read_integer(sector sec, int offset, int size){
    int result = 0;
    int val = 1;
    for (int i =offset;i<offset+size;i++){
        result+=val*(int)sec[i];
        val*=256;
    }
    return result;
}
void write_name(sector sec, char* name, int offset, int size){
    for (int i =0;i<size;i++){
        sec[i+offset]=name[i];
    }
}
void write_integer(sector sec, int integer, int offset, int size){
    for (int i =0;i<size;i++){
        sec[i+offset]=(unsigned char)(integer%256);
        integer-=sec[i+offset];
        integer/=256;
    }
}