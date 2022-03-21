//
// Created by gallaann on 08.03.2022.
//
#pragma once

#include "stdio.h"

typedef struct {
    char* type;
    char* coloration;
    char* name;
} Pet;

Pet* pet_constructor(char* type, char* coloration, char* name);
Pet* get_pet(char* raw);
int print_pet(Pet* pet);
void swap_pet(Pet* first, Pet* second);
