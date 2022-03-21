//
// Created by gallaann on 08.03.2022.
//

#include "pet.h"
#include "stdlib.h"
#include "string.h"

Pet* pet_constructor(char* type, char* coloration, char* name){
    Pet* pet = (Pet *)malloc(sizeof(Pet));

    if (pet == NULL){
        return NULL;
    }

    pet->type = type;
    pet->coloration = coloration;
    pet->name = name;

    return pet;
}

Pet* get_pet(char* raw){
    char* type = NULL;
    type = strtok(raw, " ");
    if(type == NULL){
        return NULL;
    }

    char* coloration = NULL;
    coloration = strtok(NULL, " ");
    if(coloration == NULL){
        return NULL;
    }

    char* name = NULL;
    name = strtok(NULL, " \n");
    if(name == NULL){
        return NULL;
    }

    if (strtok(NULL, " \n") != NULL){ //more than 3 elements
        return NULL;
    }

    return pet_constructor(type,coloration,name);
}

int print_pet(Pet* pet){
    if (pet == NULL){
        return 0;
    }

    printf("%s","type: ");
    puts(pet->type);
    printf("%s","coloration: ");
    puts(pet->coloration);
    printf("%s","name: ");
    puts(pet->name);
    printf("\n");

    return 1;
}

void swap_pet(Pet* first, Pet* second){
    Pet* temp = (Pet*)malloc(sizeof(Pet));

    *temp = *first;
    *first = *second;
    *second = *temp;

    free(temp);
}
