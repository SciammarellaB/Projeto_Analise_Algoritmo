#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_MOEDAS 20
#define MAX_VALOR 10000
#define REPETICOES_TEMPO 100000

typedef struct {
    int possivel;
    int total_moedas;
    int usadas[MAX_MOEDAS];
    long operacoes;
} Resultado;

int comparar_decrescente(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;

    if (x < y) {
        return 1;
    }
    if (x > y) {
        return -1;
    }
    return 0;
}

void zerar_resultado(Resultado *r, int n) {
    int i;

    r->possivel = 0;
    r->total_moedas = 0;
    r->operacoes = 0;

    for (i = 0; i < n; i++) {
        r->usadas[i] = 0;
    }
}

Resultado algoritmo_guloso(int moedas[], int n, int valor) {
    Resultado r;
    int restante;
    int i;
    int quantidade;

    zerar_resultado(&r, n);
    restante = valor;

    for (i = 0; i < n; i++) {
        quantidade = restante / moedas[i];
        r.usadas[i] = quantidade;
        r.total_moedas += quantidade;
        restante -= quantidade * moedas[i];
        r.operacoes++;
    }

    r.possivel = (restante == 0);
    return r;
}

Resultado programacao_dinamica(int moedas[], int n, int valor) {
    Resultado r;
    int dp[MAX_VALOR + 1];
    int ultima_moeda[MAX_VALOR + 1];
    int i;
    int v;
    int atual;
    int indice;

    zerar_resultado(&r, n);

    for (v = 0; v <= valor; v++) {
        dp[v] = INT_MAX / 2;
        ultima_moeda[v] = -1;
    }

    dp[0] = 0;

    for (v = 1; v <= valor; v++) {
        for (i = 0; i < n; i++) {
            r.operacoes++;

            if (moedas[i] <= v && dp[v - moedas[i]] + 1 < dp[v]) {
                dp[v] = dp[v - moedas[i]] + 1;
                ultima_moeda[v] = i;
            }
        }
    }

    if (dp[valor] < INT_MAX / 2) {
        r.possivel = 1;
        r.total_moedas = dp[valor];
        atual = valor;

        while (atual > 0) {
            indice = ultima_moeda[atual];

            if (indice < 0) {
                break;
            }

            r.usadas[indice]++;
            atual -= moedas[indice];
        }
    }

    return r;
}

void imprimir_resultado(const char *nome, int moedas[], int n, Resultado r) {
    int i;

    printf("%s\n", nome);
    printf("Possivel: %s\n", r.possivel ? "sim" : "nao");

    if (r.possivel) {
        printf("Total de moedas: %d\n", r.total_moedas);
        printf("Composicao: ");

        for (i = 0; i < n; i++) {
            if (r.usadas[i] > 0) {
                printf("%d moeda(s) de %d  ", r.usadas[i], moedas[i]);
            }
        }

        printf("\n");
    }

    printf("Operacoes estimadas: %ld\n\n", r.operacoes);
}

void medir_tempo(int moedas[], int n, int valor) {
    clock_t inicio;
    clock_t fim;
    double tempo_guloso;
    double tempo_dinamico;
    int i;
    int soma_controle;
    Resultado r;

    soma_controle = 0;

    inicio = clock();
    for (i = 0; i < REPETICOES_TEMPO; i++) {
        r = algoritmo_guloso(moedas, n, valor);
        soma_controle += r.total_moedas;
    }
    fim = clock();
    tempo_guloso = (double)(fim - inicio) / CLOCKS_PER_SEC;

    inicio = clock();
    for (i = 0; i < REPETICOES_TEMPO; i++) {
        r = programacao_dinamica(moedas, n, valor);
        soma_controle += r.total_moedas;
    }
    fim = clock();
    tempo_dinamico = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("Tempo de execucao em %d repeticoes:\n", REPETICOES_TEMPO);
    printf("Guloso: %.6f segundos\n", tempo_guloso);
    printf("Programacao dinamica: %.6f segundos\n", tempo_dinamico);
    printf("Controle: %d\n\n", soma_controle);
}

void executar_caso(const char *titulo, int moedas_originais[], int n, int valor) {
    int moedas[MAX_MOEDAS];
    int i;
    Resultado guloso;
    Resultado dinamico;

    for (i = 0; i < n; i++) {
        moedas[i] = moedas_originais[i];
    }

    qsort(moedas, n, sizeof(int), comparar_decrescente);

    printf("========================================\n");
    printf("%s\n", titulo);
    printf("Valor do troco: %d\n", valor);
    printf("Moedas disponiveis: ");

    for (i = 0; i < n; i++) {
        printf("%d ", moedas[i]);
    }

    printf("\n\n");

    guloso = algoritmo_guloso(moedas, n, valor);
    dinamico = programacao_dinamica(moedas, n, valor);

    imprimir_resultado("Algoritmo guloso", moedas, n, guloso);
    imprimir_resultado("Programacao dinamica", moedas, n, dinamico);
    medir_tempo(moedas, n, valor);
}

int main(void) {
    int moedas_caso_1[] = {1, 5, 10, 25, 50, 100};
    int moedas_caso_2[] = {1, 3, 4};

    executar_caso("Caso 1 - Moedas comuns", moedas_caso_1, 6, 289);
    executar_caso("Caso 2 - Exemplo em que o guloso nao e otimo", moedas_caso_2, 3, 6);

    return 0;
}
