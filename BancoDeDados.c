#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <string.h>

#include "TADBD.h"
#include "TADLISTA.h"
#include "Interpretador.h"

int larguraTabela(TpCampo *campo)
{
	int largura = 0;
	while(campo!=NULL)
	{
		largura+=strlen(campo->nome)+4;
		campo = campo->prox;
	}
	return largura-1;
}

void exibirLinha(TpTabela *tabela)
{
	int i;
	TpCampo *campo = tabela->pCampos;
	printf("\n+");
	while(campo!=NULL)
	{
		for(i=0; i<strlen(campo->nome);i++)
			printf("-");
		printf("---+");
		campo = campo->prox;
	}
}

void printarDado(TpDado *no, TpCampo *campo)
{
	if(no == NULL)
	{
		printf(" ");
	}
	else
	{
		switch(campo->tipo)
		{
			case 'I': printf("%d", no->valor.integer); break;
			case 'N': printf("%.2f", no->valor.numeric); break;
			case 'D': printf("%s", no->valor.date); break;
			case 'C': printf("%c", no->valor.character1); break;
			case 'T': printf("%s", no->valor.character20); break;
		}
	}
	
}

void imprimirTabelaGrade(TpTabela *tabela)
{
	TpDado *dado;
	TpCampo *campo, *campoAtual;
	printf("TABELA: %s", tabela->nome);
	exibirLinha(tabela);
	printf("\n|");
	campo = tabela->pCampos;
	while(campo!=NULL)
	{
		printf("%s   |", campo->nome);
		campo = campo->prox;
	}
	exibirLinha(tabela);
	dado = tabela->pCampos->pAtual;
	campoAtual = tabela->pCampos;
	while(dado!=NULL)
	{
		printarDado(dado, campoAtual);
	}
	
	printf("\n\n");
}

void imprimirBancoGrade(TpBanco *banco)
{
	TpTabela *tabela;

	if(banco == NULL)
		printf("Nenhum banco de dados criado.\n");
	else
	{
		printf("=== BANCO: %s ===\n", banco->nome);

		tabela = banco->pTabelas;
		if(tabela == NULL)
			printf("(nenhuma tabela criada)\n");
	
		while(tabela != NULL)
		{
			imprimirTabelaGrade(tabela);
			tabela = tabela->prox;
		}
	}
}

void processarScript(char scriptString[], char stringFormatada[], Token tokens[], int TL, DescritorLista descLista, TpBanco **banco)
{
	toStringFormatada(scriptString, stringFormatada);
	tokenizarComandos(stringFormatada, tokens, &TL);
	separarComandos(&descLista, tokens, TL);
	interpretarComandos(&*banco, &descLista);
}

int main()
{
	
	char nomeArq[30], scriptString [100000], stringFormatada[100000];
	Token tokens[1000]; 
	int TL;
	DescritorLista descLista;
	TpBanco *banco = NULL; 
	init(&descLista); 
	printf("### BANCO DE DADOS ###\n\n");
	printf("-----------------------\n");
	printf("[A] Importar um arquivo\n");
	printf("[B] Escrever script do inicio\n");
	if(toupper(getche()) == 'A')
	{
		printf("\nNome do arquivo sql: ");
//		//Verificar se arquivo SQL
		gets(nomeArq);
		FILE *ptr = fopen(nomeArq, "r");
		if(ptr != NULL)
		{
			toString(ptr, scriptString);
			fclose(ptr);
			processarScript(scriptString, stringFormatada, tokens, TL, descLista, &banco);
			imprimirBanco(banco);
			while(lerScriptUsuario(scriptString))
			{
				processarScript(scriptString, stringFormatada, tokens, TL, descLista, &banco);
				imprimirBanco(banco);
			}
			
			}
		else
			printf("Falha ao importar o arquivo!\n");
	}
	else
	{
		while(lerScriptUsuario(scriptString))
		{
			processarScript(scriptString, stringFormatada, tokens, TL, descLista, &banco);
			imprimirBanco(banco);
		}
	}
		

	
	// printf("%s", stringFormatada);
	// printf("\n\n");
	
	// printf("\n\n");
	// imprimirComandos(&descLista);
	
	// printf("\n\n");
	// imprimirBanco(banco);
	// imprimirBancoGrade(banco);
	
	
	return 0;
}
