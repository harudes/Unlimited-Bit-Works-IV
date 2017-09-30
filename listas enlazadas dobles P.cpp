#include <iostream>
using namespace std;

template <class T>
class nodo{
public:
	T valor;
	nodo *next;
	nodo *prev;
	nodo(){}
	nodo(T val):valor(val){next=NULL;}
	nodo(T val,nodo * previo , nodo* siguiente):valor(val),next(siguiente),prev(previo){}
	
};

template <class T>
class lista{
private:
	nodo<T> *head;
	nodo<T> *tail;
public:
	lista(){head=NULL;}
	lista(nodo<T>* cabeza):head(cabeza){}
	bool buscar(T dato, nodo<T>*& p){
		nodo<T>* q=tail;
		while(p->next&&q->prev){
			if(dato<=p->next->valor){
				if(p->next&&p->next->valor==dato)
					return 1;
				else 
					return 0;
			}
			if(dato>=q->prev->valor){
				p=q->prev;
				if(p->next&&p->next->valor==dato)
					return 1;
				else 
					return 0;
			}
			p=p->next;
			q=q->prev;
		}
	}
	void insertar(T valor){
		nodo<T>* p = head;
		if(!(head)){
			head = new nodo<T>(valor,NULL,NULL);
			tail=head;
		}
		else if(valor<head->valor){
			head = new nodo<T>(valor,NULL,head);
			head->next->prev=head;
		}
		else if(valor>tail->valor){
			tail = new nodo<T>(valor,tail,NULL);
			tail->prev->next=tail;
		}
		else{
			if(!(buscar(valor,p))){
				nodo <T> *a = new nodo<T>(valor,p,p->next);
				if(a->next)
					a->next->prev=a;
				else
					tail=a;
				a->prev->next=a;
			}
		}
	}
	void eliminar(T valor){
		nodo<T>* p = head;
		if(valor==head->valor){
			nodo<T> *temp = head;
			head=head->next;
			head->prev=NULL;
			delete temp;
		}
		else{
			if(buscar(valor,p)){
				nodo<T> *temp = p->next;
				p->next=p->next->next;
				if(p->next)
					p->next->prev=p;
				else
					tail=p;
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
	void imprimir_inversa(){
		nodo<T>* temp=tail;
		cout<<"La lista invertida es:";
		while(temp){
			cout<<temp->valor<<", ";
			temp=temp->prev;
		}
		cout<<endl;
	}
};
int main(int argc, char *argv[]) {
	lista<int> list;
	list.insertar(5);
	list.imprimir();
	list.insertar(3);
	list.imprimir();
	list.insertar(1);
	list.imprimir();
	list.insertar(9);
	list.imprimir();
	list.insertar(7);
	list.imprimir();
	list.eliminar(3);
	list.imprimir();
	list.insertar(2);
	list.imprimir();
	list.imprimir_inversa();
	return 0;
}

