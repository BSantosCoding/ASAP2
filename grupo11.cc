#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <set>
#include <utility>
#include <string>
#include <map>
#include <limits>

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
        void setId(string idcp);
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
    void Pixel::setId(string idcp){
        id=idcp;
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
    public:
        Edge();
        Edge(int val){
            value=val;
            pf=0;
        }
        int getPf(){
            return pf;
        }
        void setPf(int n){
            pf=n;
        }
        int getValue(){
            return value;
        }

};

class Algorithm{
    private:
    public:
        Algorithm(int n, int m){
            s->setH(n*m + 2);
        }
        void Discharge(Pixel* u);
        void Push(Pixel* u, Pixel* v, Edge* edge);
        void Relabel(Pixel* u);
        void relabelToFront(Pixel* source, Pixel* sink);
};

    void Algorithm::Push(Pixel* u, Pixel* v, Edge* edge){
        cout << "Sou:"<< u->getH() << "Para:"<<v->getH() << "\n";
        int d = min(u->getE(), edge->getValue()-edge->getPf());
        edge->setPf(edge->getPf() + d);
        v->getEdgeMap()[u]->setPf(v->getEdgeMap()[u]->getPf()-d);
        //cout << "AntesExcesso:" << u->getE();
        u->setE(u->getE()-d);
        v->setE(v->getE()+d);
        //cout << "DepoisExcesso:" << u->getE() << " Mandei:" << d << "\n";
    }
    void Algorithm::Relabel(Pixel* u){
        int minh=numeric_limits<int>::max();
        cout << "\nRelabel";
        for(pair<Pixel*,Edge*> p: u->getEdgeMap()){//PROBLEMA
            cout << "\nDENTRO" << p.second->getValue() << "-" << p.second->getPf() << "|" << p.first->getH() << "-" << u->getH();
            if((p.second->getValue()-p.second->getPf()>0) && (p.first->getH()>= u->getH())){
                cout << "\nSafety";
                minh=min(minh, min(p.first->getH(), u->getH()));
                u->setH(minh + 1);
            }
        }
        if (u->getH() > s->getH()) u->setId("C");
        cout << "\nDei Relabel para:"<< u->getH();
    }
    void Algorithm::Discharge(Pixel* u){
        list<Pixel*> test = u->getPixelList();
        list<Pixel*>::iterator it = test.begin();
        while(u->getE()>0){ //excesso > 0
            if (it==test.end()){ //se houver adjacencias
                //cout << "\nVou dar relabel";
                //cout << "\nloop1";
                Relabel(u);
                it = test.begin();
            }
            else { //caso nao haja mais vertices Relabel
                //cout << "\nloop2";
                Edge* e = u->getEdgeMap()[*it];
                //cout << "\nTeste:" << e->getValue() << "-" << e->getPf() << " H" << u->getH() << "-" << (*it)->getH();
                if((u->getH()==(*it)->getH()+1) && (e->getValue() - e->getPf() > 0)){ //se poder mandar mais de 0 e a altura
                    //cout << "\nPosso dar Push";
                    Push(u, *it, e);
                }
                else {it++;}
            }
        }
    }
    void Algorithm::relabelToFront(Pixel* source, Pixel* sink){
        Pixel* u;
        int sexcess=0;

        for(Pixel* p: L){ //fazer o push inicial (mandar de s para todos)
            Push(s, p, s->getEdgeMap()[p]);
        }
        //cout << s->getE();

        list<Pixel*>::iterator it = L.begin(); //meter o iterador no inicio da lista
        while(it!=L.end()){ //enquanto houver vertices
            u = *it;
            int oldH = u->getH();
            Discharge(u);
            //cout << "\nDischarge Completo";
            if (u->getH() > oldH){
                L.erase(it);
                L.push_front(*it);
                it = L.begin();
            }
            else it++;
        }
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
                e2 = new Edge(aux);
                e2->setPf(aux);
                s->setE(s->getE()+aux);
                (*gr)[i][j]->addEdge(e2, s);
                s->addEdge(e1, (*gr)[i][j]);
        }
    }
    cout << "--1--\n";
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
                cin >> aux;
                (*gr)[i][j]->setC(aux);
                e1 = new Edge(aux);
                e2 = new Edge(0);
                (*gr)[i][j]->addEdge(e1, t);
                t->addEdge(e2, (*gr)[i][j]);
        }
    }
    cout << "--2--\n";
    for (int i=0; i<m;i++){
        for (int j=0; j<n-1;j++){
                cin >>aux;
                e1 = new Edge(aux);
                e2 = new Edge(aux);
                e2->setPf(aux);
                (*gr)[i][j]->addEdge(e1,(*gr)[i][j+1]);
                (*gr)[i][j]->addPixel((*gr)[i][j+1]);
                (*gr)[i][j+1]->addEdge(e2,(*gr)[i][j]);
                (*gr)[i][j+1]->addPixel((*gr)[i][j]);
        }
    }
    cout << "--3--\n";
    for(int i=0;i<m-1;i++){
        for (int j=0; j<n;j++){
                cin >> aux;
                e1 = new Edge(aux);
                e2 = new Edge(aux);
                e2->setPf(aux);
                (*gr)[i][j]->addEdge(e1,(*gr)[i+1][j]);
                (*gr)[i][j]->addPixel((*gr)[i+1][j]);
                (*gr)[i+1][j]->addEdge(e2,(*gr)[i][j]);
                (*gr)[i+1][j]->addPixel((*gr)[i][j]);
        }
    }
    cout << "--4--\n";
    for(int i=0;i<m;i++){
        for(int j=0; j<n;j++){
            (*gr)[i][j]->addPixel(t);
        }
    }


    Algorithm* a = new Algorithm(n, m);
    a->relabelToFront(s,t);

    cout << "-->" << t->getE()<< "-" << s->getE() << "\n";

    for(vector<Pixel*> vp: *gr){
        for(Pixel* p: vp){
            cout << p->getId() << "-" << p->getH() << "-" << p->getE() <<" ";
        }
        cout << endl;
    }

    return 0;
}

