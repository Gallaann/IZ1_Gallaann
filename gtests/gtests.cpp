//
// Created by gallaann on 20.03.2022.
//
#include <gtest/gtest.h>

extern "C" {
#include "storage.h"
}

bool is_pets_equal(Pet* pet1, Pet* pet2){
    if ((pet1->type != pet2->type) || (pet1->coloration != pet2->coloration) || (pet1->name != pet2->name)){
        return false;
    }
    return true;
}

bool is_storages_equal(Storage* storage1, Storage* storage2){
    for (size_t i = 0; i < storage1->length; ++i) {
        if(!is_pets_equal(&storage1->pet_unit[i], &storage2->pet_unit[i])){
            return false;
        }
    }
    return true;
}

TEST(pet_tests,pet_constructor_test){
    Pet* pet_by_hand = (Pet*) malloc(sizeof (Pet));
    pet_by_hand->type=(char*)"I";
    pet_by_hand->coloration=(char*)"love";
    pet_by_hand->name=(char*)"bebra";
    Pet* pet_by_constructor = pet_constructor((char*)"I",(char*)"love",(char*)"bebra");
    EXPECT_EQ(true,is_pets_equal(pet_by_constructor,pet_by_hand));
    free(pet_by_constructor);
    free(pet_by_hand);
}

TEST(constructor_tests,storage_constructor_test){
    Storage* storage_by_hand = (Storage*) malloc(sizeof (Storage));
    storage_by_hand->length=0;
    storage_by_hand->capacity=1;
    storage_by_hand->pet_unit=NULL;
    Storage* storage_by_constructor = storage_constructor();
    EXPECT_EQ(true, is_storages_equal(storage_by_constructor,storage_by_hand));
    free_storage(&storage_by_constructor);
    free_storage(&storage_by_hand);
}

//TEST(storage_tests, free_test){
//    Storage* test_storage = storage_constructor();
//    Pet* test_pet = pet_constructor((char*)"I",(char*)"love",(char*)"bebra");
//    fill_storage(test_storage, test_pet);
//    free_storage(&test_storage);
//    test_storage = NULL;
//    ASSERT_EQ(test_storage, NULL);
//}

TEST(reading_tests, empty_file) {
    Storage* test_storage = storage_constructor();
    char str_mimic[] = "";
    FILE* input_file = fmemopen(str_mimic, strlen(str_mimic), "r");
    EXPECT_EQ(0, read_file(test_storage,input_file));
    free_storage(&test_storage);
}

TEST(reading_tests, too_many_data_fields) {
    Storage* test_storage = storage_constructor();
    char* str_mimic = (char*)"I love hor bebras\n";
    FILE* input_file = fmemopen(str_mimic, strlen(str_mimic), "r");
    EXPECT_EQ(0, read_file(test_storage,input_file));
    free_storage(&test_storage);
}

TEST(reading_tests, not_enough_data_fields) {
    Storage* test_storage = storage_constructor();
    char str_mimic[] = "two bebras\n";
    FILE* input_file = fmemopen(str_mimic, strlen(str_mimic), "r");
    EXPECT_EQ(0, read_file(test_storage,input_file));
    free_storage(&test_storage);
}

TEST(reading_tests, correct_data) {
    Storage* test_storage = storage_constructor();
    char str_mimic[] = "I love bebras\n";
    FILE* input_file = fmemopen(str_mimic, strlen(str_mimic), "r");
    EXPECT_EQ(1, read_file(test_storage,input_file));
    free_storage(&test_storage);
}

TEST(get_elements_tests, too_many_data_fields) {
    char str_mimic[] = "I love hot bebras";
    EXPECT_EQ(nullptr, get_pet(str_mimic));
}

TEST(get_elements_tests, not_enough_data_fields) {
    char str_mimic[] = "Sad bebra";
    EXPECT_EQ(nullptr, get_pet(str_mimic));
}

TEST(get_elements_tests, correct_data) {
    char str_mimic[] = "I love bebras";
    Pet* pet;
    EXPECT_NE(nullptr, pet = get_pet(str_mimic));
    free (pet);
}

TEST(pet_tests, swap_test) {
    Pet* test_pet_1 = pet_constructor((char*)"I",(char*)"love",(char*)"bebra");
    Pet* test_pet_2 = pet_constructor((char*)"bebra",(char*)"loves",(char*)"me");
    Pet* test_pet_3 = pet_constructor((char*)"I",(char*)"love",(char*)"bebra"); // 3 equals 1
    swap_pet(test_pet_1,test_pet_2);
    EXPECT_EQ(false,is_pets_equal(test_pet_3,test_pet_1));
    EXPECT_EQ(true,is_pets_equal(test_pet_3,test_pet_2));
    free(test_pet_1);
    free(test_pet_2);
    free(test_pet_3);
}

TEST(storage_tests, fill_test){
    Storage* test_storage = storage_constructor();
    Pet* test_pet = pet_constructor((char*)"I",(char*)"love",(char*)"bebra");
    EXPECT_EQ(1, fill_storage(test_storage,test_pet));
    EXPECT_EQ(0, fill_storage(test_storage,NULL));
    EXPECT_EQ(0, fill_storage(NULL,test_pet));
    EXPECT_EQ(0, fill_storage(NULL,NULL));
    free(test_pet);
    free_storage(&test_storage);
}

TEST(storage_tests, sort_test){
    Storage* test_storage = storage_constructor();
    char* str_mimic_unsorted = (char*)"cat white bebrik\ndog black stu\nunicorn purple twilight_sparkle\ncat orange garfield\n";
    FILE* input_file_1 = fmemopen(str_mimic_unsorted, strlen(str_mimic_unsorted), "r");
    read_file(test_storage,input_file_1);

    sort_storage(test_storage);

    for(size_t i = 0; i < test_storage->length-1; ++i){
        EXPECT_EQ(true,(strcmp(test_storage->pet_unit[i].type, test_storage->pet_unit[i+1].type) <= 0));
    }


    free_storage(&test_storage);
}

TEST(output_tests,print_test){
    EXPECT_EQ(0,print_storage(NULL));
    EXPECT_EQ(0,print_pet(nullptr));
    Storage* test_storage = (Storage*) malloc(sizeof (Storage));
    Pet* test_pet = pet_constructor((char*)"I",(char*)"love",(char*)"bebra");
    test_storage->length=1;
    test_storage->capacity=2;
    test_storage->pet_unit=test_pet;

    testing::internal::CaptureStdout();
    EXPECT_EQ(1, print_storage(test_storage));
    std::string print_storage_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(print_storage_output,"type: I\ncoloration: love\nname: bebra\n\n");

    testing::internal::CaptureStdout();
    EXPECT_EQ(1, print_pet(test_pet));
    std::string print_pet_output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(print_pet_output,"type: I\ncoloration: love\nname: bebra\n\n");

    free_storage(&test_storage);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}