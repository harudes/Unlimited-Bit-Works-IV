#include <iostream>
using namespace std;

template <class T>
class nodo{
public:
	T valor;
	nodo *next;
	nodo(){}
	nodo(T val):valor(val){next=NULL;}
	nodo(T val, nodo* siguiente):valor(val),next(siguiente){}
	
};

template <class T>
class lista{
private:
	nodo<T> *head;
public:
	lista(){head=NULL;}
	lista(nodo<T>* cabeza):head(cabeza){}
	bool buscar(T dato, nodo<T>**& p){
		while(*p&&dato>(*p)->valor){
			p=&((*p)->next);
		}
		if(*p&&(*p)->valor==dato)
			return 1;
		else 
			return 0;
	}
	void insertar(T valor){
		nodo<T>** p = &head;
		if(!(buscar(valor,p))){
			nodo<T>* a = new nodo<T>(valor,*p);
			(*p)=a;
		}
	}
	void eliminar(T valor){
		nodo<T>** p = &head;
		if(buscar(valor,p)){
			nodo<T>* temp=&(**p);
			*p=(*p)->next;
			delete temp;
		}
	}
	void imprimir(){
		nodo<T>* temp=head;
		while(temp){
			cout<<temp->valor<<", ";
			temp=temp->next;
		}
		cout<<endl;
	}
	nodo<T>** getHead(){return &head;} 
};

int main(int argc, char *argv[]) {
	lista<int> list;
	
	return 0;
}

