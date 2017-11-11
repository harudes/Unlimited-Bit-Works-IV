#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include "string"
#include <math.h>
using namespace std;



struct Nodo{
	int val;
	Nodo* hijos[2];
	Nodo(int valor):val(valor){hijos[1]=NULL;hijos[0]=NULL;}
};

class ArbolRB{
private:
	Nodo* head;
public:
	ArbolRB(){head=NULL;}
	int altura(Nodo *n,int l,int r){
		if(!n)
			return 0;
		if(n->hijos[0]){
			l=altura(n->hijos[0],l,r)+1;
		}
		if(n->hijos[1]){
			r=altura(n->hijos[1],0,r)+1;
		}
		if(l>r)
			return l;
		else
			return r;
	}
	bool balancear(Nodo **n){
		int l=1,r=1;
		Nodo* temp;
		if((altura((*n)->hijos[0],l,r)-altura((*n)->hijos[1],l,r)>=2)){
			if(altura((*n)->hijos[0]->hijos[0],l,r)>altura((*n)->hijos[0]->hijos[1],l,r)){
				temp=(*n)->hijos[0];
				(*n)->hijos[0]=(*n)->hijos[0]->hijos[1];
				temp->hijos[1]=*n;
				*n=temp;
			}
			else{
				temp=(*n)->hijos[0]->hijos[1];
				(*n)->hijos[0]->hijos[1]=temp->hijos[0];
				temp->hijos[0]=(*n)->hijos[0];
				(*n)->hijos[0]=temp->hijos[1];
				temp->hijos[1]=*n;
				*n=temp;
			}
			return 1;
		}
		if((altura((*n)->hijos[0],l,r)-altura((*n)->hijos[1],l,r)<=-2)){
			if(altura((*n)->hijos[1]->hijos[0],l,r)>altura((*n)->hijos[1]->hijos[1],l,r)){
				temp=(*n)->hijos[1]->hijos[0];
				(*n)->hijos[1]->hijos[0]=temp->hijos[1];
				temp->hijos[1]=(*n)->hijos[1];
				(*n)->hijos[1]=temp->hijos[0];
				temp->hijos[0]=*n;
				*n=temp;
			}
			else{
				temp=(*n)->hijos[1];
				(*n)->hijos[1]=(*n)->hijos[1]->hijos[0];
				temp->hijos[0]=*n;
				*n=temp;
			}
			return 1;
		}
		return 0;
	}
	bool buscar(int val, Nodo **&p,stack<Nodo**> &recorrido){
		while(*p){
			recorrido.push(p);
			if(val!=(*p)->val)
				p=&((*p)->hijos[val>(*p)->val]);
			else
				break;
		}
		if(*p&&(*p)->val==val)
			  return 1;
		else
			return 0;
	}
	void insertar(int val){
		Nodo** p= &head;
		stack<Nodo**> recorrido;
		if(!buscar(val,p,recorrido))
			*p = new Nodo(val);
		while(!recorrido.empty()&&!balancear(recorrido.top())){
			recorrido.pop();
		}
	}
	void eliminar(int val){
		Nodo** p= &head;
		stack<Nodo**> recorrido;
		if(buscar(val,p,recorrido)){
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
			recorrido.pop();
			while(!recorrido.empty()&&!balancear(recorrido.top())){
				recorrido.pop();
			}
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
	}
	void lvlprint(){
		queue<Nodo*> nodos;
		Nodo* temp;
		int gus=altura(head,0,0)+1;
		gus=2*pow(2,gus);
		string gus2;
		if(head)
			nodos.push(head);
		while(!(nodos.empty())){
			unsigned int i=0, tam=nodos.size();
			for(; i<tam;i++){
				temp=nodos.front();
				nodos.pop();
				gus2=string(" ",gus);
				cout<<temp->val<<",";
				if(temp->hijos[0])
					nodos.push(temp->hijos[0]);
				if(temp->hijos[1])
					nodos.push(temp->hijos[1]);
				gus /=2;
			}
			cout<<endl;
		}
	}
};

int main(int argc, char *argv[]) {
	ArbolRB arbol;
	arbol.insertar(1);
	arbol.insertar(8);
	arbol.insertar(3);
	arbol.insertar(7);
	arbol.insertar(2);
	arbol.insertar(9);
	arbol.insertar(4);
	arbol.insertar(5);
	arbol.insertar(6);
	arbol.print();
	arbol.lvlprint();
	return 0;
}
