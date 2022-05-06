#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

typedef char                                    VertexType;
typedef int                                     Vertex;
typedef int                                     WeightType;
typedef map<Vertex, map<Vertex, WeightType>>    AdjMap;
typedef enum{Directed, Disdirected}             GraphType;

class VNode{
    friend class MGraph;
    private:
        Vertex      loc;
        VertexType  data;
        MGraph*     father;
    public:
        int degree(){
            int r = 0;
            for(int i = 0; i < this->father->vexnum; i ++)
                if(this->father->arcs.find(this->loc) != this->father->arcs.endl())
                    if(this->father->arcs[this->loc].find(i) != this->father->arcs[this->loc].endl())
                        r ++;
            return r;
        }
};

class MGraph{
    friend class VNode;
    private:
        AdjMap  arcs;
        vector<VNode> vertices;
        Vertex  vexnum;
        int     arcnum;
        bool*   visited;
        bool    is_Directed_Graph;
    public:
        MGraph(GraphType gt){
            this->VNode = NULL;
            this->vexnum = 0;
            this->arcnum = 0;
            this->visited = NULL;
            this->is_Directed_Graph = gt == Directed;
        }
        void Create(int _vexnum, int _arcnum){
            Vertex x, y;
            WeightType w;
            this->vexnum = _vexnum;
            this->arcnum = _arcnum;
            for(int i = 0; i < this->vexnum; i ++)
                cin >> this->vertices[i].data;
            if(this->is_Directed_Graph)
                for(int i = 0; i < this->arcnum; i ++){
                    cin >> x >> y >> w;
                    arcs[x][y] = w;
                }
            else
                for(int i = 0; i < this->arcnum; i ++){
                    cin >> x >> y >> w;
                    arcs[x][y] = w;
                    arcs[y][x] = w;
                }
            this->visited = new bool[this->vexnum];
        }
        void Vertices_Output(){
            for(int i = 0; i < this->vexnum; i ++){
                cout << this->vertices[i].data;
                for(int j = 0; j < this->vertices[i].arcs.size(); j ++)
                    cout << " -> " << this->vertices[this->vertices[i].arcs[j].adjvex].data;
                cout << endl;
            }
            return;
        }
        void Degree_Output(){
            for(int i = 0; i < this->vexnum; i ++)
                cout << this->vertices[i].data << "'s Degree: " << this->vertices[i].degree() << endl;
            return;
        }
        void Reset_Visited(){
            for(int i = 0; i < this->vexnum; i ++)
                this->visited[i] = false;
            return;
        }
        void DFS(int v, void (*visit)(VertexType)){
            Reset_Visited();
            DFS_main(v, visit);
            return;
        }
        void DFS_main(int v, void (*visit)(VertexType)){
            visit(this->vertices[v].data);
            this->visited[v] = true;
            for(int i = 0; i < this->vertices[v].arcs.size(); i ++)
                if(!this->visited[this->vertices[v].arcs[i].adjvex])
                    DFS_main(this->vertices[v].arcs[i].adjvex, visit);
            return;
        }
        void BFS(int v, void (*visit)(VertexType)){
            Reset_Visited();
            queue<int> q;
            q.push(v);
            this->visited[v] = true;
            visit(this->vertices[v].data);
            while(!q.empty()){
                v = q.front();
                q.pop();
                for(int i = 0; i < this->vertices[v].arcs.size(); i ++)
                    if(!this->visited[this->vertices[v].arcs[i].adjvex]){
                        this->visited[this->vertices[v].arcs[i].adjvex] = true;
                        visit(this->vertices[this->vertices[v].arcs[i].adjvex].data);
                        q.push(this->vertices[v].arcs[i].adjvex);
                    }
            }
            return;
        }
};