#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void swap(int *a, int *b){
	int temp=*a;
	*a=*b;
	*b=temp;
}

bool menor(int *a, int *b){
	return *a>*b;
}

bool mayor(int *a, int *b){
	return *a<*b;
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

void generarArreglo(int *p, long tam){
	for(long i=0;i<tam;i++)
		p[i]=rand()%100000;
}

int main(int argc, char *argv[]) {
	srand(time(NULL));
	long tam=500000;
	int *arreglo = new int[tam];
	int *p=arreglo, *q=&arreglo[tam-1];
	generarArreglo(arreglo,tam);
	CoctailSort(p,q,mayor);
	cout<<"Se termino de ordenar el arreglo"<<endl;
	return 0;
}
