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
#include <stdlib.h>
#include "fat_table.h"
#include "explorer.h"

#ifdef __cplusplus
extern "C" {
#endif
    /**
     * an element can be a directory or a file.
     * it contains the low and high parts of the adresse to the first cluster 
     * of its content, but also the size and the name of the element.
     */
    typedef struct element {
        unsigned char* name;
        int cluster_high;
        int size;
        int type;
    } element;
    /**
     * the explorer contains the fat and some contextual informations to navigate 
     * into the filesystem, the adress of the cluster of the current dir, the 
     * name of the current dir and the list of sub directories.
     */
    typedef struct explorer {
        fat32* fat;
        int current_dir;
        char* current_dir_name;
        list* sub_dirs;
    } explorer;
    /**
     * starts the explorer, the explorer will read into the global variable hdd
     * and use it as a disk drive using the fat32 structure.
     */
    void start();
    /**
     * displays a dialog on the screen to ask the user to create/select/remove 
     * an element in the current directory.
     * @param ex the explorer.
     */
    void dir_dialog(explorer* ex);
    /**
     * prints a dialog to ask the user to write a number to quit the currently
     * selected file.
     * @param ex : the explorer
     */
    void file_dialog(explorer* ex);
    /**
     * ask to select an element in the list of sub directories.
     * @param ex the explorer.
     */
    void select_element(explorer* ex);
    /**
     * asks the user to give the name and type of the element he wishes to create.
     * @param ex the explorer.
     */
    void add_element(explorer* ex);
    /**
     * asks the user to give the number of the element he wishes to destroy.
     * @param ex : the explorer.
     */
    void remove_element(explorer* ex);
    /**
     * displays a directory.
     * @param ex the explorer.
     * @param element_num the number of the first cluster containing the element.
     * @param element_name the name of the directory.
     */
    void display_dir(explorer* ex,int element_num, char* element_name);
    /**
     * displays the root directory.
     * @param ex : the explorer.
     */
    void display_root_dir(explorer* ex);
    /**
     * explore a directory and returns a list of the elements found in the dir.
     * @param ex : the explorer.
     * @param cluster_number the adress of the first cluster of the directory.
     */
    void explore_element(explorer* ex, int cluster_number);
    /**
     * creates an element in the current directory.
     * @param ex : the explorer
     * @param file_name : the name of the element.
     * @param type the type : 1 for directory, 2 for file.
     */
    void create_elem(explorer* ex, char* file_name, int type);
    /**
     * displays a line of informations about an element.
     * @param element : the element.
     */
    void print_element_infos(element* element);
#ifdef __cplusplus
}
#endif

#endif /* EXPLORER_H */

