#define TOK_CREATE 0
#define TOK_ALTER 1
#define TOK_TABLE 2
#define TOK_DATABASE 3
#define TOK_INSERT 4
#define TOK_UPDATE 5
#define TOK_DELETE 6
#define TOK_SELECT 7

#define TOK_CONSTRAINT 8
#define TOK_PRIMARY 9
#define TOK_FOREIGN 10
#define TOK_KEY 11
#define TOK_INTO 12
#define TOK_VALUES 13
#define TOK_SET 14
#define TOK_FROM 15
#define TOK_WHERE 16
#define TOK_ORDER 17
#define TOK_BY 18
#define TOK_GROUP 19
#define TOK_HAVING 20
#define TOK_DISTINCT 21
#define TOK_AS 22
#define TOK_LIMIT 23
#define TOK_ADD 24
#define TOK_COLUMN 25
#define TOK_RENAME 26
#define TOK_MODIFY 27

#define TOK_TIPO_DADO 28

#define TOK_AND 29
#define TOK_OR 30
#define TOK_NOT 31

#define TOK_ABRE_PARENTESE 32
#define TOK_FECHA_PARENTESE 33
#define TOK_VIRGULA 34
#define TOK_PONTO_VIRGULA 35

#define TOK_IDENTIFICADOR 36
#define TOK_NUMERO 37
#define TOK_STRING 38

#define TOTAL_TOK 38

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
		if(caractere == '\n' || caractere == ' ' || caractere == '\t')
		{
			stringFormatada[TL++] = ' ';

			while(caractere == ' ' || caractere == '\n' || caractere == '\t')
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
		if(stricmp(palavra, tabelaTokens[i].palavra)==0)
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
						if(TLS>0 && (tokens[TLS-1].tipo>=0 && tokens[TLS-1].tipo<=7)) token = TOK_IDENTIFICADOR;
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

	// for(i=0 ;i<TLS;i++)
	// 	printf("%d:%s ", tokens[i].tipo, tokens[i].palavra);
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

char lerScriptUsuario(char scriptString[])
{
	char caractere;
	int TL=0;
	printf("Digite seu script sql abaixo (& - pular liha):\n");
	caractere = getch();
	while(caractere != 13 && caractere != 27)
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
	if(caractere == 13)
		return 1;
	return 0;
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

	if(criarCampo(&(tabelaAtual->pCampos), nomeCampo, tipo))
	{
		(*i)++;
		if(comando[*i].tipo == TOK_VIRGULA)
			(*i)++;
		else if(comando[*i].tipo != TOK_FECHA_PARENTESE)
		{
			return erro("Falta )");
		}
	}
	else
		return erro("Campos com o mesmo nome!");
		
	return 1;
}

char criarPK(TpTabela *tabelaAtual, Token comando[], int *i)
{
	TpCampo *campoPK;
	(*i)++;
	campoPK = tabelaAtual->pCampos;	
	while(campoPK != NULL && stricmp(campoPK->nome, comando[*i].palavra) != 0)
		campoPK = campoPK->prox;
	if(campoPK != NULL)
		campoPK->PK = 'S';
	else
		return erro("Campo nao encontrado para PK!");
	(*i)++;
	return 1;
}

TpCampo *buscarCampo(TpTabela *tabelaAtual, Token comando[],int  i)
{
	TpCampo *campo;
	campo = tabelaAtual->pCampos;	
	while(campo != NULL && stricmp(campo->nome, comando[i].palavra) != 0)
		campo = campo->prox;
	if(campo!=NULL)
		return campo;
	return NULL;
}

TpTabela *buscarTabela(TpBanco *banco, Token comando[],int  i)
{
	TpTabela *tabela;
	tabela = banco->pTabelas;	
	while(tabela != NULL && stricmp(tabela->nome, comando[i].palavra) != 0)
		tabela = tabela->prox;
	if(tabela!=NULL)
		return tabela;
	return NULL;
}

TpDado* buscarDado(TpCampo *campo, union dados valor)
{
	TpDado *dado = campo->pDados;

	while(dado != NULL)
	{
		switch(campo->tipo)
		{
			case 'I':
				if(dado->valor.integer == valor.integer)
					return dado;
				break;
			case 'N':
				if(dado->valor.numeric == valor.numeric)
					return dado;
				break;
			case 'D':
				if(strcmp(dado->valor.date, valor.date) == 0)
					return dado;
				break;
			case 'C':
				if(dado->valor.character1 == valor.character1)
					return dado;
				break;
			case 'T':
				if(strcmp(dado->valor.character20, valor.character20) == 0)
					return dado;
				break;
		}
		dado = dado->prox;
	}
	return NULL;
}

char criarFK(TpTabela *tabelaAtual, Token comando[], TpBanco **banco, int  *i)
{
	TpCampo *campoFK, *campoFK2;
	TpTabela *tabelaFK;
	(*i)++;
	if(comando[*i].tipo == TOK_STRING)
	{
		campoFK = buscarCampo(tabelaAtual, comando, *i);
		if(campoFK != NULL)
		{
			if(campoFK->FK==NULL)
			{
				(*i)++; 
				if(comando[*i].tipo == TOK_FECHA_PARENTESE)
				{
					(*i)++; 
					if(comando[*i].tipo == TOK_STRING && stricmp(comando[*i].palavra,"REFERENCES")==0)
					{
						(*i)++; 
						if(comando[*i].tipo == TOK_STRING)
						{
							tabelaFK = buscarTabela(*banco, comando, *i);
							if(tabelaFK != NULL)
							{
								(*i)++; 
								if(comando[*i].tipo == TOK_ABRE_PARENTESE)
								{
									(*i)++;
									campoFK2 = buscarCampo(tabelaFK, comando, *i);
									if(campoFK2 != NULL)
									{
										campoFK->FK = campoFK2;
										(*i)++;
									}
									else
										return erro("Campo referenciado nao encontrado");
								}
								else
									return erro("Falta ( apos nome da tabela referenciada");
							}
							else
								return erro("Tabela referenciada nao encontrada");
						}
						
					}
					else
						return erro("Esperado REFERENCES");
				}
				else
					return erro("Falta ) apos campo FK");
			}
		}
		else
			return erro("Campo FK nao encontrado na tabela atual");		
	}
	else
		return erro("Nome do campo ausente");

	if(comando[*i].tipo == TOK_FECHA_PARENTESE)
	{
		(*i)++;
		if(comando[*i].tipo == TOK_VIRGULA)
			(*i)++;
	}
	else 
		return erro("Falta )");
	
	return 1;
}

char interpretarCreate(TpBanco **banco, Token comando[])
{
	int i=1, temCampo=0, temPK=0;
	TpCampo *campoFK,*campoFK2;
	TpTabela *tabelaAtual,*tabelaFK;
	char nomeCampo[20], tipo, aux[20];
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
										if(comando[i].tipo == TOK_ABRE_PARENTESE && comando[i+1].tipo == TOK_STRING )
										{
											if(!criarPK(tabelaAtual, comando, &i))
												return erro("Falha ao criar PK");
											if(comando[i].tipo == TOK_VIRGULA && comando[i+1].tipo == TOK_STRING)
											{
												if(!criarPK(tabelaAtual, comando, &i))
													return erro("Falha ao criar PK");
											}
											if(comando[i].tipo == TOK_FECHA_PARENTESE)
											{
												i++;
												if(comando[i].tipo == TOK_VIRGULA)
													i++;	
												else if(comando[i].tipo != TOK_FECHA_PARENTESE)
													return erro("Falta )");
												temPK=1;
											}
											else
												return erro("Falta )");												
										}
									}
									else if(comando[i].tipo == TOK_PRIMARY && comando[i+1].tipo == TOK_KEY && temPK==1)
										return erro("Duas PK!");
									else if(comando[i].tipo == TOK_FOREIGN && comando[i+1].tipo == TOK_KEY)
									{
										i+=2;
										if(comando[i].tipo == TOK_ABRE_PARENTESE)
										{
											if(!criarFK(tabelaAtual, comando, &*banco, &i))
												return erro("Falha ao criar FK");
											
										}
									}
								}
							}
							else if(comando[i].tipo == TOK_CONSTRAINT && !temCampo)
								return erro("Nao ha campos para ter constraint");
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


char interpretarAlter(TpBanco **banco, Token comando[])
{
	int i=1;
	TpCampo *campoFK,*campoFK2;
	TpTabela *tabelaFK,*tabelaFK2;
	if(comando[i].tipo == TOK_TABLE)
	{
		if(*banco != NULL)
		{
			i++;
			if(comando[i].tipo == TOK_IDENTIFICADOR)
			{
				tabelaFK = buscarTabela(*banco, comando, i);
				if(tabelaFK!=NULL)
				{
					i++;
					if(comando[i].tipo == TOK_ADD)
					{
						i++;
						if(comando[i].tipo == TOK_CONSTRAINT)
						{
							i++;
							if(comando[i].tipo == TOK_STRING)
							{
								i++;
								if(comando[i].tipo == TOK_FOREIGN && comando[i+1].tipo == TOK_KEY)
								{
									i+=2;
									if(comando[i].tipo == TOK_ABRE_PARENTESE)
									{
										if(!criarFK(tabelaFK, comando, &*banco, &i))
											return erro("Falha ao criar FK");
										if(comando[i].tipo == TOK_FECHA_PARENTESE)
											i++;
										else
										{
											if(comando[i].tipo == TOK_PONTO_VIRGULA)
												return 1;
											else
												return erro("Falta ;");
										}
									}
									else
										return erro("Falta ( apos FOREIGN KEY");
								}
								else
									return erro("Esperado FOREIGN KEY");
							}
							else
								return erro("Nome da constraint ausente");
						}
						else
							return erro("Esperado CONSTRAINT");
					}
					else
						return erro("Esperado ADD");
				}
				else
					return erro("Tabela nao encontrada");
			}
			else
				return erro("Nome da tabela ausente!");
		}
		else
			return erro("Banco nao criado!");
	}
	else
		return erro("Comando alter nao reconhecido!");
}

char isChar1(char palavra[])
{
	if(strlen(palavra) == 1)
		return 1;
	return 0;
}

char isDate(char palavra[])
{
	int i;
	if(strlen(palavra) != 10)
		return 0;
	for(i = 0; i < 10; i++)
	{
		if(i == 4 || i == 7)
		{
			if(palavra[i] != '-')
				return 0;
		}
		else
		{
			if(!isdigit(palavra[i]))
				return 0;
		}
	}
	return 1;
}

char isChar20(char palavra[])
{
	if(strlen(palavra) <= 20 && !isDate(palavra))
		return 1;
	return 0;
}

char isInt(char palavra[])
{
	return isNumber(palavra);
}

char isFloat(char palavra[])
{
	int i, pontos = 0;
	if(palavra[0] == '\0')
		return 0;
	for(i = 0; palavra[i] != '\0'; i++)
	{
		if(palavra[i] == '.')
			pontos++;
		else if(!isdigit(palavra[i]))
			return 0;
	}
	return (pontos == 1);
}


void tirarApostrofo(char palavra[])
{
	int i;
	for(i=0; i<strlen(palavra)-1; i++)
		palavra[i] = palavra[i+1];
	palavra[i-1] = '\0';
}

char interpretarInsert(TpBanco **banco, Token comando[])
{
	int i=1, pos=0;
	TpCampo *campos[15];
	TpTabela *tabela;
	union dados valor;
	char tipo;
	if(comando[i].tipo == TOK_INTO)
	{
		i++;
		if(comando[i].tipo == TOK_STRING)
		{
			tabela = buscarTabela(*banco, comando, i);
			if(tabela!=NULL)
			{
				i++;
				if(comando[i].tipo == TOK_ABRE_PARENTESE)
				{
					i++;
					if(comando[i].tipo == TOK_FECHA_PARENTESE)
						return erro("Sem colunas");
					while(comando[i].tipo != TOK_FECHA_PARENTESE)
					{
						if(comando[i].tipo == TOK_STRING)
						{
							campos[pos] = buscarCampo(tabela, comando, i);
							if(campos[pos]==NULL)
								return erro("campo nao encontrado!");
							
							pos++;
							i++;
							if(comando[i].tipo == TOK_VIRGULA)
								i++;
							else if(comando[i].tipo != TOK_FECHA_PARENTESE)
								return erro("Falta )");
						}
						else
							return erro("Esperado nome de coluna!");
					}
					i++;
					if(comando[i].tipo == TOK_VALUES)
					{
						i++;						
						if(comando[i].tipo ==TOK_ABRE_PARENTESE)
						{
							i++;
							if(comando[i].tipo == TOK_FECHA_PARENTESE)
								return erro("Sem valores");
							pos=0;
							while(comando[i].tipo != TOK_FECHA_PARENTESE)
							{
								if(comando[i].tipo == TOK_STRING || comando[i].tipo == TOK_NUMERO)
								{
									tipo = ' ';
									if(comando[i].palavra[0]=='\'' && comando[i].palavra[strlen(comando[i].palavra)-1] == '\'' )
									{
										tirarApostrofo(comando[i].palavra);
										if(isChar1(comando[i].palavra))
										{
											valor.character1 = comando[i].palavra[0];
											tipo = 'C';
										}
										else if(isChar20(comando[i].palavra))
										{
											strcpy(valor.character20, comando[i].palavra);
											tipo = 'T';
										}
										else if(isDate(comando[i].palavra))
										{
											strcpy(valor.date, comando[i].palavra);
											tipo = 'D';
										}
										else
											return erro("Tipo de dado nao reconhecido");
									}
									else
									{
										if(isInt(comando[i].palavra))
										{
											valor.integer = atoi(comando[i].palavra);
											tipo = 'I';
										}
										else if(isFloat(comando[i].palavra))
										{
											valor.numeric = atof(comando[i].palavra);
											tipo = 'N';
										}
									}
									if(tipo == campos[pos]->tipo)
									{
										if(campos[pos]->PK == 'S' && buscarDado(campos[pos], valor))
											return erro("Dado repetido na PK");
										if(campos[pos]->FK != NULL && !buscarDado(campos[pos]->FK, valor))
											return erro("Dado nao encontrado na FK");
										criarDado(tabela->pCampos, campos[pos]->nome, valor);
									}
									else
										return erro("Tipo de dado incompativel");
									pos++;
									i++;
									if(comando[i].tipo == TOK_VIRGULA)
										i++;
								}
								else
									return erro("Esperado valor!");
							}
						}
						else
							return erro("Falta (");
					}
					else
						return erro("Esperado VALUES");
				}
				else
					return erro("Falta (");
			}
			else
				return erro("Tabela nao encontrada!");
		}
		else
			return erro("Falta nome da tabela");
	}
	else
		return erro("Esperado INTO");
}

void interpretarComandos(TpBanco **banco, DescritorLista *descLista)
{
	Lista *comandoAtual = del(&*descLista);
	char certo = 1;
	while(comandoAtual!=NULL && certo == 1)
	{
		if(comandoAtual->comando[0].tipo == TOK_CREATE)
			certo = interpretarCreate(&*banco, comandoAtual->comando);
			else if(comandoAtual->comando[0].tipo == TOK_INSERT)
				interpretarInsert(&*banco, comandoAtual->comando);
//			else if(!stricmp(aux->comando[0].palavra, "SELECT"))
//				interpretarSelect(*banco, aux->comando);
//			else if(!stricmp(aux->comando[0].palavra, "UPDATE"))
//				interpretarUpdate(*banco, aux->comando);
//			else if(!stricmp(aux->comando[0].palavra, "DELETE"))
//				interpretarDelete(*banco, aux->comando);*/
			else if(comandoAtual->comando[0].tipo == TOK_ALTER)
				certo = interpretarAlter(&*banco, comandoAtual->comando);
		free(comandoAtual);
		comandoAtual = del(&*descLista);
	}
}

void imprimirBanco(TpBanco *banco)
{
	TpTabela *tabela;
	TpCampo *campo;
	char tipo;
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
				if(campo->FK == NULL)
					printf("    CAMPO: %s (tipo: %c,PK: %c)\n", campo->nome, campo->tipo,campo->PK);
				else
					printf("    CAMPO: %s (tipo: %c,PK: %c,FK: %s)\n", campo->nome, campo->tipo,campo->PK,campo->FK->nome);
				tipo = campo->tipo;
				campo->pAtual = campo->pDados;
				while(campo->pAtual!=NULL)
				{
					switch(tipo)
					{
						case 'I':
							printf("    %d\n", campo->pAtual->valor.integer);
							break;
						case 'N':
							printf("    %.2f\n", campo->pAtual->valor.numeric);
							break;
						case 'D':
							printf("    %s\n", campo->pAtual->valor.date);
							break;
						case 'C':
							printf("    %c\n", campo->pAtual->valor.character1);
							break;
						case 'T':
							printf("    %s\n", campo->pAtual->valor.character20);
							break;
					}
					campo->pAtual = campo->pAtual->prox;
				}
				campo = campo->prox;
			}
	
			tabela = tabela->prox;
		}	
	}
	
}
