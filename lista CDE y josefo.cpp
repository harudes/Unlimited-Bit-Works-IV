#include <iostream>
using namespace std;

template <class T>
struct nodo{
	T valor;
	nodo *next;
	nodo *prev;
	nodo(){}
	nodo(T val):valor(val){next=NULL;}
	nodo(T val,nodo* anterior ,nodo* siguiente):valor(val),next(siguiente),prev(anterior){}
	
};

template <class T>
class lista{
public:
	nodo<T> *head;
	lista(){head=NULL;}
	lista(nodo<T>* cabeza):head(cabeza){}
	bool buscar(T dato, nodo<T>**& p){
		while(*p&&dato>(*p)->valor){
			p=&((*p)->next);
			if(*p==head)
				break;
		}
		if(*p&&(*p)->valor==dato)
			return 1;
		else 
			return 0;
	}
	void insertar(T valor){
		if(!head){
			head=new nodo<T>(valor);
			head->next=head;
			head->prev=head;
		}
		nodo<T>** p = &head;
		if(!(buscar(valor,p))){
			*p = new nodo<T>(valor,(*p)->prev,*p);
			(*p)->prev->next=*p;
			(*p)->next->prev=(*p);
		}
	}
	void eliminar(T valor){
		nodo<T>** p = &head;
		if(buscar(valor,p)){
			if((*p)==head)
				head->prev->next=head->next;
			nodo<T>* temp=&(**p);
			(*p)->next->prev=(*p)->prev;
			*p=(*p)->next;
			delete temp;
		}
	}
	void imprimir(){
		nodo<T>* p=head;
		cout<<p->valor<<", ";
		p=p->next;
		while(p!=head){
			cout<<p->valor<<", ";
			p=p->next;
		}
		cout<<endl;
	}
	void imprimir2(){
		nodo<T>* p=head->prev;
		cout<<p->valor<<", ";
		p=p->prev;
		while(p!=head->prev){
			cout<<p->valor<<", ";
			p=p->prev;
		}
		cout<<endl;
	}
	void josefo_aux(int k,nodo<T> *&p){
		imprimir();
		for(int i=1;i<k;i++)
			p=p->next;
		int temp=p->valor;
		p=p->next;
		eliminar(temp);
	}
	nodo<T>** getHead(){return &head;} 
};

void josefo(int n, int k){
	lista<int> list;
	for(int i=1;i<=n;i++){
		list.insertar(i);
	}
	nodo<int>* p=list.head;
	while(list.head->next!=list.head->prev){
		list.josefo_aux(k,p);
	}
	list.imprimir();
}

int main(int argc, char *argv[]) {
	josefo(10,3);
	return 0;
}

