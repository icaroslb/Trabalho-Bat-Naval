#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

//função que inicializa um nó do mapa
void iniciNo(mapa **no, unsigned short int x, unsigned short int y){
	*no=(mapa*)malloc(sizeof(mapa));
	(*no)->x=x;
	(*no)->y=y;
	(*no)->valorH=' ';
	(*no)->valorC=' ';
	(*no)->baixo=NULL;
	(*no)->esq=NULL;
	(*no)->dir=NULL;
	(*no)->barcoH=NULL;
	(*no)->barcoC=NULL;
}

//função que iniciliza o mapa
void inicializar_mapa(mapa **m, sub *submarinos){
	mapa *ini, *novo, *aux, *cima=NULL;
	unsigned short int x, y;
	
	for(x=0; x<TAMMAPAX; x++){
		y=0;
		iniciNo(&ini, x, y);
		if(x==0){*m=ini;}
		if(cima!=NULL){
			ini->cima=cima;
			cima->baixo=ini;
			cima=cima->dir;
		}
		novo=ini;
		for(y=1; y<TAMMAPAY; y++){
			aux=novo;
			iniciNo(&novo, x, y);
			aux->dir=novo;
			novo->esq=aux;
			if(cima!=NULL){
				novo->cima=cima;
				cima->baixo=novo;
				cima=cima->dir;
			}
		}
		novo->dir=ini;
		ini->esq=novo;
		cima=ini;
	}
	barco_mapa(*m, submarinos);
}

/*função que passa uma posição como parâmetro
e retorna o endereço da posição*/
mapa* caminhar(mapa *m, unsigned short int x, unsigned short int y){
	//caminha para a linha requerida
	if((m->x)<x){
		while((m->x)<x){
			m=m->baixo;
		}
	}else{
		while((m->x)>x){
			m=m->cima;
		}
	}
	//caminha para a coluna requerida
	if((m->y)<y){
		while((m->y)<y){
			m=m->dir;
		}
	}else{
		while((m->y)>y){
			m=m->esq;
		}
	}
	return m;
}

//Imprime na tela os mapas
void mostrar_mapa(mapa *m, mapa **mcomp){
	unsigned short int x, y;
	mapa *humano=m, *computador=m;
	if(m!=NULL){
		printf("      Humano\t\t\t    Computador\n");
		printf("   ABCDEFGHIJKL\t\t\t   ABCDEFGHIJKL\n");
		printf("  +------------+\t\t  +------------+\n");
		
		for(x=0; x<TAMMAPAX; x++){
			printf("%2d|", x);
			for(y=0; y<TAMMAPAY; y++){
				if((*mcomp)->valorH=='*' && ((*mcomp)->barcoH)->dano==1){
					if(humano->barcoH!=NULL && humano->valorH=='*' && (humano->barcoH)->dano==0){
						*mcomp=humano;
					}
				}
				printf("%c", humano->valorH);
				humano=humano->dir;
			}
			humano=humano->baixo;
			printf("|\t\t");
			printf("%2d|", x);
			for(y=0; y<TAMMAPAY; y++){
				printf("%c", computador->valorC);
				computador=computador->dir;
			}
			computador=computador->baixo;
			printf("|\n");
		}
		printf("  +------------+\t\t  +------------+\n");
	}
}

//Reinicia os valores do mapa
void reiniciar_mapa(mapa *m){
	mapa *aux=m;
	while(aux!=NULL){
		aux->valorH=' ';
		aux->valorC=' ';
		free(aux->barcoH);
		free(aux->barcoC);
		aux->barcoH=NULL;
		aux->barcoC=NULL;
		if(aux->dir!=m){
			aux=aux->dir;
		}else{
			m=m->baixo;
			aux=m;
		}
	}
}

//Libera o espaço do mapa
void limpar_mapa(mapa **m){
	mapa *aux, *mapa=*m;
	
	do{
		aux=mapa;
		(mapa->esq)->dir=NULL;
		if(mapa->dir!=NULL){
			mapa=mapa->dir;
		}else{
			mapa=mapa->baixo;
		}
		free(aux);
	}while(mapa!=NULL);
	*m=NULL;
}
