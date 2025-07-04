# Jogo Da Velha com Inteligência Artificial por Árvore de Decisão

## Descrição do Projeto
Este projeto consiste na implementação de um **jogo da velha** onde o jogador humano desafia o computador, que utiliza uma **inteligência artificial** baseada em uma **árvore de decisão** para escolher suas jogadas. A IA é capaz de **bloquear** as tentativas do adversário de vencer, buscar o caminho da **vitória** e **evitar derrotas**.

## Objetivo
O jogo da velha é um clássico que oferece uma excelente oportunidade para aprendizado em estruturas de dados e algoritmos, especialmente árvores de decisão. 

O objetivo do projeto é construir um sistema que:
  - Permita a interação entre humano e máquina.
  - Aplique conceitos de programação, manipulação de matrizes, e estruturas dinâmicas (árvores).
  - Demonstre a capacidade da máquina em realizar escolhas inteligentes em jogos simples.

## Tecnologias e Estruturas de Dados Utilizadas
- Linguagem: **C++**
- **Matriz**: Representa o **estado do tabuleiro** do jogo da velha e é utilizada tanto na interface com o jogador quanto na lógica da IA.
- **Árvore de Decisão**:
  - Estrutura dinâmica implementada por meio de nós com ponteiros.
  - Utilizada pela IA para simular jogadas e buscar a **melhor decisão** com base em possibilidades futuras.
- **Ponteiros**: Usados para conectar cada nó a seus filhos e manipular múltiplos estados do tabuleiro simultaneamente.
- **Vetores temporários**: Usados na **ordenação de prioridades** durante a geração dos filhos.

## Regras do Jogo
  - O tabuleiro é uma matriz 3x3.
  - Dois jogadores: humano (X) e computador (O).
  - O turno inicial é decidido aleatoriamente.
  - Os dois primeiros movimentos (um para cada jogador) são livres.
  - Nas jogadas seguintes, o computador **decide** sua jogada com base na análise da **árvore de decisão**.
  - O jogo termina quando:
    - Um dos jogadores consegue alinhar 3 dos seus símbolos em linha, coluna ou diagonal.
    - O tabuleiro está cheio e ninguém venceu, o que configura um empate.

## Lógica da Inteligência Artificial
A IA do computador utiliza uma **árvore de decisão**, onde:
  - Cada nó representa um estado do tabuleiro (matriz 3x3).
  - Cada nó pode ter até 7 filhos -> filhos são os possíveis estados após as jogadas seguintes.
  - As jogadas são priorizadas na geração dos filhos:
  1. Jogadas que resultam em **vitória imediata para o computador**.
  2. Jogadas que **bloqueiam** uma vitória iminente do **humano**.
  3. Jogadas que resultam em **empate**.
  4. **Outras** jogadas possíveis.

Fluxo da jogada do computador:
  1. Verifica se o humano pode vencer no próximo movimento.
  2. Se sim, joga para **bloquear**.
  3. Caso contrário, cria a árvore de decisão dos movimentos possíveis.
  4. Escolhe a jogada que leva à **vitória**.
  5. Se não encontrar caminho para a vitória, joga qualquer jogada válida.

## Exemplo de Execução
```bash
 === JOGO DA VELHA ===
Voce comeca!

   |   |  
---+---+---
   |   |  
---+---+---
   |   |  

Sua vez!
Informe linha (0-2) e coluna (0-2): 1 1

   |   |  
---+---+---
   | X |  
---+---+---
   |   |  

Computador esta jogando...

   |   |  
---+---+---
   | X | O
---+---+---
   |   |  

Sua vez!
Informe linha (0-2) e coluna (0-2): 0 0

 X |   |  
---+---+---
   | X | O
---+---+---
   |   |  

Computador esta jogando...

 X |   |  
---+---+---
 O | X | O
---+---+---
   |   |  

Sua vez!
Informe linha (0-2) e coluna (0-2): 2 1

 X |   |  
---+---+---
 O | X | O
---+---+---
   | X |  

Computador esta jogando...

 X |   |  
---+---+---
 O | X | O
---+---+---
 O | X |  

Computador venceu!
```
### Observações sobre o exemplo:
  - O jogo começa com o jogador humano (X), que escolhe jogar na posição (1, 1).
  - O computador (O) responde e joga em uma posição aleatória (dentro da lógica da IA).
  - O jogo alterna entre jogador e computador até que:
    - Um dos dois alinhe três símbolos (vitória) ou
    - O tabuleiro fique completamente preenchido (empate).
  - Ao final, o sistema declara o vencedor ou informa que houve empate.

## Estrutura do Código
Arquivos principais:
  - `main.cpp`: contém o loop principal do jogo, controle dos turnos e interação com o jogador.
  - `jogadas.hpp`: contém funções para:
    - Mostrar o tabuleiro.
    - Verificar vitória ou empate.
    - Receber jogada do humano.
    - Gerar os filhos da árvore de decisão.
    - Realizar a jogada do computador.
   
## Como jogar
1. Clone o repositório do jogo em seu computador com o comando abaixo:
```bash
git clone https://github.com/marias1lva/JogoDaVelha.git
cd JogoDaVelha
```
2. Compile o código usando um compilador de C++, como o g++:
```bash
g++ -o JogoDaVelha JogoDaVelha.cpp jogodas.hpp
```
3. Execute o programa:
```bash
./JogoDaVelha
```
4. Siga as instruções para jogar.
