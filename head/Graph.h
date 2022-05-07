#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

//邻接表
class ALGraph_VNode;
class ALGraph_ArcNode;
class ALGraph;

//邻接矩阵
class MGraph_VNode;
class MGraph;

//十字链表
class OLGraph_ArcNode;
class OLGraph;
class OLGraph_VNode;

typedef char                                        VertexType;
typedef int                                         Vertex;
typedef int                                         Arc;
typedef int                                         WeightType;
typedef enum{Directed, Disdirected}                 GraphType;

class ALGraph_VNode{ //邻接表节点
    friend class ALGraph;
    private:
        VertexType      data;
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
        void Create(Vertex _vexnum, Arc _arcnum);
        void Vertices_Output();
        void Degree_Output();
        void Reset_Visited();
        void DFS(Vertex v, void (*visit)(VertexType));
        void DFS_main(Vertex v, void (*visit)(VertexType));
        void BFS(Vertex v, void (*visit)(VertexType));
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
        void Create(Vertex _vexnum, int _arcnum);
        Vertex degree(Vertex v);
        void Vertices_Output();
        void Degree_Output();
        void Reset_Visited();
        void DFS(Vertex v, void (*visit)(VertexType));
        void DFS_main(Vertex v, void (*visit)(VertexType));
        void BFS(Vertex v, void (*visit)(VertexType));
};

class OLGraph_ArcNode{ //十字链表弧
    friend class OLGraph;
    friend class OLGraph_VNode;
    private:
        Vertex              tailvex;
        Vertex              headvex;
        OLGraph_ArcNode*    hlink;
        OLGraph_ArcNode*    tlink;
    public:
        OLGraph_ArcNode(Vertex _tailvex, Vertex _headvex);
};

class OLGraph_VNode{ //十字链表节点
    friend class OLGraph;
    friend class OLGraph_ArcNode;
    private:
        Vertex              loc;
        VertexType          data;
        OLGraph_ArcNode*    firstin;
        OLGraph_ArcNode*    firstout;
        OLGraph*            father;
        OLGraph_ArcNode* hfind(Vertex _headvex);
        OLGraph_ArcNode* tfind(Vertex _tailvex);
        void add_tail(OLGraph_ArcNode* _tp);
        void add_head(OLGraph_ArcNode* _hp);
    public:
        void add_arc(Vertex _headvex);
};

class OLGraph{ //十字链表图
    friend class OLGraph_ArcNode;
    friend class OLGraph_VNode;
    private:
        vector<OLGraph_VNode>   vertices;
        Vertex                  vexnum;
        Arc                     arcnum;
        bool*                   visited;
    public:
        OLGraph();
        void Create(Vertex _vexnum, Arc _arcnum);
        void Reset_Visited();
        Vertex out_degree(Vertex v);
        Vertex in_degree(Vertex v);
        void Degree_Output();
};

#include "Graph_main.h"