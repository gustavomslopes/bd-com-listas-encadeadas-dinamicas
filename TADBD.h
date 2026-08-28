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
	TpValorI uvalorI;
	TpValorN uvalorN;
	TpValorD uvalorD;
	TpValorC uvalorC;
	TpValorT uvalorT;
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
