#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <cstring>

using namespace std;

//邻接表
class ALGraph_VNode;
class ALGraph_ArcNode;
class ALGraph;

//邻接矩阵
class MGraph_VNode;
class MGraph;

//十字链表
class CLGraph_ArcNode;
class CLGraph;
class CLGraph_VNode;

//邻接多重表
class AMGraph;
class AMGraph_VNode;
class AMGraph_ArcNode;

typedef char                                        VertexType;
typedef int                                         Vertex;
typedef int                                         Arc;
typedef int                                         WeightType;
typedef enum{Directed, Disdirected}                 GraphType;
typedef enum{Weighted, Unweighted}                  ArcType;

class ALGraph_VNode{ //邻接表节点
    friend class ALGraph;
    private:
        VertexType              data;
        vector<ALGraph_ArcNode> arcs;
};

class ALGraph_ArcNode{ //邻接表弧
    friend class ALGraph;
    private:
        Arc         adjvex;
        WeightType  weight;
    public:
        ALGraph_ArcNode(Arc adjvex, WeightType weight);
};

class ALGraph{ //邻接表图
    friend class ALGraph_VNode;
    friend class ALGraph_ArcNode;
    public:
        vector<ALGraph_VNode> vertices;
        vector<ALGraph_VNode> converse_vertices;
        Vertex  vexnum;
        Arc     arcnum;
        bool*   visited;
        bool    is_Directed_Graph;
    public:
        ALGraph(GraphType gt);
        void Create(Vertex _vexnum, Arc _arcnum, ArcType at);
        void Vertices_Output();
        void Degree_Output();
        void Reset_Visited();
        void DFS(Vertex v, void (*visit)(VertexType));
        void DFS_main(Vertex v, void (*visit)(VertexType));
        void BFS(Vertex v, void (*visit)(VertexType));
        void FindInDegree(Vertex indegree[]);
        bool TopologicalSort(Vertex res[]);
        bool TopologicalSort(VertexType res[]);
};

class MGraph_VNode{ //邻接矩阵节点
    friend class MGraph;
    private:
        Vertex      loc;
        VertexType  data;
        MGraph*     father;
};

class MGraph{ //邻接矩阵图
    friend class MGraph_VNode;
    private:
        map<Vertex, map<Vertex, WeightType>>    adj_map;
        vector<MGraph_VNode>                    vertices;
        Vertex                                  vexnum;
        Arc                                     arcnum;
        bool*                                   visited;
        bool                                    is_Directed_Graph;
    public:
        MGraph(GraphType gt);
        void Create(Vertex _vexnum, int _arcnum, ArcType at);
        Vertex degree(Vertex v);
        void Vertices_Output();
        void Degree_Output();
        void Reset_Visited();
        void DFS(Vertex v, void (*visit)(VertexType));
        void DFS_main(Vertex v, void (*visit)(VertexType));
        void BFS(Vertex v, void (*visit)(VertexType));
        void FindInDegree(Vertex indegree[]);
        bool TopologicalSort(Vertex res[]);
        bool TopologicalSort(VertexType res[]);
};

class CLGraph_ArcNode{ //十字链表弧
    friend class CLGraph;
    friend class CLGraph_VNode;
    private:
        Vertex              tailvex;
        Vertex              headvex;
        CLGraph_ArcNode*    hlink;
        CLGraph_ArcNode*    tlink;
    public:
        CLGraph_ArcNode(Vertex _tailvex, Vertex _headvex);
};

class CLGraph_VNode{ //十字链表节点
    friend class CLGraph;
    friend class CLGraph_ArcNode;
    private:
        Vertex              loc;
        VertexType          data;
        CLGraph_ArcNode*    firstin;
        CLGraph_ArcNode*    firstout;
        CLGraph*            father;
        CLGraph_ArcNode* hfind(Vertex _headvex);
        CLGraph_ArcNode* tfind(Vertex _tailvex);
        void add_tail(CLGraph_ArcNode* _tp);
        void add_head(CLGraph_ArcNode* _hp);
    public:
        void add_arc(Vertex _headvex);
};

class CLGraph{ //十字链表图
    friend class CLGraph_ArcNode;
    friend class CLGraph_VNode;
    private:
        vector<CLGraph_VNode>   vertices;
        Vertex                  vexnum;
        Arc                     arcnum;
        bool*                   visited;
    public:
        CLGraph();
        void Create(Vertex _vexnum, Arc _arcnum);
        void Reset_Visited();
        Vertex out_degree(Vertex v);
        Vertex in_degree(Vertex v);
        void Degree_Output();
        void Vertices_Output();
        void DFS(Vertex v, void (*visit)(VertexType));
        void DFS_main(Vertex v, void (*visit)(VertexType));
        void BFS(Vertex v, void (*visit)(VertexType));
        void FindInDegree(Vertex indegree[]);
        bool TopologicalSort(Vertex res[]);
        bool TopologicalSort(VertexType res[]);
};

class AMGraph_ArcNode{
    friend class AMGraph;
    friend class AMGraph_VNode;
    private:
        bool mark;
        Vertex vex[2];
        AMGraph_ArcNode* link[2];
    public:
        AMGraph_ArcNode(Vertex ivex, Vertex jvex, bool SameLoc);
};

class AMGraph_VNode{
    friend class AMGraph;
    friend class AMGraph_ArcNode;
    private:
        Vertex loc;
        VertexType data;
        AMGraph_ArcNode* first_arc;
        AMGraph* father;
    public:
        void push_arc(AMGraph_ArcNode* ap);
        void add_arc(Vertex v);
};

class AMGraph{
    friend class AMGraph_ArcNode;
    friend class AMGraph_VNode;
    private:
        Vertex  vexnum;
        Arc     arcnum;
        vector<AMGraph_VNode> vertices;
        bool* visited;
        AMGraph_ArcNode* find_arc(Vertex iv, Vertex jv, bool &SameLoc);
    public:
        AMGraph();
        void Create(Vertex _vexnum, Arc _arcnum);
        void Reset_Visited();
        void DFS(Vertex v, void (*visit)(VertexType));
        void DFS_main(Vertex v, void (*visit)(VertexType));
        void BFS(Vertex v, void (*visit)(VertexType));
};

#include "Graph_main.h"