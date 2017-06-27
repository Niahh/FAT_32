/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   explorer.h
 * Author: user
 *
 * Created on 25 juin 2017, 05:23
 */

#ifndef EXPLORER_H
#define EXPLORER_H
#include "fat32.h"
#include "array_list.h"

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct element {
        unsigned char* name;
        int cluster_high;
        int size;
        int type;
    } element;

    typedef struct explorer {
        fat32* fat;
        int current_dir;
        char* current_dir_name;
        list* sub_dirs;
    } explorer;/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include "fat_table.h"
#include "explorer.h"
#include "array_list.h"
void start();
void dir_dialog(explorer* ex);
void file_dialog(explorer* ex);
void select_element(explorer* ex);
void add_element(explorer* ex);
void remove_element(explorer* ex);
void display_dir(explorer* ex,int element_num, char* element_name);
void display_root_dir(explorer* ex);
void explore_element(explorer* ex, int cluster_number);

void create_file(explorer* ex, char* file_name);
void print_element_infos(element* element);
#ifdef __cplusplus
}
#endif

#endif /* EXPLORER_H */

