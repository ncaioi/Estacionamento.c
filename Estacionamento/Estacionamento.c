#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Estacionamento.h"

Pilha* pilha_cria(void){

    Pilha *p = malloc(sizeof(Pilha));
    if(p == NULL){
        printf("\nProblema de alocação de memória\n");
        system("pause");
        exit(1);
    }
    p->num_carros = 0;
    p->prim = NULL;


    return p;
}

Pilha** cria_estacionamento(int npilhas, int ncarros){

    Pilha** estacionamento = malloc(npilhas*sizeof(Pilha*));
    int i;

    for(i = 0; i < npilhas; i++){
        Pilha* p = pilha_cria();

        estacionamento[i] = p;
    }

    return estacionamento;
}

void insere_carro(Pilha *p, char *placa, float tempo){

    Elemento *novo_carro = malloc(sizeof(Elemento));
    if(novo_carro == NULL){
        printf("\nProblema de alocação de memória\n");
        system("pause");
        exit(1);
    }
    novo_carro->placa = placa;
    novo_carro->prox = p->prim;
    novo_carro->previsao_de_retirada = tempo;
    p->prim = novo_carro;

    p->num_carros++;
}


int qtd_carros(Pilha *p){

    return p->num_carros;
}

int verifica_est_cheio(Pilha** p, int npilhas, int ncarros){

    Pilha **fileira = p;
    Pilha *q;
    int i, x;

    for(i = 0; i < npilhas; i++){
        q = fileira[i];

        x = qtd_carros(q);
        if(x == ncarros){
            x = 1;
            continue;
        }else{
            x = 0;
            break;
        }

    }

    if(x == 1)
        return 1;
    else
        return 0;
}

int verifica_est_vazio(Pilha** p, int npilhas){

    int i, x;

    for(i = 0; i < npilhas; i++){
        x = qtd_carros(p[i]);
        if(x == 0)
            continue;
        else
            break;
    }

    if(x == 0)
        return 1;
    else
        return 0;
}

int num_vagas(Pilha** fileira, int npilhas, int ncarros){

    Pilha *f;
    int i, soma = 0, vagas;

    for(i = 0; i < npilhas; i++){
        f = fileira[i];
        soma += f->num_carros;
    }

    vagas = npilhas*ncarros - soma;

    return vagas;
}

int busca_placa(Pilha **p, int npilhas, char *placa){

    Pilha *t;
    Elemento *q;
    int i, j, fileira;

    for(i = 0; i < npilhas; i++){
        t = p[i];
        q = t->prim;
        for(j = 0; j < p[i]->num_carros; j++){
            if(strcmp(q->placa, placa) == 0){
                fileira = i;
                return fileira;
            }
            else
                q = q->prox;
        }
    }

    return -1;
}

int indica_fileira(Pilha** p, int npilhas, int ncarros){

    int i, j = ncarros;
    int menor_fileira = 0;
    Pilha** fileira = p;

    for(i = 0; i < npilhas; i++){

        if(j >= fileira[i]->num_carros){
            menor_fileira = i;
            j = fileira[i]->num_carros;
        }
    }

    return menor_fileira;
}


void apresenta_estacionamento(Pilha *p, int ncarros){

    int i;
    Elemento *q = p->prim;

    for(i = ncarros; i > 0; i--){
        if(i <= p->num_carros){
            printf("|\t%-7s|", q->placa);
            q = q->prox;
        }else{
            printf("|\t%-7s|","\0");
        }
    }

}

void apresenta_rua(Pilha *r, int ncarros){

    int i;
    Elemento *t = r->prim;

    printf("\n\nRua");
    printf("\n\n");
    for(i = ncarros; i > 0; i--){
        if(i <= r->num_carros){
            printf("|\t%-7s|", t->placa);
            t = t->prox;
        }else{
            printf("|\t%-7s|","\0");
        }
    }

}

Elemento* pilha_pop(Pilha *p){

    Elemento *t, *q;

    t = p->prim;
    q = t;
    p->prim = t->prox;
    free(t);
    p->num_carros--;
    return q;
}

void retira_carro(Pilha **p, Pilha* r, char *placa, int npilhas, int ncarros, int ncarros_rua){

    Pilha **fileira = p;
    Pilha *rua = pilha_cria();
    rua = r;
    Elemento *t;
    int i, j;
    int carros_frente;
    int x = indica_fileira(fileira, npilhas, ncarros);
    int l = 0;
    Pilha *aux = pilha_cria();

    l = busca_placa(fileira, npilhas, placa);

    carros_frente = verifica_qnts_carros_na_frente(fileira[l], placa);

    if((verifica_est_cheio(fileira, npilhas, ncarros) == 1 || num_vagas(fileira, npilhas, ncarros) < carros_frente)){
        for(i = 0; i < carros_frente; i++){

            if(carros_frente > ncarros_rua){
                printf("\nNão é possível retirar esse carro agora\n");
                return;
            }else{
                system("pause");
                system("cls");
                printf("\n");
                printf("\nEstacionamento\n");
                for(j = 0; j < npilhas; j++){

                    apresenta_estacionamento(fileira[j], ncarros);
                    printf("\n");
                }

                apresenta_rua(rua, ncarros_rua);
                printf("\n");

                aux->prim = pilha_pop(fileira[l]);
                insere_carro(rua, aux->prim->placa, aux->prim->previsao_de_retirada);
                printf("\n");
                printf("Carro %s, foi para a rua...", rua->prim->placa);
                printf("\nEstacionamento\n");
                for(j = 0; j < npilhas; j++){
                    apresenta_estacionamento(fileira[j], ncarros);
                    printf("\n");
                }

                apresenta_rua(rua, ncarros_rua);
                printf("\n");

            }
        }

        t = fileira[l]->prim;
        fileira[l]->prim = t->prox;
        free(t);
        fileira[l]->num_carros--;

        for(i = 0; i < carros_frente; i++){

            if(carros_frente > ncarros_rua){
                printf("\nNão é possível retirar esse carro agora\n");
                return;
            }else{
                system("pause");
                system("cls");
                printf("\n");
                printf("\nEstacionamento\n");
                for(j = 0; j < npilhas; j++){

                    apresenta_estacionamento(fileira[j], ncarros);
                    printf("\n");
                }

                apresenta_rua(rua, ncarros_rua);
                printf("\n");

                insere_carro(fileira[l], rua->prim->placa, rua->prim->previsao_de_retirada);
                system("pause");
                printf("\n");
                printf("Carro %s, volta para a fileira %i", rua->prim->placa, l + 1);
                t = rua->prim;
                rua->prim = t->prox;
                free(t);
                rua->num_carros--;
                printf("\nEstacionamento\n");
                for(j = 0; j < npilhas; j++){
                    apresenta_estacionamento(fileira[j], ncarros);
                    printf("\n");
                }

                apresenta_rua(rua, ncarros_rua);
                printf("\n");
                system("pause");
            }
        }

        return;
    }



    for(i = 0; i < carros_frente; i++){

        system("pause");
        system("cls");
        printf("\n");
        printf("\nEstacionamento\n");
        for(j = 0; j < npilhas; j++){

            apresenta_estacionamento(fileira[j], ncarros);
            printf("\n");
        }

        apresenta_rua(rua, ncarros_rua);
        printf("\n");

        aux->prim = pilha_pop(fileira[l]);
        insere_carro(fileira[x], aux->prim->placa, aux->prim->previsao_de_retirada);
        printf("\n");
        printf("\nEstacionamento\n");
        for(j = 0; j < npilhas; j++){

            apresenta_estacionamento(fileira[j], ncarros);
            printf("\n");
        }

        apresenta_rua(rua, ncarros_rua);
        printf("\n");
        system("pause");
    }

    t = fileira[l]->prim;
    fileira[l]->prim = t->prox;
    free(t);
    fileira[l]->num_carros--;
}

int verifica_qnts_carros_na_frente(Pilha *p, char *placa){

    Elemento *q = p->prim;
    int i = 0;

    while(q != NULL){
        if(strcmp(q->placa, placa) != 0){
            q = q->prox;
            i++;
        }else
            break;
    }

    return i;
}



