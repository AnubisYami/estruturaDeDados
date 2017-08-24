	#include <stdio.h>
	#include <stdlib.h>
	#include <conio.h>
	#include <string.h>
	#include <iostream>
	#include <locale.h>
	#include <ctype.h>

	using namespace std;

	const int TAM = 50;
	char palavra[TAM];
    char palavraAux[TAM];  //Vari�vel auxiliar para guardar a palavra mais usada
    int contRepeticao; //Vari�vel para controle de quantas vezes a palavra foi inserida
    char nomeArquivoAbrir[TAM];  //Nome do arquivo para ser aberto

	struct no {
	    char dado[TAM];
	    int contador;
	    struct no *esq;
	    struct no *dir;
	};

	struct no *raiz = NULL;

	void menuOpcoes();
	void msgmCarregarArquivo();
	void msgmCarregarArquivo2();
	void msgmFailArquivo();
	void nomeArquivo();

	void insereArvore(char palavra[]){
		struct no *atual;
	    struct no *anterior;
	    struct no *aux;

	    aux = new(struct no);
	    strcpy(aux -> dado, palavra);
	    aux -> esq = NULL;
	    aux -> dir = NULL;
	    aux -> contador = 1;

	    if (raiz == NULL){
	        raiz = aux;
	        contRepeticao = raiz -> contador; //Vari�vel contador inicializa com a quantidade de
	        return;                           // palavras inseridas na raiz
	    }

	    atual = raiz;

        cout << "  Aguarde, as palavras est�o sendo inseridas na �rvore\n";
        system("cls");

	    while(atual != NULL){
	        anterior = atual;
	        if(strcmp(atual -> dado,palavra) == 0) {
                atual -> contador = atual -> contador + 1;
                cout << "  Aguarde, as palavras est�o sendo inseridas na �rvore.\n";
                system("cls");
//	            cout << "  " << endl << "  A palavra \"" << atual -> dado //Mostra se existem palavras sendo inseridas
//	            << "\" foi inserida " << atual -> contador << " vezes na �rvore." << endl; //mais de uma vez na �rvore
	            delete(aux);
	            return;
	        }
	        if(strcmp(palavra,atual -> dado) < 0) {
                cout << "  Aguarde, as palavras est�o sendo inseridas na �rvore....\n";
                system("cls");
                atual = atual -> esq;
	        }else {
                cout << "  Aguarde, as palavras est�o sendo inseridas na �rvore.....\n";
                system("cls");
	            atual = atual -> dir;
	        }
	    }
	    if (strcmp(anterior -> dado,palavra) > 0) {
            cout << "  Aguarde, as palavras est�o sendo inseridas na �rvore...\n";
            system("cls");
            anterior -> esq = aux;
        }
	    else anterior -> dir = aux;
            cout << "  Aguarde, as palavras est�o sendo inseridas na �rvore..\n";
            system("cls");

	}

	void busca (char palavra[]){  //Busca por uma palavra na �rvore
	    struct no *atual;
	    atual = raiz;
	    while (atual != NULL){
	        if(strcmp(palavra, atual -> dado) == 0){
	        	if(atual -> contador == 1) {
                    cout << "  Palavra \"" << palavra << "\" foi encontrada " << atual -> contador << " vez." << endl;
				}
				if(atual -> contador > 1) {
                    cout << "  Palavra \"" << palavra << "\" foi encontrada " << atual -> contador << " vezes." << endl;
				}
	            return;
	        }
	        if(strcmp(palavra,atual->dado) < 0) {
                atual = atual -> esq;
	        } else {
                atual = atual -> dir;
	        }
	    }
	    cout << "  A palavra \"" << palavra << "\" n�o foi encontrada na �rvore." << endl;
	}

	void emOrdem (struct no *atual){ //Ordena a impress�o da �rvore
	    if(atual != NULL){
	        emOrdem(atual -> esq);
	        if(atual -> contador >= contRepeticao) { //Recebe a qntd de repeti��es da palavra
                contRepeticao = atual -> contador;   //cuja maior qntd for encontrada
	        }
            printf("  | %27s | %3d |\n", atual -> dado, atual -> contador);
            printf("  -------------------------------------\n");
	        emOrdem(atual -> dir);
	    }
	}

	void maisRepetido (struct no *atual) {
        if(atual != NULL) {
            maisRepetido(atual -> esq);
			if (contRepeticao == atual -> contador) { //Quando o contador encontra a palavra mais repetida
                strcpy(palavraAux, atual -> dado);    //ele printa qual � a palavra
                if(contRepeticao == 1) {
				cout << "  - Palavra mais encontrada na �rvore  \n  - foi \"" << palavraAux << "\"" << endl;
				cout << "  - encontrada " << contRepeticao << " vez" << endl;
                } else {
				cout << "  - Palavra mais encontrada na �rvore  \n  - foi \"" << palavraAux << "\"" << endl;
				cout << "  - encontrada " << contRepeticao << " vezes" << endl;
                }
			}
            maisRepetido(atual -> dir);
		}
	}

	void toLower(char palavra[]) {              //Transforma todas as palavras inseridas em min�sculas
		for(int i=0; palavra[i] != '\0'; i++) { //e altera na vari�vel global palavra[]
			palavra[i] = tolower(palavra[i]);
		}
	}

	void inserePalavra() {  //Insere palavras na �rvore
        printf("  -------------------------------------\n");
        printf("  -         INSERIR NA �RVORE         -\n");
        printf("  -------------------------------------\n");
	   	printf("  - Insira uma palavra:               -\n");
        printf("  -------------------------------------\n");
	   	printf("  - ");
		cin >> palavra;
		fflush(stdin);      //Se o usuario inserir uma palavra ser� chamada a fun��o toLower()
		toLower(palavra);   //sendo passada como parametro a palavra inserida pelo usu�rio
		system("cls");
        cout << "  \"" << palavra << "\" inserido com sucesso na �rvore!" << endl;
	}

    void leArquivo() { //Faz a leitura do arquivo
    	FILE *fp;
    	char palavraTemp[TAM], c; //Vari�vel para armazenar temporariamente a palavra lida no arquivo
	    fp = fopen(nomeArquivoAbrir,"r");  //Abre o arquivo com o nome padr�o "arquivo"
	    if (fp == NULL){ //Testa se foi poss�vel abrir o arquivo para leitura
//	        cout << "  Erro! N�o foi poss�vel abrir o arquivo." << endl;
	        return;
	    }

        int cont = 0;  //Contador auxiliar

        while(!feof(fp)){
            c = getc(fp);   // Le um caractere por caractere no arquivo
            if(!isalpha(c)){      //Verifica se o caractere � v�lido ou se � algum sinal de pontua��o
                palavraTemp[cont] = '\0'; //Se encontrar algum sinal de pontua��o ou ponto na leitura
                if(cont > 0) {            //ele insere um final na string, assim separando as palavras
                    for(int i=0; palavraTemp[i] != '\0'; i++) { //faz a copia do que foi armazenado na vari�vel
                        strcpy(palavra, palavraTemp);           //tempor�ria para a vari�vel global
                    }
                    toLower(palavra);   //transforma a palavra lida em min�scula
                    insereArvore(palavra);  //insere a palavra que foi lida e transformada em min�scula na �rvore
                }
                cont = 0;  //Contador zera pois foi formada uma palavra
            } else {
                palavraTemp[cont] = c;  //Caso n�o seja encontrado sinal pontua��o ou espa�o
                cont++;                 //cada caractere � armazenado na vari�vel tempor�ria
            }                           //e o contador � incrementado
        }
		fclose(fp);  //Fecha o arquivo
	}

	void nomeArquivo() {
        printf("  -------------------------------------\n");
	    printf("  - Insira o nome do arquivo que      -\n");
	    printf("  - deseja abrir seguido de \".txt\"    -\n");
	    printf("  -------------------------------------\n");
	    printf("  - O arquivo deve estar no mesmo     -\n");
	    printf("  - diret�rio do projeto              -\n");
        printf("  -------------------------------------\n");
        printf("  - ");
    	cin >> nomeArquivoAbrir;
    	fflush(stdin);
    	system("cls");
	}

	bool verificaArquivo() {
        FILE *fp;
    	char palavraTemp[TAM], c; //Vari�vel para armazenar temporariamente a palavra lida no arquivo
	    fp = fopen(nomeArquivoAbrir,"r");  //Abre o arquivo com o nome padr�o "arquivo"
	    if (fp == NULL){ //Testa se foi poss�vel abrir o arquivo para leitura
	       return false;
	    } else {
            return true;
	    }
	}

	void msgmFailArquivo() {
        char esc;
        printf("  -------------------------------------\n");
        printf("  -                ERRO               -\n");
        printf("  -------------------------------------\n");
	    printf("  - Parece que n�o existe nenhum      -\n");
	    printf("  - arquivo salvo com esse nome no    -\n");
	    printf("  - diret�rio                         -\n");
	    printf("  -------------------------------------\n");
        printf("  - Pressione qualquer tecla para     -\n");
        printf("  - continuar                         -\n");
        printf("  -------------------------------------\n  ");
        esc = getche();
        system("cls");
        return;
	}

	void msgmCarregarArquivo2() {
        char esc;
        printf("  -------------------------------------\n");
	    printf("  - O arquivo \"arquivo.txt\" salvo     -\n");
	    printf("  - na pasta padr�o do projeto ser�   -\n");
	    printf("  - aberto. Deseja continuar?         -\n");
	    printf("  -------------------------------------\n");
        printf("  - Digite S (sim) ou N (n�o):        -\n");
        printf("  -------------------------------------\n  ");
        esc = getche();
        fflush(stdin);
        system("cls");
        switch (esc) {
        case 'S':
//            leArquivo();
            break;
        case 's':
//            leArquivo();
            break;
        case 'N':
            msgmCarregarArquivo();
            break;
        case 'n':
            msgmCarregarArquivo();
            break;
        default:
            printf("  -------------------------------------\n");
	        printf("  - Op��o incorreta. Tente novamente! -\n");
	        msgmCarregarArquivo2();
        }
	}

	void msgmCarregarArquivo() {
	    char esc;
        printf("  -------------------------------------\n");
	    printf("  - Deseja carregar arquivo de texto  -\n");
	    printf("  - para inser��o na �rvore?          -\n");
	    printf("  -------------------------------------\n");
        printf("  - Digite: S (sim) ou N (n�o):       -\n");
        printf("  -------------------------------------\n  ");
        esc = getche();
        fflush(stdin);
        system("cls");
        switch (esc) {
        case 'S':
            nomeArquivo();
            if(verificaArquivo()) {
                leArquivo();
            } else {
                msgmFailArquivo();
            }
            break;
        case 's':
            nomeArquivo();
            if(verificaArquivo()) {
                leArquivo();
            } else {
                msgmFailArquivo();
            }
            break;
        case 'N':
            menuOpcoes();
            break;
        case 'n':
            menuOpcoes();
            break;
        default:
            printf("  -------------------------------------\n");
	        printf("  - Op��o incorreta. Tente novamente! -\n");
	        msgmCarregarArquivo();
        }
	}

	bool verificaVazio() {
	    if(raiz == NULL) {
            return true;
	    } else {
            return false;
	    }
	}

    void menuOpcoes () {
	    char esc;
	    printf("  -------------------------------------\n");
	    printf("  -           �RVORE BIN�RIA          -\n");
	    printf("  -------------------------------------\n");
	    printf("  -  1  |  Imprimir a arvore          -\n");
        printf("  -------------------------------------\n");
   	    printf("  -  2  |  Buscar na arvore           -\n");
	    printf("  -------------------------------------\n");
   	    printf("  -  3  |  Inserir manualmente        -\n");
	    printf("  -------------------------------------\n");
        printf("  -  4  |  Carregar de um arquivo     -\n");
	    printf("  -------------------------------------\n");
	    printf("  -  0  |  Sair                       -\n");
   	    printf("  -------------------------------------\n");
   	    printf("  - Valor: ");

   	    //Com a utiliza��o da biblioteca <conio.h> (Sem enter)
   	    esc = getche();

   	    //Com a utiliza��o da biblioteca padr�o (Com enter)
	    //scanf("%c", &esc);

	    fflush(stdin);
	    //system("clear"); (Para linux)
	    system("cls");
	    switch (esc) {
	    case '1':
	        if(!verificaVazio()) {
                printf("  -------------------------------------\n");
                printf("  |           PALAVRA           | QTD |\n");
                printf("  -------------------------------------\n");
                emOrdem(raiz);
                maisRepetido(raiz);
	        } else {
            printf("  -------------------------------------\n");
	        printf("  -           �RVORE VAZIA!           -\n");
	        }
	        break;
        case '2':
            if(!verificaVazio()) {
                inserePalavra();
                busca(palavra);
            } else {
                printf("  -------------------------------------\n");
                printf("  -           �RVORE VAZIA!           -\n");
            }
	        break;
        case '3':
	    	inserePalavra();
	    	insereArvore(palavra);
            break;
        case '4':
            msgmCarregarArquivo();
            break;
        case '0':
            return;
            break;
	    default:
            printf("  -------------------------------------\n");
	        printf("  - Op��o incorreta. Tente novamente! -\n");
	        menuOpcoes();
	    }
	    //Faz um loop do menu at� o usu�rio sair
	    menuOpcoes();
	}

	int main(){
		setlocale(LC_ALL, "Portuguese");
	    menuOpcoes();
		return 0;
	}
