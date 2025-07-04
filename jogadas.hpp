#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

//estrutura do nó da árvore de decisão
struct No{
    char tabuleiro[3][3]; //estado atual do tabuleiro
    No* filhos[7]; //ponteiros para até 7 filhos
    int numFilhos; //quantidade de filhos gerados

    No(){
        numFilhos = 0; 
        for(int i = 0; i < 7; i++){
            filhos[i] = nullptr;
        }
        //inicializa o tabuleiro vazio
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                tabuleiro[i][j] = ' ';
            }
        }
    }
};

//exibe o tabuleiro
void mostrarTabuleiro(char tab[3][3]){
    cout << endl;
    for(int i = 0; i < 3; i++){
        cout << " ";
        for(int j = 0; j < 3; j++){
            cout << tab[i][j];
            if(j < 2) cout << " | ";
        }
        cout << endl;
        if(i < 2) cout << "---+---+---" << endl;
    }
    cout << endl;
}

//verifica se há vitória e retorna o vencedor ('X', 'O') ou ' ' se ninguém venceu
char verificarVitoria(char tab[3][3]){
    //linhas e colunas
    for(int i = 0; i < 3; i++){
        if(tab[i][0] == tab[i][1] && tab[i][1] == tab[i][2] && tab[i][0] != ' ')
            return tab[i][0];
        if(tab[0][i] == tab[1][i] && tab[1][i] == tab[2][i] && tab[0][i] != ' ')
            return tab[0][i];
    }
    //diagonais
    if(tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2] && tab[0][0] != ' ')
        return tab[0][0];
    if(tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0] && tab[0][2] != ' ')
        return tab[0][2];

    return ' '; //ninguém venceu ainda
}

//verifica se houve empate (tabuleiro cheio e ninguém venceu)
bool verificarEmpate(char tab[3][3]){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if (tab[i][j] == ' ') return false; //ainda há jogadas
        }
    }
    return verificarVitoria(tab) == ' '; //se não há vencedor e tabuleiro cheio, é empate
}

//lê a jogada do jogador humano e garante que seja válida
void jogarHumano(char tab[3][3]){
    int linha, coluna;
    do{
        cout << "Informe linha (0-2) e coluna (0-2): ";
        cin >> linha >> coluna;
        if(tab[linha][coluna] != ' '){
            cout << "Posicao ocupada! Tente novamente." << endl;
        }
    }while(linha < 0 || linha > 2 || coluna < 0 || coluna > 2 || tab[linha][coluna] != ' ');

    tab[linha][coluna] = 'X';
}

//função que vai gerar as próximas jogadas possíveis (os filhos)
void gerarFilhosComPrioridade(No* noAtual, char simbolo){
    No* ordem[7];
    int indice = 0;
    char adversario = (simbolo == 'O') ? 'X' : 'O';

    //prioridade 1: jogadas vencedoras
    for(int i = 0; i < 3 && indice < 7; i++){
        for(int j = 0; j < 3 && indice < 7; j++){
            if(noAtual->tabuleiro[i][j] == ' '){
                No* filho = new No(); //cria um novo nó filho, representando um possível estado do jogo após a jogada
                for(int x = 0; x < 3; x++)
                    for(int y = 0; y < 3; y++)
                        filho->tabuleiro[x][y] = noAtual->tabuleiro[x][y]; //copia o tabuleiro atual (noAtual) para o novo filho
                filho->tabuleiro[i][j] = simbolo; //aplicamos a jogada do símbolo atual na posição (i, j)

                if(verificarVitoria(filho->tabuleiro) == simbolo) //verifica se essa jogada levaria à vitória do jogador atual
                    ordem[indice++] = filho; //se sim, adiciona esse filho ao vetor ordem
                else
                    delete filho; //caso contrário, descarta o filho
            }
        }
    }

    //prioridade 2: jogadas que bloqueiam o jogador
    for(int i = 0; i < 3 && indice < 7; i++){
        for(int j = 0; j < 3 && indice < 7; j++){
            if(noAtual->tabuleiro[i][j] == ' '){
                No* filho = new No(); //cria um novo nó filho pra simulação
                for(int x = 0; x < 3; x++)
                    for(int y = 0; y < 3; y++)
                        filho->tabuleiro[x][y] = noAtual->tabuleiro[x][y]; //copia o tabuleiro atual para o filho

                //simula a jogada do adversário
                filho->tabuleiro[i][j] = adversario; //coloca o símbolo do adversário na posição (i, j)
                if(verificarVitoria(filho->tabuleiro) == adversario){ //verifica se essa jogada levaria à vitória do adversário
                    filho->tabuleiro[i][j] = simbolo; //se sim, o computador joga nessa posição para bloquear a vitória do adversário
                    ordem[indice++] = filho; //adiciona esse filho ao vetor ordem
                }else{
                    delete filho; //se o adversário não venceria, o filho é descartado
                }
            }
        }
    }

    //prioridade 3: jogadas que empatam o jogo
    for(int i = 0; i < 3 && indice < 7; i++){
        for(int j = 0; j < 3 && indice < 7; j++){
            if(noAtual->tabuleiro[i][j] == ' '){
                No* filho = new No(); //cria um novo nó
                for(int x = 0; x < 3; x++)
                    for(int y = 0; y < 3; y++)
                        filho->tabuleiro[x][y] = noAtual->tabuleiro[x][y]; //copia o tabuleiro para o filho
                filho->tabuleiro[i][j] = simbolo; //simula a jogada na posição (i, j)

                if(verificarEmpate(filho->tabuleiro)) //verifica se essa jogada levaria a um empate
                    ordem[indice++] = filho; // se sim, adiciona o filho ao vetor ordem
                else
                    delete filho;
            }
        }
    }

    //prioridade 4: outras jogadas
    for(int i = 0; i < 3 && indice < 7; i++){
        for(int j = 0; j < 3 && indice < 7; j++){
            if(noAtual->tabuleiro[i][j] == ' '){
                No* filho = new No(); //cria um novo nó
                for(int x = 0; x < 3; x++)
                    for(int y = 0; y < 3; y++)
                        filho->tabuleiro[x][y] = noAtual->tabuleiro[x][y]; //copia o tabuleiro
                filho->tabuleiro[i][j] = simbolo; //simula a jogada nessa casa
                ordem[indice++] = filho; //adiciona ao vetor ordem mesmo sem prioridade, se ainda houver espaço
            }
        }
    }

    //atribui os filhos gerados ao noAtual
    noAtual->numFilhos = indice;
    for(int i = 0; i < indice; i++){
        noAtual->filhos[i] = ordem[i];
    }
}

//executa a jogada do computador (tenta bloquear o humano, se necessário, ou gera a árvore e escolhe uma jogada aleatória entre os filhos)
void jogarComputador(char tab[3][3]) {
    No* raiz = new No(); //cria o nó raiz da árvore de decisão com o estado atual do tabuleiro
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            raiz->tabuleiro[i][j] = tab[i][j]; //copia o estado atual do tabuleiro para o nó raiz

    gerarFilhosComPrioridade(raiz, 'O'); //gera os filhos do nó raiz com base nas jogadas possíveis, priorizando vitória, bloqueio, etc.

    if(raiz->numFilhos > 0){ //se houver pelo menos uma jogada possível
        No* melhor = raiz->filhos[0]; //seleciona o primeiro filho como a melhor jogada (prioridade já foi considerada na geração)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                tab[i][j] = melhor->tabuleiro[i][j]; //atualiza o tabuleiro principal com o tabuleiro do filho escolhido
    }

    delete raiz;
}

