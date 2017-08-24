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

	struct no {
	    char dado[TAM];
	    int contador;
	    struct no *esq;
	    struct no *dir;
	};

	struct no *raiz = NULL;

	void insereArvore(char palavra[]){ //Inserir palavra na �rvore
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

	    while(atual != NULL){
	        anterior = atual;
	        if(strcmp(atual -> dado,palavra) == 0) {
                atual -> contador = atual -> contador + 1;
//	            cout << "  " << endl << "  A palavra \"" << atual -> dado //Mostra se existem palavras sendo inseridas
//	            << "\" foi inserida " << atual -> contador << " vezes na �rvore." << endl; //mais de uma vez na �rvore
	            delete(aux);
	            return;
	        }
	        if(strcmp(palavra,atual -> dado) < 0) {
                atual = atual -> esq;
	        }else {
	            atual = atual -> dir;
	        }
	    }
	    if (strcmp(anterior -> dado,palavra) > 0) {
            anterior -> esq = aux;
        }
	    else anterior -> dir = aux; {
            cout << "  Aguarde, as palavras est�o sendo inseridas na �rvore";
            system("cls");
	    }
	}

	void emOrdem (struct no *atual){ //Ordena a impress�o da �rvore
	    if(atual != NULL){
	        emOrdem(atual -> esq);
	        if(atual -> contador >= contRepeticao) { //Recebe a qntd de repeti��es da palavra
                contRepeticao = atual -> contador;   //cuja maior qntd for encontrada
	        }
            printf("  | %23s | %3d |\n", atual -> dado, atual -> contador);
            printf("  ---------------------------------\n");
	        emOrdem(atual -> dir);
	    }
	}

	void maisRepetido (struct no *atual) {
        if(atual != NULL) {
            maisRepetido(atual -> esq);
			if (contRepeticao == atual -> contador) { //Quando o contador encontra a palavra mais repetida
                strcpy(palavraAux, atual -> dado);    //ele printa qual � a palavra
				cout << "  Palavra mais encontrada na �rvore foi \"" << palavraAux << "\", encontrada "
                << contRepeticao << " vezes" << endl;
			}
            maisRepetido(atual -> dir);
		}
	}

	void toLower(char palavra[]) {              //Transforma todas as palavras inseridas em min�sculas
		for(int i=0; palavra[i] != '\0'; i++) { //e altera na vari�vel global palavra[]
			palavra[i] = tolower(palavra[i]);
		}
	}

    void leArquivo() { //Faz a leitura do arquivo
    	FILE *fp;
    	char palavraTemp[TAM], c; //Vari�vel para armazenar temporariamente a palavra lida no arquivo
	    fp = fopen("arquivo.txt","r");  //Abre o arquivo com o nome padr�o "arquivo"
	    if (fp == NULL){ //Testa se foi poss�vel abrir o arquivo para leitura
	        cout << "  Erro! N�o foi poss�vel abrir o arquivo." << endl;
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

	int main(){
		setlocale(LC_ALL, "Portuguese");
    	leArquivo();
    	emOrdem(raiz);
    	maisRepetido(raiz);
		return 0;
	}
