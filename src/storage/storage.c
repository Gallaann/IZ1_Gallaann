//
// Created by gallaann on 08.03.2022.
//

#include "storage.h"
#include "stdlib.h"
#include "string.h"

#define first_run_length 0U
#define first_run_capacity 1U
#define check 1U
#define double_size 2U

Storage* storage_constructor(){
    Storage* storage = (Storage*) malloc(sizeof(Storage));

    if (storage == NULL){
        return NULL;
    }

    storage->length = first_run_length;
    storage->capacity = first_run_capacity;
    storage->pet_unit = NULL;

    return storage;
}

int read_file(Storage* storage, FILE* file){ //Fuck this shit ARGH!!!
    if (storage == NULL){
        return 0;
    }

//    FILE* file = fopen(input_file, "r");

    if (file == NULL){
        printf("Failed:\n\tcan't open file\n");
        return 0;
    }

    char* raw = NULL;
    size_t input_size;
    size_t counter = 0;
    Pet* pet;

    while(getline(&raw, &input_size, file) != EOF) {
        pet = get_pet(raw);
        if (pet == NULL){
            free(pet);
            pet = NULL;
            return 0;
        }

        fill_storage(storage,pet);
        raw = NULL;

        counter++;
    }

    free(pet);
    pet = NULL;

    if (counter == 0){
        return 0;
    }

    return 1;
}

int fill_storage(Storage* storage, Pet* pet){
    if((storage == NULL) || (pet == NULL)){
        return 0;
    }

    if (storage->length + check >= storage->capacity){
        storage->capacity *= double_size;
        storage->pet_unit = (Pet *) realloc(storage->pet_unit,sizeof(Pet) * storage->capacity);

        if (storage->pet_unit == NULL) {
            return 0;
        }
    }

    storage->pet_unit[storage->length] = *pet;
    storage->length += 1;

    return 1;
}

int sort_storage(Storage* storage){
    if (storage->pet_unit == NULL) {
        return 0;
    }

    if (storage->length > 2){ //it makes no sense to sort array of <= 2 elements
        for (size_t j = 0; j < storage->length-1; ++j){
            for (size_t i = 0; i < storage->length - j-1; ++i){
                if (strcmp(storage->pet_unit[i].type, storage->pet_unit[i+1].type) > 0){
                    swap_pet(&storage->pet_unit[i], &storage->pet_unit[i+1]);
                }
            }
        }
    }

    return 1;
}

int print_storage(Storage* storage){
    if (storage == NULL) {
        return 0;
    }

    for (size_t i = 0; i < storage->length; ++i) {
        print_pet(&storage->pet_unit[i]);
    }
    return 1;
}

void free_storage(Storage** storage){
    free((*storage)->pet_unit);
    (*storage)->pet_unit = NULL;

    free(*storage);
    *storage = NULL;
}
