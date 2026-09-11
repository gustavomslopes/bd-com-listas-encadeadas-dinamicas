#define TOK_CREATE 0
#define TOK_ALTER 1
#define TOK_DROP 2
#define TOK_TABLE 3
#define TOK_DATABASE 4
#define TOK_INSERT 5
#define TOK_UPDATE 6
#define TOK_DELETE 7
#define TOK_SELECT 8

#define TOK_CONSTRAINT 9
#define TOK_PRIMARY 10
#define TOK_FOREIGN 11
#define TOK_KEY 12
#define TOK_INTO 13
#define TOK_VALUES 14
#define TOK_SET 15
#define TOK_FROM 16
#define TOK_WHERE 17
#define TOK_ORDER 18
#define TOK_BY 19
#define TOK_GROUP 20
#define TOK_HAVING 21
#define TOK_DISTINCT 22
#define TOK_AS 23
#define TOK_LIMIT 24
#define TOK_ADD 25
#define TOK_COLUMN 26
#define TOK_RENAME 27
#define TOK_MODIFY 28

#define TOK_TIPO_DADO 29

#define TOK_AND 30
#define TOK_OR 31
#define TOK_NOT 32

#define TOK_ABRE_PARENTESE 33
#define TOK_FECHA_PARENTESE 34
#define TOK_VIRGULA 35
#define TOK_PONTO_VIRGULA 36

#define TOK_IDENTIFICADOR 37
#define TOK_NUMERO 38
#define TOK_STRING 39

#define TOTAL_TOK 39

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
	return -1;
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
		{"CREATE", TOK_CREATE}, 
		{"ALTER", TOK_ALTER}, 
		{"DROP", TOK_DROP},
		{"TABLE", TOK_TABLE}, 
		{"DATABASE", TOK_DATABASE},
		{"INSERT", TOK_INSERT}, 
		{"UPDATE", TOK_UPDATE}, 
		{"DELETE", TOK_DELETE}, 
		{"SELECT", TOK_SELECT},
		{"CONSTRAINT", TOK_CONSTRAINT}, 
		{"PRIMARY", TOK_PRIMARY}, 
		{"FOREIGN", TOK_FOREIGN},
		{"KEY", TOK_KEY},
		{"INTO", TOK_INTO}, 
		{"VALUES", TOK_VALUES}, 
		{"SET", TOK_SET}, 
		{"FROM", TOK_FROM},
		{"WHERE", TOK_WHERE}, 
		{"ORDER", TOK_ORDER}, 
		{"BY", TOK_BY}, 
		{"GROUP", TOK_GROUP},
		{"HAVING", TOK_HAVING},
		{"DISTINCT", TOK_DISTINCT}, 
		{"AS", TOK_AS}, 
		{"LIMIT", TOK_LIMIT},
		{"ADD", TOK_ADD}, 
		{"COLUMN", TOK_COLUMN}, 
		{"RENAME", TOK_RENAME}, 
		{"MODIFY", TOK_MODIFY},
		{"INT", TOK_TIPO_DADO}, 
		{"INTEGER", TOK_TIPO_DADO}, 
		{"CHAR", TOK_TIPO_DADO}, 
		{"CHARACTER", TOK_TIPO_DADO},
		{"FLOAT", TOK_TIPO_DADO}, 
		{"DOUBLE", TOK_TIPO_DADO},
		{"DATE", TOK_TIPO_DADO}, 
		{"BOOLEAN", TOK_TIPO_DADO},
		{"AND", TOK_AND}, 
		{"OR", TOK_OR}, 
		{"NOT", TOK_NOT}
	};
	char comando[100], palavra[30];
	
	int i=0, TLP, TLS=0, token;
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
			if(TLP!=0)
			{
				token = tokenizarPalavra(tabelaTokens, palavra);
				if(token == -1)
				{
					if(isNumber(palavra)) token = TOK_NUMERO;
					else if(TLP==1)
					{
						if(strcmp(palavra, ")") == 0) token = TOK_FECHA_PARENTESE;
						else if((strcmp(palavra, "(") == 0)) token = TOK_ABRE_PARENTESE;
						else if((strcmp(palavra, ",") == 0)) token = TOK_VIRGULA;
						else if((strcmp(palavra, ";") == 0)) token = TOK_PONTO_VIRGULA;
						else token = TOK_IDENTIFICADOR;
					}
					else
					{
						token = TOK_STRING;
						if(TLS>0 && (tokens[TLS-1].tipo>=0 && tokens[TLS-1].tipo<=8)) token = TOK_IDENTIFICADOR;
					}
				}
				if(token != -1)
				{
					strcpy(tokens[TLS].palavra, palavra); 
					tokens[TLS++].tipo = token; 
				}
			}
				
			if(caractere!='\0')	
				caractere = stringFormatada[i++];
		}
		if(caractere == ';')
		{
			strcpy(tokens[TLS].palavra, ";");
			tokens[TLS++].tipo = TOK_PONTO_VIRGULA;
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

		if(tokens[i].tipo == TOK_PONTO_VIRGULA)
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
		while(aux->comando[i].tipo != TOK_PONTO_VIRGULA)
		{
			printf("%d ", aux->comando[i].tipo);

			i++;
		}
		printf("%d ", aux->comando[i].tipo);
		printf("\n");

		aux = aux->prox;
		numComando++;
	}
}

char erro(char palavra[])
{
	printf("ERRO: %s", palavra);
	return 0;
}

char interpretarCampo(TpTabela *tabelaAtual, Token comando[], int *i)
{
	char nomeCampo[20], tipo;

	strcpy(nomeCampo, comando[*i].palavra);
	(*i)++;

	if(!stricmp(comando[*i].palavra, "INT") || !stricmp(comando[*i].palavra, "INTEGER"))
		tipo = 'I';
	else if(!stricmp(comando[*i].palavra, "FLOAT") || !stricmp(comando[*i].palavra, "DOUBLE"))
		tipo = 'N';
	else if(!stricmp(comando[*i].palavra, "DATE"))
		tipo = 'D';
	else if(!stricmp(comando[*i].palavra, "CHAR") || !stricmp(comando[*i].palavra, "CHARACTER"))
	{
		(*i)++;
		if(comando[*i].tipo == TOK_ABRE_PARENTESE)
		{
			(*i)++;
			if(comando[*i].tipo == TOK_NUMERO)
			{
				if(atoi(comando[*i].palavra) == 20)
					tipo = 'T';
				else if(atoi(comando[*i].palavra) == 1)
					tipo = 'C';
				else
					return erro("Tamanho de CHAR nao suportado (use 1 ou 20)");

				(*i)++;
				if(comando[*i].tipo != TOK_FECHA_PARENTESE)
					return erro("Faltou )");
			}
			else
				return erro("Esperava numero em CHAR(n)");
		}
		else
			return erro("Faltou (");
	}
	else
		return erro("Tipo de dado nao reconhecido");

	criarCampo(&(tabelaAtual->pCampos), nomeCampo, tipo, 'N');

	(*i)++;
	if(comando[*i].tipo == TOK_VIRGULA)
		(*i)++;
	else if(comando[*i].tipo != TOK_FECHA_PARENTESE)
		return erro("Falta )");

	return 1;
}

char interpretarCreate(TpBanco **banco, Token comando[])
{
	int i=1, temCampo=0, temPK=0;
	TpCampo *campoPK;
	TpTabela *tabelaAtual;
	char nomeCampo[20], tipo;
	if(comando[i].tipo == TOK_TABLE)
	{
		if(*banco != NULL)
		{
			i++;
			if(comando[i].tipo == TOK_IDENTIFICADOR)
			{
				tabelaAtual = criarTabela(&((*banco)->pTabelas), comando[i].palavra);
				i++;
				if(tabelaAtual!=NULL)
				{
					if(comando[i].tipo == TOK_ABRE_PARENTESE)
					{
						i++;
						while(comando[i].tipo != TOK_FECHA_PARENTESE)
						{
							if(comando[i].tipo == TOK_STRING && comando[i+1].tipo == TOK_TIPO_DADO)
							{
								if(!interpretarCampo(tabelaAtual, comando, &i))
									return erro("Erro ao interpretar campo");
								temCampo=1;			
							}
							else if(comando[i].tipo == TOK_CONSTRAINT && temCampo)
							{
								i++;
								if(comando[i].tipo == TOK_STRING)
								{
									i++;
									if(comando[i].tipo == TOK_PRIMARY && comando[i+1].tipo == TOK_KEY && temPK==0)
									{
										i+=2;
										if(comando[i].tipo == TOK_ABRE_PARENTESE)
										{
											i++;
											if(comando[i].tipo == TOK_STRING)
											{
												campoPK = tabelaAtual->pCampos;
												while(campoPK != NULL && stricmp(campoPK->nome, comando[i].palavra) != 0)
													campoPK = campoPK->prox;
												if(campoPK != NULL)
													campoPK->PK = 'S';
												i++;
												if(comando[i].tipo == TOK_FECHA_PARENTESE)
													i++;
												if(comando[i].tipo == TOK_VIRGULA)
													i++;
												else if(comando[i].tipo != TOK_FECHA_PARENTESE)
													return erro("Falta )");
												temPK=1;
											}
										}
									}
									else if(temPK==1)
										return erro("Duas PK!");
									else if(comando[i].tipo == TOK_FOREIGN && comando[i+1].tipo == TOK_KEY)
									{
										
									}
								}
							}
							else
								return erro("Campo estruturado errado!");
						}
						i++;
						if(comando[i].tipo == TOK_PONTO_VIRGULA)
							return 1;
					}
					else
						return erro("Sem (");
				}
				else
					return erro("Nome da tabela ja existente!");				
			}
			else
				return erro("Nome da tabela ausente!");
		}
		else
			return erro("Banco nao criado!");
		
	}
	else if(comando[i].tipo == TOK_DATABASE)
	{
		if(comando[++i].tipo == TOK_IDENTIFICADOR)
		{
			if(*banco == NULL)
				criarBanco(&*banco, comando[i].palavra);
				
			if(comando[++i].tipo == TOK_PONTO_VIRGULA)
				return 1;
		}
		return erro("Erro ao criar banco");
	}
	else
		return erro("Comando create nao reconhecido!");
		
}
//{
//	char nomeCampo[20],tipo;
//	int i, pilha, temPK;
//	
//	if(!stricmp(comando[1].palavra, "TABLE"))
//	{
//		if(*banco != NULL)
//		{
//			criarTabela(&((*banco)->pTabelas), comando[2].palavra);
//			TpTabela *tabelaAtual = (*banco)->pTabelas;
//			while(tabelaAtual->prox != NULL)
//				tabelaAtual = tabelaAtual->prox;

//			i = 4;
//			pilha = 1;
//			temPK = 0;
//			while(pilha>0 && temPK<=1)
//			{
//				if(strcmp(comando[i].palavra, ",") == 0)
//						i++;
//				else if(stricmp(comando[i].palavra,"CONSTRAINT")==0)
//				{
//					i+=2;
//					if(stricmp(comando[i].palavra,"PRIMARY")==0 && temPK==0)
//					{
//						while(stricmp(comando[i].palavra, "KEY") != 0)
//							i++;
//						i+=2;
//						TpCampo *campoPK = tabelaAtual->pCampos;
//						while(campoPK != NULL && strcmp(campoPK->nome, comando[i].palavra) != 0)
//							campoPK = campoPK->prox;
//						if(campoPK != NULL)
//							campoPK->PK = 'S';
//						i+=2;
//						if(comando[i].tipo == TOK_STRING)
//						{
//							campoPK = tabelaAtual->pCampos;
//							while(campoPK != NULL && strcmp(campoPK->nome, comando[i].palavra) != 0)
//								campoPK = campoPK->prox;
//							if(campoPK != NULL)
//								campoPK->PK = 'S';
//						}
//						temPK=1;
//					}
//					else
//					{
//						temPK++;
//						printf("ERRO: DUAS PK!");
//					}
//						
//					
//				}
//				else if(strcmp(comando[i].palavra, "(") == 0)
//				{
//					pilha++;
//					i++;
//				}
//				else if(strcmp(comando[i].palavra, ")") == 0)
//				{
//					pilha--;
//					i++;
//				}
//				else if(pilha==1)
//				{
//					if(comando[i].tipo == TOK_STRING && comando[i+1].tipo == TOK_TIPO_DADO)
//					{
//						strcpy(nomeCampo, comando[i].palavra);
//						i++;
//						if(!stricmp(comando[i].palavra, "INT") || !stricmp(comando[i].palavra, "INTEGER"))
//							tipo = 'I';
//						else if(!stricmp(comando[i].palavra, "FLOAT") || !stricmp(comando[i].palavra, "DOUBLE"))
//							tipo = 'N';
//						else if(!stricmp(comando[i].palavra, "DATE"))
//							tipo = 'D';
//						else if(!stricmp(comando[i].palavra, "CHAR") || !stricmp(comando[i].palavra, "CHARACTER"))
//							tipo = 'C';
//						
//		
//						criarCampo(&(tabelaAtual->pCampos), nomeCampo, tipo, 'N');
//		
//						i++; 
//						if(strcmp(comando[i].palavra, ",") == 0)
//							i++;
//					}
//					
//				}
//				else
//					i++;
//			}
//		}
//	}
//	else if(!stricmp(comando[1].palavra, "DATABASE"))
//	{
//		if(*banco == NULL)
//			criarBanco(banco, comando[2].palavra);
//	}
//}


void interpretarComandos(TpBanco **banco, DescritorLista *descLista)
{
	Lista *comandoAtual = del(&*descLista);
	char certo = 1;
	while(comandoAtual!=NULL && certo == 1)
	{
		if(comandoAtual->comando[0].tipo == TOK_CREATE)
			certo = interpretarCreate(&*banco, comandoAtual->comando);
//			/*else if(!stricmp(aux->comando[0].palavra, "INSERT"))
//				interpretarInsert(*banco, aux->comando);
//			else if(!stricmp(aux->comando[0].palavra, "SELECT"))
//				interpretarSelect(*banco, aux->comando);
//			else if(!stricmp(aux->comando[0].palavra, "UPDATE"))
//				interpretarUpdate(*banco, aux->comando);
//			else if(!stricmp(aux->comando[0].palavra, "DELETE"))
//				interpretarDelete(*banco, aux->comando);
//			else if(!stricmp(aux->comando[0].palavra, "ALTER"))
//				interpretarAlter(*banco, aux->comando);*/
		free(comandoAtual);
		comandoAtual = del(&*descLista);
	}
}
//{
//	Lista *aux = descLista->inicio;
//	while(aux != NULL)
//	{
//		if(aux->comando[0].tipo == TOK_COMANDO)
//		{
//			if(!stricmp(aux->comando[0].palavra, "CREATE"))
//				interpretarCreate(banco, aux->comando);
//			/*else if(!stricmp(aux->comando[0].palavra, "INSERT"))
//				interpretarInsert(*banco, aux->comando);
//			else if(!stricmp(aux->comando[0].palavra, "SELECT"))
//				interpretarSelect(*banco, aux->comando);
//			else if(!stricmp(aux->comando[0].palavra, "UPDATE"))
//				interpretarUpdate(*banco, aux->comando);
//			else if(!stricmp(aux->comando[0].palavra, "DELETE"))
//				interpretarDelete(*banco, aux->comando);
//			else if(!stricmp(aux->comando[0].palavra, "ALTER"))
//				interpretarAlter(*banco, aux->comando);*/
//			
//		}
//		aux = aux->prox;
//	}
//}

void imprimirBanco(TpBanco *banco)
{
	TpTabela *tabela;
	TpCampo *campo;
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
			printf("  TABELA: %s\n", tabela->nome);
	
			campo = tabela->pCampos;
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
	
}
