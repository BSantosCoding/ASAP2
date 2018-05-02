#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <string>
#include <unordered_map>
#include <limits>
#include <stack>

using namespace std;
class Edge;
class Graph;
class Algorithm;

class Pixel{
    private:
        int nid;
        int c;
        int p;
        Pixel* parent;
        Edge* parentE;
        list<Edge*> edgeMap;
        list<Pixel*> pixelList;
        string id = "";

    public:
        Pixel(){
            c=0;
            p=0;
            id="P";
            parent = NULL;
        }
        int getC();
        int getP();
        int getNid();
        Edge* getParentEdge();
        Pixel* getParent();
        string getId();
        list<Edge*> getEdgeMap();
        list<Pixel*> getPixelList();
        void setC(int n);
        void setNid(int n);
        void setP(int n);
        void setParentEdge(Edge* e);
        void setParent(Pixel* p);
        void setId(string idcp);
        void addEdge(Edge* edge);
        void addPixel(Pixel* pixel);
};
    inline int Pixel::getC(){
        return c;
    }
    inline int Pixel::getP(){
        return p;
    }
    inline Edge* Pixel::getParentEdge(){
        return parentE;
    }
    inline Pixel* Pixel::getParent(){
        return parent;
    }
    inline int Pixel::getNid(){
        return nid;
    }
    inline string Pixel::getId(){
        return id;
    }
    inline list<Edge*> Pixel::getEdgeMap(){
        return edgeMap;
    }
    inline list<Pixel*> Pixel::getPixelList(){
        return pixelList;
    }
    inline void Pixel::setC(int n){
        c=n;
    }
    inline void Pixel::setNid(int n){
        nid=n;
    }
    inline void Pixel::setP(int n){
        p=n;
    }
    inline void Pixel::setParentEdge(Edge* e){
        parentE=e;
    }
    inline void Pixel::setParent(Pixel* p){
        parent=p;
    }
    inline void Pixel::setId(string idcp){
        id=idcp;
    }
    inline void Pixel::addEdge(Edge* edge){
        edgeMap.push_back(edge);
    }
    inline void Pixel::addPixel(Pixel* pixel){
        pixelList.push_back(pixel);
    }

Pixel* spred = new Pixel();
Pixel* startp = new Pixel();
Pixel* s = new Pixel();
Pixel* t = new Pixel();
list<Pixel*> L;
int nid = -1;

class Graph{
    private:
        vector<vector<Pixel*> >* graph ;
    public:
        Graph(int n, int m){
            spred->setNid(nid); nid++;
            startp->setNid(nid); nid++;
            s->setNid(nid); nid++;
            t->setNid(nid); nid++;
            graph = new vector<vector<Pixel*> >(m);
        }
        inline vector<vector<Pixel*> >* getGraph(){
            return graph;
        }
};

class Edge{
    private:
        int value;
        Edge* e;
    public:
        Edge();
        Edge(int val){
            value=val;
        }

        inline int getValue(){
            return value;
        }
        inline void setValue(int n){
            value=n;
        }
        inline void setEdge (Edge* ed){
            e=ed;
        }
        inline Edge* getEdge(){
            return e;
        }
};

class Algorithm{
    private:
        int m, n, flow;
        list<Pixel*> pixelPath;
    public:
        Algorithm(int n, int m){
            m=m;
            n=n;
            s->setParent(spred);
        }
        inline int ekBfs(){
            pixelPath.clear();
            int augmentFlow = 0;
            for(Pixel* p: L){
                p->setParent(startp);
            } 
            t->setParent(startp);
            stack<Pixel*> ekBfsQueue = stack<Pixel*>();
            stack<int> augmentCap = stack<int>();
            ekBfsQueue.push(s);
            augmentCap.push(numeric_limits<int>::max());
            while(!ekBfsQueue.empty()){
                Pixel* u = ekBfsQueue.top();
                int cap = augmentCap.top();
                ekBfsQueue.pop();
                augmentCap.pop();
                list<Pixel*> adjLst = u->getPixelList();
                list<Edge*> weightLst = u->getEdgeMap();
                list<Pixel*>::iterator it;
                list<Edge*>::iterator itw;
                for(it = adjLst.begin(),itw = weightLst.begin(); it!=adjLst.end(), itw!=weightLst.end(); it++, itw++){
                    if((*itw)->getValue()>0 && (*it)->getParent()->getNid()==startp->getNid()){
                        ekBfsQueue.push((*it));
                        augmentCap.push(min(cap, (*itw)->getValue()));
                        (*it)->setParent(u);
                        (*it)->setParentEdge((*itw));
                        if((*it)->getNid()==t->getNid()){
                            augmentFlow = min(cap  , (*itw)->getValue());
                            break;
                        }
                        pixelPath.push_back((*it));
                    }
                }
            }
            if(augmentFlow>0){
                Pixel* currentPixel = t;
                while(currentPixel->getNid()!=s->getNid()){
                    currentPixel->getParentEdge()->setValue(currentPixel->getParentEdge()->getValue()-augmentFlow);
                    if(currentPixel->getParentEdge()->getEdge()!=NULL && currentPixel->getParentEdge()!=NULL){
                        currentPixel->getParentEdge()->getEdge()->setValue(currentPixel->getParentEdge()->getEdge()->getValue()+augmentFlow);
                    }
                    currentPixel = currentPixel->getParent();
                }
            }
            return augmentFlow;
        }

        inline int EK(){
            flow = 0;
            while(true){
                int currentFlow = ekBfs();
                if(currentFlow==0){ 
                    break;
                }
                else {
                    flow += currentFlow;
                }
            }
            return flow;
        }

        inline void findCut(){
            for(Pixel* p:pixelPath){
                p->setId("C");
            }
        }

};

int main(){
    int n, m, aux,flow=0;
    Edge *e1, *e2;
    cin >> m;
    cin >> n;
    Graph* g = new Graph(n,m);
    vector<vector<Pixel*> >* gr = g->getGraph();
    for (int i=0; i<m;i++){
        for (int j=0; j<n; j++){
                cin >> aux;
                Pixel* p = new Pixel();
                p->setNid(nid); nid++;
                p->setP(aux);
                L.push_back(p);
                (*gr)[i].push_back(p);
        }
    }
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
            cin >> aux;
            (*gr)[i][j]->setC(aux);
            flow += min((*gr)[i][j]->getC(), (*gr)[i][j]->getP());
            if((*gr)[i][j]->getC()>(*gr)[i][j]->getP()){
                e1 = new Edge((aux-(*gr)[i][j]->getP()));
                (*gr)[i][j]->addEdge(e1);
                (*gr)[i][j]->addPixel(t);
            }
            else if((*gr)[i][j]->getC()<(*gr)[i][j]->getP()){
                e1 = new Edge((*gr)[i][j]->getP()-aux);
                s->addEdge(e1);
                s->addPixel((*gr)[i][j]);
            }
        }
    }
    for (int i=0; i<m;i++){
        for (int j=0; j<n-1;j++){
                cin >>aux;
                if(aux!=0){
                    e1 = new Edge(aux);
                    e2 = new Edge(aux);
                    e1->setEdge(e2);
                    e2->setEdge(e1);
                    (*gr)[i][j]->addEdge(e1);
                    (*gr)[i][j]->addPixel((*gr)[i][j+1]);
                    (*gr)[i][j+1]->addEdge(e2);
                    (*gr)[i][j+1]->addPixel((*gr)[i][j]);
                }
        }
    }
    for(int i=0;i<m-1;i++){
        for (int j=0; j<n;j++){
                cin >> aux;
                if(aux!=0){
                    e1 = new Edge(aux);
                    e2 = new Edge(aux);
                    e2->setEdge(e1);
                    e1->setEdge(e2);
                    (*gr)[i][j]->addEdge(e1);
                    (*gr)[i][j]->addPixel((*gr)[i+1][j]);
                    (*gr)[i+1][j]->addEdge(e2);
                    (*gr)[i+1][j]->addPixel((*gr)[i][j]);
                }
        }
    }

    Algorithm* a = new Algorithm(n, m);
    flow += a->EK();
    a->findCut();
    cout << flow << "\n";

    cout << endl;
    for(vector<Pixel*> vp: (*gr)){
        for(Pixel* p: vp){
            cout << p->getId() << " ";
        }
        cout << endl;
    }

    return 0;
}
