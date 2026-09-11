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

char isEmpty(DescritorLista descritor)
{
	return descritor.inicio == NULL;
}

void add(DescritorLista *descritor, Token info[], int TL)
{
    Lista *novo = (Lista *) malloc(sizeof(Lista));
    int i;
    for (i = 0; i < TL; i++) {
        novo->comando[i] = info[i];
    }
    novo->prox = NULL;

    if (isEmpty(*descritor))
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

Lista *del(DescritorLista *descritor)
{
	if(isEmpty(*descritor))
		return NULL;
	Lista *aux = (*descritor).inicio;
	(*descritor).inicio = (*descritor).inicio->prox;
	if(descritor->inicio == NULL)
		descritor->fim = NULL;
	return aux;
}




