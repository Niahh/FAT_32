/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include <stdlib.h>
#include "fat_table.h"
#include "explorer.h"
#include "array_list.h"
void start(){
    explorer* ex = malloc(sizeof(explorer));
    ex->fat = malloc(sizeof(fat32));
    fat32_init(ex->fat);
    display_root_dir(ex);
    ex->current_dir = get_root_dir(ex->fat);
    ex->current_dir_name = "root";
    dir_dialog(ex);
}
void dir_dialog(explorer* ex){
    printf("press 1 to select an element, 2 to add a element or 3 to remove a element\n");
    int choice;
    scanf("%d",&choice);
    switch (choice){
        case 1 :
            select_element(ex);
            break;
        case 2 :
            add_element(ex);
            break;
        case 3 :
            remove_element(ex);
            break;
    }
}
void file_dialog(explorer* ex){
    int quit = 0;
    printf("\n\nenter any number to quit file");
    scanf("%d",&quit);
    display_dir(ex,ex->current_dir,ex->current_dir_name);
    dir_dialog(ex);
}
void select_element(explorer* ex){
    printf("type the number of the element you want to select(0 for the first element)\n");
    int to_rd = 0;
    scanf("%d",&to_rd);
    element* elem = (element*)(list_at(ex->sub_dirs,to_rd));
    if (elem->type==0){
        printf("\n\n\n\n\n\nfile : %s\n\n",(elem)->name);
        printf("%s\n",read_file(ex->fat,read_sector(ex->current_dir),32*to_rd));
    } else if (elem->type==4){
        int next_cluster_id = get_dir_clus(ex->fat, read_sector(ex->current_dir), 32*to_rd);
        display_dir(ex,next_cluster_id, (char*)elem->name);
        dir_dialog(ex);
    }
    file_dialog(ex);
}
void add_element(explorer* ex){
    printf("type the name of the element you want to create\n");
    char name[11];
    scanf("%s",name);
    printf("chosen name is %s\n",name);
    printf("type 1 to create a directory or 2 to create a file\n");
    int type;
    scanf("%d",&type);
    create_elem(ex,name,type);
    display_dir(ex,ex->current_dir,ex->current_dir_name);
    dir_dialog(ex);
}
void remove_element(explorer* ex){
    printf("type the number of the element you want to remove(0 for the first element)\n");
    int to_rem = 0;
    scanf("%d",&to_rem);
    sector cluster_beg = read_sector(ex->current_dir);
    write_integer(cluster_beg,0xE5,32*to_rem,32);
    write_sector(ex->current_dir,cluster_beg);
    display_dir(ex,ex->current_dir,ex->current_dir_name);
    dir_dialog(ex);
}


void display_dir(explorer* ex,int element_num, char* element_name){
    ex->current_dir = element_num;
    ex->current_dir_name = element_name;
    printf("\n\n\n\n\n\n=====================\n element : %s : \n\n",element_name);
    explore_element(ex,element_num);
    for (int i= 0;i<ex->sub_dirs->size;i++){
        print_element_infos(list_at(ex->sub_dirs,i));
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n");
}
void display_root_dir(explorer* ex){
    display_dir(ex,get_root_dir(ex->fat),"root");
}

void explore_element(explorer* ex, int cluster_number){
    sector cluster_begin = read_sector(cluster_number);
    ex->sub_dirs = list_create();
    for (int i =0;read_integer(cluster_begin,i*32,1)!=0;i++){
        if (read_integer(cluster_begin,i*32,32)!=0xE5){
            element* element = malloc(sizeof(element));
            element->name = read_name(cluster_begin,i*32,6);
            element->cluster_high = read_integer(cluster_begin, i*32+0x14,2);
            element->size = read_integer(cluster_begin, i*32+0x1C,4);
            element->type = read_integer(cluster_begin,i*32+0x0B,1);
            list_add(ex->sub_dirs, element);
        }
        if (i==(512*ex->fat->BPB_SecPerClus)/32-1){
            cluster_number = get_next_cluster(ex->fat,cluster_number);
            cluster_begin = read_sector(cluster_number);
            i = 0;
        }
    }
}


void create_elem(explorer* ex, char* file_name, int type){
    int cluster_number = ex->current_dir;
    sector cluster_begin = read_sector(cluster_number);
    ex->sub_dirs = list_create();
    int i;
    for (i =0;read_integer(cluster_begin,i*32,1)!=0;i++){
        if (read_integer(cluster_begin,i*32,32)==0xE5){
            if (type == 2){
                printf("add file : \n\n");
                add_file(ex->fat,cluster_begin,i*32,file_name);
            } if (type == 1){
                printf("add dir : \n\n");
                add_dir(ex->fat,cluster_begin, ex->current_dir,i*32,file_name);
            }
            write_sector(cluster_number,cluster_begin);
            return ;
        }
        if (i==(512*ex->fat->BPB_SecPerClus)/32-1){
            cluster_number = get_next_cluster(ex->fat,cluster_number);
            cluster_begin = read_sector(cluster_number);
            i = 0;
        }
    }
    if (type == 2){
        printf("add file : \n\n");
        add_file(ex->fat,cluster_begin,i*32,file_name);
    } if (type == 1){
        printf("add dir : \n\n");
        add_dir(ex->fat,cluster_begin, ex->current_dir,i*32,file_name);
    }
    write_sector(cluster_number,cluster_begin);
}

void print_element_infos(element* element){
    if (element->type!=0){
        printf("dir : ");
    } else {
        printf("file : ");
    }
        printf("%s     size : %d     type : %d\n",element->name, element->size, element->type);
        
}