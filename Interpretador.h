#define TOK_COMANDO 0
#define TOK_PALAVRA_CHAVE 1
#define TOK_TIPO_DADO 2
#define TOK_OPERADOR_LOGICO 3
#define TOK_PONTUACAO 4
#define TOK_OPERADOR_RELACIONAL 5
#define TOK_IDENTIFICADOR 6
#define TOK_NUMERO 7
#define TOK_STRING 8

#define TOTAL_TOK 37

void toString(FILE *arq, char stringFormatada[])
{
	char caractere = fgetc(arq);
	int TL = 0;
	while(!feof(arq))
	{
		stringFormatada[TL++] = caractere;
		caractere = fgetc(arq);
	}
	stringFormatada[TL] = '\0';
}

void toStringFormatada(char scriptString[], char stringFormatada[])
{
	char caractere;
	int TL=0, i=0;
	caractere = scriptString[i++];
	while(caractere!= '\0')
	{
		if(caractere == '\n' || caractere == ' ')
		{
			stringFormatada[TL++] = ' ';

			while(caractere == ' ' || caractere == '\n')
					caractere = scriptString[i++];
			if(caractere != '\0')
					stringFormatada[TL++] = caractere;
			
		}
		else if(caractere == '(' || caractere == ')' || caractere == ',' || caractere == ';')
		{
			if(TL> 0 && stringFormatada[TL-1] != ' ')
				stringFormatada[TL++] = ' ';	
				
			stringFormatada[TL++] = caractere;
		}
		else
		{
			if (TL > 0 && (stringFormatada[TL-1] == '(' || stringFormatada[TL-1] == ')' || stringFormatada[TL-1] == ',' || stringFormatada[TL-1] == ';'))
				stringFormatada[TL++] = ' ';	
			stringFormatada[TL++] = caractere;
		}	
		if(caractere!='\0')
			caractere = scriptString[i++];
	}
	stringFormatada[TL] = '\0';
}

int tokenizarPalavra(Token tabelaTokens[], char palavra[])
{
	int i;
	for(i=0; i<TOTAL_TOK; i++)
	{
		if(!stricmp(palavra, tabelaTokens[i].palavra))
			return tabelaTokens[i].tipo;
	}
	return TOK_STRING;
}

char isNumber(char palavra[])
{
	int i=0;
	if(palavra[0] == '\0')
		return 0;
	while(palavra[i]!='\0')
	{
		if(!isdigit(palavra[i]))
			return 0;
		i++;
	}

	return 1;
}

void tokenizarComandos(char stringFormatada[], Token tokens[], int *TLToken)
{
	Token tabelaTokens[] =
	{
		{"CREATE", TOK_COMANDO},
		{"ALTER", TOK_COMANDO},
		{"DROP", TOK_COMANDO},
		{"TABLE", TOK_COMANDO},
		{"DATABASE", TOK_COMANDO},
	
		{"INSERT", TOK_COMANDO},
		{"UPDATE", TOK_COMANDO},
		{"DELETE", TOK_COMANDO},
		{"SELECT", TOK_COMANDO},
	
		{"INTO", TOK_PALAVRA_CHAVE},
		{"VALUES", TOK_PALAVRA_CHAVE},
		{"SET", TOK_PALAVRA_CHAVE},
		{"FROM", TOK_PALAVRA_CHAVE},
		{"WHERE", TOK_PALAVRA_CHAVE},
		{"ORDER", TOK_PALAVRA_CHAVE},
		{"BY", TOK_PALAVRA_CHAVE},
		{"GROUP", TOK_PALAVRA_CHAVE},
		{"HAVING", TOK_PALAVRA_CHAVE},
		{"DISTINCT", TOK_PALAVRA_CHAVE},
		{"AS", TOK_PALAVRA_CHAVE},
		{"LIMIT", TOK_PALAVRA_CHAVE},
	
		{"ADD", TOK_PALAVRA_CHAVE},
		{"COLUMN", TOK_PALAVRA_CHAVE},
		{"RENAME", TOK_PALAVRA_CHAVE},
		{"MODIFY", TOK_PALAVRA_CHAVE},
	
		{"INT", TOK_TIPO_DADO},
		{"INTEGER", TOK_TIPO_DADO},
		{"CHAR", TOK_TIPO_DADO},
		{"CHARACTER", TOK_TIPO_DADO},
		{"VARCHAR", TOK_TIPO_DADO},
		{"FLOAT", TOK_TIPO_DADO},
		{"DOUBLE", TOK_TIPO_DADO},
		{"DATE", TOK_TIPO_DADO},
		{"BOOLEAN", TOK_TIPO_DADO},
	
		{"AND", TOK_OPERADOR_LOGICO},
		{"OR", TOK_OPERADOR_LOGICO},
		{"NOT", TOK_OPERADOR_LOGICO}
	};
	char comando[100], palavra[30];
	
	int i=0, TLP, TLS=0;
	char caractere = stringFormatada[i++];
	while(caractere!= '\0')
	{
		while(caractere!=';' && caractere!= '\0')
		{
			TLP=0;
			palavra[0] = '\0';
			while(caractere!=' ' && caractere!=';' && caractere!= '\0')
			{
				palavra[TLP++] = caractere;
				caractere = stringFormatada[i++];
			}
			palavra[TLP]='\0';
			if(isNumber(palavra))
			{
				strcpy(tokens[TLS].palavra, palavra); 
				tokens[TLS].tipo = TOK_NUMERO;        
				TLS++;                                           
			}
			else if(TLP>1)
			{
				if(TLS>0 && tokenizarPalavra(tabelaTokens, palavra) == TOK_STRING && tokens[TLS-1].tipo != TOK_PONTUACAO) 
				{
					strcpy(tokens[TLS].palavra, palavra); 
					tokens[TLS].tipo = TOK_IDENTIFICADOR; 
					TLS++;                                          
				}
				else
				{
					strcpy(tokens[TLS].palavra, palavra); 
					tokens[TLS].tipo = tokenizarPalavra(tabelaTokens, palavra); 
					TLS++;
				}
			}
			else if(TLP==1)
			{
				strcpy(tokens[TLS].palavra, palavra);
				tokens[TLS].tipo = TOK_PONTUACAO;
				TLS++;
			}
				
			if(caractere!='\0')	
				caractere = stringFormatada[i++];
		}
		if(caractere == ';')
		{
			strcpy(tokens[TLS].palavra, ";");
			tokens[TLS].tipo = TOK_PONTUACAO;
			TLS++;
		}
		caractere = stringFormatada[i++];
	}
	
	*TLToken = TLS;

	for(i=0 ;i<TLS;i++)
		printf("%d:%s ", tokens[i].tipo, tokens[i].palavra);
}

void separarComandos(DescritorLista *descLista, Token tokens[], int TL)
{
	Token comando[100];
	int TLC = 0, i;

	for(i = 0; i < TL; i++)
	{
		comando[TLC++] = tokens[i];

		if(tokens[i].tipo == TOK_PONTUACAO && strcmp(tokens[i].palavra, ";") == 0)
		{
			add(descLista, comando, TLC);
			TLC = 0;
		}
	}

	if(TLC > 0)
		add(descLista, comando, TLC);
}

void lerScriptUsuario(char scriptString[])
{
	char caractere;
	int TL=0;
	printf("Digite seu script sql abaixo (& - pular liha):\n");
	caractere = getch();
	while(caractere != 13)
	{
		if (caractere == 0 || caractere == -32)
			getch();
		else if(caractere>=32 && caractere<=127 || caractere == 8 || caractere == 9)
		{
			if(caractere == '&')
			{
				printf("\n");
				scriptString[TL++] = '\n';
			}
			else if(caractere == 8)
			{
				if(TL>0)
				{
					printf("\b \b");
					scriptString[TL--] = '\0';
				}
			}
			else
				printf("%c", caractere);
				
			if(caractere != 8 && caractere != '&')
				scriptString[TL++] = caractere;
			
		}
		caractere = getch();
	}
	scriptString[TL] = '\0';
}

void imprimirComandos(DescritorLista *descLista)
{
	Lista *aux = descLista->inicio;
	int numComando=1,i;

	while(aux != NULL)
	{
		printf("\nComando %d: ", numComando);

		i=0;
		while(aux->comando[i].tipo != TOK_PONTUACAO || strcmp(aux->comando[i].palavra, ";") != 0)
		{
			printf("%s ", aux->comando[i].palavra);

			i++;
		}
		printf("%s ", aux->comando[i].palavra);
		printf("\n");

		aux = aux->prox;
		numComando++;
	}
}

void interpretarCreate(TpBanco **banco, Token comando[])
{
	char nomeCampo[20],tipo;
	if(!stricmp(comando[1].palavra, "TABLE"))
	{
		if(*banco != NULL)
		{
			
		
			criarTabela(&((*banco)->pTabelas), comando[2].palavra);
			TpTabela *tabelaAtual = (*banco)->pTabelas;
			while(tabelaAtual->prox != NULL)
				tabelaAtual = tabelaAtual->prox;

			// agora percorre as colunas: CREATE(0) TABLE(1) nome(2) "("(3) col TIPO , col TIPO ) ;
			int i = 4;
			int pilha = 1;
			while(pilha>0)
			{
				if(strcmp(comando[i].palavra, ",") == 0)
						i++;
				else if(stricmp(comando[i].palavra,"CONSTRAINT")==0)
				{
					while(stricmp(comando[i].palavra, "KEY") != 0 && strcmp(comando[i].palavra, ";") != 0)
						i++;
					i+=2;
					TpCampo *campoPK = tabelaAtual->pCampos;
					while(campoPK != NULL && strcmp(campoPK->nome, comando[i].palavra) != 0)
						campoPK = campoPK->prox;
					if(campoPK != NULL)
						campoPK->PK = 'S';
				
					pilha = 0;
				}
				else if(strcmp(comando[i].palavra, "(") == 0)
				{
					pilha++;
					i++;
				}
				else if(strcmp(comando[i].palavra, ")") == 0)
				{
					pilha--;
					i++;
				}
				else if(pilha==1)
				{
					strcpy(nomeCampo, comando[i].palavra);
					i++; // avança pro tipo
					if(!stricmp(comando[i].palavra, "INT") || !stricmp(comando[i].palavra, "INTEGER"))
						tipo = 'I';
					else if(!stricmp(comando[i].palavra, "FLOAT") || !stricmp(comando[i].palavra, "DOUBLE"))
						tipo = 'N';
					else if(!stricmp(comando[i].palavra, "DATE"))
						tipo = 'D';
					else if(!stricmp(comando[i].palavra, "CHAR") || !stricmp(comando[i].palavra, "CHARACTER"))
						tipo = 'C';
					else if(!stricmp(comando[i].palavra, "VARCHAR"))
						tipo = 'T';
	
					criarCampo(&(tabelaAtual->pCampos), nomeCampo, tipo, 'N');
	
					i++; // avança pra depois do tipo
					if(strcmp(comando[i].palavra, ",") == 0)
						i++; // pula a vírgula
				}
				else
				{
					i++;
				}
			}
		}
	}
	else if(!stricmp(comando[1].palavra, "DATABASE"))
	{
		if(*banco == NULL)
			criarBanco(banco, comando[2].palavra);
	}
}


void interpretarComandos(TpBanco **banco, DescritorLista *descLista)
{
	Lista *aux = descLista->inicio;
	while(aux != NULL)
	{
		if(aux->comando[0].tipo == TOK_COMANDO)
		{
			if(!stricmp(aux->comando[0].palavra, "CREATE"))
				interpretarCreate(banco, aux->comando);
			/*else if(!stricmp(aux->comando[0].palavra, "INSERT"))
				interpretarInsert(*banco, aux->comando);
			else if(!stricmp(aux->comando[0].palavra, "SELECT"))
				interpretarSelect(*banco, aux->comando);
			else if(!stricmp(aux->comando[0].palavra, "UPDATE"))
				interpretarUpdate(*banco, aux->comando);
			else if(!stricmp(aux->comando[0].palavra, "DELETE"))
				interpretarDelete(*banco, aux->comando);
			else if(!stricmp(aux->comando[0].palavra, "ALTER"))
				interpretarAlter(*banco, aux->comando);*/
			
		}
		aux = aux->prox;
	}
}

void imprimirBanco(TpBanco *banco)
{
	if(banco == NULL)
	{
		printf("Nenhum banco de dados criado.\n");
		return;
	}

	printf("=== BANCO: %s ===\n", banco->nome);

	TpTabela *tabela = banco->pTabelas;
	if(tabela == NULL)
		printf("(nenhuma tabela criada)\n");

	while(tabela != NULL)
	{
		printf("  TABELA: %s\n", tabela->nome);

		TpCampo *campo = tabela->pCampos;
		if(campo == NULL)
			printf("    (nenhum campo criado)\n");

		while(campo != NULL)
		{
			printf("    CAMPO: %s (tipo: %c,PK: %c)\n", campo->nome, campo->tipo,campo->PK);
			campo = campo->prox;
		}

		tabela = tabela->prox;
	}
}
