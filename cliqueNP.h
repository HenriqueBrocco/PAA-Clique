int comparacoes1 = 0;  // Número de comparações feitas
int subconjuntos1 = 0; // Número de subconjuntos testados

int numeroBits(int num){
    int count = 0;
    while(num){
        count += (num & 1);
        num >>= 1;          
    }
    return count;
}

// Função para verificar se um subconjunto de vértices forma um clique
bool isClique(int n, int grafo[100][100], int subVertice){
    for(int i = 0; i < n; i++){
        if(subVertice & (1 << i)) {
            for(int j = i + 1; j < n; j++){
                if(subVertice & (1 << j)){
                    comparacoes1++; // Contabiliza a comparação entre vértices
                    if(grafo[i][j] == 0) {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

// Função principal para encontrar um clique de tamanho k
bool clique(int n, int grafo[100][100], int k){
    unsigned long long maximo = (1ULL << n); // Total de subconjuntos possíveis (2^n)

    for(unsigned long long subVertice = 0; subVertice < maximo; subVertice++){
        if (numeroBits(subVertice) == k){
            subconjuntos1++; // Contabiliza o subconjunto testado
            if(isClique(n, grafo, subVertice)){
                return true;
            }
        }
    }
    return false;
}