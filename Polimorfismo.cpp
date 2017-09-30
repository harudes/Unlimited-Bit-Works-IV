#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void swap(int *a, int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

void print(int *p,int *q){
	int tam=q-p+1;
	cout<<"[";
	for(int i=0;i<tam;i++){
		if(i!=tam-1)
			cout<<p[i]<<",";
		else
			cout<<p[i];
	}
	cout<<"]"<<endl;
}

class ordenamiento{
private:
    virtual bool comparar()=0;
public:
    void CoctailSort(int *p, int *q, bool (*comparar)(int *a, int *b)){
	int *temp=p;
	bool intercambio=1;
	while(intercambio==1&&q>p){
		intercambio=0;
		for(;p<q;p++){
			if(comparar(p,p+1)){
				swap(p,p+1);
				intercambio=1;
			}
		}
		for(;q>temp;q--){
			if(comparar(q-1,q)){
				swap(q-1,q);
				intercambio=1;
			}
		}
		temp=q;
		q=p;
		temp++;
		p=temp;
		q--;
	}
}
};

class mayor: public ordenamiento{
    bool comparar(int *a, int *b){
        return *a<*b;
    }
};

class menor: public ordenamiento{
    bool comparar(int *a, int *b){
        return *a>*b;
    }
};

void generarArreglo(int *p, long tam){
	for(long i=0;i<tam;i++)
		p[i]=rand()%100;
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	long tam=10;
	int *arreglo = new int[tam];
	int *p=arreglo, *q=&arreglo[tam-1];
	menor ordenador;
	generarArreglo(arreglo,tam);
	print(p,q);
	ordenador.CoctailSort(p,q);
	print(p,q);
	cout<<"Se termino de ordenar el arreglo"<<endl;
	return 0;
}
