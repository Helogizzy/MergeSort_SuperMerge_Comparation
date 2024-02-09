#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void merge(int arr[], int l, int m1, int m2, int m3, int r) {
    int n1 = m1 - l + 1;
    int n2 = m2 - m1;
    int n3 = m3 - m2;
    int n4 = r - m3;

    int *L1 = (int *)malloc(n1 * sizeof(int));
    int *L2 = (int *)malloc(n2 * sizeof(int));
    int *L3 = (int *)malloc(n3 * sizeof(int));
    int *L4 = (int *)malloc(n4 * sizeof(int));

    for (int i = 0; i < n1; i++)
        L1[i] = arr[l + i];
    for (int i = 0; i < n2; i++)
        L2[i] = arr[m1 + 1 + i];
    for (int i = 0; i < n3; i++)
        L3[i] = arr[m2 + 1 + i];
    for (int i = 0; i < n4; i++)
        L4[i] = arr[m3 + 1 + i];

    int i = 0, j = 0, k = 0, p = 0;

    int curr = l;
    while (i < n1 && j < n2 && k < n3 && p < n4) {
        if (L1[i] <= L2[j] && L1[i] <= L3[k] && L1[i] <= L4[p]) {
            arr[curr++] = L1[i++];
        } else if (L2[j] <= L1[i] && L2[j] <= L3[k] && L2[j] <= L4[p]) {
            arr[curr++] = L2[j++];
        } else if (L3[k] <= L1[i] && L3[k] <= L2[j] && L3[k] <= L4[p]) {
            arr[curr++] = L3[k++];
        } else {
            arr[curr++] = L4[p++];
        }
    }

    while (i < n1)
        arr[curr++] = L1[i++];

    while (j < n2)
        arr[curr++] = L2[j++];

    while (k < n3)
        arr[curr++] = L3[k++];

    while (p < n4)
        arr[curr++] = L4[p++];

    free(L1);
    free(L2);
    free(L3);
    free(L4);
}

void superMerge(int arr[], int l, int r) {
    if (r - l >= 3) {
        int sz = (r - l + 1) / 4;
        int m1 = l + sz - 1;
        int m2 = l + 2 * sz - 1;
        int m3 = l + 3 * sz - 1;

        superMerge(arr, l, m1);
        superMerge(arr, m1 + 1, m2);
        superMerge(arr, m2 + 1, m3);
        superMerge(arr, m3 + 1, r);

        merge(arr, l, m1, m2, m3, r);
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

void superMergeSortForFile(const char *filename) {
    int capacity = 1000; // Tamanho inicial do vetor
    int *arr = (int *)malloc(capacity * sizeof(int));
    int size;

    readFileToArray(filename, &arr, &size, &capacity);

    superMerge(arr, 0, size - 1);
    free(arr);
}

int main() {
    const char *fileNames[] = {"a2000000.txt"};
    //const char *fileNames[] = {"a100.txt", "a200.txt", "a500.txt","a1000.txt","a2000.txt","a5000.txt","a7500.txt","a10000.txt","a15000.txt","a30000.txt","a50000.txt","a75000.txt","a100000.txt","a200000.txt","a500000.txt","a750000.txt","a1000000.txt","a1250000.txt","a1500000.txt","a2000000.txt"};
    //const char *fileNames[] = {"d100.txt", "d200.txt", "d500.txt","d1000.txt","d2000.txt","d5000.txt","d7500.txt","d10000.txt","d15000.txt","d30000.txt","d50000.txt","d75000.txt","d100000.txt","d200000.txt","d500000.txt","d750000.txt","d1000000.txt","d1250000.txt","d1500000.txt","d2000000.txt"};
    //const char *fileNames[] = {"o100.txt", "o200.txt", "o500.txt","o1000.txt","o2000.txt","o5000.txt","o7500.txt","o10000.txt","o15000.txt","o30000.txt","o50000.txt","o75000.txt","o100000.txt","o200000.txt","o500000.txt","o750000.txt","o1000000.txt","o1250000.txt","o1500000.txt","o2000000.txt"};
    //const char *fileNames[] = {"po100.txt", "po200.txt", "po500.txt","po1000.txt","po2000.txt","po5000.txt","po7500.txt","po10000.txt","po15000.txt","po30000.txt","po50000.txt","po75000.txt","po100000.txt","po200000.txt","po500000.txt","po750000.txt","po1000000.txt","po1250000.txt","po1500000.txt","po2000000.txt"};
    
    int numFiles = sizeof(fileNames) / sizeof(fileNames[0]);
  clock_t start_time = clock(); // Inicia a contagem do tempo

    for (int i = 0; i < numFiles; i++) {
        superMergeSortForFile(fileNames[i]);
    }
  clock_t end_time = clock(); // Finaliza a contagem do tempo

  double total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

  printf("Tempo total de execução: %f segundos\n", total_time);
    return 0;
}
