#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

#define TAM_EVENTO 50

typedef enum {false, true} bool; //Apenas para ANSI C

typedef struct no {
    char evento[TAM_EVENTO];
    int data;
    struct no *prox;
} noEvento;


noEvento *prim = NULL;
noEvento *ult = NULL;

bool insereEvento(char evento[], int data){
  //alocando memória para um novo evento
  noEvento *novoEvento = (noEvento *) malloc(sizeof(noEvento));
  noEvento *ant = NULL;
  noEvento *atual = prim;

  //encontra a posição de inserção do novoEvento
  while((atual != NULL) && (atual->data < data)){
    ant = atual;
    atual = atual->prox;
  }//fim while

  //conferindo se é a primeira posição
  if(ant == NULL){
    prim = novoEvento;
  }
  else{
    ant->prox = novoEvento;
  }//fim if

  //atualizando valores para o novo nó
  strcpy(novoEvento->evento, evento);
  novoEvento->data = data;
  return true;

}
void imprimeAgenda(){
  noEvento* atual = prim;
  int ano = atual->data/366+2019;
  int mes = (atual->data%366)/31;
  int dia = ((atual->data%366)%31);

  while(atual != NULL){
    printf("\nNome do evento: %s\n", atual->evento);
    printf("Data: %d/%d/%d\n", dia, mes, ano);
    atual = atual->prox;
  }
}

bool removeEvento(int data){
  noEvento *atual, *ant;
  atual = prim;
  ant = prim;

  while((atual != NULL)&&(atual->data != data)){
    ant = atual;
    atual = atual->prox;
  }

  if(atual != NULL){
    if(atual == prim){
      prim = prim->prox;
    }else{
      ant->prox = atual->prox;
    }
    free(atual);
    return true;
  }else{
    return false;
  }
}

void inicializaEventos(){
	char data[][12] ={
		"28/09/2019",
		"29/09/2019",
		"30/09/2019",
		"01/10/2019",
		"02/10/2019",
		"03/10/2019",
		"04/10/2019",
		"05/10/2019",
		"06/10/2019",
		"07/10/2019",
		"08/10/2019",
		"09/10/2019",
		"10/10/2019",
		"11/10/2019",
		"12/10/2019",
		"13/10/2019",
		"14/10/2019",
		"15/10/2019",
		"16/10/2019",
		"17/10/2019"};

	char evento[][TAM_EVENTO]={
		"UFC Fight Night: Usman vs. Ponzinibbio",
		"UFC 224: Nunes vs. Pennington",
		"UFC Fight Night: Barboza vs. Lee",
		"UFC on Fox: Poirier vs. Gaethje",
		"UFC 223: Khabib vs. Iaquinta",
		"UFC Fight Night: Werdum vs. Volkov",
		"UFC 222: Cyborg vs. Kunitskaya",
		"UFC on Fox: Emmett vs. Stephens",
		"UFC Fight Night: Cowboy vs. Medeiros",
		"UFC 221: Romero vs. Rockhold",
		"UFC Fight Night: Machida vs. Anders",
		"UFC on Fox: Jacaré vs. Brunson 2",
		"UFC 220: Miocic vs. Ngannou",
		"UFC Fight Night: Stephens vs. Choi",
		"UFC 219: Cyborg vs. Holm",
		"UFC on Fox: Lawler vs. dos Anjos",
		"UFC Fight Night: Swanson vs. Ortega",
		"UFC 218: Holloway vs. Aldo 2",
		"The Ultimate Fighter: A New World Champion Finale",
		"UFC Fight Night: Bisping vs. Gastelum"};
	int i;
	for (i=0;i<20;i++){
		//dd/mm/yyyy
		int dataN,dia,mes,ano;
		ano = (data[i][8]-48)*10+data[i][9]-48-19;
		mes = (data[i][3]-48)*10+data[i][4]-48;
		dia = (data[i][0]-48)*10+data[i][1]-48;
		dataN = ano*366+mes*31+dia;
		insereEvento(evento[i],dataN);
	}
}


int main() {
    inicializaEventos();
    int opcao = 1;
    while(opcao != 3) {
        printf("***LISTA DINAMICA CIRCULAR***\n");
        printf("\n Digite uma das opcoes abaixo: \n");
        printf(">> 1 imprime eventos em data crescente\n");
        printf(">> 2 para remover um evento\n");
        printf(">> 3 para sair da agenda\n");
        printf(">> ");
        scanf("%d", &opcao);
        getchar();
        switch(opcao) {
        case 1:
            printf(">> Agenda crescente: \n");
            imprimeAgenda();
            getchar();
            break;
        case 2:
            printf(">> Remocao de um evento: \n");
            printf(">>> Data: dd/mm/aaaa\n");
		 int data, dia, mes, ano;
            scanf("%d/%d/%d", &dia, &mes, &ano);
		 data = (ano-2019)*366+mes*31+dia;
 fflush(stdin);
            if (removeEvento(data))
			printf("Data removida!\n");
		 else
			printf("Data nao encontrada!\n");
            getchar();
            break;
        case 3:
            printf(">> Saindo da agenda...\n");
            return 0;
            getchar();
            break;
        default:
            printf(">> Opção inválida: %c\n", opcao);
            break;
        }
        system("cls");
    }
    return 0;
}
