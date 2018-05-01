#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <string>
#include <map>
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
        map<Pixel*, Edge*> edgeMap;
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
        Pixel* getParent();
        string getId();
        map<Pixel*, Edge*> getEdgeMap();
        list<Pixel*> getPixelList();
        void setC(int n);
        void setNid(int n);
        void setP(int n);
        void setParent(Pixel* p);
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
    Pixel* Pixel::getParent(){
        return parent;
    }
    int Pixel::getNid(){
        return nid;
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
    void Pixel::setNid(int n){
        nid=n;
    }
    void Pixel::setP(int n){
        p=n;
    }
    void Pixel::setParent(Pixel* p){
        parent=p;
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

Pixel* spred = new Pixel();
Pixel* startp = new Pixel();
Pixel* s = new Pixel();
Pixel* t = new Pixel();
list<Pixel*> L;

class Graph{
    private:
        vector<vector<Pixel*> >* graph ;
    public:
        Graph(int n, int m){
            int nid=-1;
            spred->setNid(nid); nid++;
            startp->setNid(nid); nid++;
            s->setNid(nid); nid++;
            t->setNid(nid); nid++;
            graph = new vector<vector<Pixel*> >();
            graph->resize(m);
            for (int i=0; i<m; i++){
                graph->at(i).resize(n);
                for (int j=0; j<n; j++){
                    Pixel* p = new Pixel();
                    p->setNid(nid); nid++;
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
    public:
        Edge();
        Edge(int val){
            value=val;
        }
        int getValue(){
            return value;
        }
        void setValue(int n){
            value=n;
        }

};

class Algorithm{
    private:
        int m, n, flow;
        list<Pixel*> pixelPath;
        list<Edge*> edgePath;
    public:
        Algorithm(int n, int m){
            m=m;
            n=n;
            s->setParent(spred);
        }
        inline int ekBfs(){
            edgePath.clear();
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
                list<Pixel*>::iterator it;
                for(auto it = adjLst.begin(); it!=adjLst.end(); it++){
                    Edge* e = u->getEdgeMap()[*it];
                    if(e->getValue()>0 && (*it)->getParent()->getNid()==startp->getNid()){
                        ekBfsQueue.push((*it));
                        augmentCap.push(min(cap, e->getValue()));
                        (*it)->setParent(u);
                        if((*it)->getNid()==t->getNid()){
                            augmentFlow = min(cap  , e->getValue());
                            break;
                        }
                        edgePath.push_back(e);
                        pixelPath.push_back((*it));
                    }
                }
            }
            if(augmentFlow>0){
                Pixel* currentPixel = t;
                while(currentPixel->getNid() != s->getNid()){
                    currentPixel->getParent()->getEdgeMap()[currentPixel]->setValue(currentPixel->getParent()->getEdgeMap()[currentPixel]->getValue()-augmentFlow);
                    if (currentPixel->getNid()!=t->getNid() && currentPixel->getParent()->getNid()!=s->getNid())
                        currentPixel->getEdgeMap()[currentPixel->getParent()]->setValue(currentPixel->getEdgeMap()[currentPixel->getParent()]->getValue()+augmentFlow);
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

        void findCut(){
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
                (*gr)[i][j]->setP(aux);
                if(aux!=0){
                    e1 = new Edge(aux);
                    s->addEdge(e1, (*gr)[i][j]);
                    s->addPixel((*gr)[i][j]);
                } 
        }
    }
    for (int i=0; i<m; i++){
        for (int j=0; j<n; j++){
                cin >> aux;
                (*gr)[i][j]->setC(aux);
                if(aux!=0){
                    e1 = new Edge(aux);
                    (*gr)[i][j]->addEdge(e1, t);
                    (*gr)[i][j]->addPixel(t);
                    /*if((*gr)[i][j]->getC()==(*gr)[i][j]->getP()){
                        s->getEdgeMap().erase((*gr)[i][j]);
                        s->getPixelList().remove((*gr)[i][j]);
                    }
                    else if((*gr)[i][j]->getC()>(*gr)[i][j]->getP()){
                        s->getEdgeMap().erase((*gr)[i][j]);
                        s->getPixelList().remove((*gr)[i][j]);
                        e1 = new Edge(aux-(*gr)[i][j]->getP());
                        (*gr)[i][j]->addEdge(e1, t);
                        (*gr)[i][j]->addPixel(t);
                    }
                    else{
                        s->getEdgeMap()[(*gr)[i][j]]->setValue((*gr)[i][j]->getP()-(*gr)[i][j]->getC());
                    }*/
                }
                //flow += min((*gr)[i][j]->getC(), (*gr)[i][j]->getP());
        }
    }
    for (int i=0; i<m;i++){
        for (int j=0; j<n-1;j++){
                cin >>aux;
                if(aux!=0){
                    e1 = new Edge(aux);
                    e2 = new Edge(aux);
                    (*gr)[i][j]->addEdge(e1,(*gr)[i][j+1]);
                    (*gr)[i][j]->addPixel((*gr)[i][j+1]);
                    (*gr)[i][j+1]->addEdge(e2,(*gr)[i][j]);
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
                    (*gr)[i][j]->addEdge(e1,(*gr)[i+1][j]);
                    (*gr)[i][j]->addPixel((*gr)[i+1][j]);
                    (*gr)[i+1][j]->addEdge(e2,(*gr)[i][j]);
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
