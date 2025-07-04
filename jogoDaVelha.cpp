#include <cstdlib>
#include <iostream>
#include "jogadas.hpp"

using namespace std;

int main() {
    char tab[3][3];
    srand(time(0)); //gerador de números aleatórios

    //inicializa tabuleiro vazio
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tab[i][j] = ' ';
        }
    }
    cout << "=== JOGO DA VELHA ===" << endl;
    //sorteia quem começa
    bool turnoJogador = rand() % 2 == 0;
    if(turnoJogador) 
        cout << "Voce comeca!" << endl;
    else 
        cout << "Computador comeca!" << endl;

    //caso o computador comece, ele faz sua jogada antes de entrar no loop 
    if(!turnoJogador){
        cout << "\nComputador esta jogando...\n";
        jogarComputador(tab);
        mostrarTabuleiro(tab); //mostra o tabuleiro após a jogada do computador
    }else{
        mostrarTabuleiro(tab); //se o jogador começa, mostra o tabuleiro vazio
    }

    //loop principal do jogo
    while(true){
        //turno do jogador humano
        cout << "\nSua vez!\n";
        jogarHumano(tab); //jogada do jogador
        mostrarTabuleiro(tab); //mostra o tabuleiro atualizado

        //verifica se houve vitória após a jogada do jogador
        char vencedor = verificarVitoria(tab);
        if(vencedor != ' '){
            cout << (vencedor == 'X' ? "Voce venceu!" : "Computador venceu!") << endl;
            break;
        }

        //verifica se houve empate após a jogada do jogador
        if(verificarEmpate(tab)){
            cout << "Empate!" << endl;
            break;
        }

        //turno do computador
        cout << "\nComputador esta jogando...\n";
        jogarComputador(tab); //jogada do computador
        mostrarTabuleiro(tab); //mostra o tabuleiro atualizado após a jogada do computador
        
        //verifica se houve vitória após a jogada do computador
        vencedor = verificarVitoria(tab);
        if(vencedor != ' '){
            cout << (vencedor == 'X' ? "Voce venceu!" : "Computador venceu!") << endl;
            break;
        }

        //verifica se houve empate após a jogada do computador
        if(verificarEmpate(tab)){
            cout << "Empate!" << endl;
            break;
        }
    }

    return 0;
}
