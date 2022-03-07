#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "Estacionamento.h"

/// funções que chmam as funções do .c para a execução do programa.
void continua(void);
void menu(void);
int opcao(void);
void insere(Pilha** fileira, Pilha* rua, int num_pilhas, int num_carros_est, int num_carros_rua);
void Exibe(Pilha** fileira, Pilha* rua, int num_pilhas, int num_carros_est, int num_carros_rua);
void retira(Pilha** fileira, Pilha* rua, char *placa, int num_pilhas, int num_carros, int num_carros_rua);

int main()
{
    setlocale(LC_ALL, "");

    int op;
    char c[30];
    char *s = malloc(9*sizeof(char));
    int num_pilhas = 0, num_carros_est = 0, num_carros_rua = 0;

    while(1){
        menu();
        do{
            printf("\n\nEntre com a sua opção: ");
            scanf("%s", c);
            op = atoi(c);
        }while(op < 1 || op > 5);

        switch(op){
            case 1:
                continua();
                printf("\nCriação do estacionamento\n\nEntre com o número de pilhas: ");
                fflush(stdin);
                scanf("%s", c);
                num_pilhas = atoi(c);
                while(num_pilhas < 0){
                    printf("\nEntre com um número de pilhas válido, inteiro acima de 0: ");
                    fflush(stdin);
                    scanf("%s", c);
                    num_pilhas = atoi(c);
                }
                printf("\nEntre com o número de carros máximo para o estacionamento: ");
                fflush(stdin);
                scanf("%s", c);
                num_carros_est = atoi(c);
                while(num_carros_est < 0){
                    printf("\nEntre com o número de carros máximo válido para o estacionamento, acima de 0: ");
                    fflush(stdin);
                    scanf("%s", c);
                    num_carros_est = atoi(c);
                }
                printf("\nEntre com o número de carros máximo para a rua: ");
                fflush(stdin);
                scanf("%s", c);
                num_carros_rua = atoi(c);
                while(num_carros_rua < 0){
                    printf("\nEntre com o número de carros máximo para a rua, acima de 0: ");
                    fflush(stdin);
                    scanf("%s", c);
                    num_carros_rua = atoi(c);
                }
                Pilha **fileira;
                fileira = cria_estacionamento(num_pilhas, num_carros_est);
                Pilha *rua = pilha_cria();
                printf("\nEstacionamento configurado com sucesso\n");
                Exibe(fileira, rua, num_pilhas, num_carros_est, num_carros_rua);
                system("pause");
                continua();
                break;
            case 2:
                if(num_pilhas == 0){
                    printf("\nEstacionamento ainda não foi criado\n\n");
                    system("pause");
                    continua();
                    break;
                }
                insere(fileira, rua, num_pilhas, num_carros_est, num_carros_rua);
                continua();
                break;
            case 3:
                if(num_pilhas == 0){
                    printf("\nEstacionamento ainda não foi criado\n\n");
                    system("pause");
                    continua();
                    break;
                }
                system("cls");
                printf("\n\n");
                Exibe(fileira, rua, num_pilhas, num_carros_est, num_carros_rua);
                system("pause");
                continua();
                break;
            case 4:
                if(num_pilhas == 0){
                    printf("\nEstacionamento ainda não foi criado\n\n");
                    system("pause");
                    continua();
                    break;
                }
                if(verifica_est_vazio(fileira, num_pilhas) == 1){
                    printf("\nEstacionamento vazio, não há carros para remover\n");
                    system("pause");
                    continua();
                    break;
                }

                system("cls");
                printf("\n\n");
                Exibe(fileira, rua, num_pilhas, num_carros_est, num_carros_rua);
                printf("\nEntre com o carro que deseja remover: ");
                fflush(stdin);
                scanf("%s", s);
                retira(fileira, rua, s, num_pilhas, num_carros_est, num_carros_rua);
                continua();
                break;
            case 5:
                exit(1);

        }
    }

}

void continua(void){

    printf("\n");
    system("cls");
    printf("\n");
}

void menu(void){

    printf("\n\n\n\n\t\t\t\t 1 - Configurar Estacionamento.");
    printf("\n\n\n\n\t\t\t\t 2 - Inserir Carro.");
    printf("\n\n\n\n\t\t\t\t 3 - Exibir Estacionamento.");
    printf("\n\n\n\n\t\t\t\t 4 - Retirar Carro do Estacionamento.");
    printf("\n\n\n\n\t\t\t\t 5 - Sair.");

}

void insere(Pilha** fileira, Pilha* rua, int num_pilhas, int num_carros_est, int num_carros_rua){

    continua();
    int x;
    x = indica_fileira(fileira, num_pilhas, num_carros_est);

    printf("\nSugiro estacionar na fileira %i", x + 1);
    Exibe(fileira, rua, num_pilhas, num_carros_est, num_carros_rua);
    int pos, aux_pos;
    float tempo = -1;
    char *s, c[30];
    s = malloc(9*sizeof(char));

    if(verifica_est_cheio(fileira, num_pilhas, num_carros_est) == 1){
        printf("\nEstacionamento lotado!\nRemova um carro primeiro para inserir novos carros\n");
        system("pause");
        return;
    }

    printf("\nEm qual fileira deseja colocar o carro: ");
    fflush(stdin);
    scanf("%s", c);
    pos = atoi(c);
    while(pos < 1 || pos > num_pilhas){
        printf("\nEm qual fileira deseja colocar o carro: ");
        fflush(stdin);
        scanf("%s", c);
        pos = atoi(c);
    }

    while(1){
        if(fileira[pos-1]->num_carros == num_carros_est){
            printf("\nNão é possível colocar o carro nessa fileira\n");
            printf("Entre em outra fileira");
            aux_pos = pos;
            while(pos == aux_pos || pos > num_pilhas){
                printf("\nEm qual fileira deseja colocar o carro: ");
                fflush(stdin);
                scanf("%s", c);
                pos = atoi(c);
            }
        }else
            break;
    }

    printf("\nEntre com a previsão de retirada, trabalhamos apenas com hora(1 a 24): ");
    fflush(stdin);
    scanf("%s", c);
    tempo = atoi(c);
    while(tempo < 1 || tempo > 24){
        printf("\nEntre com a previsão de retirada(1 a 24)hora(s): ");
        fflush(stdin);
        scanf("%s", c);
        tempo = atoi(c);
    }

    printf("\nEntre com a placa: ");
    fflush(stdin);
    scanf("%s", s);
    if(verifica_est_vazio(fileira, num_pilhas) == 0){

        while(busca_placa(fileira, num_pilhas, s) != -1){
            printf("\nEsse carro já foi inserido no estacionamento\nEntre com um novo");
            printf("\nEntre com a placa: ");
            fflush(stdin);
            scanf("%s", s);
        }
    }

    insere_carro(fileira[pos-1], s, tempo);
    Exibe(fileira, rua, num_pilhas, num_carros_est, num_carros_rua);
    system("pause");
}

void Exibe(Pilha** fileira, Pilha* rua,int num_pilhas, int num_carros_est, int num_carros_rua){

    int i = 0;
    printf("\nEstacionamento\n");
    while(i < num_pilhas){

        apresenta_estacionamento(fileira[i], num_carros_est);
        i++;
        printf("\n");
    }

    apresenta_rua(rua, num_carros_rua);
    printf("\n");

}

void retira(Pilha** fileira, Pilha* rua, char *placa, int num_pilhas, int num_carros_est, int num_carros_rua){

    retira_carro(fileira, rua, placa, num_pilhas, num_carros_est, num_carros_rua);
    continua();
    Exibe(fileira, rua, num_pilhas, num_carros_est, num_carros_rua);
    system("pause");
}


