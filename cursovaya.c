#include <stdio.h>
#include <stdlib.h> //Заголовочный файл для реализации динамического массива
#include <time.h>

typedef struct {
    int *array; //объявление массива
    size_t size; //объявление размера массива
    size_t capacity; //объявление вместимости
} dynamic_array; //динамический массив

dynamic_array* create_dynamic_array(size_t initial_capacity) { //функция создания динамического массива
    dynamic_array *da = (dynamic_array*)malloc(sizeof(dynamic_array)); //использование функции malloc для выделения блока памяти
    (*da).array = (int*)malloc(initial_capacity * sizeof(int));
    (*da).size = 0;
    (*da).capacity = initial_capacity;
    return da;
}

void free_dynamic_array(dynamic_array *da) { //функция освобождения выделенной памяти с помощью free
    free((*da).array);
    free(da);
}

void append(dynamic_array *da, int value) { //функция добавления элемента 
    if ((*da).size == (*da).capacity) {
        (*da).capacity *= 2; //увеличение вместимости в 2 раза
        (*da).array = (int*)realloc((*da).array, (*da).capacity * sizeof(int)); //перевыделение памяти под массив при помощи realloc
    }
    (*da).array[(*da).size++] = value;//добавление элемента в массив
}

void deletion(dynamic_array *da, size_t index) { //функция удаления элемента
    if (index >= (*da).size) { //если номер индекса выходит за рамки размера массива вывести ошибку
        printf("error: index out of range\n"); 
        return;
    }
    for (size_t i = index; i < (*da).size - 1; i++) { // цикл начинает с индекса удаляемого элемента и проходит до предпоследнего элемента массива
        (*da).array[i] = (*da).array[i + 1]; // перемещение каждого элемента массива на одну позицию влево, заменяя удаляемый элемент
    }
    (*da).size--; //уменьшение размера массива на единицу после удаления элемента
}

int sum(dynamic_array *da) { //функция поиска суммы элементов массива
    int total = 0; //объявление переменной, хранящей значение суммы
    for (size_t i = 0; i < (*da).size; i++) { //цикл для перебора всех элементов динамического массива от первого до последнего
        total += (*da).array[i]; // Суммирование значения, хранящемся в переменной со значением элемента 
    }
    return total; //возвращение суммы 
}

double average(dynamic_array *da) { // функция нахождения среднего значения элементов массива
    if ((*da).size == 0) { // проверка массива на заполненность
        return 0;
    }
    return (double)sum(da) / (*da).size; //возвращение среднего значения, используя функцию суммы
}

void find_min_max(dynamic_array *da, int *min, int *max) { //функция поиска минимального и максимального значения
    if ((*da).size == 0) { //проверка массива на заполненность
        *min = *max = 0;
        return; //вывод нулевых значений минимума и максимума
    }
    *min = *max = (*da).array[0]; //присвоение переменным максимума и минимума значение 1 элемента 
    for (size_t i = 1; i < (*da).size; i++) { //цикл для перебора всех элементов динамического массива от первого до последнего
        if ((*da).array[i] < *min) { //проверка элемента "меньше минимума"
            *min = (*da).array[i];
        }
        if ((*da).array[i] > *max) {//проверка элемента "больше максимума"
            *max = (*da).array[i];
        }
    }
}

void print_array(dynamic_array *da) { //функция вывода массива
    for (size_t i = 0; i < (*da).size; i++) {//цикл для перебора всех элементов динамического массива от первого до последнего
        printf("%d ", (*da).array[i]); //вывод элемента
    }
    printf("\n");
}

void resize_array(dynamic_array *da, size_t new_size) { //функция перевыделения памяти под массив при помощи realloc
    if (new_size > (*da).capacity) {
        (*da).capacity = new_size;
        (*da).array = (int*)realloc((*da).array, (*da).capacity * sizeof(int));
    }
    if (new_size > (*da).size) {
        for (size_t i = (*da).size; i < new_size; i++) {
            (*da).array[i] = rand() % 10000; //заполнение массива псевдо-случайными числами 
        }
    } else if (new_size < (*da).size) {
        (*da).size = new_size;
    }
    (*da).size = new_size;
}

void fill_array_with_zeros(dynamic_array *da, size_t size) { //функция перевыделения памяти для заполненного нулями массива при помощи calloc
    (*da).array = (int*)calloc(size, sizeof(int));
    (*da).size = size;
    (*da).capacity = size;
}


int main() { 
    srand(time(NULL));
    dynamic_array *da = NULL;
    int choice;
    int first_choice = 1;

//Вывод меню с доступными операциями над динамическим массивом
    while (1) {
        printf("1. enter array size\n");
        printf("2. add element to array\n");
        printf("3. delete element by index\n");
        printf("4. print sum of elements\n");
        printf("5. print average\n");
        printf("6. print minimum and maximum\n");
        printf("7. print array\n");
        printf("8. change number of elements in array\n");
        printf("9. exit\n");
        printf("choose an operation: ");
        scanf("%d", &choice);

        switch (choice) { //оператор switch для исполнения различных функций в зависимости от значения, введённого пользователем
            case 1:
                if (da != NULL) {
                    free_dynamic_array(da);
                }
                size_t initial_size;
                printf("enter the number of elements: ");
                scanf("%zu", &initial_size);
                da = create_dynamic_array(initial_size);

                printf("choose how to fill the array:\n");
                printf("1. fill with random numbers\n");
                printf("2. fill with zeros\n");
                int fill_choice;
                scanf("%d", &fill_choice);

                switch (fill_choice) {
                    case 1:
                        resize_array(da, initial_size);
                        break;
                    case 2:
                        fill_array_with_zeros(da, initial_size);
                        break;
                    default:
                        printf("incorrect choice. filling with zeros by default.\n");
                        fill_array_with_zeros(da, initial_size);
                        break;
                }

                first_choice = 0;
                break;
            case 2:
                if (first_choice) {
                    printf("incorrect choice.\n");
                    break;
                }
                if (da == NULL) {
                    printf("error: first set the array size (select 1)\n");
                    break;
                }
                int value;
                printf("enter the element for addition: ");
                scanf("%d", &value);
                append(da, value);
                break;
            case 3:
                if (first_choice) {
                    printf("incorrect choice.\n");
                    break;
                }
                if (da == NULL) {
                    printf("error: first set the array size (select 1)\n");
                    break;
                }
                size_t index;
                printf("enter the index for deletion: ");
                scanf("%zu", &index);
                deletion(da, index);
                break;
            case 4:
                if (first_choice) {
                    printf("incorrect choice.\n");
                    break;
                }
                if (da == NULL) {
                    printf("error: first set the array size (select 1)\n");
                    break;
                }
                printf("sum of elements: %d\n", sum(da));
                break;
            case 5:
                if (first_choice) {
                    printf("incorrect choice.\n");
                    break;
                }
                if (da == NULL) {
                    printf("error: first set the array size (select 1)\n");
                    break;
                }
                printf("average: %.2f\n", average(da));
                break;
            case 6:
                if (first_choice) {
                    printf("incorrect choice.\n");
                    break;
                }
                if (da == NULL) {
                    printf("error: first set the array size (select 1)\n");
                    break;
                }
                int min, max;
                find_min_max(da, &min, &max);
                printf("minimum: %d\n", min);
                printf("maximum: %d\n", max);
                break;
            case 7:
                if (first_choice) {
                    printf("incorrect choice.\n");
                    break;
                }
                if (da == NULL) {
                    printf("error: first set the array size (select 1)\n");
                    break;
                }
                print_array(da);
                break;
            case 8:
                if (first_choice) {
                    printf("incorrect choice.\n");
                    break;
                }
                if (da == NULL) {
                    printf("error: first set the array size (select 1)\n");
                    break;
                }
                size_t new_size;
                printf("enter the new number of elements: ");
                scanf("%zu", &new_size);
                resize_array(da, new_size);
                break;
            case 9:
                if (da != NULL) {
                    free_dynamic_array(da);
                }
                return 0;
            default:
                if (first_choice) {
                    printf("incorrect choice.\n");
                } else {
                    printf("incorrect choice.\n");
                }
        }
    }

    return 0;
}
