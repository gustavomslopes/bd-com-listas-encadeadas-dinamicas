union dados
{
	int integer;
	float numeric;
	char date[10];
	char character1;
	char character20[20];
};

struct dado
{
	union dados valor;
	struct dado *prox;
};
typedef struct dado TpDado;

struct campo
{
	TpDado *pAtual;
	char nome[20];
	char tipo;
	char PK;
	struct campo *FK;
	TpDado *pDados;
	struct campo *prox;
};
typedef struct campo TpCampo;

struct tabela
{
	struct tabela *ant;
	char nome[20];
	TpCampo *pCampos;
	struct tabela *prox;
	
};
typedef struct tabela TpTabela;

struct banco
{
	char nome[20];
	TpTabela *pTabelas;
	
};
typedef struct banco TpBanco;


void criarBanco(TpBanco **pontDB, char nome[])
{
	*pontDB = (TpBanco*)malloc(sizeof(TpBanco));
	strcpy((*pontDB)->nome,nome);
	(*pontDB)->pTabelas = NULL;
}

void caixaTabela(TpTabela **tabela, char nome[])
{
	*tabela = (TpTabela*)malloc(sizeof(TpTabela));
	(*tabela)->ant=NULL;
	strcpy((*tabela)->nome,nome);
	(*tabela)->pCampos=NULL;
	(*tabela)->prox=NULL;
	
}

TpTabela * criarTabela(TpTabela **pTabelas, char nome[])
{
	TpTabela *novaTabela;
	caixaTabela(&novaTabela, nome);
	
	if(*pTabelas==NULL)
	{
		*pTabelas = novaTabela;
		return novaTabela;
	}
	TpTabela *aux = *pTabelas;
	while(aux->prox!=NULL && strcmp(aux->nome,nome)!=0)
		aux = aux->prox;
	if(!strcmp(aux->nome,nome)==0)
	{
		aux->prox = novaTabela;
		novaTabela->ant = aux;
		
		return novaTabela;
	}	
	free(novaTabela);
	return NULL;
}

void caixaCampo(TpCampo **campo, char nome[],char tipo)
{
	*campo = (TpCampo*)malloc(sizeof(TpCampo));
	(*campo)->prox=NULL;
	strcpy((*campo)->nome,nome);
	(*campo)->tipo = tipo;
	(*campo)->PK = 'N';
	(*campo)->FK = NULL;
	(*campo)->pDados=NULL;
	(*campo)->pAtual=NULL;
}

char criarCampo(TpCampo **pCampos, char nome[], char tipo)
{
	TpCampo *novoCampo;
	caixaCampo(&novoCampo, nome, tipo);
	if(*pCampos==NULL)
	{
		*pCampos = novoCampo;
		return 1;
	}
	TpCampo *aux = *pCampos;
	while(aux->prox!=NULL && strcmp(aux->nome,nome)!=0)
		aux = aux->prox;
	if(strcmp(aux->nome,nome)!=0)
	{
		aux->prox = novoCampo;
		
		return 1;
	}	
	free(novoCampo);
	return 0;
}

//void apagarCampo(TpCampo **pCampos)
//{
//	TpCampo *aux = *pCampos;
//	while(aux->prox->prox!=NULL)
//		aux = aux->prox;
//	free(aux->prox);
//	aux->prox = NULL;
//}

// union dado converterValor(char tipo, char *texto)
// {
//     union dado valor;

//     switch (tipo)
//     {
//         case 'I':
//             valor.integer.valorI = atoi(texto);
//             valor.integer.prox = NULL;
//             break;

//         case 'N':
//             valor.numeric.valorN = atof(texto);
//             valor.numeric.prox = NULL;
//             break;

//         case 'D':
//             strcpy(valor.date.valorD, texto);
//             valor.date.prox = NULL;
//             break;

//         case 'C':
//             valor.character1.valorC = texto[0];
//             valor.character1.prox = NULL;
//             break;

//         case 'T':
//             strcpy(valor.character20.valorT, texto);
//             valor.character20.prox = NULL;
//             break;
//     }

//     return valor;
// }

char criarDado(TpCampo *pCampos,char nome[], union dados Dado)
{
	TpDado *novo;
	while(pCampos!=NULL && strcmp(pCampos->nome,nome)!=0)
		pCampos=pCampos->prox;
	if(pCampos!=NULL)
	{
		novo = (TpDado*) malloc(sizeof(TpDado));
	    novo -> prox = NULL;
		if (pCampos->pDados == NULL)
			pCampos->pDados = novo;
			
		else
		{
			pCampos->pAtual = pCampos->pDados;
			while (pCampos->pAtual->prox != NULL)
				pCampos->pAtual = pCampos->pAtual->prox;
			pCampos->pAtual->prox = novo;
		}
	    switch (pCampos->tipo)
	    {
	        case 'I':
	            novo->valor.integer = Dado.integer;
	            break;
	
	        case 'N':
	            novo->valor.numeric = Dado.numeric;
	            break;
	
	        case 'D':
	            strcpy(novo->valor.date, Dado.date);
	            break;
	
	        case 'C':
	            novo->valor.character1 = Dado.character1;
	            break;
	
	        case 'T':
	            strcpy(novo->valor.character20, Dado.character20);
	            break;
	    }
	
	    return 1;
	}
	return 0;
}



