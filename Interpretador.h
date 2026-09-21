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

#define TOK_IGUAL 36
#define TOK_DIFERENTE 37
#define TOK_MENOR 38
#define TOK_MAIOR 39
#define TOK_MENOR_IGUAL 40
#define TOK_MAIOR_IGUAL 41

#define TOK_IDENTIFICADOR 42
#define TOK_NUMERO 43

#define TOK_BETWEEN 44

#define TOK_STRING 45

#define TOTAL_TOK 41

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
		else if(caractere == '(' || caractere == ')' || caractere == ',' || caractere == ';' || caractere == '=')
		{
			if(TL> 0 && stringFormatada[TL-1] != ' ')
				stringFormatada[TL++] = ' ';	
				
			stringFormatada[TL++] = caractere;
		}
		else
		{
			if (TL > 0 && (stringFormatada[TL-1] == '(' || stringFormatada[TL-1] == ')' || stringFormatada[TL-1] == ',' || stringFormatada[TL-1] == ';' || stringFormatada[TL-1] == '='))
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
		{"BETWEEN", TOK_BETWEEN}, 
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
		{"NUMERIC", TOK_TIPO_DADO},
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
		
		    if(caractere == '\'')
		    {
		        palavra[TLP++] = caractere;
		        caractere = stringFormatada[i++];
		        while(caractere != '\'' && caractere != '\0')
		        {
		            palavra[TLP++] = caractere;
		            caractere = stringFormatada[i++];
		        }
		        if(caractere == '\'')
		        {
		            palavra[TLP++] = caractere;
		            caractere = stringFormatada[i++];
		        }
		    }
		    else
		    {
		        while(caractere!=' ' && caractere!=';' && caractere!= '\0')
		        {
		            palavra[TLP++] = caractere;
		            caractere = stringFormatada[i++];
		        }
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
						else if((strcmp(palavra, "=") == 0)) token = TOK_IGUAL;
						else if((strcmp(palavra, "<") == 0)) token = TOK_MENOR;
						else if((strcmp(palavra, ">") == 0)) token = TOK_MAIOR;
						else token = TOK_IDENTIFICADOR;
					}
					else if(TLP==2)
					{
						if(strcmp(palavra, ">=") == 0) token = TOK_MAIOR_IGUAL;
						else if((strcmp(palavra, "<=") == 0)) token = TOK_MENOR_IGUAL;
						else token = TOK_DIFERENTE;
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

char erro(char logErro[], char palavra[])
{
	strcpy(logErro, palavra);
	return 0;
}

char interpretarCampo(TpTabela *tabelaAtual, Token comando[], int *i, char logErro[])
{
	char nomeCampo[20], tipo;

	strcpy(nomeCampo, comando[*i].palavra);
	(*i)++;

	if(!stricmp(comando[*i].palavra, "INT") || !stricmp(comando[*i].palavra, "INTEGER"))
		tipo = 'I';
	else if(!stricmp(comando[*i].palavra, "FLOAT") || !stricmp(comando[*i].palavra, "DOUBLE"))
		tipo = 'N';
	else if(!stricmp(comando[*i].palavra, "NUMERIC"))
	{
		tipo = 'N';
		(*i)++;
		if(comando[*i].tipo == TOK_ABRE_PARENTESE)
		{
			(*i)++;
			if(comando[*i].tipo != TOK_NUMERO)
				return erro(logErro, "Esperava numero em NUMERIC");
			(*i)++;
			if(comando[*i].tipo != TOK_VIRGULA)
				return erro(logErro, "Esperava , em NUMERIC");
			(*i)++;
			if(comando[*i].tipo != TOK_NUMERO)
				return erro(logErro, "Esperava numero em NUMERIC");
			(*i)++;
			if(comando[*i].tipo != TOK_FECHA_PARENTESE)
				return erro(logErro, "Faltou ) em NUMERIC");
		}
	}
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
					return erro(logErro, "Tamanho de CHAR nao suportado (use 1 ou 20)");

				(*i)++;
				if(comando[*i].tipo != TOK_FECHA_PARENTESE)
					return erro(logErro, "Faltou )");
			}
			else
				return erro(logErro, "Esperava numero em CHAR(n)");
		}
		else
			return erro(logErro, "Faltou (");
	}
	else
		return erro(logErro, "Tipo de dado nao reconhecido");

	if(criarCampo(&(tabelaAtual->pCampos), nomeCampo, tipo))
	{
		(*i)++;
		if(comando[*i].tipo == TOK_VIRGULA)
			(*i)++;
		else if(comando[*i].tipo != TOK_FECHA_PARENTESE)
		{
			return erro(logErro, "Falta )");
		}
	}
	else
		return erro(logErro, "Campos com o mesmo nome!");
		
	return 1;
}

char criarPK(TpTabela *tabelaAtual, Token comando[], int *i, char logErro[])
{
	TpCampo *campoPK;
	(*i)++;
	campoPK = tabelaAtual->pCampos;	
	while(campoPK != NULL && stricmp(campoPK->nome, comando[*i].palavra) != 0)
		campoPK = campoPK->prox;
	if(campoPK != NULL)
		campoPK->PK = 'S';
	else
		return erro(logErro, "Campo nao encontrado para PK!");
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

char criarFK(TpTabela *tabelaAtual, Token comando[], TpBanco **banco, int  *i, char logErro[])
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
										return erro(logErro, "Campo referenciado nao encontrado");
								}
								else
									return erro(logErro, "Falta ( apos nome da tabela referenciada");
							}
							else
								return erro(logErro, "Tabela referenciada nao encontrada");
						}
						
					}
					else
						return erro(logErro, "Esperado REFERENCES");
				}
				else
					return erro(logErro, "Falta ) apos campo FK");
			}
		}
		else
			return erro(logErro, "Campo FK nao encontrado na tabela atual");		
	}
	else
		return erro(logErro, "Nome do campo ausente");

	if(comando[*i].tipo == TOK_FECHA_PARENTESE)
	{
		(*i)++;
		if(comando[*i].tipo == TOK_VIRGULA)
			(*i)++;
	}
	else 
		return erro(logErro, "Falta )");
	
	return 1;
}

char interpretarCreate(TpBanco **banco, Token comando[], char logErro[])
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
								if(!interpretarCampo(tabelaAtual, comando, &i, logErro))
									return erro(logErro, "Erro ao interpretar campo");
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
											if(!criarPK(tabelaAtual, comando, &i, logErro))
												return erro(logErro, "Falha ao criar PK");
											if(comando[i].tipo == TOK_VIRGULA && comando[i+1].tipo == TOK_STRING)
											{
												if(!criarPK(tabelaAtual, comando, &i, logErro))
													return erro(logErro, "Falha ao criar PK");
											}
											if(comando[i].tipo == TOK_FECHA_PARENTESE)
											{
												i++;
												if(comando[i].tipo == TOK_VIRGULA)
													i++;	
												else if(comando[i].tipo != TOK_FECHA_PARENTESE)
													return erro(logErro, "Falta )");
												temPK=1;
											}
											else
												return erro(logErro, "Falta )");												
										}
									}
									else if(comando[i].tipo == TOK_PRIMARY && comando[i+1].tipo == TOK_KEY && temPK==1)
										return erro(logErro, "Duas PK!");
									else if(comando[i].tipo == TOK_FOREIGN && comando[i+1].tipo == TOK_KEY)
									{
										i+=2;
										if(comando[i].tipo == TOK_ABRE_PARENTESE)
										{
											if(!criarFK(tabelaAtual, comando, &*banco, &i, logErro))
												return erro(logErro, "Falha ao criar FK");
											
										}
									}
								}
							}
							else if(comando[i].tipo == TOK_CONSTRAINT && !temCampo)
								return erro(logErro, "Nao ha campos para ter constraint");
							else
								return erro(logErro, "Campo estruturado errado!");
						}
						i++;
						if(comando[i].tipo == TOK_PONTO_VIRGULA)
							return 1;
					}
					else
						return erro(logErro, "Sem (");
				}
				else
					return erro(logErro, "Nome da tabela ja existente!");				
			}
			else
				return erro(logErro, "Nome da tabela ausente!");
		}
		else
			return erro(logErro, "Banco nao criado!");
		
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
		return erro(logErro, "Erro ao criar banco");
	}
	else
		return erro(logErro, "Comando create nao reconhecido!");
		
}


char interpretarAlter(TpBanco **banco, Token comando[], char logErro[])
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
										if(!criarFK(tabelaFK, comando, &*banco, &i, logErro))
											return erro(logErro, "Falha ao criar FK");
										if(comando[i].tipo == TOK_FECHA_PARENTESE)
											i++;
										else
										{
											if(comando[i].tipo == TOK_PONTO_VIRGULA)
												return 1;
											else
												return erro(logErro, "Falta ;");
										}
									}
									else
										return erro(logErro, "Falta ( apos FOREIGN KEY");
								}
								else
									return erro(logErro, "Esperado FOREIGN KEY");
							}
							else
								return erro(logErro, "Nome da constraint ausente");
						}
						else
							return erro(logErro, "Esperado CONSTRAINT");
					}
					else
						return erro(logErro, "Esperado ADD");
				}
				else
					return erro(logErro, "Tabela nao encontrada");
			}
			else
				return erro(logErro, "Nome da tabela ausente!");
		}
		else
			return erro(logErro, "Banco nao criado!");
	}
	else
		return erro(logErro, "Comando alter nao reconhecido!");
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

char interpretarInsert(TpBanco **banco, Token comando[], char logErro[])
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
						return erro(logErro, "Sem colunas");
					while(comando[i].tipo != TOK_FECHA_PARENTESE)
					{
						if(comando[i].tipo == TOK_STRING)
						{
							campos[pos] = buscarCampo(tabela, comando, i);
							if(campos[pos]==NULL)
								return erro(logErro, "campo nao encontrado!");
							
							pos++;
							i++;
							if(comando[i].tipo == TOK_VIRGULA)
								i++;
							else if(comando[i].tipo != TOK_FECHA_PARENTESE)
								return erro(logErro, "Falta )");
						}
						else
							return erro(logErro, "Esperado nome de coluna!");
					}
					i++;
					if(comando[i].tipo == TOK_VALUES)
					{
						i++;						
						if(comando[i].tipo ==TOK_ABRE_PARENTESE)
						{
							i++;
							if(comando[i].tipo == TOK_FECHA_PARENTESE)
								return erro(logErro, "Sem valores");
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
											return erro(logErro, "Tipo de dado nao reconhecido");
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
											return erro(logErro, "Dado repetido na PK");
										if(campos[pos]->FK != NULL && !buscarDado(campos[pos]->FK, valor))
											return erro(logErro, "Dado nao encontrado na FK");
										criarDado(tabela->pCampos, campos[pos]->nome, valor);
									}
									else
										return erro(logErro, "Tipo de dado incompativel");
									pos++;
									i++;
									if(comando[i].tipo == TOK_VIRGULA)
										i++;
								}
								else
									return erro(logErro, "Esperado valor!");
							}
							return 1;
						}
						else
							return erro(logErro, "Falta (");
					}
					else
						return erro(logErro, "Esperado VALUES");
				}
				else
					return erro(logErro, "Falta (");
			}
			else
				return erro(logErro, "Tabela nao encontrada!");
		}
		else
			return erro(logErro, "Falta nome da tabela");
	}
	else
		return erro(logErro, "Esperado INTO");
}

union dados converterValor(char tipo, char palavra[])
{
    union dados valor;
    char copia[30];
    strcpy(copia, palavra);

    if (copia[0] == '\'' && copia[strlen(copia) - 1] == '\'')
        tirarApostrofo(copia);

    switch (tipo)
    {
        case 'I': valor.integer = atoi(copia); break;
        case 'N': valor.numeric = atof(copia); break;
        case 'D': strcpy(valor.date, copia); break;
        case 'C': valor.character1 = copia[0]; break;
        case 'T': strcpy(valor.character20, copia); break;
    }
    return valor;
}

char verificaJOIN(Token comando[],int  i)
{
	int j=0;
	while(comando[i].palavra[j]!='\0' && comando[i].palavra[j]!='.')
		j++;
	if(comando[i].palavra[j]=='\0')
		return 0;	
	return 1;
}

void separarTabelaCampo(char palavra[], char nomeTabela[], char nomeCampo[])
{
	int j = 0;
	while(palavra[j] != '.')
	{
		nomeTabela[j] = palavra[j];
		j++;
	}
	nomeTabela[j] = '\0';
	strcpy(nomeCampo, palavra + j + 1);
}

TpCampo *buscarCampoJoin(TpBanco *banco, char palavra[])
{
	char nomeTabela[20], nomeCampo[20];
	TpTabela *tabela;
	TpCampo *campo;

	separarTabelaCampo(palavra, nomeTabela, nomeCampo);

	tabela = banco->pTabelas;
	while(tabela != NULL && stricmp(tabela->nome, nomeTabela) != 0)
		tabela = tabela->prox;
	if(tabela == NULL)
		return NULL;

	campo = tabela->pCampos;
	while(campo != NULL && stricmp(campo->nome, nomeCampo) != 0)
		campo = campo->prox;
	return campo;
}

TpCondicao *InterpretarWHERE(TpBanco *banco, TpTabela *tabelas[], int numTabelas, Token comando[], int *i, char logErro[])
{
    TpCondicao *nova, *L = NULL, *aux;
	int t;
    (*i)++; 

    if(comando[*i].tipo != TOK_STRING && comando[*i].tipo != TOK_IDENTIFICADOR)
    {
        erro(logErro, "Esperado o nome de campo do WHERE");
        return NULL;
    }

    while(comando[*i].tipo != TOK_PONTO_VIRGULA)
    {
        nova = (TpCondicao*)malloc(sizeof(TpCondicao));
        nova->prox = NULL;
        nova->campoComparado = NULL; 
        if(L == NULL)
            L = nova;
        else
        {
            aux = L;
            while(aux->prox != NULL)
                aux = aux->prox;
            aux->prox = nova;
        }
        
        nova->join = verificaJOIN(comando, *i);
        
        // ADAPTAÇÃO: Se não for JOIN (não tem prefixo 'tabela.'), procura em todas as tabelas do FROM
        if(!nova->join)
        {
			t=0;
            nova->campo = buscarCampo(tabelas[t], comando, *i);
			while(nova->campo != NULL && t<numTabelas)
			{
				t++;
				nova->campo = buscarCampo(tabelas[t], comando, *i);
			}
        }
        else
        {
            // Se for JOIN (tabela.campo), a lógica atual usando o banco já resolve perfeitamente
            nova->campo = buscarCampoJoin(banco, comando[*i].palavra);
        }
        
        if(nova->campo == NULL)
        {
            erro(logErro, "Campo nao encontrado");
            free(nova);
            return NULL;
        }
        (*i)++;

        if(comando[*i].tipo == TOK_IGUAL || comando[*i].tipo == TOK_DIFERENTE || comando[*i].tipo == TOK_MENOR || comando[*i].tipo == TOK_MAIOR || comando[*i].tipo == TOK_MENOR_IGUAL || comando[*i].tipo == TOK_MAIOR_IGUAL)
        {
            nova->operador = comando[*i].tipo;
            (*i)++;
        
            if(verificaJOIN(comando, *i))
            {
                nova->campoComparado = buscarCampoJoin(banco, comando[*i].palavra);
                if(nova->campoComparado == NULL)
                {
                    erro(logErro, "Campo referenciado no JOIN nao encontrado");
                    free(nova);
                    return NULL;
                }
            }
            else
            {
                nova->campoComparado = NULL;
                nova->valor = converterValor(nova->campo->tipo, comando[*i].palavra);
            }
            (*i)++;
        }
        else if(comando[*i].tipo == TOK_BETWEEN)
        {
            nova->operador = comando[*i].tipo;
            (*i)++;
            nova->valor = converterValor(nova->campo->tipo, comando[*i].palavra);
            (*i)++;
            (*i)++;
            nova->valor2 = converterValor(nova->campo->tipo, comando[*i].palavra);
            (*i)++;
        }
        else
        {
            erro(logErro, "Sem operador");
            free(nova);
            return NULL;
        }

        if(comando[*i].tipo == TOK_AND || comando[*i].tipo == TOK_OR)
        {
            nova->conector = comando[*i].tipo;
            (*i)++;
        }
        else
            nova->conector = -1;
    }
    
    if (comando[*i].tipo != TOK_PONTO_VIRGULA){
        erro(logErro, "Falta ;");
        return NULL;
    }
    return L;
}


int posicaoDoCampo(TpTabela *tabela, TpCampo *alvo)
{
    TpCampo *campo = tabela->pCampos;
    int pos = 0;
    while (campo != NULL)
    {
        if (campo == alvo) 
			return pos;
        campo = campo->prox;
        pos++;
    }
    return -1;
}

int contarCampos(TpTabela *tabela)
{
    TpCampo *campo = tabela->pCampos;
    int n = 0;
    while (campo != NULL) {
	 n++; 
	 campo = campo->prox; 
	 }
    return n;
}


char avaliarCondicao(TpCondicao *cond, union dados valorLinha)
{
    switch (cond->campo->tipo)
    {
        case 'I':
            switch (cond->operador)
            {
                case TOK_IGUAL: return valorLinha.integer == cond->valor.integer;
                case TOK_DIFERENTE: return valorLinha.integer != cond->valor.integer;
                case TOK_MENOR: return valorLinha.integer <  cond->valor.integer;
                case TOK_MAIOR: return valorLinha.integer >  cond->valor.integer;
                case TOK_MENOR_IGUAL: return valorLinha.integer <= cond->valor.integer;
                case TOK_MAIOR_IGUAL: return valorLinha.integer >= cond->valor.integer;
                case TOK_BETWEEN: return valorLinha.integer >= cond->valor.integer && valorLinha.integer <= cond->valor2.integer;
            }
            break;

        case 'N':
            switch (cond->operador)
            {
                case TOK_IGUAL: return valorLinha.numeric == cond->valor.numeric;
                case TOK_DIFERENTE: return valorLinha.numeric != cond->valor.numeric;
                case TOK_MENOR: return valorLinha.numeric <  cond->valor.numeric;
                case TOK_MAIOR: return valorLinha.numeric >  cond->valor.numeric;
                case TOK_MENOR_IGUAL: return valorLinha.numeric <= cond->valor.numeric;
                case TOK_MAIOR_IGUAL: return valorLinha.numeric >= cond->valor.numeric;
                case TOK_BETWEEN: return valorLinha.numeric >= cond->valor.numeric && valorLinha.numeric <= cond->valor2.numeric;
            }
            break;

        case 'D':
        {
            int cmp = strcmp(valorLinha.date, cond->valor.date);
            switch (cond->operador)
            {
                case TOK_IGUAL: return cmp == 0;
                case TOK_DIFERENTE: return cmp != 0;
                case TOK_MENOR: return cmp <  0;
                case TOK_MAIOR: return cmp >  0;
                case TOK_MENOR_IGUAL: return cmp <= 0;
                case TOK_MAIOR_IGUAL: return cmp >= 0;
                case TOK_BETWEEN: return strcmp(valorLinha.date, cond->valor.date)  >= 0 && strcmp(valorLinha.date, cond->valor2.date) <= 0;
            }
            break;
        }

        case 'T':
        {
            int cmp = strcmp(valorLinha.character20, cond->valor.character20);
            switch (cond->operador)
            {
                case TOK_IGUAL: return cmp == 0;
                case TOK_DIFERENTE: return cmp != 0;
                case TOK_MENOR: return cmp <  0;
                case TOK_MAIOR: return cmp >  0;
                case TOK_MENOR_IGUAL: return cmp <= 0;
                case TOK_MAIOR_IGUAL: return cmp >= 0;
            }
            break;
        }

        case 'C':
            switch (cond->operador)
            {
                case TOK_IGUAL: return valorLinha.character1 == cond->valor.character1;
                case TOK_DIFERENTE: return valorLinha.character1 != cond->valor.character1;
            }
            break;
    }
    return 0;
}


char avaliarLinha(TpCondicao *condicoes, TpDado *valoresDaLinha[])
{
    TpCondicao *c = condicoes;
    int k = 0;
    char resultado = avaliarCondicao(c, valoresDaLinha[k]->valor);

    while (c->conector != -1)
    {
        char parcial;
        k++;
        parcial = avaliarCondicao(c->prox, valoresDaLinha[k]->valor);
        if (c->conector == TOK_AND)
            resultado = resultado && parcial;
        else
            resultado = resultado || parcial;
        c = c->prox;
    }
    return resultado;
}

void imprimirCondicoes(TpCondicao *condicoes)
{
	TpCondicao *c = condicoes;
	int n = 1;

	while(c != NULL)
	{
		printf("Condicao %d:\n", n);
		printf("  campo: %s\n", c->campo->nome);
		printf("  operador (token): %d\n", c->operador);
		printf("  join: %d\n", c->join);

		if(c->campoComparado != NULL)
			printf("  campo comparado: %s\n", c->campoComparado->nome);
		else
		{
			switch(c->campo->tipo)
			{
				case 'I': printf("  valor: %d\n", c->valor.integer); break;
				case 'N': printf("  valor: %f\n", c->valor.numeric); break;
				case 'D': printf("  valor: %s\n", c->valor.date); break;
				case 'C': printf("  valor: %c\n", c->valor.character1); break;
				case 'T': printf("  valor: %s\n", c->valor.character20); break;
			}
			if(c->operador == TOK_BETWEEN)
			{
				switch(c->campo->tipo)
				{
					case 'I': printf("  valor2: %d\n", c->valor2.integer); break;
					case 'N': printf("  valor2: %f\n", c->valor2.numeric); break;
					case 'D': printf("  valor2: %s\n", c->valor2.date); break;
					case 'T': printf("  valor2: %s\n", c->valor2.character20); break;
				}
			}
		}
		if(c->conector == TOK_AND)
			printf("  conector: %d (%s)\n", c->conector,"AND");
		else if(c->conector == TOK_OR)
			printf("  conector: %d (%s)\n", c->conector,"OR");
		else
			printf("  conector: %d (%s)\n", c->conector,"fim");

		c = c->prox;
		n++;
	}
}


int dadosSaoIguais(TpDado *dado1, TpDado *dado2, char tipoCampo)
{
    if (dado1 == NULL || dado2 == NULL) 
        return 0;

    switch (tipoCampo)
    {
        case 'I': return (dado1->valor.integer == dado2->valor.integer);
        case 'N': return (dado1->valor.numeric == dado2->valor.numeric);
        case 'C': return (dado1->valor.character1 == dado2->valor.character1);
        case 'D': return (strcmp(dado1->valor.date, dado2->valor.date) == 0);
        case 'T': return (strcmp(dado1->valor.character20, dado2->valor.character20) == 0);
        
        default: return 0;
    }
}
char ehReferenciadoEmOutraTabela(TpBanco *banco, TpTabela *tabela, TpDado **atualPorCampo)
{
    TpTabela *tabela2;
    TpCampo *campoPK, *campo2;
    TpDado *dadoAux;
    TpDado *dadoPK;
    int posPK = 0;

    campoPK = tabela->pCampos;
    while (campoPK != NULL && campoPK->PK != 'S')
    {
        posPK++;
        campoPK = campoPK->prox;
    }
    if (campoPK == NULL)
        return 0;

    dadoPK = atualPorCampo[posPK];
    if (dadoPK == NULL)
        return 0;

    tabela2 = banco->pTabelas;
    while (tabela2 != NULL)
    {
        if (tabela2 != tabela)
        {
            campo2 = tabela2->pCampos;
            while (campo2 != NULL)
            {
                if (campo2->FK == campoPK)
                {
                    dadoAux = campo2->pDados;
                    while (dadoAux != NULL)
                    {
                        if (dadosSaoIguais(dadoAux, dadoPK, campoPK->tipo))
                            return 1;
                        dadoAux = dadoAux->prox;
                    }
                }
                campo2 = campo2->prox;
            }
        }
        tabela2 = tabela2->prox;
    }
    return 0;
}

char interpretarDelete(TpBanco **banco, Token comando[], char logErro[])
{
    int i = 1, nCampos, k;
    TpTabela *tabela;
    TpCampo *campo;
    TpCondicao *condicoes = NULL;
    TpDado **atualPorCampo, **anteriorPorCampo, **proximoPorCampo;
    TpDado *valoresCondicoes[10];
    char bate;

    if(comando[i].tipo != TOK_FROM)
        return erro(logErro, "Sem o FROM");
    i++;

    if(comando[i].tipo != TOK_STRING && comando[i].tipo != TOK_IDENTIFICADOR)
        return erro(logErro, "Sem nome da tabela");

    tabela = buscarTabela(*banco, comando, i);
    if(tabela == NULL)
        return erro(logErro, "Tabela nao encontrada");
    i++;

    if(comando[i].tipo == TOK_WHERE)
    {
        condicoes = InterpretarWHERE(*banco, &tabela, 1, comando, &i, logErro);
        if(condicoes == NULL)
            return 0;
        imprimirCondicoes(condicoes);
    }

    if(comando[i].tipo != TOK_PONTO_VIRGULA)
        return erro(logErro, "Falta ;");

    nCampos = contarCampos(tabela);
    atualPorCampo = (TpDado**) malloc(nCampos * sizeof(TpDado*));
    anteriorPorCampo = (TpDado**) malloc(nCampos * sizeof(TpDado*));
    proximoPorCampo = (TpDado**) malloc(nCampos * sizeof(TpDado*));
    campo = tabela->pCampos;
    for(k = 0; k < nCampos; k++)
    {
        atualPorCampo[k] = campo->pDados;
        campo = campo->prox;
    }

    while(atualPorCampo[0] != NULL)
    {
        if(condicoes == NULL)
            bate = 1;
        else
        {
            TpCondicao *c = condicoes;
            int j = 0;
            while(c != NULL)
            {
                int pos = posicaoDoCampo(tabela, c->campo);
                valoresCondicoes[j++] = atualPorCampo[pos];
                c = c->prox;
            }
            bate = avaliarLinha(condicoes, valoresCondicoes);
        }
        if(bate)
        {
            if(ehReferenciadoEmOutraTabela(*banco, tabela, atualPorCampo))
            {
                free(atualPorCampo);
                free(anteriorPorCampo);
                free(proximoPorCampo);
                return erro(logErro, "Violacao de chave estrangeira: um ou mais registros estao em uso.");
            }
        }
        for(k = 0; k < nCampos; k++)
            atualPorCampo[k] = atualPorCampo[k]->prox;
    }
    campo = tabela->pCampos;
    for(k = 0; k < nCampos; k++)
    {
        atualPorCampo[k] = campo->pDados;
        anteriorPorCampo[k] = NULL;
        campo = campo->prox;
    }

    while(atualPorCampo[0] != NULL)
    {
        if(condicoes == NULL)
            bate = 1;
        else
        {
            TpCondicao *c = condicoes;
            int j = 0;
            while(c != NULL)
            {
                int pos = posicaoDoCampo(tabela, c->campo);
                valoresCondicoes[j++] = atualPorCampo[pos];
                c = c->prox;
            }
            bate = avaliarLinha(condicoes, valoresCondicoes);
        }

        for(k = 0; k < nCampos; k++)
            proximoPorCampo[k] = atualPorCampo[k]->prox;

        if(bate)
        {
            campo = tabela->pCampos;
            for(k = 0; k < nCampos; k++)
            {
                if(anteriorPorCampo[k] == NULL)
                    campo->pDados = atualPorCampo[k]->prox;
                else
                    anteriorPorCampo[k]->prox = atualPorCampo[k]->prox;

                free(atualPorCampo[k]);
                campo = campo->prox;
            }
        }
        else
        {
            for(k = 0; k < nCampos; k++)
                anteriorPorCampo[k] = atualPorCampo[k];
        }

        for(k = 0; k < nCampos; k++)
            atualPorCampo[k] = proximoPorCampo[k];
    }

    free(atualPorCampo);
    free(anteriorPorCampo);
    free(proximoPorCampo);
    return 1;
}


char interpretarUpdate(TpBanco **banco, Token comando[], char logErro[])
{
    int i = 1, nCampos, k, nSets = 0;
    TpTabela *tabela;
    TpCampo *campo;
    TpCampo *camposSet[15];
    union dados valoresSet[15];
    TpCondicao *condicoes = NULL;
    TpDado **atualPorCampo;
    TpDado *valoresCondicoes[10];
    char bate;

    if(comando[i].tipo != TOK_STRING && comando[i].tipo != TOK_IDENTIFICADOR)
        return erro(logErro, "Falta o nome da tabela");

    tabela = buscarTabela(*banco, comando, i);
    if(tabela == NULL)
        return erro(logErro, "Tabela nao encontrada");
    i++;

    if(comando[i].tipo != TOK_SET)
        return erro(logErro, "Falta o SET");
    i++;

    while(comando[i].tipo != TOK_WHERE && comando[i].tipo != TOK_PONTO_VIRGULA)
    {
        if(comando[i].tipo != TOK_STRING && comando[i].tipo != TOK_IDENTIFICADOR)
            return erro(logErro, "Esperado nome de coluna no SET");

        camposSet[nSets] = buscarCampo(tabela, comando, i);
        if(camposSet[nSets] == NULL)
            return erro(logErro, "Coluna do SET nao encontrada");
        i++;

        if(comando[i].tipo != TOK_IGUAL)
            return erro(logErro, "Esperado = no SET");
        i++;

        valoresSet[nSets] = converterValor(camposSet[nSets]->tipo, comando[i].palavra);
        nSets++;
        i++;

        if(comando[i].tipo == TOK_VIRGULA)
            i++;
    }

    if(comando[i].tipo == TOK_WHERE)
    {
        condicoes = InterpretarWHERE(*banco, &tabela, 1, comando, &i, logErro);
        if(condicoes == NULL)
            return 0;
    }

    if(comando[i].tipo != TOK_PONTO_VIRGULA)
        return erro(logErro, "Falta ;");

    nCampos = contarCampos(tabela);
    atualPorCampo = (TpDado**) malloc(nCampos * sizeof(TpDado*));

    campo = tabela->pCampos;
    for(k = 0; k < nCampos; k++)
    {
        atualPorCampo[k] = campo->pDados;
        campo = campo->prox;
    }

    while(atualPorCampo[0] != NULL)
    {
        if(condicoes == NULL)
            bate = 1;
        else
        {
            TpCondicao *c = condicoes;
            int j = 0;
            while(c != NULL)
            {
                int pos = posicaoDoCampo(tabela, c->campo);
                valoresCondicoes[j++] = atualPorCampo[pos];
                c = c->prox;
            }
            bate = avaliarLinha(condicoes, valoresCondicoes);
        }

        if(bate)
        {
        	for(k = 0; k < nSets; k++) 
		    {
		        if(camposSet[k]->PK == 'S')
		        {
		            if(ehReferenciadoEmOutraTabela(*banco, tabela, atualPorCampo))
		            {
		                free(atualPorCampo);
		                return erro(logErro, "Nao e possivel alterar a PK: ela esta sendo referenciada por uma FK.");
		            }
		        }
		    }
            for(k = 0; k < nSets; k++)
            {
                int pos = posicaoDoCampo(tabela, camposSet[k]);
                atualPorCampo[pos]->valor = valoresSet[k];
            }
        }

        for(k = 0; k < nCampos; k++)
            atualPorCampo[k] = atualPorCampo[k]->prox;
    }

    free(atualPorCampo);
    return 1;
}

char interpretarSelect(TpBanco **banco, Token comando[], char logErro[])
{
	int i=1, pos=0;
	TpTabela *tabelas[20];
	TpCondicao *condicoes;
	if(comando[i].palavra[0] == '*')
	{
		i++;
		if(comando[i].tipo == TOK_FROM)
		{
			i++;
			if(comando[i].tipo == TOK_STRING)
			{
				tabelas[pos] = buscarTabela(*banco, comando, i);
				if(tabelas[pos]!=NULL)
				{
					i++;
					while(comando[i].tipo != TOK_PONTO_VIRGULA)
					{
						if(comando[i].tipo == TOK_VIRGULA)
						{
							i++;
							while(comando[i].tipo != TOK_PONTO_VIRGULA && comando[i].tipo != TOK_WHERE)
							{
								if(comando[i].tipo == TOK_STRING)
								{
									tabelas[++pos] = buscarTabela(*banco, comando, i);
									if(tabelas[pos] != NULL)
										i++;
									else
										return erro (logErro, "Tabela nao encontrada");

									if(comando[i].tipo == TOK_VIRGULA)
										i++;
									else if(comando[i].tipo != TOK_PONTO_VIRGULA && comando[i].tipo != TOK_WHERE)
										return erro(logErro, "esperado ; ou WHERE");
								}
							}
							if(comando[i].tipo == TOK_WHERE)
							{
								condicoes = InterpretarWHERE(*banco, tabelas, pos+1, comando, &i, logErro);
								while(condicoes!=NULL)
								{
									printf("%d, %c, %s", condicoes->operador, condicoes->join, condicoes->campo->nome);
									condicoes = condicoes->prox;
								}
								
							}
						}
							
						else if(comando[i].tipo == TOK_WHERE)
						{
							
						}
					}
				}
				
			}
		}
	}

}

void interpretarComandos(TpBanco **banco, DescritorLista *descLista, char logErro[])
{
	Lista *comandoAtual = del(&*descLista);
	char certo = 1;
	while(comandoAtual!=NULL && certo == 1)
	{
		if(comandoAtual->comando[0].tipo == TOK_CREATE)
			certo = interpretarCreate(&*banco, comandoAtual->comando, logErro);
		else if(comandoAtual->comando[0].tipo == TOK_INSERT)
			certo =	interpretarInsert(&*banco, comandoAtual->comando, logErro);
		else if(comandoAtual->comando[0].tipo == TOK_SELECT)
			certo = interpretarSelect(&*banco, comandoAtual->comando, logErro);
		else if(comandoAtual->comando[0].tipo == TOK_UPDATE)
			certo = interpretarUpdate(&*banco, comandoAtual->comando, logErro);
		else if(comandoAtual->comando[0].tipo == TOK_DELETE)
			certo = interpretarDelete(&*banco, comandoAtual->comando, logErro);
		else if(comandoAtual->comando[0].tipo == TOK_ALTER)
			certo = interpretarAlter(&*banco, comandoAtual->comando, logErro);
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
