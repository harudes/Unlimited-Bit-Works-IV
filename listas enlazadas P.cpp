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
	bool buscar(T dato, nodo<T>*& p){
		while(p->next&&dato>p->next->valor){
			p=p->next;
		}
		if(p->next&&p->next->valor==dato)
			return 1;
		else 
			return 0;
	}
	void insertar(T valor){
		nodo<T>* p = head;
		if(!(head)||valor<head->valor)
			head = new nodo<T>(valor,head);
		else{
			if(!(buscar(valor,p))){
				nodo <T> *a = new nodo<T>(valor,p->next);
				p->next=a;
			}
		}
	}
	void eliminar(T valor){
		nodo<T>* p = head;
		if(valor==head->valor){
			nodo<T> *temp = head;
			head=head->next;
			delete temp;
		}
		else{
			if(buscar(valor,p)){
				nodo<T> *temp = p->next;
				p->next=p->next->next;
				delete temp;
			}
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
	return 0;
}

