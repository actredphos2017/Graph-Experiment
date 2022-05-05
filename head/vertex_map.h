#pragma once

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
class ArcNode{
    public:
        int adjvex;
        int weight;
};

#define VertexType char //顶点元素类型
class VNode{
    public:
        VertexType data;
        vector<ArcNode>  arcs;
}; 

typedef vector<VNode> AdjList;
class ALGraph{
    public:
        AdjList vertices;
        AdjList converse_vertices;
        int vexnum;
        int arcnum;
        bool *visited;
    public:
        ALGraph(){
            this->vexnum = 0;
            this->arcnum = 0;
            this->visited = NULL;
        }
        void Directed_Create(int _vexnum, int _arcnum){
            int x, y, w;
            this->vexnum = _vexnum;
            this->arcnum = _arcnum;
            this->vertices.resize(this->vexnum);
            for(int i = 0; i < this->vexnum; i ++)
                cin >> this->vertices[i].data;
            for(int i = 0; i < this->arcnum; i ++){
                cin >> x >> y >> w;
                this->vertices[x].arcs.push_back(ArcNode{y, w});
            }
            this->visited = new bool[this->vexnum];
        }
        void Disdirected_Create(int _vexnum, int _arcnum){
            int x, y, w;
            this->vexnum = _vexnum;
            this->arcnum = _arcnum;
            this->vertices.resize(this->vexnum);
            for(int i = 0; i < this->vexnum; i ++)
                cin >> this->vertices[i].data;
            for(int i = 0; i < this->arcnum; i ++){
                cin >> x >> y >> w;
                this->vertices[x].arcs.push_back(ArcNode{y, w});
                this->vertices[y].arcs.push_back(ArcNode{x, w});
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
                cout << this->vertices[i].data << "'s Degree: " << this->vertices[i].arcs.size() << endl;
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