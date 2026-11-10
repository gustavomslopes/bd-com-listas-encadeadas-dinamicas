🗄️ Mini-SGBD: Interpretador SQL em C

Este repositório contém a implementação completa de um Sistema de Gerenciamento de Banco de Dados (SGBD) em memória, desenvolvido inteiramente na linguagem C.

O sistema possui um interpretador próprio capaz de ler, formatar, tokenizar e executar comandos SQL (DDL e DML), simulando tabelas e relações em memória através de estruturas de dados dinâmicas avançadas (listas encadeadas duplas, descritores e matrizes de ponteiros).

🚀 Funcionalidades

O SGBD suporta a execução interativa de scripts no terminal ou o carregamento em lote através de um arquivo .txt ou .sql.

Comandos SQL Suportados

DDL (Data Definition Language):

CREATE DATABASE

CREATE TABLE com suporte a múltiplas colunas de diferentes tipos.

Definição de PRIMARY KEY (PK) e FOREIGN KEY (FK).

ALTER TABLE ADD CONSTRAINT para criação posterior de chaves estrangeiras com a cláusula REFERENCES.

DML (Data Manipulation Language):

INSERT INTO ... VALUES com verificação de tipagem e integridade referencial.

SELECT com suporte a seleção específica de colunas e uso de *.

UPDATE e DELETE com cláusula WHERE estruturada.

Filtros e Lógica (WHERE):

Suporte aos conectores lógicos AND e OR.

Operadores relacionais (=, <>, >, <, >=, <=) e BETWEEN.

Simulação de JOINs implícitos ao relacionar colunas de tabelas diferentes.

Tipagem de Dados em Memória

Para otimizar o uso da memória na linguagem C, o sistema armazena os dados polimórficos utilizando a estrutura union, suportando os seguintes tipos:

INT / INTEGER

FLOAT / DOUBLE / NUMERIC

CHAR(1) / CHAR(20) / CHARACTER

DATE (Formato YYYY-MM-DD)

🛠️ Arquitetura do Interpretador

O coração do SGBD é o seu parser SQL:

Limpeza e Formatação: A entrada de texto crua é limpa, removendo quebras de linha e tabulações extras.

Tokenização Léxica: As palavras do script são analisadas e convertidas em tokens numéricos (ex: CREATE vira TOK_CREATE = 0, SELECT vira TOK_SELECT = 7).

Árvore de Execução: Uma estrutura DescritorLista atua como uma fila de instruções, separando comandos pelo terminador ;. O sistema então roteia cada comando para a sua função de manipulação correspondente no TADBD.

📂 Estrutura de Arquivos

BancoDeDados.c: Arquivo principal (Main). Gerencia a interface interativa do usuário, interage com o interpretador e imprime a grade visual das tabelas.

Interpretador.h: Núcleo lógico. Contém todo o processamento de texto, tokenização léxica e validação das regras SQL antes de invocar a manipulação de dados.

TADBD.h: Tipos Abstratos de Dados. Define as structs e funções de criação/deleção para a hierarquia do banco (TpBanco -> TpTabela -> TpCampo -> TpDado).

TADLISTA.h: Define as estruturas da fila descritora responsável por organizar o fluxo de tokens dos comandos SQL.

script.txt: Arquivo contendo um script SQL de teste pronto, modelando o banco de dados de uma oficina mecânica.

⚠️ Dependência: Biblioteca conio2.h

Este projeto utiliza a biblioteca conio2.h para posicionar o cursor no console (através da função gotoxy) e montar a grade visual das tabelas. Como ela não é uma biblioteca padrão do C, compiladores modernos como o MinGW (frequentemente usado com o VS Code) acusarão erro de arquivo não encontrado caso não estejam configurados.

Como configurar no MinGW (Windows):

Baixe os arquivos da biblioteca conio2 (geralmente compostos por conio2.h e libconio.a).

Copie o arquivo conio2.h para a pasta include do seu compilador (ex: C:\MinGW\include).

Copie o arquivo libconio.a para a pasta lib do seu compilador (ex: C:\MinGW\lib).

(Opcional, mas recomendado) Se for fornecer esses arquivos dentro do próprio repositório, coloque-os na mesma pasta do projeto e adapte o comando de compilação.

⚙️ Como Compilar e Executar

1. Clone o repositório:

git clone https://github.com/gustavomslopes/seu-repositorio.git
cd seu-repositorio


2. Compilação:
Após configurar a conio2.h, abra o terminal no VS Code (ou CMD) e execute:

gcc BancoDeDados.c -o SGBD -lconio


(A flag -lconio indica ao compilador para linkar a biblioteca conio2).

3. Execução:

./SGBD


No menu inicial do sistema, digite A para importar o arquivo de demonstração e, em seguida, digite script.txt. O SGBD executará todas as querys e mostrará as tabelas geradas no terminal.
