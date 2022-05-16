//
// Created by leva on 14.05.2022. 19:38
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "inoutput_funcs.h"
#include "head.h"

#define MAX_RIVERS 1000
#define RSIZE sizeof(river);


int main(void) {


    srand(time(NULL));
    system("chcp 65001 > nul");


    size_t river_size = sizeof(river);
    river *river_array = malloc(river_size * MAX_RIVERS);
    river *last_river = river_array;
//    char name[5][10] = {"aboba", "abiba", "atata", "akunamata", "dababy?"};
//    for (int i = 0; i < 5; i++) {
//        add_river(rand() % 1000, name[i], rand() % 5, &last_river);
//    }

    int menu_variant;
    do {
        puts("1. Добавить реку");
        puts("2. Удалить реку по номеру");
        puts("3. Вывести реки");
        puts("4. Отсортировать реки");
        puts("5. Меню фильтрации");
        puts("6. Сохранить реки в файл");
        puts("7. Загрузить реки из файла и вывести их");
        puts("8. Выйти");


        menu_variant = input_int();

        switch (menu_variant) {
            case 1:
                if ((last_river - river_array) == MAX_RIVERS) {
                    puts("Больше нет места для рек(");
                    break;
                }
                puts("Введите назавние реки:");
                char *name = input_string();
                if (name[0] == '\0') {
                    puts("Некорректное имя!");
                    break;
                }
                puts("Введите длину реки:");
                int lenght = input_int();
                if (lenght == -1) {
                    puts("Некорректная длина!");
                    break;
                }
                puts("Введите минимальную глубину реки:");
                int depth = input_int();
                if (depth < 1) {
                    puts("Некорректная минимальная глубина!");
                    break;
                }
                add_river(lenght, name, depth, &last_river);
                puts("Река успешно добавлена");
                break;

            case 2:
                puts("Введите номер реки для удаления:");
                int num = input_int();
                delete_river(num, river_array, &last_river);
                break;

            case 3:
                print_rivers(river_array, last_river);
                break;

            case 4:
                printf("");
                int sort_variant;
                do {
                    puts("1. Отсортировать по имени");
                    puts("2. Отсортировать по длине");
                    puts("3. Отсортировать по минимальной глубине");
                    puts("4. Отсортировать по проходимости для судов");
                    puts("5. Выйти из меню сортировки");
                    sort_variant = input_int();
                    switch (sort_variant) {
                        case 1:
                            qsort(river_array,
                                  last_river - river_array,
                                  river_size,
                                  &compare_names);
                            print_rivers(river_array, last_river);
                            break;
                        case 2:
                            qsort(river_array,
                                  last_river - river_array,
                                  river_size,
                                  &compare_lens);
                            print_rivers(river_array, last_river);
                            break;
                        case 3:
                            qsort(river_array,
                                  last_river - river_array,
                                  river_size,
                                  &compare_depths);
                            print_rivers(river_array, last_river);
                            break;
                        case 4:
                            qsort(river_array,
                                  last_river - river_array,
                                  river_size,
                                  &compare_pass);
                            print_rivers(river_array, last_river);
                            break;
                        case 5:
                            break;
                        default:
                            puts("Такого варианта выбора нет!");
                    }
                } while (sort_variant != 5);

            break;
            case 5: {
                unsigned char *fields = pick_ffields();
                print_filters(fields, river_array, last_river);
            } break;
            case 6:
                save(river_array, last_river - river_array);
                puts("Реки успешно сохранены в файл");
                break;
            case 7:
                load();
                break;
            case 8:
                free(river_array);
                break;
            default:
                puts("Такого варианта в меню нет!");
                break;
        }
    } while (menu_variant != 8);


    free(river_array);
    return 0;
}


unsigned char *pick_ffields(){
    unsigned char *picked_fields = calloc(4, sizeof(unsigned char));
    int variant;
    puts("Выберите поля по которым будет произведена фильтрация");
    do {
        (picked_fields[0]) ? puts("1. Вхождение в имя + ") :
        puts("1. Вхождение в имя");
        (picked_fields[1]) ? puts("2. Протяженность + ") :
        puts("2. Протяженность");
        (picked_fields[2]) ? puts("3. Наим. глубина + ") :
        puts("3. Наим. глубина");
        (picked_fields[3]) ? puts("4. Проходимость судов + ") :
        puts("4. Проходимость судов");
        puts("5. Сбросить фильтр");
        puts("6. Завершить выбор фильтров");
        variant = input_int();
        switch (variant) {
            case 1:
                picked_fields[0] = 1;
                break;
            case 2:
                picked_fields[1] = 1;
                break;
            case 3:
                picked_fields[2] = 1;
                break;
            case 4:
                picked_fields[3] = 1;
                break;
            case 5:
                for (int i = 0; i < 4; i++) picked_fields[i] = 0;
                break;
            case 6:
                return picked_fields;
            default:
                puts("Такого варианта выбора нет!");
                break;
        }
    } while (1);
}


void print_filters(unsigned char *filters, river *r_array, river *end_ptr){
    river *f_rivers = malloc(sizeof(river) * (end_ptr - r_array));
    river *last_friver = f_rivers + (end_ptr - r_array);
    for (int i = 0; i < end_ptr - r_array; i++){
        f_rivers[i] = r_array[i];
    }
    while (1){
        if (filters[0]) {
            puts("\nВведите подстроку для имени");
            char *subname = input_string();
            if (subname[0] == '\0') {
                puts("Некорректное значение!");
                continue;
            }
            for (int i = 0; i < last_friver - f_rivers; i++) {
                if (strstr(f_rivers[i].name, subname) == NULL) {
                    f_rivers[i].length = -1;
                }
            }
        }

        if (filters[1]){
            puts("Введите значение протяженности, от которого будем считать");
            int flenght = input_int();
            if (flenght <= 0) {
                puts("Некорректное значение!");
                continue;
            }
            printf("1. Ищем <%d\n", flenght);
            printf("2. Ищем >%d\n", flenght);
            int variant = input_int();
            switch (variant) {
                case 1:
                    for (int i = 0; i < last_friver - f_rivers; i++) {
                        if (f_rivers[i].length >= flenght) f_rivers[i].length = -1;
                    }
                    break;
                case 2:
                    for (int i = 0; i < last_friver - f_rivers; i++) {
                        if (f_rivers[i].length > 0 && f_rivers[i].length < flenght)
                            f_rivers[i].length = -1;
                    }
                    break;
                default:
                    puts("Некорректное значение!");
                    continue;
            }

        }

        if (filters[2]){
            puts("Введите значение минимальной глубины,"
                 " от которого будем считать");
            int fdepth = input_int();
            if (fdepth <= 0) {
                puts("Некорректное значение!");
                continue;
            }
            printf("1. Ищем <%d\n", fdepth);
            printf("2. Ищем >%d\n", fdepth);
            int variant = input_int();
            switch (variant) {
                case 1:
                    for (int i = 0; i < last_friver - f_rivers; i++) {
                        if (f_rivers[i].min_depth >= fdepth) f_rivers[i].length = -1;
                    }
                    break;
                case 2:
                    for (int i = 0; i < last_friver - f_rivers; i++) {
                        if (f_rivers[i].min_depth < fdepth) f_rivers[i].length = -1;
                    }
                    break;
                default:
                    puts("Некорректное значение!");
                    continue;
            }
        }
        if (filters[3]){
            puts("1. Несудоходная");
            puts("2. Проходима для малых судов");
            puts("3. Проходима для крупных судов");
            int varinant = input_int();
            switch (varinant) {
                case 1:
                    for (int i = 0; i < last_friver - f_rivers; i++) {
                        if (f_rivers[i].passability_lvl != 0)
                            f_rivers[i].length = -1;
                    }
                    break;
                case 2:
                    for (int i = 0; i < last_friver - f_rivers; i++) {
                        if (f_rivers[i].passability_lvl != 1)
                            f_rivers[i].length = -1;
                    }
                    break;
                case 3:
                    for (int i = 0; i < last_friver - f_rivers; i++) {
                        if (f_rivers[i].passability_lvl != 2)
                            f_rivers[i].length = -1;
                    }
                    break;
                default:
                    puts("Некорректное значение!");
                    continue;
            }

        }
        break;
    }
        print_rivers(f_rivers, last_friver);

    free(f_rivers);
    free(filters);
}


void add_river(int length, char *name, int depth, river **end_ptr) {
    river *exemplar = *end_ptr;

    exemplar->name = name;
    exemplar->length = length;
    exemplar->min_depth = depth;
    if (depth < 2)
        exemplar->passability_lvl = 0;
    else if (2 <= depth && depth < 4)
        exemplar->passability_lvl = 1;
    else if (4 <= depth)
        exemplar->passability_lvl = 2;
    (*end_ptr)++;

}

void delete_river(int river_num, river *r_array, river **end_ptr) {
    river *end_p = *end_ptr;

    int river_count = end_p - r_array;

    if (river_num > river_count || river_num <= 0) {
        puts("Некорректное значение!");
        return;
    }

    for (r_array += river_num - 1; r_array != (end_p - 1); ++r_array) {
        river next_river = *(++r_array);
        --r_array;
        *r_array = next_river;
    }

    (*end_ptr)--;
}

void print_river(river *my_river) {
    printf("Река: %s\n", my_river->name);
    printf("\tПротяженность: %d\n", my_river->length);
    printf("\tМинимальная глубина: %d\n", my_river->min_depth);
    if (my_river->passability_lvl == 0)
        puts("\tНесудоходная");
    else if (my_river->passability_lvl == 1)
        puts("\tПроходима для малых судов");
    else if (my_river->passability_lvl == 2)
        puts("\tПроходима для крупных судов");
}

void print_rivers(river *r_array, river *end_ptr) {
    if (r_array == end_ptr) {
        puts("Вы не добавили ни одной реки");
        return;
    }
    for (int i = 1; r_array != end_ptr; ++r_array, i++) {
        if (r_array->length != -1){
            printf("%d-я ", i);
            print_river(r_array);
        }
    }
}

int save(river *st, int rivers_count) {
    FILE *fp = fopen("rivers.dat", "w");
    char *c_river_ptr;

    int size = rivers_count * sizeof(river);

    c_river_ptr = (char *) &rivers_count;
    for (int i = 0; i < sizeof(int); ++i) {
        putc(*c_river_ptr++, fp);
    }

    c_river_ptr = (char *) st;
    for (int i = 0; i < size; ++i) {
        putc(*c_river_ptr, fp);
        c_river_ptr++;
    }
    fclose(fp);
    return 0;
}


int load() {
    FILE *fp = fopen("rivers.dat", "r");
    char *c;
    int m = sizeof(int);
    int n, i;

    int *pti = (int *) malloc(m);

    c = (char *) pti;
    while (m > 0) {
        i = getc(fp);
        if (i == EOF) break;
        *c = i;
        c++;
        m--;
    }
    n = *pti;

    river *ptr = (river *) malloc(n * sizeof(river));
    c = (char *) ptr;
    while ((i = getc(fp)) != EOF) {
        *c = i;
        c++;
    }

    for (int k = 0; k < n; ++k) {
        print_river((ptr + k));
    }

    free(pti);
    free(ptr);
    fclose(fp);
    return 0;
}


int compare_names(const void* river1, const void* river2) {
    const char* name1 = ((const river*)river1)->name;
    const char* name2 = ((const river*)river2)->name;
    return strcmp(name1, name2);
}


int compare_lens(const void* river1, const void* river2) {
    const int len1 = ((const river*)river1)->length;
    const int len2 = ((const river*)river2)->length;
    if (len1 > len2) return 1;
    else if (len1 < len2) return -1;
    else return 0;
}


int compare_depths(const void* river1, const void* river2) {
    const int depth1 = ((const river*)river1)->min_depth;
    const int depth2 = ((const river*)river2)->min_depth;
    if (depth1 > depth2) return 1;
    else if (depth1 < depth2) return -1;
    else return 0;
}


int compare_pass(const void* river1, const void* river2) {
    const int pass1 = ((const river*)river1)->passability_lvl;
    const int pass2 = ((const river*)river2)->passability_lvl;
    if (pass1 > pass2) return 1;
    else if (pass1 < pass2) return -1;
    else return 0;
}