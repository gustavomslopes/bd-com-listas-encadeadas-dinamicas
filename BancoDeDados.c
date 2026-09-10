#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio2.h>
#include <string.h>

#include "TADBD.h"
#include "TADLISTA.h"
#include "Interpretador.h"

int main()
{
	char nomeArq[30], scriptString [100000], stringFormatada[100000];
	Token tokens[1000]; 
	int TL;
	DescritorLista descLista;
	init(&descLista); 

	printf("### BANCO DE DADOS ###\n\n");
	printf("Deseja importar um arquivo [S/N]? ");
	if(toupper(getche()) == 'S')
	{
		printf("\nNome do arquivo sql: ");
//		//Verificar se arquivo SQL
		gets(nomeArq);
		FILE *ptr = fopen(nomeArq, "r");
		if(ptr != NULL)
		{
			toString(ptr, scriptString);
			fclose(ptr);
		}
		else
			printf("Falha ao importar o arquivo!\n");
	}
	else
		lerScriptUsuario(scriptString);

	toStringFormatada(scriptString, stringFormatada);
	printf("%s", stringFormatada);
	printf("\n\n");
	tokenizarComandos(stringFormatada, tokens, &TL);
	separarComandos(&descLista, tokens, TL);
		
	
	
	return 0;
}
