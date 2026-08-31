#define QTD_COMANDOS 6

char verifComando(char palavra[], char comandos[][16])
{
	int i;
	for(i=0; i<QTD_COMANDOS; i++)
	{
		if(stricmp(palavra, comandos[i]) == 0)
			return comandos[i][0];
	}
	return 0;
}

void lerPalavra(FILE *arq, char palavra[], char *caractere, char parada)
{
	int j=0;
	palavra[0]='\0';
	while((*caractere)==' ')
		*caractere = fgetc(arq);
	
	while((*caractere)!=parada && (*caractere)!='\n')
	{
		palavra[j] = *caractere;
		*caractere = fgetc(arq);
		j++;	
	}
	palavra[j] = '\0';
}

char temComandoLinha(FILE *arq, char *caractere)
{
	char comandos[QTD_COMANDOS][16] = 
	{
		"CREATE",
		"ALTER",
		"INSERT",
		"UPDATE",
		"DELETE",
		"SELECT",	
	};
	char palavra[20];
	char comando;
	*caractere = fgetc(arq);
	while(*caractere!='\n')
	{
		lerPalavra(arq, palavra, &(*caractere), ' ');
		comando = verifComando(palavra, comandos);

		if(comando)
		{
			if(comando == 'C')
			{
				lerPalavra(arq, palavra, &(*caractere), ' ');
				printf("[%s] tamanho=%d\n", palavra, (int)strlen(palavra));
				if(stricmp(palavra, "table")==0)
					return 'T';
				else if(stricmp(palavra, "database")==0)
					return 'C';
			}
			return comando;
		}
	}
	return 0;
}

void interpretarSQL(FILE *arq, TpBanco **pontBD)
{
	char comando, caractere, palavra[20], proximo;
	while(!feof(arq))
	{
		comando = temComandoLinha(arq, &caractere);
		if(comando)
		{
			if(comando == 'C')
			{
				lerPalavra(arq, palavra, &caractere, ';');
				criarBanco(&(*pontBD), palavra);
				printf("%s", (*pontBD)->nome);
			} 
			else if (comando == 'T') printf("T\n");
			else if (comando == 'A')printf("A\n");
			else if (comando == 'I')printf("I\n");
			else if (comando == 'U')printf("U\n");
			else if (comando == 'D')printf("D\n");
			else printf("S\n");
			
			
			
		}
		if(caractere == '\n')
		{
			proximo = fgetc(arq);
		    if(proximo != '\n')
		        ungetc(proximo, arq);
		}
			
	}
}
