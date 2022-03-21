//
// Created by gallaann on 08.03.2022.
//

#include "storage.h"

int main(){
    Storage* storage = storage_constructor();

    FILE* input_file = fopen("../read_file.txt","r");

    read_file(storage, input_file);

    sort_storage(storage);

    print_storage(storage);

    free_storage(&storage);

    fclose(input_file);

    return 0;
}
