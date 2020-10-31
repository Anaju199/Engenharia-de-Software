#include<iostream>
#include<windows.h>
#include<fstream>
#include<cstdlib>
#include<stdlib.h>
#include<cstring>
#include<locale.h>
#include<sstream>
#include<ctype.h>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include <queue>
#include<list>

#define Max 500

using namespace std;

        struct registro {
          int p; //prioridade do processo
          int c; //o instante de chegada do processo
          int s; //o tempo de serviço do processo
          int esp=-1; //variavel para somar o tempo de espera
          int resp=-1; //somar o tempo resposta
          int t; //tempo de serviço
          int com;
          int fim;
        };

        struct resultado {
          float espe; //retorna espera
          float respo; //retorna resposta
        };

        resultado funcaoPRIO(list<registro> lista);
        resultado funcaoRRQ5(list<registro> lista);
        void lerArquivo(string nome, string vetor[Max]);
        bool comparaC(registro a, registro b);
        bool comparaS(registro a, registro b);
        bool comparaP(registro a, registro b);
        void salvarArquivo(float matrizSalv[4][2]);
        int converte(string s);
        char linha[Max];
        char *palavra= strtok(linha," ");
        int tamL=0;


int main(){

    setlocale(LC_ALL,"portuguese");
    string vetPalavras[Max], nome, vetLinhas[Max], vetSalvar[Max], f;
    resultado PRIO, RRQ5;


    int tamP, n=0, anterior=0,Ttotal,teste,j=0;
    float total=0, matrizFinal[4][2];
    queue<registro> fila;
    list<registro> lista, listaAux,lista1;
	list<registro>::iterator it,ti;
    registro aux;

    nome="Teste.txt";
        //Ler arquivo
        tamP=lerArquivo(nome);
        tamP=i;

    for(int a;a<tamP;a++){
            cout<<vetPalavras[a]<<endl;
    }
    //Salva a quantidade de linhas n
    /*  stringstream ss(vetPalavras[0]);
    ss >> n;
    */
        n = converte(vetPalavras[0]);

    for(int i=1;i<tamP;i+=3){

        aux.p = converte(vetPalavras[i]);
        aux.c = converte(vetPalavras[i+1]);
        aux.s = converte(vetPalavras[i+2]);
        aux.t=0;
        aux.com=0;
        aux.fim=0;
        //j++;
        fila.push(aux);
        lista.push_back(aux);
    }


	for(int i=0;i<n;i++){
        cout << fila.front().p <<" " << fila.front().c <<" " << fila.front().s<<endl;
        fila.pop();

		if(fila.empty()){
			cout << "Vazio na iteração " << i+1 << endl;
		}
	}

    cout<<"**************************************************************"<<endl;
	lista.sort(comparaC);
	for(it = lista.begin(); it!=lista.end();it++){

        cout<< (*it).p << " "<< (*it).c << " "<<(*it).s<< " "<<(*it).t <<endl;
	}
	cout<<endl<<"**************************************************************"<<endl;
	Ttotal=lista.front().c;
	for(it = lista.begin(); it!=lista.end();it++){
        total=total+Ttotal-(*it).c;
        Ttotal+=(*it).s;
	

	}


	cout<<endl;
	total=total/n;
    cout.precision(2);
    cout <<fixed << total;


	cout<<"FIFO "<<endl<<total;
cout<<endl<<Ttotal;

matrizFinal[0][0] = total;
    matrizFinal[0][1] = matrizFinal[0][0];

	lista.sort(comparaC);
	Ttotal=lista.front().c;
	total=0;
	for(it = lista.begin(); it!=lista.end();it++){
        total=total+Ttotal-(*it).c;
        Ttotal+=(*it).s;
        lista.sort(comparaS);


	}


	cout<<endl;
	total=total/n;
    cout.precision(2);
    cout <<fixed << total;


	cout<<"SRT_ "<<endl<<total;
cout<<endl<<Ttotal;
matrizFinal[2][0] = total;
matrizFinal[2][1] = matrizFinal[2][0];
    RRQ5 = funcaoRRQ5(lista);
    matrizFinal[3][0]=RRQ5.espe;
    matrizFinal[3][1]=RRQ5.respo;

    PRIO = funcaoPRIO(lista);
    matrizFinal[1][0]=PRIO.espe;
    matrizFinal[1][1]=PRIO.respo;
    salvarArquivo(matrizFinal);


}

resultado funcaoPRIO(list<registro> lista){
    list<registro>::iterator it;
    list<registro> listaAux;
    queue<registro> filaN;
    registro aux1;
    resultado resposta;
    int n = lista.size();
    int Stotal=0, inicio;
    float totalEsp=0, totalResp=0;

    lista.sort(comparaC);
    for(it = lista.begin(); it!=lista.end();it++){
        Stotal+=(*it).s;
	}
	for(int i;i<=filaN.size();i++){
        filaN.pop();
	}
	it = lista.begin();
    filaN.push(lista.front());
	inicio=(*it).c;
    aux1=filaN.front();
    lista.erase(it);
	for(int i=inicio;i<Stotal+inicio;i++){
        it = lista.begin();
        aux1.c=(*it).c;
        while((aux1.c==i)&&(lista.size()!=0)){
            if(filaN.front().p>(*it).p){
                aux1=filaN.front();
                filaN.pop();
                listaAux.push_back(aux1);
                it = lista.begin();
                filaN.push(lista.front());
                lista.erase(it);
            }else{
                it = lista.begin();
                listaAux.push_back(lista.front());
                lista.erase(it);
            }
            listaAux.sort(comparaP);
        }
        aux1=filaN.front();
        filaN.pop();
        if(aux1.esp==-1){
            aux1.esp=aux1.c;
        }
        if(aux1.s!=0){
            if(aux1.esp==i){
                totalEsp+=i-aux1.esp;
                aux1.esp=i;

            }else{
                totalEsp+=i-aux1.esp-1;
                aux1.esp=i;
            }
            aux1.s--;
            if(aux1.resp==-1){
                aux1.resp=i-aux1.c;
                totalResp+=i-aux1.c;
            }
            filaN.push(aux1);
        }else{
            while(filaN.empty()!=true){
                filaN.pop();
            }
            it = listaAux.begin();
            filaN.push(listaAux.front());
            listaAux.erase(it);
            aux1=filaN.front();
            i--;
        }
    }
    resposta.espe = totalEsp/n;
    resposta.respo = totalResp/n;

    return resposta;
}

resultado funcaoRRQ5(list<registro> lista){
    list<registro>::iterator it;
    queue<registro> filaN;
    registro aux1;
    resultado resposta;
    int n = lista.size();
    int Stotal=0, inicio, tam=5;
    float totalEsp=0, totalResp=0;

    lista.sort(comparaC);
    for(it = lista.begin(); it!=lista.end();it++){
        Stotal+=(*it).s;
	}
	for(int i;i<=filaN.size();i++){
        filaN.pop();
	}
	it = lista.begin();
    filaN.push(lista.front());
	inicio=(*it).c;
    aux1=filaN.front();
    lista.erase(it);
	for(int i=inicio;i<Stotal+inicio;i+=tam){
        it = lista.begin();
        aux1.c=(*it).c;
        while((aux1.c>i)&&(aux1.c<=i+tam)&&(lista.size()!=0)){
            it = lista.begin();
            filaN.push(lista.front());
            lista.erase(it);
            it = lista.begin();
            aux1.c=(*it).c;
        }
        aux1=filaN.front();
        filaN.pop();
        if(aux1.esp==-1){
            aux1.esp=aux1.c;
        }
        if(aux1.s>=tam){
            totalEsp+=i-aux1.esp;
            aux1.esp=i+tam;
            aux1.s-=tam;
            if(aux1.resp==-1){
                aux1.resp=i-aux1.c;
                totalResp+=i-aux1.c;
            }
            if(aux1.s!=0){
                filaN.push(aux1);
            }
        }else if((aux1.s<tam)&&(aux1.s>=0)){
            totalEsp+=i-aux1.esp;
            aux1.esp=i+aux1.s;
            if(aux1.resp==-1){
                aux1.resp=i-aux1.c;
                totalResp+=i-aux1.c;
            }
            i-=tam-aux1.s;
            aux1.s=0;
        }
    }
    resposta.espe = totalEsp/n;
    resposta.respo = totalResp/n;

    return resposta;
}

int converte(string s){
    int num;
    stringstream ss(s);
    ss >> num;
    return num;
}


void lerArquivo(string nome, string vetor[Max]){
    int i=0;
    ifstream leia(nome);
        while(!leia.eof()){
            leia.getline(linha,Max);
            palavra = strtok(linha, " ");
            vetor[i]=palavra;
            i++;
        }
}

int lerArquivo(string nome){
    string   vetLinhas[Max], vetSalvar[Max];

  ifstream ler(nome);
         int i=0;
         while(!ler.eof()){
            ler.getline(linha,Max);
            vetLinhas[tamL] = linha;
            tamL++;
            palavra = strtok(linha, (" "));
            while(palavra!=nullptr){
                    vetPalavras[i]=palavra;
                    i++;
                    palavra = strtok(NULL, (" "));
            }
        }
    return i;
}

void salvarArquivo(float matrizSalv[4][2]){
        ofstream saida;
        saida.open("Resultado.txt");
        saida.precision(2);
        saida<<fixed<<"FIFO "<<matrizSalv[0][0]<<" "<<matrizSalv[0][1]<<endl;
        saida<<"PRIO "<<matrizSalv[1][0]<<" "<<matrizSalv[1][1]<<endl;
        saida<<"SRT_ "<<matrizSalv[2][0]<<" "<<matrizSalv[2][1]<<endl;
        saida<<"RRQ5 "<<matrizSalv[3][0]<<" "<<matrizSalv[3][1]<<endl;
        cout<<endl;
        cout<<"Resposta salva em Resultado.txt"<<endl;
}

bool comparaC(registro a, registro b){ //Função para compara Alunos
  return a.c < b.c ; //Aluno a vem antes do Aluno b se a nota do aluno a é menor que a nota do aluno b
}
bool comparaS(registro a, registro b){ //Função para compara Alunos
  return a.s < b.s; //Aluno a vem antes do Aluno b se a nota do aluno a é menor que a nota do aluno b
}
bool comparaP(registro a, registro b){ //Função para compara Alunos
  return a.p < b.p; //Aluno a vem antes do Aluno b se a nota do aluno a é menor que a nota do aluno b
}

