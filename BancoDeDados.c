#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio2.h>
#include <string.h>

#include "TADBD.h"
#include "TADLISTA.h"
#include "Interpretador.h"

#define LARGURA_SETOR 14

 int larguraTabela(int qtd)
 {
 	return qtd*14;
 }

 int qtdCampos(TpTabela *tabela)
 {
 	int cont=0;
 	TpCampo *aux;
 	aux = tabela->pCampos;
 	while(aux!=NULL)
 	{
 		cont++;
 		aux=aux->prox;
 	}
 	return cont;
 }

 int qtdDados(TpDado *dado)
 {
 	int cont=0;
 	while(dado!=NULL)
 	{
 		cont++;
 		dado = dado->prox;
 	}
 	return cont;
 }

 void exibirLinha(int largura, int sep)
 {
 	int aux = sep;
 	printf("+");
 	while(largura>0)
 	{
 		if(aux==0)
 		{
 			printf("+");
 			aux = sep;
 		}
 		else
 		{
 			printf("-");
 			largura--;
 			aux--;
 		}
 	}
 	printf("+");
 }

 int printarDado(TpDado *no, TpCampo *campo)
 {
 	int tam, numI;
 	float numF;
 	if(no == NULL)
 	{
 		printf("NULL");
 		tam = 4;
 	}
 	else
 	{
 		switch(campo->tipo)
 		{
 			case 'I': 
 				numI = no->valor.integer;
 				printf("%d", numI); 
 				if(numI<10)
 					tam=1;
 				else if(numI<100)
 					tam = 2;
 				else
 					tam=3;
 				break;
 			case 'N': 
 				numF = no->valor.numeric;
 				printf("%.2f", numF); 
 				if(numF<10)
 					tam = 3;
 				else if(numF<100)
 					tam = 4;
 				else 
 					tam = 5;
 				break;
 			case 'D': 
 				printf("%s", no->valor.date); 
 				tam = strlen(no->valor.date);
 				break;
 			case 'C': 
 				printf("%c", no->valor.character1);
 				tam = 1;
 				break;
 			case 'T':
 				printf("%s", no->valor.character20); 
 				tam = strlen(no->valor.character20);
 				break;
 		}
 	}
 	return tam;
 }

 void imprimirTabelaGrade(TpTabela *tabela, int *l, int c)
 {
 	int largura, qtdC, qtdD, aux, cInicial, lAux, cAux, i;
 	cInicial = c;
 	TpDado *dadoAtual;
 	TpCampo *campo, *campoAtual;
 	gotoxy(c, ++(*l));
 	printf("TABELA: %s", tabela->nome);
 	qtdC = qtdCampos(tabela);
 	qtdD = qtdDados(tabela->pCampos->pDados);
 	largura = larguraTabela(qtdC);
 	gotoxy(c, ++(*l));
 	exibirLinha(largura, LARGURA_SETOR);
 	gotoxy(c, ++(*l));
 	printf("|");
 	campo = tabela->pCampos;
 	while(campo!=NULL)
 	{
 		if(campo->PK == 'S' && campo->FK != NULL)
 			printf("%s* **", campo->nome);
 		else if (campo->FK != NULL)
 			printf("%s**", campo->nome);
 		else if (campo->PK == 'S')
 			printf("%s*", campo->nome);
 		else 
 			printf("%s", campo->nome);
 		c = c + LARGURA_SETOR+1;
 		gotoxy(c, *l);
			
 		printf("|");
 		campo = campo->prox;
 	}
 	c = cInicial;
 	gotoxy(c, ++(*l));
 	exibirLinha(largura, LARGURA_SETOR);
 	campoAtual = tabela->pCampos;
 	lAux = ++(*l);
 	while(campoAtual!=NULL)
 	{	
 		dadoAtual = campoAtual->pDados;
 		cAux = c;
 		while(dadoAtual!=NULL)
 		{
 			gotoxy(cAux, *l);
 			printf("|");
 			printarDado(dadoAtual, campoAtual);
 			c = cAux + LARGURA_SETOR+1;
 			gotoxy(c, *l);
 			printf("|");
 			c = cAux;
 			gotoxy(c, ++(*l));
 			printf("+");
 			for(i=0;i<LARGURA_SETOR;i++)
 			{
 				gotoxy(++c, *l);
 				printf("-");
 			}
 			gotoxy(++c, *l);
 			printf("+");
 			dadoAtual = dadoAtual->prox;
 			(*l)++;	
 		}
 		*l = lAux;
 		campoAtual= campoAtual->prox;
 	}
 	*l += qtdD+2;
}

 void imprimirBancoGrade(TpBanco *banco)
 {
 	TpTabela *tabela;
 	int l=1, lAux, c=30;
 	system("cls");
 	if(banco == NULL)
 		printf("Nenhum banco de dados criado.\n");
 	else
 	{
 		gotoxy(c, l);
 		printf("=== BANCO: %s ===", banco->nome);
 		l++;
 		tabela = banco->pTabelas;
 		if(tabela == NULL)
 			printf("(nenhuma tabela criada)");
 		else
 		{
 			c=1;
 			while(tabela != NULL)
 			{
 				imprimirTabelaGrade(tabela, &l, c);
 				tabela = tabela->prox;
 			}
 		}	
 	}
 }

void processarScript(char scriptString[], char stringFormatada[], Token tokens[], int TL, DescritorLista descLista, TpBanco **banco, char logErro[])
{
	logErro[0] = '\0';
	toStringFormatada(scriptString, stringFormatada);
	tokenizarComandos(stringFormatada, tokens, &TL);
	separarComandos(&descLista, tokens, TL);
	interpretarComandos(&*banco, &descLista, logErro);
}

int main()
{
	char nomeArq[30], scriptString [100000], stringFormatada[100000], logErro[100]="";
	Token tokens[1000]; 
	int TL;
	DescritorLista descLista;
	TpBanco *banco = NULL; 
	init(&descLista); 
	printf("### BANCO DE DADOS ###\n");
	printf("-----------------------\n");
	printf("[A] Importar um arquivo\n");
	printf("[B] Escrever script do inicio\n");
	if(toupper(getche()) == 'A')
	{
		printf("\nNome do arquivo sql: ");
		gets(nomeArq);
		FILE *ptr = fopen(nomeArq, "r");
		if(ptr != NULL)
		{
			toString(ptr, scriptString);
			fclose(ptr);
			processarScript(scriptString, stringFormatada, tokens, TL, descLista, &banco, logErro);
			imprimirBancoGrade(banco);
			printf("\n");
			while(lerScriptUsuario(scriptString))
			{
				processarScript(scriptString, stringFormatada, tokens, TL, descLista, &banco, logErro);
				imprimirBancoGrade(banco);
				printf("\n");
				if(logErro[0]!='\0')
					printf("ERRO: %s\n\n", logErro);
				
			}
			
		}
		else
			printf("Falha ao importar o arquivo!\n");
	}
	else
	{
		while(lerScriptUsuario(scriptString))
		{
			processarScript(scriptString, stringFormatada, tokens, TL, descLista, &banco, logErro);
			imprimirBancoGrade(banco);
		}
	}
		

	
	// printf("%s", stringFormatada);
	// printf("\n\n");
	
	// printf("\n\n");
	// imprimirComandos(&descLista);
	
	// printf("\n\n");
	// imprimirBanco(banco);
	
	
	
	return 0;
}
