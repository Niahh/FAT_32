/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
/* 
 * File:   main.c
 * Author: user
 *
 * Created on 3 juin 2017, 22:44
 */
#include <stdio.h>
#include <stdlib.h>
#include "fat32.h"
#include "explorer.h"
/*
 * 
 */
int main(int argc, char** argv) {
    fat32_format(65536*512,10,30);
    printf("\n=======================================\nstart reading here\n\n");
    start();
    return (EXIT_SUCCESS);
}