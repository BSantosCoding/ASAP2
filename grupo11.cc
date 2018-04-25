#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <set>
#include <utility>
#include <string>
#include <map>

using namespace std;
class Edge;
class Graph;
class Algorithm;

class Pixel{
    private:
        int c;
        int p;
        int h;
        int e;
        map<Pixel*, Edge*> edgeMap;
        list<Pixel*> pixelList;
        string id = "";
    public:
        Pixel(){
            c=0;
            p=0;
            h=0;
            e=0;
            id="P";
        }
        int getC();
        int getP();
        int getE();
        int getH();
        string getId();
        map<Pixel*, Edge*> getEdgeMap();
        list<Pixel*> getPixelList();
        void setC(int n);
        void setP(int n);
        void setE(int n);
        void setH(int n);
        void setId(string id);
        void addEdge(Edge* edge, Pixel* pixel);
        void addPixel(Pixel* pixel);
};
    int Pixel::getC(){
        return c;
    }
    int Pixel::getP(){
        return p;
    }
    int Pixel::getE(){
        return e;
    }
    int Pixel::getH(){
        return h;
    }
    string Pixel::getId(){
        return id;
    }
    map<Pixel*, Edge*> Pixel::getEdgeMap(){
        return edgeMap;
    }
    list<Pixel*> Pixel::getPixelList(){
        return pixelList;
    }
    void Pixel::setC(int n){
        c=n;
    }
    void Pixel::setP(int n){
        p=n;
    }
    void Pixel::setE(int n){
        e=n;
    }
    void Pixel::setH(int n){
        h=n;
    }
    void Pixel::setId(string id){
        id=id;
    }
    void Pixel::addEdge(Edge* edge, Pixel* pixel){
        edgeMap[pixel]=edge;
    }
    void Pixel::addPixel(Pixel* pixel){
        pixelList.push_back(pixel);
    }

Pixel* s = new Pixel();
Pixel* t = new Pixel();
list<Pixel*> L;

class Graph{
    private:
        vector<vector<Pixel*> >* graph ;
    public:
        Graph(int n, int m){
            graph = new vector<vector<Pixel*> >();
            Pixel* p;
            graph->resize(m);
            for (int i=0; i<m; i++){
                graph->at(i).resize(n);
                for (int j=0; j<n; j++){
                    p = new Pixel();
                    s->addPixel(p);
                    p->addPixel(s);
                    t->addPixel(p);
                    p->addPixel(t);
                    L.push_back(p);
                    graph->at(i).at(j) = p;
                }
            }
        }
        vector<vector<Pixel*> >* getGraph(){
            return graph;
        }
};

class Edge{
    private:
        int value;
        int pf;
        int nf;
    public:
        Edge();
        Edge(int val){
            value=val;
            pf=0;
            nf=0;
        }
        int getPf(){
            return pf;
        }
        int getNf(){
            return nf;
        }
        int setPf(int n){
            pf=n;
        }
        int setNf(int n){
            nf=n;
        }
        int getValue(){
            return value;
        }

};

class Algorithm{
    private:
    public:
        Algorithm(int n, int m){
            s->setH(n*m);
            for(pair<Pixel*,Edge*> p: s->getEdgeMap()){
                p.second->setPf(p.second->getValue());
                p.second->setNf(-p.second->getValue());
                p.first->setE(p.second->getValue());
                s->setE(s->getE()-p.second->getValue());
            }
        }
        void Discharge(Pixel* u);
        void Push(Pixel* u, Pixel* v, Edge* edge);
        void Relabel(Pixel* u);
        void relabelToFront(Pixel* source, Pixel* sink);
};

    void Algorithm::Push(Pixel* u, Pixel* v, Edge* edge){
        int d = min(u->getE(), edge->getValue()-edge->getPf());
        edge->setPf(edge->getPf() + d);
        edge->setNf(edge->getNf() - d);
        u->setE(u->getE()-d);
        v->setE(v->getE()+d);
    }
    void Algorithm::Relabel(Pixel* u){
        int minh=-1;
        for(pair<Pixel*,Edge*> p: u->getEdgeMap()){
            if(p.second->getValue()-p.second->getPf()>0){
                if(minh=-1) minh=p.first->getH();
                else minh=min(minh,p.first->getH());
                u->setH(minh + 1);
                if (u->getH() > s->getH()) u->setId("C");
            }
        }
    }
    void Algorithm::Discharge(Pixel* u){
        Pixel* v;
        list<Pixel*>::iterator it = u->getPixelList().begin();
        cout << u->getE();
        cout << u->getH();
        while(u->getE()>0){
            cout << "oi\n";
            if (it!=u->getPixelList().end()){
                cout << *(u->getPixelList().end()) << "\n";
                v = *it;
                Edge* e = u->getEdgeMap()[v];
                if(e->getValue() - e->getPf() > 0 && u->getH()==v->getH()+1){
                    Push(u, v, e);
                }
                else{
                    it++;
                }
            }
            else {
                Relabel(u);
            }
        }
        cout<< "dispreso\n";
    }
    void Algorithm::relabelToFront(Pixel* source, Pixel* sink){
        Pixel* u;
        for(Pixel* p: L){
            Push(s, p, s->getEdgeMap()[p]);
        }
        list<Pixel*>::iterator it = L.begin();
        while(it!=L.end()){
            u = *it;
            int oldH = u->getH();
            cout<< "pila\n";
            Discharge(u);
            cout<< "sai\n";
            if (u->getH() > oldH){
                L.erase(it);
                L.push_front(*it);
            }
            it++;
        }
        cout<< "IMPORTANTEpreso\n";
    }

int main(){
    int n, m, aux;
    Edge *e1, *e2;
    cin >> m;
    cin >> n;
    Graph* g = new Graph(n,m);
    vector<vector<Pixel*> >* gr = g->getGraph();
    for (int i=0; i<m;i++){
        for (int j=0; j<n; j++){
                cin >> aux;
                (*gr)[i][j]->setP(aux);
                e1 = new Edge(aux);
                (*gr)[i][j]->addEdge(e1, s);
                s->addEdge(e1, (*gr)[i][j]);
        }
    }
    cout << "--1--\n";
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
                cin >> aux;
                (*gr)[i][j]->setC(aux);
                e2 = new Edge(aux);
                (*gr)[i][j]->addEdge(e2, t);
                t->addEdge(e2, (*gr)[i][j]);
        }
    }
    cout << "--2--\n";
    for (int i=0; i<m;i++){
        for (int j=0; j<n-1;j++){
                cin >>aux;
                e1 = new Edge(aux);
                (*gr)[i][j]->addEdge(e1,(*gr)[i][j+1]);
                (*gr)[i][j]->addPixel((*gr)[i][j+1]);
                (*gr)[i][j+1]->addEdge(e1,(*gr)[i][j]);
                (*gr)[i][j+1]->addPixel((*gr)[i][j]);
        }
    }
    cout << "--3--\n";
    for(int i=0;i<m-1;i++){
        for (int j=0; j<n;j++){
                cin >> aux;
                e1 = new Edge(aux);
                (*gr)[i][j]->addEdge(e1,(*gr)[i+1][j]);
                (*gr)[i][j]->addPixel((*gr)[i+1][j]);
                (*gr)[i+1][j]->addEdge(e1,(*gr)[i][j]);
                (*gr)[i+1][j]->addPixel((*gr)[i][j]);
        }
    }
    cout << "--4--\n";
    Algorithm* a = new Algorithm(n, m);
    a->relabelToFront(s,t);

    cout << "--" << t->getE();

    for(vector<Pixel*> vp: *gr){
        for(Pixel* p: vp){
            cout << p->getId() + " ";
        }
        cout << endl;
    }

    int c=-1, b=-1;
    for(vector<Pixel*> vp: *gr){
        c++;
        for(Pixel* p: vp){
            b++;
            for(pair<Pixel*, Edge*> pe: p->getEdgeMap()){
                cout << c << "/" << b << "/" << pe.second->getValue() << "-"; 
            }
            cout<< " ";
        }
        b=-1;
        cout << endl;
    }


    return 0;
}

