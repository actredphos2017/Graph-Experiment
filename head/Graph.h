#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class ALGraph_VNode;
class ArcNode;
class ALGraph;
class MGraph_VNode;
class MGraph;

typedef char                                    VertexType;
typedef int                                     Vertex;
typedef int                                     Arc;
typedef int                                     WeightType;
typedef enum{Directed, Disdirected}             GraphType;

typedef vector<ALGraph_VNode>                   AdjList;
typedef map<Vertex, map<Vertex, WeightType>>    AdjMap;

class ALGraph_VNode{
    friend class ALGraph;
    private:
        VertexType      data;
        vector<ArcNode> arcs;
}; 

class ArcNode{
    friend class ALGraph;
    private:
        Arc         adjvex;
        WeightType  weight;
    public:
        ArcNode(Arc adjvex, WeightType weight){
            this->adjvex = adjvex;
            this->weight = weight;
        }
};

class ALGraph{
    friend class ALGraph_VNode;
    friend class ArcNode;
    public:
        AdjList vertices;
        AdjList converse_vertices;
        Vertex  vexnum;
        Arc     arcnum;
        bool*   visited;
        bool    is_Directed_Graph;
    public:
        ALGraph(GraphType gt){
            this->vexnum = 0;
            this->arcnum = 0;
            this->visited = NULL;
            this->is_Directed_Graph = gt == Directed;
        }
        void Create(Vertex _vexnum, Arc _arcnum){
            Vertex x, y;
            WeightType w;
            this->vexnum = _vexnum;
            this->arcnum = _arcnum;
            this->vertices.resize(this->vexnum);
            this->converse_vertices.resize(this->vexnum);
            map<Vertex, map<Vertex, bool>> hash;
            for(Vertex i = 0; i < this->vexnum; i ++)
                cin >> this->vertices[i].data;
            if(this->is_Directed_Graph)
                for(Arc i = 0; i < this->arcnum; i ++){
                    cin >> x >> y >> w;
                    if(!hash[x][y]){
                        this->vertices[x].arcs.push_back(ArcNode(y, w));
                        this->converse_vertices[y].arcs.push_back(ArcNode(x, w));
                        hash[x][y] = true;
                    }
                }
            else
                for(Arc i = 0; i < this->arcnum; i ++){
                    cin >> x >> y >> w;
                    if(!hash[x>y?y:x][x>y?x:y]){
                        this->vertices[x].arcs.push_back(ArcNode(y, w));
                        this->converse_vertices[y].arcs.push_back(ArcNode(x, w));
                        this->vertices[y].arcs.push_back(ArcNode(x, w));
                        this->converse_vertices[x].arcs.push_back(ArcNode(y, w));
                        hash[x>y?y:x][x>y?x:y] = true;
                    }
                }
            this->visited = new bool[this->vexnum];
        }
        void Vertices_Output(){
            for(Vertex i = 0; i < this->vexnum; i ++){
                cout << this->vertices[i].data;
                for(Arc j = 0; j < this->vertices[i].arcs.size(); j ++)
                    cout << " -> " << this->vertices[this->vertices[i].arcs[j].adjvex].data;
                cout << endl;
            }
            return;
        }
        void Degree_Output(){
            for(Vertex i = 0; i < this->vexnum; i ++)
                cout << this->vertices[i].data << "'s Degree: " << this->vertices[i].arcs.size() << endl;
            return;
        }
        void Reset_Visited(){
            for(Vertex i = 0; i < this->vexnum; i ++)
                this->visited[i] = false;
            return;
        }
        void DFS(Vertex v, void (*visit)(VertexType)){
            Reset_Visited();
            DFS_main(v, visit);
            return;
        }
        void DFS_main(Vertex v, void (*visit)(VertexType)){
            visit(this->vertices[v].data);
            this->visited[v] = true;
            for(Arc i = 0; i < this->vertices[v].arcs.size(); i ++)
                if(!this->visited[this->vertices[v].arcs[i].adjvex])
                    DFS_main(this->vertices[v].arcs[i].adjvex, visit);
            return;
        }
        void BFS(Vertex v, void (*visit)(VertexType)){
            Reset_Visited();
            queue<int> q;
            q.push(v);
            this->visited[v] = true;
            visit(this->vertices[v].data);
            while(!q.empty()){
                v = q.front();
                q.pop();
                for(Arc i = 0; i < this->vertices[v].arcs.size(); i ++)
                    if(!this->visited[this->vertices[v].arcs[i].adjvex]){
                        this->visited[this->vertices[v].arcs[i].adjvex] = true;
                        visit(this->vertices[this->vertices[v].arcs[i].adjvex].data);
                        q.push(this->vertices[v].arcs[i].adjvex);
                    }
            }
            return;
        }
};

class MGraph_VNode{
    friend class MGraph;
    private:
        Vertex      loc;
        VertexType  data;
        MGraph*     father;
};

class MGraph{
    friend class MGraph_VNode;
    private:
        AdjMap                  adj_map;
        vector<MGraph_VNode>    vertices;
        Vertex                  vexnum;
        Arc                     arcnum;
        bool*                   visited;
        bool                    is_Directed_Graph;
    public:
        MGraph(GraphType gt){
            this->vexnum = 0;
            this->arcnum = 0;
            this->visited = NULL;
            this->is_Directed_Graph = gt == Directed;
        }
        void Create(Vertex _vexnum, int _arcnum){
            Vertex x, y;
            WeightType w;
            this->vexnum = _vexnum;
            this->arcnum = _arcnum;
            this->vertices.resize(this->vexnum);
            for(Vertex i = 0; i < this->vexnum; i ++){
                cin >> this->vertices[i].data;
                this->vertices[i].loc = i;
                this->vertices[i].father = this;
            }
            if(this->is_Directed_Graph)
                for(Arc i = 0; i < this->arcnum; i ++){
                    cin >> x >> y >> w;
                    adj_map[x][y] = w;
                }
            else
                for(Arc i = 0; i < this->arcnum; i ++){
                    cin >> x >> y >> w;
                    adj_map[x][y] = w;
                    adj_map[y][x] = w;
                }
            this->visited = new bool[this->vexnum];
        }
        Vertex degree(Vertex v){
            Vertex res = 0;
            for(auto i = this->adj_map[v].begin(); i != this->adj_map[v].end(); i ++)
                res ++;
            return res;
        }
        void Vertices_Output(){
            for(Vertex i = 0; i < this->vexnum; i ++)
                cout << this->vertices[i].data << " ";
            cout << endl;
        }
        void Degree_Output(){
            for(Vertex i = 0; i < this->vexnum; i ++)
                cout << this->vertices[i].data << "'s Degree: " << this->degree(i) << endl;
            cout << endl;
        }
        void Reset_Visited(){
            for(Vertex i = 0; i < this->vexnum; i ++)
                this->visited[i] = false;
            return;
        }
        void DFS(Vertex v, void (*visit)(VertexType)){
            Reset_Visited();
            DFS_main(v, visit);
            return;
        }
        void DFS_main(Vertex v, void (*visit)(VertexType)){
            this->visited[v] = true;
            visit(this->vertices[v].data);
            for(Vertex i = 0; i < this->vexnum; i ++)
                if(this->adj_map.find(v) != this->adj_map.end())
                    if(this->adj_map[v].find(i) != this->adj_map[v].end())
                        if(!this->visited[i])
                            DFS_main(i, visit);
            return;
        }
        void BFS(Vertex v, void (*visit)(VertexType)){
            Reset_Visited();
            queue<Vertex> q;
            q.push(v);
            this->visited[v] = true;
            visit(this->vertices[v].data);
            while(!q.empty()){
                Vertex x = q.front();
                q.pop();
                for(Vertex i = 0; i < this->vexnum; i ++)
                    if(this->adj_map.find(x) != this->adj_map.end())
                        if(this->adj_map[x].find(i) != this->adj_map[x].end())
                            if(!this->visited[i]){
                                q.push(i);
                                this->visited[i] = true;
                                visit(this->vertices[i].data);
                            }
            }
        }
};