#include <stdio.h>


int main() {
    int tabuleiro[10][10];
    int i, j;

    // 1. Inicializa o tabuleiro com 0 (água)
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // 2. Define os navios (cada um com 3 partes representadas por 3)
    int navioHorizontal[3] = {3, 3, 3};
    int navioVertical[3]   = {3, 3, 3};

    // 3. Define as coordenadas iniciais dos navios
    int linhaH = 2; // linha inicial do navio horizontal
    int colH   = 4; // coluna inicial do navio horizontal

    int linhaV = 5; // linha inicial do navio vertical
    int colV   = 7; // coluna inicial do navio vertical

    // 4. Valida se os navios cabem no tabuleiro
    if (colH + 3 > 10) {
        printf("Erro: o navio horizontal nao cabe no tabuleiro!\n");
        return 1;
    }

    if (linhaV + 3 > 10) {
        printf("Erro: o navio vertical nao cabe no tabuleiro!\n");
        return 1;
    }

    // 5. Verifica sobreposição simples (para este nível)
    int sobrepoe = 0;
    for (i = 0; i < 3; i++) {
        if (tabuleiro[linhaH][colH + i] == 3 || tabuleiro[linhaV + i][colV] == 3) {
            sobrepoe = 1;
            break;
        }
    }

    if (sobrepoe) {
        printf("Erro: os navios se sobrepoem!\n");
        return 1;
    }

    // 6. Posiciona o navio horizontal no tabuleiro
    for (i = 0; i < 10; i++) {
        tabuleiro[linhaH][colH + i] = navioHorizontal[i];
    }

    // 7. Posiciona o navio vertical no tabuleiro
    for (i = 0; i < 3; i++) {
        tabuleiro[linhaV + i][colV] = navioVertical[i];
    }

    // 8. Exibe o tabuleiro no console
    printf("\n=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
