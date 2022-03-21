//
// Created by gallaann on 08.03.2022.
//
#pragma once

#include "stdlib.h"
#include "pet.h"

typedef struct {
    size_t length;
    size_t capacity;
    Pet* pet_unit;
} Storage; //vector of Pet*

Storage* storage_constructor();
int read_file(Storage* storage,FILE* file);
//int read_file(Storage* storage,char* input_file);
int fill_storage(Storage* storage, Pet* pet);
int sort_storage(Storage* storage);
int print_storage(Storage* storage);
void free_storage(Storage** storage);
