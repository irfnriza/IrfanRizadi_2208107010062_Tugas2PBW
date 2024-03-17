#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 1000000

void generateRandomNumbers(int arr[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n) {
    for (int i = 0; i < n-1; i++) {
        int minIndex = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j = j - 1;
        }
        arr[j+1] = key;
    }
}

void saveToFile(int arr[], int n, char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%d\n", arr[i]);
    }

    fclose(file);
}

int main() {
    int dataSizes[] = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000};

    printf("=====================================================================\n");
    printf("Jenis Algoritma            |   Jumlah Bilangan   |   Waktu Eksekusi (ms)\n");
    printf("---------------------------------------------------------------------\n");

    for (int i = 0; i < sizeof(dataSizes)/sizeof(dataSizes[0]); i++) {
        int n = dataSizes[i];
        int *arr = malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed!\n");
            return 1;
        }

        generateRandomNumbers(arr, n);

        clock_t start, end;
        double cpu_time_used;

        start = clock();
        bubbleSort(arr, n);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
        printf("Bubble Sort %dk              |   %d                  |   %.2f\n", n / 1000, n, cpu_time_used);
        saveToFile(arr, n, "bubble_sort_output.txt");

        start = clock();
        selectionSort(arr, n);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
        printf("Selection Sort %dk           |   %d                  |   %.2f\n", n / 1000, n, cpu_time_used);
        saveToFile(arr, n, "selection_sort_output.txt");

        start = clock();
        insertionSort(arr, n);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC * 1000;
        printf("Insertion Sort %dk           |   %d                  |   %.2f\n", n / 1000, n, cpu_time_used);
        saveToFile(arr, n, "insertion_sort_output.txt");

        free(arr);
    }

    printf("=====================================================================\n");

    return 0;
}
