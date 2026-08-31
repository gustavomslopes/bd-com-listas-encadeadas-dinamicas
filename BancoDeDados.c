#include <stdio.h>
#include <ctype.h>
#include <windows.h>
#include <conio2.h>
#include <string.h>

#include "TADBD.h"
#include "InterpretadorSQL.h"


int main()
{
	FILE *arqSQL;
	TpBanco pontBD;
	
 	printf("Deseja importar o scriptDB.sql [S/N]?\n");
	if(toupper(getche()) == 'S')
	{
		arqSQL = fopen("scriptBD.sql", "r");
		if(arqSQL != NULL)
		{
			interpretarSQL(arqSQL, &pontBD);
		}
		else
		{
			printf("Falha ao abrir o arquivo!");
			Sleep(1000);
		}
	}
	else
	{
		printf("Saindo...");
		Sleep(1000);
	}
	return 0;
}
