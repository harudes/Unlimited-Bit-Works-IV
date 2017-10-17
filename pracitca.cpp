#include <iostream>
#include <vector>
using namespace std;

class Nodo{
public:
	int val;
	Nodo* right;
	Nodo* left;
	Nodo(int valor):val(valor){right=NULL;left=NULL;}
};

class ArbolB{
private:
	Nodo* head;
public:
	ArbolB(){head=NULL;}
	bool buscar(int val, Nodo **&p){
		while(*p){
			if(val>(*p)->val)
				p=&((*p)->right);
			else{
				if(val<(*p)->val)
					p=&((*p)->left);
				else
					break;
			}
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
			if((*p)->left&&(*p)->right){
				Nodo* aux = *p;
				p=&((*p)->left);
				while((*p)->right)
					p=&((*p)->right);
				aux->val=(*p)->val;
			}
			Nodo* temp=*p;
			if((*p)->right)
				*p=(*p)->right;
			else
				*p=(*p)->left;
			delete(temp);
		}
	}
	void print2(Nodo* p){
		if(p->left){
			print2(p->left);
		}
		cout<<p->val<<",";
		if(p->right){
			print2(p->right);
		}
	}
	void print(){
		Nodo* p=head;
		if(p){
			if(p->left){
				print2(p->left);
			}
			cout<<p->val<<",";
			if(p->right){
				print2(p->right);
			}
		}
		cout<<endl;
	}
	void lvlprint2(vector<Nodo*> nodo){
		vector<Nodo*> nodos;
		for(int i=0;i<nodo.size();i++){
			cout<<nodo[i]->val;
			if(nodo[i]->left)
				nodos.push_back(nodo[i]->left);
			if(nodo[i]->right)
				nodos.push_back(nodo[i]->right);
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

