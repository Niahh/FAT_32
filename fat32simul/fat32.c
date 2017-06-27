/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include "fat32.h"
#include "fat_table.h"
#include "helper.h"

void fat32_init(fat32* fat) {
    sector first_sec = read_sector(0);
    if (!((int) first_sec[451] == 11 || (int) first_sec[451] == 12)) {
        printf("%d", (int) first_sec[451]);
        printf("type is not fat32\n");
    }
    fat->Partition_LBA_Begin = read_integer(first_sec, 455, 3);
    printf("lba begin =  %d\n", (int) fat->Partition_LBA_Begin);
    fat32_read_vol_id(fat);
}

int get_root_dir(fat32* fat) {
    return fat->cluster_begin_lba + fat->BPB_RootClus * fat->BPB_SecPerClus;
}

void fat32_read_vol_id(fat32* fat) {
    sector vol_id = read_sector(fat->Partition_LBA_Begin);
    fat->Number_of_Reserved_Sectors = read_integer(vol_id, 0x0E, 2);
    fat->Number_of_FATs = 2;
    fat->BPB_SecPerClus = read_integer(vol_id, 0x0D, 1);
    fat->BPB_RootClus = read_integer(vol_id, 0x2C, 4);
    fat->Sectors_Per_FAT = read_integer(vol_id, 0x24, 4);
    fat->fat_begin_lba = fat->Partition_LBA_Begin + fat->Number_of_Reserved_Sectors;
    printf("fat begin : %lu \n\n\n", fat->fat_begin_lba);
    fat->cluster_begin_lba = fat->Partition_LBA_Begin + fat->Number_of_Reserved_Sectors
            + (fat->Number_of_FATs * fat->Sectors_Per_FAT);
    printf("number of reserved sectors : %lu \n", fat->Number_of_Reserved_Sectors);
    printf("number of fat : %lu \n", fat->Number_of_FATs);
    printf("sec per fat : %lu \n", fat->Sectors_Per_FAT);
    printf("sec per clus : %lu \n", fat->BPB_SecPerClus);
    printf("clust begin : %lu \n", fat->cluster_begin_lba);
    printf("root cluster : %lu \n", fat->BPB_RootClus);
    printf("fat begin : %lu \n", fat->fat_begin_lba);
    printf("root dir : %d\n\n\n", get_root_dir(fat));
}

void fat32_format(int disk_size, int sec_per_clus, int sec_per_fat) {
    hdd = malloc(disk_size * sizeof (unsigned char));
    for (int i = 0; i < disk_size; i++) {
        hdd[i] = 0;
    }
    hdd[451] = 0x0B; // type of fs : fat32
    write_integer(hdd, 1, 455, 3);
    int vol_id = 512;
    write_integer(hdd, 0x0200, 0x0B, 2);
    hdd[vol_id + 0x0D] = sec_per_clus; // sectors per clusters, can be 2,4,8,256 ... 128
    write_integer(hdd, 0x020, vol_id + 0x0E, 2); // root dir begin
    hdd[vol_id + 0x10] = 0x10; // number of fat
    write_integer(hdd, 0x20, 0xE, 4); // number of reserved sectors
    write_integer(hdd, sec_per_fat, vol_id + 0x24, 2); // sectors per fat
    printf("\n");
    fat32* fat = malloc(sizeof (fat32));
    fat32_init(fat);
    printf("init table : \n");
    add_to_table(fat, get_root_dir(fat), 0xFFFF);
    create_root(fat);
}

void create_root(fat32* fat) {
    sector root_cluster_begin = malloc(512 * sizeof (unsigned char));
    int sec = get_root_dir(fat);
    int j = 0;
    for (int i = 0; i < 2; i++) {
        add_file(fat,root_cluster_begin,j*32,i < 1 ? "sec" : "sup");
        for (int h = 0; h < 512; h += 32) {
            printf("%d", read_integer(root_cluster_begin, h, 32));
        }
        if (j == (512 * fat->BPB_SecPerClus) / 32 - 1) {
            printf("got to the end : %d\n", i);
            write_sector(sec, root_cluster_begin);
            sec = realloc_directory(fat, sec);
            root_cluster_begin = malloc(512 * sizeof (unsigned char));
            j = 0;
        }
        j++;
    }
    printf("secrt at %p\n",root_cluster_begin);
    add_dir(fat,root_cluster_begin,get_root_dir(fat),64,"subdir");
    write_integer(root_cluster_begin, 0, (j+1) * 32, 32);
    write_sector(sec, root_cluster_begin);
    display_sector_at(fat,sec);
    printf("test file \n\n");
    read_file(fat,root_cluster_begin,64);
}

void add_file(fat32* fat, unsigned char* sec, int offset, char* name) {
    printf("sec is at : %p\n", sec);
    write_name(sec, name, offset, 11);
    sec[offset + 11] = 8;
    int file_cluster = get_next_empty_cluster(fat);
    printf("found next cluster :%d",file_cluster);
    add_to_table(fat,file_cluster,0xFFFF);
    write_integer(sec, file_cluster / 65536, offset+0x14, 2);
    write_integer(sec,0,offset+0x0B,1);
    write_integer(sec, file_cluster % 65536, offset+0x1A, 2);
    sector file_content = read_sector(file_cluster);
    write_name(file_content,"this is the content of a file",0,14);
    write_sector(file_cluster,file_content);
}



void add_dir(fat32* fat, unsigned char* sec, int cur_dir, int offset, char* name) {
    printf("sec is at : %p\n", sec);
    write_name(sec, name, offset, 11);
    sec[offset + 11] = 8;
    int file_cluster = get_next_empty_cluster(fat);
    printf("found next cluster :%d",file_cluster);
    add_to_table(fat,file_cluster,0xFFFF);
    write_integer(sec, file_cluster / 65536, offset+0x14, 2);
    write_integer(sec,4,offset+0x0B,1);
    write_integer(sec, file_cluster % 65536, offset+0x1A, 2);
    sector dir_content = read_sector(file_cluster);
    write_name(dir_content, "..", 0, 11);
    write_integer(dir_content, cur_dir / 65536, 0x14, 2);
    write_integer(dir_content,4,0x0B,1);
    write_integer(dir_content, cur_dir % 65536, 0x1A, 2);
    write_sector(file_cluster,dir_content);
}




unsigned char* read_file(fat32* fat, sector sec, int offset){
    int file_cluster = read_integer(sec,offset+0x1A,2)+65536*read_integer(sec,offset+0x14,2);
    sector file_content = read_sector(file_cluster);
    unsigned char * file_text = read_name(file_content,0,14);
    return file_text;
}
int get_dir_clus(fat32* fat, sector sec, int offset){
    return read_integer(sec,offset+0x1A,2)+65536*read_integer(sec,offset+0x14,2);
}
void display_sector_at(fat32* fat, int sec) {
    printf("sec : %d\n", sec);
    sector found = read_sector(sec);
    for (int i = 0; i < 512; i += 32) {
        printf(" %d", read_integer(found, i, 32));
    }
}