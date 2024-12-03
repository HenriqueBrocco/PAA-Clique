int comparacoes2 = 0;  // Número de comparações feitas
int subconjuntos2 = 0; // Número de subconjuntos testados

// Função para verificar se um vértice pode ser adicionado ao clique
bool adiciona(int grafo[100][100], int clique[], int tamanhoClique, int vertice){
    for(int i = 0; i < tamanhoClique; i++){
        comparacoes2++; // Incrementa o número de comparações
        if(grafo[clique[i]][vertice] == 0){
            return false; // Não há aresta entre vertice e algum outro vértice do clique
        }
    }
    return true;
}

// Função gulosa para verificar se existe um clique de tamanho k
bool cliqueGuloso(int n, int grafo[100][100], int k){
    int clique[100];
    int tamanhoClique = 0;

    for(int v = 0; v < n; v++){
        subconjuntos2++; // Incrementa o número de subconjuntos testados
        if(adiciona(grafo, clique, tamanhoClique, v)){
            clique[tamanhoClique++] = v;
            if(tamanhoClique == k){
                return true; // Encontrou um clique de tamanho k
            }
        }
    }
    return false; // Não encontrou clique de tamanho k
}