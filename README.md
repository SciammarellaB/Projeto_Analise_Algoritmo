# Projeto e Analise de Algoritmos

Repositorio com os codigos e o material de apoio do trabalho de Projeto e Analise de Algoritmos.

## Arquivos

- `Questao1.c`: problema do troco com algoritmo guloso, programacao dinamica e comparacao de tempo.
- `Questao3.c`: sistema anti-spam com trie, incluindo as operacoes `ADD`, `CHECK` e `COUNT`.
- `Trabalho_Projeto_Analise_Algoritmos.md`: versao em Markdown do trabalho, com capa, respostas, saidas esperadas e codigos completos.

## Como executar no Dev-C++

1. Abrir o arquivo `Questao1.c` ou `Questao3.c`.
2. Compilar.
3. Executar.

Os dados de teste ja estao definidos dentro do `main`, entao nao e necessario digitar entrada pelo teclado.

## Resumo das questoes

### Q1 - Problema do Troco

Foram implementadas duas solucoes:

- Algoritmo guloso: escolhe sempre a maior moeda possivel para o valor restante.
- Programacao dinamica: calcula a melhor resposta para todos os valores ate o troco desejado.

O codigo tambem mede o tempo de execucao dos dois metodos usando `clock()`, repetindo as execucoes para deixar a diferenca de custo mais visivel.

### Q2 - Analise Big O

As respostas da analise de complexidade estao no arquivo `Trabalho_Projeto_Analise_Algoritmos.md`.

Resultados principais:

- `Algoritmo1(n)`: `O(log n)`
- `Funcao2(n)`: `O(log n)`
- `Fib(n)`: `O(2^n)`
- `Funcao4(n)`: `O(n log n)`

### Q3 - Trie anti-spam

A trie armazena palavras proibidas e permite:

- adicionar uma nova palavra proibida;
- verificar se um texto comeca com alguma palavra proibida;
- contar quantas palavras proibidas possuem determinado prefixo.
