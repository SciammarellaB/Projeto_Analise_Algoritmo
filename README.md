# Projeto e Analise de Algoritmos

Repositorio de apoio para o trabalho de Projeto e Analise de Algoritmos.

Link do repositorio: <https://github.com/SciammarellaB/Projeto_Analise_Algoritmo>

Os codigos foram escritos em C de forma simples, com valores fixos no proprio `main`, para facilitar a execucao direta no Dev-C++.

## Arquivos

- `Questao1.c`: problema do troco com algoritmo guloso e programacao dinamica.
- `Questao3.c`: sistema anti-spam com trie, incluindo `ADD`, `CHECK` e `COUNT`.

## Como executar no Dev-C++

1. Abrir o arquivo `.c` desejado.
2. Compilar.
3. Executar.

Os dados de teste ja estao definidos dentro do `main`, entao nao e necessario digitar entrada pelo teclado.

## Q1 - Problema do Troco

O Problema do Troco consiste em formar um determinado valor usando a menor quantidade possivel de moedas.

Foram implementadas duas estrategias:

- Algoritmo guloso.
- Programacao dinamica.

### Algoritmo guloso

O algoritmo guloso ordena as moedas em ordem decrescente e sempre escolhe a maior moeda possivel para o valor restante.

Passos:

1. Ordenar as moedas da maior para a menor.
2. Pegar a maior quantidade possivel da moeda atual.
3. Subtrair o valor usado do troco restante.
4. Repetir o processo para as proximas moedas.

Complexidade:

- Tempo: `O(M log M)` por causa da ordenacao, mais `O(M)` para percorrer as moedas.
- Espaco: `O(M)` para armazenar a composicao da resposta.

O algoritmo guloso e rapido, mas nem sempre encontra a menor quantidade possivel de moedas.

### Programacao dinamica

A programacao dinamica calcula a melhor resposta para todos os valores de `0` ate o valor do troco. O vetor `dp[v]` guarda a menor quantidade de moedas necessaria para formar o valor `v`.

Passos:

1. Criar o vetor `dp`.
2. Definir `dp[0] = 0`.
3. Para cada valor, testar todas as moedas.
4. Guardar a menor quantidade encontrada.
5. Reconstruir a composicao final da resposta.

Complexidade:

- Tempo: `O(M * V)`, em que `M` e a quantidade de moedas e `V` e o valor do troco.
- Espaco: `O(V + M)`.

A programacao dinamica tem custo maior, mas encontra a melhor resposta quando o troco pode ser formado.

### Comparacao

No primeiro teste, usando moedas comuns, os dois algoritmos encontram a mesma resposta.

No segundo teste, usando moedas `(1, 3, 4)` para formar o valor `6`, o algoritmo guloso escolhe `4 + 1 + 1`, totalizando 3 moedas. A programacao dinamica encontra `3 + 3`, totalizando 2 moedas.

Tambem foi adicionada uma medicao simples de tempo com `clock()`. Cada algoritmo e executado varias vezes para que a diferenca de tempo fique visivel. O tempo pode variar conforme o computador, mas a tendencia e o guloso ser mais rapido e a programacao dinamica ser mais custosa.

## Q2 - Analise de Complexidade Big O

| Algoritmo | Complexidade | Justificativa |
|---|---:|---|
| `Algoritmo1(n)` | `O(log n)` | A variavel `i` comeca em `n` e e dividida por 2 a cada repeticao. |
| `Funcao2(n)` | `O(log n)` | A funcao faz apenas uma chamada recursiva para `n / 2`. |
| `Fib(n)` | `O(2^n)` | Cada chamada gera duas novas chamadas, repetindo muitos subproblemas. |
| `Funcao4(n)` | `O(n log n)` | A recorrencia e `T(n) = T(n/3) + T(2n/3) + O(n)`. Cada nivel soma `O(n)` e ha altura logaritmica. |

### Algoritmo1(n)

```text
cont = 0
i = n
enquanto i > 1 faca:
    i = i / 2
    cont = cont + 1
```

A cada repeticao, `i` e dividido por 2. Depois de `k` repeticoes, o valor sera aproximadamente `n / 2^k`. Portanto, a complexidade e `O(log n)`.

### Funcao2(n)

```text
Funcao2(n):
    se n <= 1 entao:
        retornar 1
    senao:
        retornar Funcao2(n / 2) + 1
```

A funcao reduz o problema pela metade e faz apenas uma chamada recursiva. A recorrencia e `T(n) = T(n/2) + O(1)`. Portanto, a complexidade e `O(log n)`.

### Fib(n)

```text
Fib(n):
    se n <= 1 entao:
        retornar n
    senao:
        retornar Fib(n - 1) + Fib(n - 2)
```

Essa implementacao recursiva recalcula os mesmos valores varias vezes. Como cada chamada pode gerar duas novas chamadas, a quantidade de chamadas cresce exponencialmente. Portanto, a complexidade e `O(2^n)`.

### Funcao4(n)

```text
Funcao4(n):
    se n <= 1 entao:
        retornar
    senao:
        Funcao4(n / 3)
        Funcao4(2n / 3)
        para i de 1 ate n faca:
            operacao_constante()
```

A funcao divide o problema em duas partes e ainda executa um laco linear. A soma dos tamanhos dos subproblemas em cada nivel e `n`, e a altura da arvore de recursao e logaritmica. Portanto, a complexidade e `O(n log n)`.

## Q3 - Sistema de Autocompletar com Restricoes

A terceira questao foi implementada usando uma trie.

Uma trie e uma arvore em que cada caminho representa um prefixo. Quando uma palavra proibida termina, o no correspondente e marcado como fim de palavra.

O codigo usa palavras proibidas fixas no `main`: `spam`, `golpe` e `promo`. Depois, ele adiciona a palavra `bot` para demonstrar a operacao `ADD`.

### Operacoes implementadas

- `ADD`: adiciona uma nova palavra proibida na trie.
- `CHECK`: verifica se o texto comeca com alguma palavra proibida.
- `COUNT`: conta quantas palavras proibidas possuem determinado prefixo.

### Funcionamento

Para verificar um texto, o programa percorre seus caracteres na trie. Se durante esse percurso encontrar um no marcado como fim de palavra, significa que o texto comeca com uma palavra proibida e deve ser bloqueado.

Complexidade:

- Insercao: `O(L)`, em que `L` e o tamanho da palavra.
- `CHECK`: `O(T)`, em que `T` e o tamanho do texto consultado.
- `COUNT`: `O(P)`, em que `P` e o tamanho do prefixo.
- Espaco: `O(S)`, em que `S` e a soma dos tamanhos das palavras armazenadas.
