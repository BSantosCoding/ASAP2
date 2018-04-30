#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <string>
#include <map>
#include <limits>

using namespace std;
class Edge;
class Graph;
class Algorithm;

int NID=0;

class Pixel{
    private:
        int nid;
        int h;
        int e;
        map<Pixel*, Edge*> edgeMap;
        list<Pixel*> pixelList;
        string id = "";
    public:
        Pixel(){
            nid = NID;
            h=0;
            e=0;
            id="P";
            NID++;
        }
        int getE();
        int getH();
        string getId();
        map<Pixel*, Edge*> getEdgeMap();
        list<Pixel*> getPixelList();
        void setE(int n);
        void setH(int n);
        void setId(string idcp);
        void addEdge(Edge* edge, Pixel* pixel);
        void addPixel(Pixel* pixel);
};
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

Pixel *s, *t;
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
            if (pf<0) pf=0;
        }
        int getValue(){
            return value;
        }

};

class Algorithm{
    private:
    public:
};

int main(){
    int m, n, aux;
    Edge *e1, *e2;
    cin >> m;
    cin >> n;
    Graph *g = new Graph(n, m);
    vector<vector<Pixel*> >* gr = g->getGraph();

    for(int i=0; i<m; i++){
        for(int j=0; j<n; j++){
            cin >> aux;
            e1 = new Edge(aux);
            e2 = new Edge(aux);
            e2->setPf(aux); //meter uma das arestas "cheias"
            (*gr)[i][j]->addEdge(e1, s);
            (*gr)[i][j]->addPixel(s);

        }
    }

    return 0;
}