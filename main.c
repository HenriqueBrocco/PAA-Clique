#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "cliqueNP.h"
#include "cliqueGuloso.h"

void GerarGrafo(int n, int grafo[100][100]){
    printf("\nGRAFO GERADO DE %d VERTICES:", n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            int temp = rand() % 2;
            grafo[i][j] = temp;
            grafo[j][i] = temp;
            if (i == j)
                grafo[i][j] = 0;
        }
    }
    for(int i = 0; i < n; i++){
        printf("\n");
        for(int j = 0; j < n; j++){
            printf("%d, ", grafo[i][j]);
        }
    }
    printf("\n");
}

void GerarArquivo(int n, int grafo[100][100]){
    char nomeArquivo[10];
    sprintf(nomeArquivo, "grafo_%d.txt", n);
    FILE *grafogerado = fopen(nomeArquivo, "a");
    for(int i = 0; i < n; i++){
        fprintf(grafogerado, "\n");
        for(int j = 0; j < n; j++){
            fprintf(grafogerado, "%d, ", grafo[i][j]);
        }
    }
    fprintf(grafogerado, "\n");
}

int main(){
    //time_t start, end;
    LARGE_INTEGER start, end, freq;
    double tempo;
    FILE *log = fopen("log.csv", "a");
    bool cliqueSN;
    int grafo[100][100];
    srand(clock());
    
    for(int n = 10; n <= 25 ; n += 5){                     //Grafos de 10, 15, 20, 25, 30 e 35 vértices
        GerarGrafo(n, grafo);
        //GerarArquivo(n, grafo);
        printf("ALGORITMO DE FORCA BRUTA:\n");
        for(int k = 5; k <= 9; k +=2 ){                    //Cliques de Tamanho 5, 7 e 9;
            //start = clock();
            QueryPerformanceFrequency(&freq);
            QueryPerformanceCounter(&start);
            cliqueSN = clique(n, grafo, k);
            //end = clock();
            //tempo = ((double)(end-start))/CLOCKS_PER_SEC;
            QueryPerformanceCounter(&end);
            tempo = (double)(end.QuadPart-start.QuadPart)/freq.QuadPart;
            fprintf(log, "FORÇA BRUTA - Grafo de Tamanho: %d, Clique de Tamanho: %d, Tempo: %.7f Seg, Comparações: %d, Subconjuntos Testados: %d, Clique: %d\n", n, k, tempo, comparacoes1, subconjuntos1, cliqueSN);
            
            if(cliqueSN)
                printf("EXISTE CLIQUE DE TAMANHO %d\n", k);
            else
                printf("SEM CLIQUE DE TAMANHO %d\n", k);
            
        }
        printf("ALGORITMO GULOSO:\n");
        for(int k = 5; k <= 9; k += 2){                    //Cliques de Tamanho 5, 7 e 9;
            //start = clock();
            QueryPerformanceFrequency(&freq);
            QueryPerformanceCounter(&start);
            cliqueSN = cliqueGuloso(n, grafo, k);
            //end = clock();
            //tempo = ((double)(end-start))/CLOCKS_PER_SEC;
            QueryPerformanceCounter(&end);
            tempo = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
            fprintf(log, "GULOSO - Grafo de Tamanho: %d, Clique de Tamanho: %d, Tempo: %.7f Seg, Comparações: %d, Subconjuntos Testados: %d, Clique: %d\n", n, k, tempo, comparacoes2, subconjuntos2, cliqueSN);

            if (cliqueSN)
                printf("EXISTE CLIQUE DE TAMANHO %d\n", k);
            else
                printf("SEM CLIQUE DE TAMANHO %d\n", k);
        }
    }
    fprintf(log,"\n");
    fclose(log);
    return 0;
}