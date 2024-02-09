#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

void readFileToArray(const char *filename, int **arr, int *size, int *capacity) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    int number;
    *size = 0;

    while (fscanf(file, "%d", &number) == 1) {
        if (*size >= *capacity) {
            *capacity *= 2;
            *arr = (int *)realloc(*arr, *capacity * sizeof(int));
        }

        (*arr)[*size] = number;
        (*size)++;
    }

    fclose(file);
}

void mergeSortForFile(const char *filename) {
    int capacity = 1000; // Tamanho inicial do vetor
    int *arr = (int *)malloc(capacity * sizeof(int));
    int size;

    readFileToArray(filename, &arr, &size, &capacity);

    mergeSort(arr, 0, size - 1);

    // printf("Array ordenado para o arquivo %s:\n", filename);
    // for (int i = 0; i < size; i++) {
    //     printf("%d ", arr[i]);
    // }
    // printf("\n\n");

    free(arr);
}

int main() {
    const char *fileNames[] = {"po2000000.txt"};
    //const char *fileNames[] = {"a100.txt", "a200.txt", "a500.txt","a1000.txt","a2000.txt","a5000.txt","a7500.txt","a10000.txt","a15000.txt","a30000.txt","a50000.txt","a75000.txt","a100000.txt","a200000.txt","a500000.txt","a750000.txt","a1000000.txt","a1250000.txt","a1500000.txt","a2000000.txt"};
    //const char *fileNames[] = {"d100.txt", "d200.txt", "d500.txt","d1000.txt","d2000.txt","d5000.txt","d7500.txt","d10000.txt","d15000.txt","d30000.txt","d50000.txt","d75000.txt","d100000.txt","d200000.txt","d500000.txt","d750000.txt","d1000000.txt","d1250000.txt","d1500000.txt","d2000000.txt"};
    //const char *fileNames[] = {"o100.txt", "o200.txt", "o500.txt","o1000.txt","o2000.txt","o5000.txt","o7500.txt","o10000.txt","o15000.txt","o30000.txt","o50000.txt","o75000.txt","o100000.txt","o200000.txt","o500000.txt","o750000.txt","o1000000.txt","o1250000.txt","o1500000.txt","o2000000.txt"};
   //const char *fileNames[] = {"po100.txt", "po200.txt", "po500.txt","po1000.txt","po2000.txt","po5000.txt","po7500.txt","po10000.txt","po15000.txt","po30000.txt","po50000.txt","po75000.txt","po100000.txt","po200000.txt","po500000.txt","po750000.txt","po1000000.txt","po1250000.txt","po1500000.txt","po2000000.txt"};
    
    int numFiles = sizeof(fileNames) / sizeof(fileNames[0]);

    clock_t start_time = clock(); // Inicia a contagem do tempo

    for (int i = 0; i < numFiles; i++) {
        mergeSortForFile(fileNames[i]);
    }

    clock_t end_time = clock(); // Finaliza a contagem do tempo

    double total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("Tempo total de execução: %f segundos\n", total_time);

    return 0;
}
