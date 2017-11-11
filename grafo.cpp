#include <iostream>
#include <vector>

using namespace std;

template <class G>
struct Recorrido{
	typedef typename G:: Node Node;
	Node* nodo;
	vector<Node*> nodos;
	int tam;
	Recorrido(Node* n):nodo(n){tam=0;}
};

template <typename G>
struct CNode{
	typedef typename G::Edge Edge;
	typedef typename G::n N;
	typedef typename G::Path Path;
	N nombre;
	vector<Edge*> aristas;
	CNode(N dato):nombre(dato){}
};

template <class G>
struct CEdge{
	typedef typename G:: Node Node;
	typedef typename G:: e E;
	Node* nodos[2];
	E tam;
	bool dir;
	CEdge(Node* a, Node* b, E dato, bool direccion):tam(dato),dir(direccion){nodos[0]=a;nodos[1]=b;}
};

template <class N, class E>
class CGraph{
public:
	typedef CGraph<N,E> Self;
	typedef CNode<Self> Node;
	typedef CEdge<Self> Edge;
	typedef Recorrido<Self> Path;
	typedef N n;
	typedef E e;
	vector<Node*> nodos;
	void imprimirNodos(){
		for(int i=0;i<nodos.size();i++){
			cout<<nodos[i]->nombre;
			if(i!=nodos.size()-1)
				cout<<",";
		}
		cout<<endl;
	}
	bool nodePos(Edge* arista, Node* nodo){
		if(arista->nodos[0]==nodo)
			return 0;
		return 1;
	}
	unsigned int edgePos(Node* n, Node* a, Node* b, e dato, bool direccion){
		Edge* temp;
		for(unsigned int i=0;i<n->aristas.size();i++){
			temp=n->aristas[i];
			if((temp->nodos[0]==a)&&(temp->nodos[1]==b)&&(temp->tam==dato)&&(temp->dir==direccion))
				return i;
		}
		return -1;
	}
	unsigned int nodeGraphPos(n dato){
		for(unsigned int i=0;i<nodos.size();i++){
			if(nodos[i]->nombre==dato)
				return i;
		}
		return -1;
	}
	void imprimirGrafo(){
		cout<<"Nodos: ";
		for(int i=0;i<nodos.size();i++){
			cout<<nodos[i]->nombre;
			if(i!=nodos.size()-1)
				cout<<",";
		}
		cout<<endl;
		cout<<"Aristas:"<<endl;
		Node* temp;
		Edge* arista;
		for(int i=0;i<nodos.size();i++){
			temp=nodos[i];
			for(int j=0;j<temp->aristas.size();j++){
				arista=temp->aristas[j];
				if(arista->dir==0)
					cout<<arista->nodos[0]->nombre<<" <-> "<<arista->nodos[1]->nombre<<" = "<<arista->tam<<endl;
				else{
					if(!nodePos(arista,temp)){
						cout<<arista->nodos[0]->nombre<<" -> "<<arista->nodos[1]->nombre<<" = "<<arista->tam<<endl; 
					}
				}
			}
		}
	}
	bool findNode(n dato, Node*& p){
		for(int i=0;i<nodos.size();i++){
			if(nodos[i]->nombre==dato){
				p=nodos[i];
				return 1;
			}
		}
		return 0;
	}
	bool findEdge(Node* a, Node* b, e dato, bool direccion, Edge*& arista){
		Edge* temp;
		for(int i=0;i<a->aristas.size();i++){
			temp=a->aristas[i];
			if((temp->nodos[0]==a)&&(temp->nodos[1]==b)&&(temp->tam==dato)&&(temp->dir==direccion)){
				arista=temp;
				return 1;
			}
		}
		return 0;
	}
	bool insertNode(n dato){
		Node* p;
		if(!findNode(dato,p)){
			Node* n = new Node(dato);
			nodos.push_back(n);
			return 1;
		}
		return 0;
	}
	bool insertEdge(n a ,n b ,e tam ,bool dir){
		Node* A;
		Node* B;
		if(findNode(a,A)&&findNode(b,B)){
			Edge* arista=new Edge(A,B,tam,dir);
			A->aristas.push_back(arista);
			B->aristas.push_back(arista);
			return 1;
		}
		return 0;
	}
	bool removeEdge(n a, n b, e tam, bool dir){
		Node *A;
		Node *B;
		Edge *arista;
		if(findNode(a,A)&&findNode(b,B)){
			if(findEdge(A,B,tam,dir,arista)){
				A->aristas.erase(A->aristas.begin()+edgePos(A,A,B,tam,dir));
				B->aristas.erase(B->aristas.begin()+edgePos(B,A,B,tam,dir));
				delete(arista);
				return 1;
			}
		}
		return 0;
	}
	bool deleteNode(n dato){
		Node* A;
		if(findNode(dato,A)){
			int tam=A->aristas.size();
			for(int i=tam-1;i>0;i--){
				removeEdge(A->aristas[i]->nodos[0]->nombre,A->aristas[i]->nodos[1]->nombre,A->aristas[i]->tam,A->aristas[i]->dir);
			}
			nodos.erase(nodos.begin()+nodeGraphPos(dato));
			delete(A);
			return 1;
		}
		return 0;
	}
	Path* findPath(Node *nodo,vector<Path*> &rutas){
		for(int i=0; i<rutas.size();i++){
			if(rutas[i]->nodo==nodo){
				return rutas[i];
			}
		}
		return 0;
	}
	bool findNode_Path(Path *recorrido, Node *nodo){
		for(int i=0;i<recorrido->nodos.size()-1;i++){
			if(recorrido->nodos[i]==nodo)
				return 1;
		}
		return 0;
	}
	bool findNode2(Node *p, vector<Node*> vec){
		for(int i=0;i<vec.size();i++){
			if(vec[i]==p)
				return 1;
		}
		return 0;
	}
	void restaVector(vector<Node*> &a, vector<Node*> b){
		for(int i=a.size()-1;i>=0;i--){
			if(findNode2(a[i],b))
				a.erase(a.begin()+i);
		}
	}
	void sumaVector(vector<Node*> &a, vector<Node*> b){
		for(int i=0;i<b.size();i++){
			if(!findNode2(b[i],a))
				a.push_back(b[i]);
		}
	}
	void recorrer(vector<Path*> &rutas,Node *nodo,Edge *arista,vector<Node*> &modificados){
		Path* temp;
		Node* b;
		if(arista->nodos[0]==nodo)
			b=arista->nodos[1];
		else
			b=arista->nodos[0];
		temp=new Path(b);
		temp->nodos=findPath(nodo,rutas)->nodos;
		temp->nodos.push_back(nodo);
		temp->tam=arista->tam+findPath(nodo,rutas)->tam;
		if(!findPath(b,rutas)){
			rutas.push_back(temp);
			if(!findNode2(b,modificados))
				modificados.push_back(b);
		}
		else{
			Path* ruta=findPath(b,rutas);
			if(!findNode_Path(ruta,b)){
				if((ruta->tam)>(temp->tam)){
					ruta->nodos=temp->nodos;
					ruta->tam=temp->tam;
					if(!findNode2(b,modificados))
						modificados.push_back(b);
				}
			}
		}
	}
	void dijkstra2(vector<Node*> visitados, vector<Path*> &rutas,Node *start){
		vector<Node*> visitados2;
		for(int j=0;j<visitados.size();j++){
			Node* A=visitados[j];
			for(int i=0;i<A->aristas.size();i++){
				if(!(A->aristas[i]->dir&&nodePos(A->aristas[i],A))&&A->aristas[i]->nodos[0]!=start &&A->aristas[i]->nodos[1]!=start){
					recorrer(rutas,A,A->aristas[i],visitados2);
				}
			}
		}
		if(visitados2.size()>0)
			dijkstra2(visitados2,rutas,start);
	}
	void dijkstra(n a){
		Node* A;
		vector<Path*> rutas;
		vector<Node*> modificados;
		if(findNode(a,A)){
			Path* inicio=new Path(A);
			rutas.push_back(inicio);
			for(int i=0;i<A->aristas.size();i++){
				if(!(A->aristas[i]->dir&&nodePos(A->aristas[i],A)))
					recorrer(rutas,A,A->aristas[i],modificados);
			}
			dijkstra2(modificados,rutas,A);
		}
		for(int i=1;i<rutas.size();i++){
			for(int j=0;j<rutas[i]->nodos.size();j++){
				cout<<rutas[i]->nodos[j]->nombre<<"->";
			}
			cout<<rutas[i]->nodo->nombre<<"="<<rutas[i]->tam;
			cout<<endl;
		}
	}
};

int main(){
	CGraph<char,int> grafo;
	grafo.insertNode('A');
	grafo.insertNode('B');
	grafo.insertNode('C');
	grafo.insertNode('D');
	grafo.insertNode('E');
	grafo.insertNode('F');
	grafo.insertEdge('A','B',10,1);
	grafo.insertEdge('B','C',5,1);
	grafo.insertEdge('A','D',1,1);
	grafo.insertEdge('D','F',1,1);
	grafo.insertEdge('F','B',2,1);
	grafo.deleteNode('F');
	grafo.imprimirGrafo();
	grafo.dijkstra('A');
	return 0;
}
