/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   array_list.h
 * Author: user
 *
 * Created on 21 mai 2017, 18:35
 */

#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#include <stdlib.h>
#include <stdio.h>
typedef struct array_list list;
/**
 * A list implementation, allows to add at the end, get at index and find by key.
 */
struct array_list {
    void** list;
    int size;
    int max_size;
};
/**
 * reserve new memory, equivalent of reallo
 * @param l 
 * the list
 * @param size 
 * the size to add to the list
 */
void list_reserve(list* l,int size);
/**
 * add an element to the list
 * @param l the list
 * @param elem : the element to add
 */
void list_add(list* l,void* elem);
/**
 * returns the element at a specific position
 * @param l the list
 * @param index the index of the element to return 
 * @return the element at the index.
 */
void* list_at(list* l,int index);
/**
 * returns the last element of the list.
 * @param l the list.
 * @return the last element.
 */
void* list_last(list* l);
/**
 * removes the list from memory.
 * @param l the list
 * @param destructor the destructor function for the elements.
 */
void list_free(list* l, int (*destructor)(void*));
/**
 * remove an element at the specified position.
 * @param l the list
 * @param index the position of the element.
 * @return the removed element
 */
void* list_rm_at(list* l, int index);
/**
 * find an element in the list by a comparator function and.
 * @param l : the list
 * @param key : the argument to give to the function
 * @param compare : the function, must return 1 if the element matched
 * @return the matched element
 */
int list_find_by_key(list* l, int key, int(*compare)(void*,int)); 
/**
 * creates an empty list.
 * @return the list.
 */
list* list_create();
#endif /* ARRAY_LIST_H */

