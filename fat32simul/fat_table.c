/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "fat32.h"

int get_next_cluster(fat32* fat, int cluster_number){
    printf("cluster number is : %d\n",cluster_number);
    printf("read at : %d\n",cluster_number*32);
    int curr_sec = 0;
    sector _fat_table = read_sector(fat->fat_begin_lba);
    int i= cluster_number;
    while (i >16){
        curr_sec++;
        _fat_table = read_sector(fat->fat_begin_lba+curr_sec);
        i -=16;
    }
    return read_integer(_fat_table,i*32,32);
}
int get_next_empty_cluster(fat32* fat){
    printf ("get empty cluster :\n");
    int curr_sec = 0;
    sector _fat_table = read_sector(fat->fat_begin_lba);
    int i= get_root_dir(fat)+1;
    int j = get_root_dir(fat)+1;
    while (i >16){
        curr_sec++;
        _fat_table = read_sector(fat->fat_begin_lba+curr_sec);
        i -=16;
    }
    for( ;read_integer(_fat_table,i*32,32)!=0;i++){
        while (i >16){
            curr_sec++;
            _fat_table = read_sector(fat->fat_begin_lba+curr_sec);
            i -=16;
        }
        printf("-  %d : %d ",i,read_integer(_fat_table,i*32,32));
        j++;
    }
    printf("  %d : %d  ",i,read_integer(_fat_table,i*32,32));
    printf("at %d\n",i*32);
    printf("found : %d\n",j);
    return j;
}
void add_to_table(fat32* fat, int cluster_begin, int cluster_following){
    int to_read = (32*cluster_begin)/512;
    sector _fat_table = read_sector(fat->fat_begin_lba+to_read);
    write_integer(_fat_table,cluster_following,(32*cluster_begin)%512,4);
    write_sector(fat->fat_begin_lba+to_read,_fat_table);
}
int realloc_directory(fat32* fat, int cluster_number){
    printf("got to an end\n");
    int new_cluster = get_next_empty_cluster(fat);
    printf("new cluster : %d\n",new_cluster);
    add_to_table(fat,cluster_number,new_cluster);
    return new_cluster;
}
void display_fat(fat32* fat){
    for (int i = fat->fat_begin_lba;i<fat->fat_begin_lba+fat->Sectors_Per_FAT;i++){
        for (int j = 0;j<512;j+=32){
            printf("%d",read_integer(hdd,j+i*512,32));
        }
    }
}
