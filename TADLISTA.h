struct token
{
	char palavra[20];
	int tipo;
}; typedef struct token Token;

struct lista
{
	Token comando[100];
	struct lista *prox;	
};
typedef struct lista Lista;

struct descritorlista
{
	Lista *inicio;
	Lista *fim;
};
typedef struct descritorlista DescritorLista;

void init(DescritorLista *descritor)
{
	(*descritor).inicio = NULL;
	(*descritor).fim = NULL;
}

void add(DescritorLista *descritor, Token info[], int TL)
{
    Lista *novo = (Lista *) malloc(sizeof(Lista));
    int i;
    for (i = 0; i < TL; i++) {
        novo->comando[i] = info[i];
    }
    novo->prox = NULL;

    if ((*descritor).inicio == NULL)
	{
        (*descritor).inicio = novo;
        (*descritor).fim = novo;
    } 
	else
	{
        (*descritor).fim->prox = novo;
        (*descritor).fim = novo;
    }
}




