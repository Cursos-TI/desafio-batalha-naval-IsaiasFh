#include <stdio.h>

#define TAM 10        // tamanho do tabuleiro
#define TAM_NAVIO 3   // tamanho fixo de cada navio
#define NAVIO 3       // valor que representa o navio no tabuleiro
#define AGUA 0        // valor que representa água

// Função para verificar se uma posição está livre
int posicao_livre(int tabuleiro[TAM][TAM], int linha, int coluna) {
    return (tabuleiro[linha][coluna] == AGUA);
}

// Função para imprimir o tabuleiro no console
void exibir_tabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se o navio cabe no tabuleiro
int cabe_no_tabuleiro(int linha, int coluna, char orientacao) {
    switch (orientacao) {
        case 'H': return (coluna + TAM_NAVIO <= TAM);
        case 'V': return (linha + TAM_NAVIO <= TAM);
        case 'D': return (linha + TAM_NAVIO <= TAM && coluna + TAM_NAVIO <= TAM); // diagonal descendo à direita
        case 'E': return (linha + TAM_NAVIO <= TAM && coluna - TAM_NAVIO + 1 >= 0); // diagonal descendo à esquerda
        default: return 0;
    }
}

// Função para verificar sobreposição antes de posicionar
int sobrepoe(int tabuleiro[TAM][TAM], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;
        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'E') { l += i; c -= i; }

        if (!posicao_livre(tabuleiro, l, c)) return 1; // encontrou sobreposição
    }
    return 0;
}

// Função para posicionar o navio no tabuleiro
void posicionar_navio(int tabuleiro[TAM][TAM], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha, c = coluna;
        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'D') { l += i; c += i; }
        else if (orientacao == 'E') { l += i; c -= i; }

        tabuleiro[l][c] = NAVIO;
    }
}

int main() {
    int tabuleiro[TAM][TAM];

    // 1. Inicializa o tabuleiro com água
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }

    // 2. Define coordenadas e orientações dos 4 navios
    // Orientações: H = horizontal, V = vertical, D = diagonal direita, E = diagonal esquerda
    int linha1 = 2, coluna1 = 3; char o1 = 'H';
    int linha2 = 5, coluna2 = 1; char o2 = 'V';
    int linha3 = 0, coluna3 = 0; char o3 = 'D'; // diagonal descendo à direita
    int linha4 = 0, coluna4 = 9; char o4 = 'E'; // diagonal descendo à esquerda

    // 3. Validação e posicionamento
    struct {
        int linha, coluna;
        char orientacao;
    } navios[4] = {
        {linha1, coluna1, o1},
        {linha2, coluna2, o2},
        {linha3, coluna3, o3},
        {linha4, coluna4, o4}
    };

    for (int n = 0; n < 4; n++) {
        int l = navios[n].linha;
        int c = navios[n].coluna;
        char o = navios[n].orientacao;

        // Verifica se cabe
        if (!cabe_no_tabuleiro(l, c, o)) {
            printf("Erro: navio %d nao cabe no tabuleiro!\n", n + 1);
            return 1;
        }

        // Verifica sobreposição
        if (sobrepoe(tabuleiro, l, c, o)) {
            printf("Erro: navio %d sobrepoe outro navio!\n", n + 1);
            return 1;
        }

        // Posiciona o navio
        posicionar_navio(tabuleiro, l, c, o);
    }

    // 4. Exibe o tabuleiro final
    exibir_tabuleiro(tabuleiro);

    return 0;
}