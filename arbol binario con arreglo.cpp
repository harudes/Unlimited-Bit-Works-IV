#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Nodo{
public:
	int val;
	Nodo* hijos[2];
	Nodo(int valor):val(valor){hijos[1]=NULL;hijos[0]=NULL;}
};

class ArbolB{
private:
	Nodo* head;
public:
	ArbolB(){head=NULL;}
	bool buscar(int val, Nodo **&p){
		while(*p){
			if(val!=(*p)->val)
				p=&((*p)->hijos[val>(*p)->val]);
		}
		if(*p&&(*p)->val==val)
			return 1;
		else
			return 0;
	}
	void insertar(int val){
		Nodo** p= &head;
		if(!buscar(val,p))
			*p = new Nodo(val);
	}
	void eliminar(int val){
		Nodo** p= &head;
		if(buscar(val,p)){
			if((*p)->hijos[0]&&(*p)->hijos[1]){
				Nodo* aux = *p;
				p=&((*p)->hijos[0]);
				while((*p)->hijos[1])
					p=&((*p)->hijos[1]);
				aux->val=(*p)->val;
			}
			Nodo* temp=*p;
			*p=(*p)->hijos[(*p)->hijos[1]!=NULL];
			delete(temp);
		}
	}
	void print2(Nodo* p){
		if(p->hijos[0]){
			print2(p->hijos[0]);
		}
		cout<<p->val<<",";
		if(p->hijos[1]){
			print2(p->hijos[1]);
		}
	}
	void print(){
		Nodo* p=head;
		if(p){
			if(p->hijos[0]){
				print2(p->hijos[0]);
			}
			cout<<p->val<<",";
			if(p->hijos[1]){
				print2(p->hijos[1]);
			}
		}
		cout<<endl;
	}/*
	void lvlprint2(vector<Nodo*> nodo){
		vector<Nodo*> nodos;
		for(unsigned int i=0;i<nodo.size();i++){
			cout<<nodo[i]->val;
			if(nodo[i]->hijos[0])
				nodos.push_back(nodo[i]->hijos[0]);
			if(nodo[i]->hijos[1])
				nodos.push_back(nodo[i]->hijos[1]);
		}
		cout<<endl;
		if(nodos.size()>0)
			lvlprint2(nodos);
	}
	void lvlprint(){
		vector<Nodo*> nodos;
		Nodo* p=head;
		if(head){
			nodos.push_back(p);
		}
		lvlprint2(nodos);
	}*/
	void lvlprint(){
		queue<Nodo*> nodos;
		Nodo* temp;
		if(head)
			nodos.push(head);
		while(!(nodos.empty())){
			unsigned int i=0, tam=nodos.size();
			for(; i<tam;i++){
				temp=nodos.front();
				nodos.pop();
				cout<<temp->val<<",";
				if(temp->hijos[0])
					nodos.push(temp->hijos[0]);
				if(temp->hijos[1])
					nodos.push(temp->hijos[1]);
			}
			cout<<endl;
		}
	}
};

int main(int argc, char *argv[]) {
	ArbolB arbol;
	arbol.insertar(5);
	arbol.insertar(7);
	arbol.insertar(3);
	arbol.insertar(1);
	arbol.insertar(4);
	arbol.insertar(2);
	arbol.insertar(9);
	arbol.insertar(8);
	arbol.insertar(6);
	arbol.print();
	arbol.lvlprint();
	return 0;
}

