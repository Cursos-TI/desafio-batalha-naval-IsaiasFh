#include <stdio.h>
#include <stdlib.h>

#define TAM 10        // tamanho do tabuleiro
#define TAM_HAB 5     // tamanho das matrizes de habilidade
#define NAVIO 3
#define AGUA 0
#define HABILIDADE 5

// Função para exibir o tabuleiro
void exibir_tabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para inicializar o tabuleiro com água
void inicializar_tabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// ======== CRIAÇÃO DAS MATRIZES DE HABILIDADE ========

// Habilidade em forma de cone (ponta para baixo)
void criar_cone(int cone[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (j >= (TAM_HAB / 2 - i) && j <= (TAM_HAB / 2 + i))
                cone[i][j] = 1;
            else
                cone[i][j] = 0;
        }
    }
}

// Habilidade em forma de cruz
void criar_cruz(int cruz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (i == TAM_HAB / 2 || j == TAM_HAB / 2)
                cruz[i][j] = 1;
            else
                cruz[i][j] = 0;
        }
    }
}

// Habilidade em forma de octaedro (losango)
void criar_octaedro(int octa[TAM_HAB][TAM_HAB]) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // A posição faz parte do octaedro se a soma das distâncias ao centro for menor ou igual ao raio
            if (abs(i - centro) + abs(j - centro) <= centro)
                octa[i][j] = 1;
            else
                octa[i][j] = 0;
        }
    }
}

// ======== FUNÇÃO DE SOBREPOSIÇÃO ========

// Sobrepõe a matriz da habilidade ao tabuleiro, centrando no ponto de origem
void aplicar_habilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int origem_linha, int origem_coluna) {
    int centro = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (habilidade[i][j] == 1) {
                int linha = origem_linha - centro + i;
                int coluna = origem_coluna - centro + j;

                // Verifica se a posição está dentro dos limites do tabuleiro
                if (linha >= 0 && linha < TAM && coluna >= 0 && coluna < TAM) {
                    // Marca apenas se não for navio
                    if (tabuleiro[linha][coluna] == AGUA)
                        tabuleiro[linha][coluna] = HABILIDADE;
                }
            }
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    inicializar_tabuleiro(tabuleiro);

    // Posicionamento simples de dois navios de exemplo (para visualização)
    tabuleiro[2][4] = NAVIO;
    tabuleiro[2][5] = NAVIO;
    tabuleiro[6][7] = NAVIO;
    tabuleiro[7][7] = NAVIO;

    // ======== Criação das habilidades ========
    int cone[TAM_HAB][TAM_HAB];
    int cruz[TAM_HAB][TAM_HAB];
    int octa[TAM_HAB][TAM_HAB];

    criar_cone(cone);
    criar_cruz(cruz);
    criar_octaedro(octa);

    // ======== Aplicação das habilidades no tabuleiro ========
    aplicar_habilidade(tabuleiro, cone, 1, 2);   // Cone centrado próximo ao topo
    aplicar_habilidade(tabuleiro, cruz, 5, 5);   // Cruz no centro
    aplicar_habilidade(tabuleiro, octa, 8, 8);   // Octaedro no canto inferior direito

    // ======== Exibição final ========
    exibir_tabuleiro(tabuleiro);

    return 0;
}