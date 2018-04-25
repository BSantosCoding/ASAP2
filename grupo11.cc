#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <set>
#include <utility>
#include <string>

using namespace std;
class Edge;
class Graph;
class Algorithm;

class Pixel{
    private:
        int compare;
        int c;
        int p;
        int h;
        int e;
        list<pair <Edge*,Pixel*> > edgeList;
        list<Pixel*> pixelList;
        string id = "";
    public:
        Pixel(){
            c=-1;
            p=-1;
            h=0;
            e=0;
        }
        int getC();
        int getP();
        int getE();
        int getH();
        int getCompare();
        string getId();
        list<pair <Edge*,Pixel*> > getEdgeList();
        list<Pixel*> getPixelList();
        void setC(int n);
        void setP(int n);
        void setE(int n);
        void setH(int n);
        void setCompare(int n);
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
    int Pixel::getCompare(){
        return compare;
    }
    string Pixel::getId(){
        return id;
    }
    list<pair <Edge*,Pixel*> > Pixel::getEdgeList(){
        return edgeList;
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
    void Pixel::setCompare(int n){
        compare=n;
    }
    void Pixel::setId(string id){
        id=id;
    }
    void Pixel::addEdge(Edge* edge, Pixel* pixel){
        edgeList.push_back(make_pair(edge,pixel));
    }
    void Pixel::addPixel(Pixel* pixel){
        pixelList.push_back(pixel);
    }

class Graph{
    private:
        vector<vector<Pixel*> > graph;
    public:
        Graph(int n, int m){
            Pixel* p;
            int comparen=0;
            graph.resize(n);
            for (int i=0; i<n; i++){
                graph.at(i).resize(m);
                for (int j=0; j<m; j++){
                    p->setCompare(comparen);
                    comparen++;
                    L.push_back(p);
                    graph.at(i).at(j) = p;
                }
            }
        }
        vector<vector<Pixel*> > getGraph(){
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
        Pixel* current;
        Pixel* head;
        Pixel* neighboor;
    public:
        Algorithm(int n, int m){
            s->setH(n*m);
            for(pair<Edge* ,Pixel* > p: s->getEdgeList()){
                p.first->setPf(p.first->getValue());
                p.first->setNf(-p.first->getValue());
                p.second->setE(p.first->getValue());
                s->setE(s->getE()-p.first->getValue());
            }
        }
        void Discharge(Pixel* u);
        void Push(Pixel* u, Pixel* v, Edge* edge);
        void Relabel(Pixel* u);
        void relabelToFront(Graph* g, Pixel* source, Pixel* sink);
};

    void Algorithm::Push(Pixel* u, Pixel* v, Edge* edge){
        int d = min(u->getE(), edge->getValue());
        edge->setPf(edge->getPf()+d);
        edge->setNf(-edge->getPf());
        u->setE(u->getE()-d);
        v->setE(v->getE()+d);
    }
    void Algorithm::Relabel(Pixel* u){
        int minh=-1;
        for(pair<Edge*,Pixel*> p: u->getEdgeList()){
            if(minh=-1) minh=p.second->getH();
            else minh=min(minh,p.second->getH());
        }
    }
    void Algorithm::Discharge(Pixel* u){
        Pixel* v;
        while(u->getE()>0){
            v = current;
            if (v==NULL){
                Relabel(u);
                current = head;
            }
            else{
                Edge* e;
                for (pair<Edge*,Pixel*> p: u->getEdgeList()){
                    if (p.second->getCompare()==v->getCompare()){
                        e=p.first;
                    }
                }
                if(e->getValue() && u->getH()==v->getH()+1){
                    Push(u, v, e);
                }
                else{
                    current=neighboor;
                }
            }
        }
    }
    void Algorithm::relabelToFront(Graph* g, Pixel* source, Pixel* sink){

    }

Pixel* s = new Pixel();
Pixel* t = new Pixel();
list<Pixel*> L;

int main(){
    int n, m, aux;
    Edge *e1, *e2;
    cin >> n;
    cin >> m;
    Graph* g = new Graph(n,m);
    vector<vector<Pixel*> > gr = g->getGraph();
    for (int i=0; i<n;i++){
        for (int j=0; j<m; j++){
                cin >> aux;
                gr[i][j]->setP(aux);
                e1 = new Edge(aux);
                gr[i][j]->addEdge(e1, s);
                s->addEdge(e1, gr[i][j]);
        }
    }
    for (int i=0; i<n; i++){
        for (int j=0; j<m; j++){
                cin >> aux;
                gr[i][j]->setC(aux);
                e2 = new Edge(aux);
                gr[i][j]->addEdge(e2, t);
                t->addEdge(e2, gr[i][j]);
        }
    }
    for (int i=0; i<n;i++){
        for (int j=0; j<m-1;j++){
                cin >>aux;
                e1 = new Edge(aux);
                gr[i][j]->addEdge(e1,gr[i][j+1]);
                gr[i][j]->addPixel(gr[i][j+1]);
                gr[i][j+1]->addEdge(e1,gr[i][j]);
                gr[i][j+1]->addPixel(gr[i][j]);
        }
    }
    for(int i=0;i<n-1l;i++){
        for (int j=0; j<m;j++){
                cin >> aux;
                e1 = new Edge(aux);
                gr[i][j]->addEdge(e1,gr[i+1][j]);
                gr[i][j]->addPixel(gr[i+1][j]);
                gr[i+1][j]->addEdge(e1,gr[i][j]);
                gr[i+1][j]->addPixel(gr[i][j]);
        }
    }
    Algorithm* a = new Algorithm(n, m);
    return 0;
}

