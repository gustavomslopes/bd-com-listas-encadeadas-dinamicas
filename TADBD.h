struct valori
{
	int valorI;
	struct valori *prox;
};
typedef struct valori TpValorI;

struct valorn
{
	float valorN;
	struct valorn *prox;
};
typedef struct valorn TpValorN;

struct valord
{
	char valorD[10];
	struct valord *prox;
};
typedef struct valord TpValorD;

struct valorc
{
	char valorC;
	struct valorc *prox;
};
typedef struct valorc TpValorC;

struct valort
{
	char valorT[20];
	struct valort *prox;
};
typedef struct valort TpValorT;

union dado
{
	TpValorI integer;
	TpValorN numeric;
	TpValorD date;
	TpValorC character1;
	TpValorT character20;
};

struct campo
{
	union dado *pAtual;
	char nome[20];
	char tipo;
	char PK;
	struct campo *FK;
	union dado *pDados;
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
	strcpy(*pontDB->nome,nome);
	*pontDB->pTabelas = NULL;
}

void caixaTabela(TpTabela **tabela, char nome[])
{
	*tabela = (TpTabela*)malloc(sizeof(TpTabela));
	*tabela->ant=NULL;
	strcpy(*tabela->nome,nome);
	*tabela->pCampos=NULL
	*tabela->prox=NULL;
	
}

char criarTabela(TpTabela **pTabelas, char nome[])
{
	TpTabela *novaTabela;
	novaTabela = caixaTabela(&novaTabela, nome);
	
	if(*pTabelas==NULL)
	{
		*pTabelas = novaTabela;
		return 1;
	}
	TpTabela *aux = *pTabelas;
	while(aux->prox!=NULL && strcmp(aux->nome,nome)!=0)
		aux = aux->prox;
	if(!strcmp(aux->nome,nome)==0)
	{
		aux->prox = novaTabela;
		novaTabela->ant = aux;
		
		return 1;
	}	
	
	return 0;
}

void caixaCampo(TpCampo **campo, char nome[],char tipo)
{
	*campo = (TpCampo*)malloc(sizeof(TpCampo));
	*campo->prox=NULL;
	strcpy(*campo->nome,nome);
	*campo->tipo = tipo;
	*campo->PK = 'N';
	*campo->FK = NULL;
	*campo->pDados=NULL;
	*campo->pAtual=NULL;
}

char criarCampo(TpCampo **pCampos, char nome[], char tipo, char isNULL)
{
	TpCampo *novoCampo;
	novoCampo = caixaCampo(&novoCampo, nome, tipo);
	if(*pCampos==NULL)
	{
		*pCampos = novoCampo;
		return 1;
	}
	TpCampo *aux = *pCampo;
	while(aux->prox!=NULL && strcmp(aux->nome,nome)!=0)
		aux = aux->prox;
	if(!strcmp(aux->nome,nome)==0)
	{
		aux->prox = novoCampo;
		
		return 1;
	}	
	
	return 0;
}



