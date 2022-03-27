// A loja “Casa Bela” de artigos de decoração vende muito em prestação. E para isso deseja armazenara uma lista com os clientes pendentes.
// Como número de clientes varia constantemente, a lista deve ser implementada como usando os conceitos de lista ligada.
// As informações a serem armazenadas na lista são:

//DADOS{
// Nome do Cliente – string de no máximo 50 caracteres
// Data da Compra – uma estrutura com dia, mês e ano inteiros
// Valor da Dívida - valor real
// Número de Prestações – número inteiro
// Número de prestações já pagas – numero inteiro
//}

//FUNCOES{
// O programa deverá ter uma tela com as seguintes opções:
//
// Inserção de Novo Cliente (Se o Time conseguir, seria interessante que fosse em ordem alfabética) = Feito
// Remoção de um Cliente = Feito
// Buscar um Cliente para atualizar o número de prestações pagas. Caso seja a última prestação do Cliente, deve ser impresso um aviso e o nome dele retirado da lista = Feito
// Busca de um cliente – Impressão das informações com o valor do Saldo devedor, considerando que sempre serão parcelas iguais e que se houve uma entrada não foi considerada no Valor da Dívida = NAO IMPLEMENTADO
// Impressão do nome de todos os Clientes da Lista com o número de prestações que faltam pagar e o saldo devedor = NAO IMPLEMENTADO
//}



//Definicao struct que armazena os dados dos clientes solicitados para o exercicio
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>


typedef struct data
{
    int dia;
    int mes;
    int ano;
}Data;
typedef struct dadosCliente
{
    char nomeCliente[50];
    float valorDivida;
    Data dataCompra;
    int numPrestacoes;
    int numPrestacoesPagas;
}DadosCliente;
//Definicao struct que armazena os dados do cliente junto com o encadeamento para o proximo no
typedef struct noDadosCliente
{
    DadosCliente dados;
    struct noDadosClientes* proximo;
}NoDadosCliente;

//Definicao struct que armazena o tamanho da lista formada por nos e tambem o primeiro no da lista
typedef struct lista
{
    int tam;
    NoDadosCliente* primeiroNoLista;
}Lista;


//FUNCOES//
// struct lista criarLista();
// void insereCliente(struct lista* lista);
// void solicitaDadosCliente(NoDadosCliente* no);
// void imprime (Lista* recebida);


//Aloca e retorna ponteiro para lista
Lista* criarLista(){
    Lista* lista = (Lista*)malloc(sizeof(Lista));

    lista->tam = NULL;
    lista->primeiroNoLista = NULL;

    return lista;
}

//Insere um novo no
void insereCliente(Lista *lista){
    NoDadosCliente* no = (NoDadosCliente*)malloc(sizeof(NoDadosCliente));

    solicitaDadosCliente(&no->dados);

    //Garante que o no inserido
    no->proximo = lista->primeiroNoLista;
    lista->primeiroNoLista = no;
    lista->tam ++;
}

//Solicita e armazena os dados necessarios para satisfazer o no tipo DadosClientes
void solicitaDadosCliente(DadosCliente *dados){
    //FAZER VERIFICACAO DE DADOS
    fflush(stdin);
    printf("\nDigite o nome do cliente: ");
    fgets(dados->nomeCliente,50,stdin);
    fflush(stdout);

    ////data
    printf("\nDigite o dia da compra: ");
    scanf("%d",&dados->dataCompra.dia);

    printf("\nDigite o mes da compra: ");
    scanf("%d",&dados->dataCompra.mes);
    fflush(stdin);

    printf("\nDigite o ano da compra: ");
    scanf("%d",&dados->dataCompra.ano);
    fflush(stdin);

    printf("\nDigite o numero de prestacoes: ");
    scanf("%d",&dados->numPrestacoes);
    fflush(stdin);

    printf("\nDigite o numero de prestacoes pagas: ");
    scanf("%d",&dados->numPrestacoesPagas);
    fflush(stdin);

    printf("\nDigite o valor da divida: ");
    scanf("%f",&dados->valorDivida);
    fflush(stdin);

    printf("\n||||||||||||||||||||||||||||||||||||||||||||||||\n");

    //printf("\n\n\tNOME: %s\n\n\tDATA: %d\n\n\tVALOR: %f",dados->nomeCliente, dados->dataCompra.dia, dados->valorDivida);
    printf("\nData: %i/%i/%i \n",dados->dataCompra.dia,dados->dataCompra.mes,dados->dataCompra.ano);
    printf("\nNome: %s\nValor da divida: %.2f\n",dados->nomeCliente,dados->valorDivida);

    printf("\n||||||||||||||||||||||||||||||||||||||||||||||||\n");



}

//Imprime os dados e o tamanho da lista
void imprime (Lista *lista){

    if(Vazia(lista)){
        return printf("Lista vazia");
    }

    NoDadosCliente *aux = lista->primeiroNoLista; /* variável auxiliar para percorrer a lista */

    while(aux != NULL){
        printf("\n||||||||||||||||||||||||||||||||||||||||||||||||\n");
        printf("\n\tCliente = %s", aux->dados.nomeCliente);
        printf("\n\tValor: R$ %.2f", aux->dados.valorDivida);
        printf("\n\t Numero de prestacoes pagas = %d\n\n", aux->dados.numPrestacoesPagas);
        float parcela = (aux->dados.valorDivida / aux->dados.numPrestacoes);
        printf("\n\tSaldo devedor = R$ %.2f", (parcela*(aux->dados.numPrestacoes - aux->dados.numPrestacoesPagas)));


        aux = aux->proximo;
    }
    printf("\nTamanho: %d", lista->tam);
}

//Retorna 1, caso lista vazia
int Vazia(Lista *lista){
    return (lista->primeiroNoLista == NULL || lista->primeiroNoLista == 0 || lista->tam == 0);
}

//Retorna indice de um no, dado o nome para busca
int indiceNo (Lista *lista){
    char nomeSolicitado[50];

    //Solicita nome para busca
    fflush(stdin);
    printf("\nDigite o nome do cliente: ");
    fgets(nomeSolicitado,50,stdin);
    fflush(stdout);

    NoDadosCliente* aux = lista->primeiroNoLista;

    if(aux != NULL){

        //VERIFICAR SE EH NECESSARIO INICIAR COMO 1 OU 0//
        int index = 0;

        while(strcmp(aux->dados.nomeCliente, nomeSolicitado) != 0 && aux){
            aux = aux->proximo;
            index++;
        }
        if (aux != NULL){
            return index;
        }

        printf("\nCliente nao pertencente a lista\n");
        return -1;
    }

    return printf("\n\n\tLista vazia");

}

//Retorna o no da posicao informada
NoDadosCliente* noNaPosicao(Lista *lista, int index){
    if(index >= 0 && index < lista->tam){
        index;
        NoDadosCliente *aux = lista->primeiroNoLista;
        for(int i = 0; i < index; i++){
            aux  = aux->proximo;
        }
        return aux;
    }
    return NULL;
}

//Retorna no via index
NoDadosCliente* buscarNome(Lista *lista){
    int index = indiceNo(lista);
    NoDadosCliente *aux;
    aux = noNaPosicao(lista, index);

    return aux;
}

//Atualizada o numero de prestacoes pagas
void attNumPrestacoesPagas(Lista *lista, NoDadosCliente *noSolicitado){

    if(Vazia(lista)){
        return printf("Lista vazia");
    }

    NoDadosCliente *aux = noSolicitado;
    

    if(aux){
        printf("\nNumero de prestacoes atual: %d", aux->dados.numPrestacoesPagas);

        int att;
        printf("\nDigite o numero atualizado de prestacoes pagas: ");
        scanf("%d", &att);
        aux->dados.numPrestacoesPagas = att;
        fflush(stdin);
        if(aux->dados.numPrestacoesPagas == aux->dados.numPrestacoes){
            printf("\n\n\tAtualizacao: Todas as parcelas pagas!");
            printf("\n\n\tRemovendo cliente da lista...");
            removeCliente(lista, aux);
        }
    }


}

//Remove um cliente de acordo com o indice
void removeCliente(Lista *lista, NoDadosCliente *noSolicitado){

    printf("\n\n\tTamanho lista atual: %d", lista->tam);

    NoDadosCliente *aux = lista->primeiroNoLista;

    //Caso tenha apenas um elemento na lista
    if(lista->tam == 1){
        free(aux);
        lista->primeiroNoLista = NULL;
        lista->tam --;
        printf("\nAtualizacao pos remocao Tamanho: %d", lista->tam);
    }

    //Caso o elemento buscado seja o no cabeca
    if(aux && aux == noSolicitado){
        lista->primeiroNoLista = aux->proximo;
        free(noSolicitado);
        lista->tam --;
        printf("\nAtualizacao pos remocao Tamanho: %d", lista->tam);
    }

    //Caso nao seja o no cabeca
    while(aux && aux->proximo != noSolicitado){
        aux = aux->proximo;
    }
    if(aux){
        aux->proximo = noSolicitado->proximo;
        free(noSolicitado);
        lista->tam --;
        printf("\nAtualizacao pos remocao Tamanho: %d", lista->tam);
    }

}

//Imprime valor do Saldo devedor de um no
void imprimeSaldoDevedor(Lista *lista, NoDadosCliente *noSolicitado){

    printf("\n||||||||||||||||||||||||||||||||||||||||||||||||\n");
    float parcela = (noSolicitado->dados.valorDivida / noSolicitado->dados.numPrestacoes);
    printf("\n\tSaldo devedor = R$ %.2f", (parcela*(noSolicitado->dados.numPrestacoes - noSolicitado->dados.numPrestacoesPagas)));


}

int main(){

    setlocale(LC_ALL, "Portuguese");
    int finalizar = 0;
    int opcao;
    Lista* listaClientes = criarLista();
    NoDadosCliente *noSolicitado, *noRetorno;
    int index;
    char nomeSolicitado[50];


   do{
       printf("\n\n1 - Inserir cliente\n2 - imprimir\n3 - Buscar cliente pelo nome\n4 - Remover cliente via nome informado\n5 - Atualizar numero de prestacoes\n6 - Imprime saldo devedor do cliente\n8 - Sair\n\nOpcao: ");
       scanf("%d", &opcao);
       switch(opcao){
           case 1:
                printf("\nTamanho: %d", listaClientes->tam);
                insereCliente(listaClientes);
                printf("\nATT Tamanho: %d", listaClientes->tam);
				break;
           case 2:
				imprime(listaClientes);
				break;
           case 3:
                noSolicitado = buscarNome(listaClientes);
                printf("\n\tNome retornado: %s", noSolicitado->dados.nomeCliente);
				break;
            case 4:
                noSolicitado = buscarNome(listaClientes);
				removeCliente(listaClientes, noSolicitado);
				break;
            case 5:
                noSolicitado = buscarNome(listaClientes);
                attNumPrestacoesPagas(listaClientes, noSolicitado);
				break;
            case 6:
                noSolicitado = buscarNome(listaClientes);
                imprimeSaldoDevedor(listaClientes, noSolicitado);
				break;
           case 8:
               	printf("\nFinalizando...\n");
               	finalizar = 1;
               	break;
           default:
               	printf("Opcao invalida!\n");
       }
   } while (!finalizar);
}