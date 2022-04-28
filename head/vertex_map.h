#pragma once

#include <iostream>
#include <vector>

using namespace std;

typedef char VertexType;

class ArcNode{
    public:
        int             adjVex;
        int             weight;
};

class VNode{
    friend class ALGraph;
    private:
        VertexType      data;
        vector<ArcNode> arcs;
    public:
        int degree(){
            return arcs.size();
        }
};
typedef vector<VNode>   AdjList;
class ALGraph{
    friend class VNode;
    private:
        AdjList         vertices;
        int             vexnum;
        int             arcnum;
    public:
        ALGraph(int _vexnum = 0, int _arcnum = 0){
            vexnum = _vexnum;
            arcnum = _arcnum;
            vertices.reserve(vexnum);
            int x, y, _weight;
            for(int i = 0; i < vexnum; i ++){
                cin >> vertices[i].data;
                if(vertices[i].data == ' ' || vertices[i].data == '\n'){
                    i --;
                    continue;
                }
            }
            for(int i = 0; i < arcnum; i ++){
                cin >> x >> y >> _weight;
                vertices[x].arcs.push_back({y,_weight});
            }
        }
        void output(){
            for(auto i = vertices.begin(); i != vertices.end(); i ++){
                cout << i->data;
                for(auto j = i->arcs.begin(); j != i->arcs.end(); j ++)
                    cout << " -> " << vertices[j->adjVex].data;
                cout << endl << "   Degree:" << i->degree() << endl;
            }
        }
};