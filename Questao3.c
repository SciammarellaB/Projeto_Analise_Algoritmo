#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALFABETO 256

typedef struct NoTrie {
    struct NoTrie *filhos[ALFABETO];
    int fim_de_palavra;
    int qtd_prefixo;
} NoTrie;

NoTrie *criar_no(void) {
    NoTrie *no;
    int i;

    no = (NoTrie *)malloc(sizeof(NoTrie));

    if (no == NULL) {
        printf("Erro ao alocar memoria.\n");
        exit(1);
    }

    no->fim_de_palavra = 0;
    no->qtd_prefixo = 0;

    for (i = 0; i < ALFABETO; i++) {
        no->filhos[i] = NULL;
    }

    return no;
}

int contem_palavra(NoTrie *raiz, const char *palavra) {
    NoTrie *atual;
    unsigned char c;
    int i;

    atual = raiz;

    for (i = 0; palavra[i] != '\0'; i++) {
        c = (unsigned char)palavra[i];

        if (atual->filhos[c] == NULL) {
            return 0;
        }

        atual = atual->filhos[c];
    }

    return atual->fim_de_palavra;
}

void inserir(NoTrie *raiz, const char *palavra) {
    NoTrie *atual;
    unsigned char c;
    int i;

    if (palavra[0] == '\0' || contem_palavra(raiz, palavra)) {
        return;
    }

    atual = raiz;
    raiz->qtd_prefixo++;

    for (i = 0; palavra[i] != '\0'; i++) {
        c = (unsigned char)palavra[i];

        if (atual->filhos[c] == NULL) {
            atual->filhos[c] = criar_no();
        }

        atual = atual->filhos[c];
        atual->qtd_prefixo++;
    }

    atual->fim_de_palavra = 1;
}

int texto_bloqueado(NoTrie *raiz, const char *texto) {
    NoTrie *atual;
    unsigned char c;
    int i;

    atual = raiz;

    for (i = 0; texto[i] != '\0'; i++) {
        c = (unsigned char)texto[i];

        if (atual->filhos[c] == NULL) {
            return 0;
        }

        atual = atual->filhos[c];

        if (atual->fim_de_palavra) {
            return 1;
        }
    }

    return 0;
}

int contar_com_prefixo(NoTrie *raiz, const char *prefixo) {
    NoTrie *atual;
    unsigned char c;
    int i;

    atual = raiz;

    for (i = 0; prefixo[i] != '\0'; i++) {
        c = (unsigned char)prefixo[i];

        if (atual->filhos[c] == NULL) {
            return 0;
        }

        atual = atual->filhos[c];
    }

    return atual->qtd_prefixo;
}

void liberar_trie(NoTrie *no) {
    int i;

    if (no == NULL) {
        return;
    }

    for (i = 0; i < ALFABETO; i++) {
        liberar_trie(no->filhos[i]);
    }

    free(no);
}

void consultar_texto(NoTrie *raiz, const char *texto) {
    printf("CHECK %-25s -> %s\n", texto, texto_bloqueado(raiz, texto) ? "BLOQUEADA" : "PERMITIDA");
}

void consultar_prefixo(NoTrie *raiz, const char *prefixo) {
    printf("COUNT %-25s -> %d\n", prefixo, contar_com_prefixo(raiz, prefixo));
}

int main(void) {
    NoTrie *raiz;

    raiz = criar_no();

    inserir(raiz, "spam");
    inserir(raiz, "golpe");
    inserir(raiz, "promo");

    printf("Palavras proibidas iniciais: spam, golpe, promo\n\n");

    consultar_texto(raiz, "spam hoje");
    consultar_texto(raiz, "mensagem normal");
    consultar_texto(raiz, "promocao gratis");

    printf("\nAdicionando nova palavra proibida: bot\n\n");
    inserir(raiz, "bot");

    consultar_texto(raiz, "bot enviado");
    consultar_prefixo(raiz, "pro");
    consultar_prefixo(raiz, "g");

    liberar_trie(raiz);

    return 0;
}
