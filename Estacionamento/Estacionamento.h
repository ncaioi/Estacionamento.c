#ifndef ESTACIONAMENTO_H_INCLUDED
#define ESTACIONAMENTO_H_INCLUDED

typedef struct elemento{
    float previsao_de_retirada;
    char *placa;
    struct elemento *prox;
}Elemento;

typedef struct pilha{

    int num_carros;
    Elemento *prim;
}Pilha;

Pilha* pilha_cria(void);    /// cria uma pilha vazia.
Pilha** cria_estacionamento(int npilhas, int ncarros); /// cria um estacionamento vazio, criando n ponteiros para pilhas
                                                      ///de carros
int qtd_carros(Pilha* p);   /// retorna a quantidade de carros em uma fileira(pilha)
int busca_placa(Pilha** p, int npilhas, char *placa);   /// busca um carro no estacionamento, retorna em qual fileira ele está
int indica_fileira(Pilha** p, int npilhas, int ncarros);    /// indica a fileira com menos carros, a mais vazia.
void insere_carro(Pilha *p, char *placa, float tempo);   /// insere um carro em uma fileira(pilha)
void retira_carro(Pilha **p, Pilha *r, char *placa, int npilhas, int ncarros, int ncarros_rua); /// retira o carro de uma fileira
                                                                                 /// manobrando ele para fileira mais vazia
                                                                                /// caso estacionamento cheio, manobra para rua
                                                                               /// e depois retorna a fileira original.
void apresenta_estacionamento(Pilha *p, int ncarros);          /// imprime estacionamento na tela
void apresenta_rua(Pilha *r, int ncarros);                    /// imprime rua na tela;
int verifica_qnts_carros_na_frente(Pilha *p, char *placa);   /// verifica quantos carros estão na frente do carro a ser retirado.
int num_vagas(Pilha** fileira, int npilhas, int ncarros);   /// verifica quantas vagas vazias tem no estacionamento.
int verifica_est_cheio(Pilha** p, int npilhas, int ncarros);     /// verifica se estacionamento está cheio. 1 = cheio.
int verifica_est_vazio(Pilha** p, int npilhas);                 /// verifica se estacionamento está vazio. 1 = vazio.
Elemento* pilha_pop(Pilha* p);                                 /// retira elemento da pilha.
#endif // ESTACIONAMENTO_H_INCLUDED
