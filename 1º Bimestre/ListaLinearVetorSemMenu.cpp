    #include <iostream>
    #include <stdio.h>
    #include <stdlib.h>
    #include <ctime>
    #include <clocale>
    #include <ctime>

    //Constantes globais
    const int TAM = 10;

    //Vari�veis globais
    int lista[TAM];
    int tamanho = 0;

    using namespace std;

    //Procedimentos principais
    void insereLista(int valor);
    void removeLista(int posicao);
    void recuperaLista(int posicao);
    void buscaLista(int valor);
    void imprime();

    int main () {
        setlocale(LC_ALL,"");
		cout << "  Lista linear com vetor" << endl;
        cout << "  O vetor est� definido em " << TAM << " posi��es" << endl;
		insereLista(5);  //Insere um valor na lista
		insereLista(8);
    	imprime();  //Imprime lista
   	    recuperaLista(1);  //Verifica o valor em determinada posi��o
    	buscaLista(5);  //Busca se o valor existe na lista 
   	    removeLista(1);  //Remove um valor na lista
    	imprime();
        cout << "  Eduardo Soares - 16016923\n";
        cout << "  Matheus Gomes  - 16267723\n";
        return 0;
    }

    void insereLista(int valor) {
        int i;
        //Verifica se a lista est� cheia.
          if(tamanho == TAM) {
            cout << "  N�mero n�o p�de ser inserido na lista. Lista Cheia!\n";
            return;
        }
        for(i = tamanho; i > 0 && valor < lista[i-1]; i--) {
            lista[i] = lista [i-1];
        }
        lista[i] = valor;
        tamanho++;
        cout << "  N�mero " << valor << " inserido com sucesso!\n";
    }

    void removeLista(int posicao) {
        //Verifica se a lista est� vazia.
        if(tamanho <= 0) {
            printf("  Lista Vazia!\n");
            return;
        }
        if(posicao <= 0 || posicao > tamanho) {
            cout << "  Posi��o inv�lida!\n";
            return;
        }
        for(int i = posicao; i < tamanho; i++) {
            lista[i-1]=lista[i];
        }
        tamanho--;
        for(int i = tamanho; i <= TAM-1; i++) {
            lista[i] = 0;
        }
        cout << "  N�mero removido com sucesso!\n";
    }

    void buscaLista(int valor) {
        int posicao, qntd = 0;
        for(int i = 0; i < TAM; i ++){
            if(lista[i] == valor){
                posicao = i;
                qntd++;
                cout << "  O n�mero " << valor << " foi encontrado na posi��o: " << posicao+1 << "\n";
            }
        }
        if(qntd == 0)
            cout << "  O n�mero n�o foi encontrado na lista! =/\n";
        else if (qntd == 1)
                cout << "  O n�mero " << valor << " foi encontrado " << qntd << " vez.\n";
            else
                cout << "  O n�mero " << valor << " foi encontrado " << qntd << " vezes.\n";
    }

    void recuperaLista(int posicao) {
        int valor;
        //Verifica se a lista est� vazia.
        if(tamanho <= 0) {
            printf("  Lista Vazia!\n");
            return;
        }
        if(posicao <= 0 || posicao > tamanho) {
            cout << "  Posi��o inv�lida!\n";
            return;
        }
        valor = lista[posicao-1];
        cout << "  O valor encontrado na posi��o " << posicao << " �: " << valor << "\n";
    }

    void imprime() {
        printf("  -------------------\n");
        printf("  | P. |  VALORES   |\n");
        for(int i=TAM-1; i>=0; i--) {
            printf("  -------------------\n");
            printf("  | %2i | %10i |\n", i+1, lista[i]);
        }
        printf("  -------------------\n");
        cout << "  Impress�o feita com sucesso!\n";
    }

