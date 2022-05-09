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
class CLGraph_ArcNode;
class CLGraph;
class CLGraph_VNode;

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
};


ALGraph_ArcNode::ALGraph_ArcNode(Arc adjvex, WeightType weight){
    this->adjvex = adjvex;
    this->weight = weight;
}

ALGraph::ALGraph(GraphType gt){
    this->vexnum = 0;
    this->arcnum = 0;
    this->visited = NULL;
    this->is_Directed_Graph = gt == Directed;
}

void ALGraph::Create(Vertex _vexnum, Arc _arcnum, ArcType at){
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
            cin >> x >> y;
            if(at == Weighted)
                cin >> w;
            else
                w = 1;
            if(!hash[x][y]){
                this->vertices[x].arcs.push_back(ALGraph_ArcNode(y, w));
                this->converse_vertices[y].arcs.push_back(ALGraph_ArcNode(x, w));
                hash[x][y] = true;
            }
        }
    else
        for(Arc i = 0; i < this->arcnum; i ++){
            cin >> x >> y;
            if(at == Weighted)
                cin >> w;
            else
                w = 1;
            if(!hash[x>y?y:x][x>y?x:y]){
                this->vertices[x].arcs.push_back(ALGraph_ArcNode(y, w));
                this->converse_vertices[y].arcs.push_back(ALGraph_ArcNode(x, w));
                this->vertices[y].arcs.push_back(ALGraph_ArcNode(x, w));
                this->converse_vertices[x].arcs.push_back(ALGraph_ArcNode(y, w));
                hash[x>y?y:x][x>y?x:y] = true;
            }
        }
    this->visited = new bool[this->vexnum];
}

void ALGraph::Vertices_Output(){
    for(Vertex i = 0; i < this->vexnum; i ++){
        cout << " " << this->vertices[i].data;
        for(Arc j = 0; j < this->vertices[i].arcs.size(); j ++)
            cout << " -> " << this->vertices[this->vertices[i].arcs[j].adjvex].data;
        cout << endl;
    }
    return;
}

void ALGraph::Degree_Output(){
    for(Vertex i = 0; i < this->vexnum; i ++)
        cout << this->vertices[i].data << "'s Degree: " << this->vertices[i].arcs.size() << endl;
    return;
}

void ALGraph::Reset_Visited(){
    for(Vertex i = 0; i < this->vexnum; i ++)
        this->visited[i] = false;
    return;
}

void ALGraph::DFS(Vertex v, void (*visit)(VertexType)){
    Reset_Visited();
    DFS_main(v, visit);
    return;
}

void ALGraph::DFS_main(Vertex v, void (*visit)(VertexType)){
    visit(this->vertices[v].data);
    this->visited[v] = true;
    for(Arc i = 0; i < this->vertices[v].arcs.size(); i ++)
        if(!this->visited[this->vertices[v].arcs[i].adjvex])
            DFS_main(this->vertices[v].arcs[i].adjvex, visit);
    return;
}

void ALGraph::BFS(Vertex v, void (*visit)(VertexType)){
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

MGraph::MGraph(GraphType gt){
    this->vexnum = 0;
    this->arcnum = 0;
    this->visited = NULL;
    this->is_Directed_Graph = gt == Directed;
}

void MGraph::Create(Vertex _vexnum, int _arcnum, ArcType at){
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
            cin >> x >> y;
            if(at == Weighted)
                cin >> w;
            else
                w = 1;
            adj_map[x][y] = w;
        }
    else
        for(Arc i = 0; i < this->arcnum; i ++){
            cin >> x >> y;
            if(at == Weighted)
                cin >> w;
            else
                w = 1;
            adj_map[x][y] = w;
            adj_map[y][x] = w;
        }
    this->visited = new bool[this->vexnum];
}

Vertex MGraph::degree(Vertex v){
    Vertex res = 0;
    for(auto i = this->adj_map[v].begin(); i != this->adj_map[v].end(); i ++)
        res ++;
    return res;
}

void MGraph::Vertices_Output(){
    for(Vertex i = 0; i < this->vexnum; i ++)
        cout << this->vertices[i].data << " ";
    cout << endl;
}

void MGraph::Degree_Output(){
    for(Vertex i = 0; i < this->vexnum; i ++)
        cout << this->vertices[i].data << "'s Degree: " << this->degree(i) << endl;
    cout << endl;
}

void MGraph::Reset_Visited(){
    for(Vertex i = 0; i < this->vexnum; i ++)
        this->visited[i] = false;
    return;
}

void MGraph::DFS(Vertex v, void (*visit)(VertexType)){
    Reset_Visited();
    DFS_main(v, visit);
    return;
}

void MGraph::DFS_main(Vertex v, void (*visit)(VertexType)){
    this->visited[v] = true;
    visit(this->vertices[v].data);
    for(Vertex i = 0; i < this->vexnum; i ++)
        if(this->adj_map.find(v) != this->adj_map.end())
            if(this->adj_map[v].find(i) != this->adj_map[v].end())
                if(!this->visited[i])
                    DFS_main(i, visit);
    return;
}

void MGraph::BFS(Vertex v, void (*visit)(VertexType)){
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

CLGraph_ArcNode::CLGraph_ArcNode(Vertex _tailvex, Vertex _headvex){
    this->tailvex = _tailvex;
    this->headvex = _headvex;
    this->hlink = NULL;
    this->tlink = NULL;
}

CLGraph_ArcNode* CLGraph_VNode::hfind(Vertex _headvex){ //判断出度是否存在
    CLGraph_ArcNode* p = this->firstin;
    while(p){
        if(p->headvex == _headvex)
            break;
        p = p->hlink;
    }
    return p;
}

CLGraph_ArcNode* CLGraph_VNode::tfind(Vertex _tailvex){ //判断入度是否存在
    CLGraph_ArcNode* p = this->firstout;
    while(p){
        if(p->tailvex == _tailvex)
            break;
        p = p->tlink;
    }
    return p;
}

void CLGraph_VNode::add_tail(CLGraph_ArcNode* _tp){ //添加入度
    if(!this->firstin)
        firstin = _tp;
    else{
        CLGraph_ArcNode* p = this->firstin;
        while(p->tlink)
            p = p->tlink;
        p->tlink = _tp;
    }
}

void CLGraph_VNode::add_head(CLGraph_ArcNode* _hp){ //添加出度
    if(!this->firstout)
        firstout = _hp;
    else{
        CLGraph_ArcNode* p = this->firstout;
        while(p->hlink)
            p = p->hlink;
        p->hlink = _hp;
    }
}

void CLGraph_VNode::add_arc(Vertex _headvex){
    if(this->hfind(_headvex))
        return;
    CLGraph_ArcNode *p = this->tfind(_headvex);
    p = p ? p : new CLGraph_ArcNode(this->loc, _headvex);
    this->add_head(p);
    if(!this->father->vertices[_headvex].hfind(p->tailvex))
        this->father->vertices[_headvex].add_tail(p);
}


CLGraph::CLGraph(){
    this->vexnum = 0;
    this->arcnum = 0;
    this->visited = NULL;
}

void CLGraph::Create(Vertex _vexnum, Arc _arcnum){
    this->vexnum = _vexnum;
    this->arcnum = _arcnum;
    this->visited = new bool[this->vexnum];
    this->vertices.resize(this->vexnum);
    Vertex x, y;
    for(Vertex i = 0; i < this->vexnum; i ++){
        cin >> this->vertices[i].data;
        this->vertices[i].father = this;
        this->vertices[i].loc = i;
    }
    for(Arc i = 0; i < this->arcnum; i ++){
        cin >> x >> y;
        this->vertices[x].add_arc(y);
    }
}

void CLGraph::Reset_Visited(){
    for(Vertex i = 0; i < this->vexnum; i ++)
        this->visited[i] = false;
}

Vertex CLGraph::out_degree(Vertex v){
    Vertex res = 0;
    CLGraph_ArcNode* p = this->vertices[v].firstout;
    while(p){
        res ++;
        p = p->hlink;
    }
    return res;
}

Vertex CLGraph::in_degree(Vertex v){
    Vertex res = 0;
    CLGraph_ArcNode* p = this->vertices[v].firstin;
    while(p){
        res ++;
        p = p->tlink;
    }
    return res;
}

void CLGraph::Degree_Output(){
    for(Vertex i = 0; i < this->vexnum; i ++)
        cout << this->vertices[i].data << "'s Degree: " << this->out_degree(i) << endl;
    cout << endl;
}

void CLGraph::Vertices_Output(){
    for(Vertex i = 0; i < this->vexnum; i ++)
        cout << this->vertices[i].data << endl;
    cout << endl;
}

void CLGraph::DFS(Vertex v, void (*visit)(VertexType)){
    this->Reset_Visited();
    this->DFS_main(v, visit);
}

void CLGraph::DFS_main(Vertex v, void (*visit)(VertexType)){
    this->visited[v] = true;
    visit(this->vertices[v].data);
    CLGraph_ArcNode* p = this->vertices[v].firstout;
    while(p){
        if(!this->visited[p->headvex])
            this->DFS_main(p->headvex, visit);
        p = p->hlink;
    }
}

void CLGraph::BFS(Vertex v, void (*visit)(VertexType)){
    this->Reset_Visited();
    queue<Vertex> q;
    q.push(v);
    this->visited[v] = true;
    visit(this->vertices[v].data);
    while(!q.empty()){
        Vertex x = q.front();
        q.pop();
        CLGraph_ArcNode* p = this->vertices[x].firstout;
        while(p)
            if(!this->visited[p->headvex]){
                q.push(p->headvex);
                this->visited[p->headvex] = true;
                visit(this->vertices[p->headvex].data);
            }
            else
                p = p->hlink;
    }
}

void visit(VertexType v){
    cout << v << " ";
}

int main(){
    system("cls");
    cout << "=========================" << endl << endl;
    cout << " 1.邻接表" << endl;
    cout << " 2.邻接矩阵" << endl;
    cout << " 3.十字链表" << endl;
    cout << endl << " 选择创建链表的类型：";
    int choice;
    cin >> choice;
    switch(choice){
        case 1:{
            cout << endl;
            cout << "=========================" << endl << endl;
            Vertex vexnum;
            Arc arcnum;
            cout << " 请输入节点数：";
            cin >> vexnum;
            cout << " 请输入弧数：";
            cin >> arcnum;
            cout << endl;
            cout << "=========================" << endl << endl;
            cout << " 是否为有向图？(Y/N) ";
            char tc;
            while(1){
                cin >> tc;
                if(tc == 'y' || tc == 'Y' || tc == 'N' || tc == 'n')
                    break;
            }
            GraphType gt = (tc == 'Y' || tc == 'y') ? Directed : Disdirected;
            cout << endl;
            cout << " 弧是否有权？(Y/N) ";
            while(1){
                cin >> tc;
                if(tc == 'y' || tc == 'Y' || tc == 'N' || tc == 'n')
                    break;
            }
            ArcType at = (tc == 'Y' || tc == 'y') ? Weighted : Unweighted;
            ALGraph al(gt);
            cout << " 开始执行 Create 函数" << endl;
            cout << " 先输入各个节点的值(char型)" << endl;
            if(at == Weighted)
                cout << " 随后按顺序输入 \"出节点下标 入节点下标 权值\"" << endl;
            else
                cout << " 随后按顺序输入 \"出节点下标 入节点下标\"" << endl;
            al.Create(vexnum, arcnum, at);
            cout << "=========================" << endl << endl;
            cout << " 邻接表：" << endl;
            al.Vertices_Output();
            cout << endl;
            cout << " 各节点的度：" << endl;
            al.Degree_Output();
            cout << "=========================" << endl << endl;
            cout << " 请输入深度优先遍历的开始节点下标：";
            Vertex vt;
            cin >> vt;
            al.DFS(vt, visit);
            cout << endl;
            cout << "=========================" << endl << endl;
            cout << " 请输入广度优先遍历的开始节点下标：";
            cin >> vt;
            al.BFS(vt, visit);
            cout << endl;
            break;
        }
        case 2:{
            cout << endl;
            cout << "=========================" << endl << endl;
            Vertex vexnum;
            Arc arcnum;
            cout << " 请输入节点数：";
            cin >> vexnum;
            cout << " 请输入弧数：";
            cin >> arcnum;
            cout << endl;
            cout << "=========================" << endl << endl;
            cout << " 是否为有向图？(Y/N) ";
            char tc;
            while(1){
                cin >> tc;
                if(tc == 'y' || tc == 'Y' || tc == 'N' || tc == 'n')
                    break;
            }
            GraphType gt = (tc == 'Y' || tc == 'y') ? Directed : Disdirected;
            MGraph mg(gt);
            cout << " 是否为有权？(Y/N) ";
            while(1){
                cin >> tc;
                if(tc == 'y' || tc == 'Y' || tc == 'N' || tc == 'n')
                    break;
            }
            ArcType at = (tc == 'Y' || tc == 'y') ? Weighted : Unweighted;
            cout << " 开始执行 Create 函数" << endl;
            cout << " 先输入各个节点的值(char型)" << endl;
            if(at == Weighted)
                cout << " 随后按顺序输入 \"出节点下标 入节点下标 权值\"" << endl;
            else
                cout << " 随后按顺序输入 \"出节点下标 入节点下标\"" << endl;
            mg.Create(vexnum, arcnum, at);
            cout << "=========================" << endl << endl;
            cout << " 邻接矩阵：" << endl;
            mg.Vertices_Output();
            cout << endl;
            cout << " 各节点的度：" << endl;
            mg.Degree_Output();
            cout << "=========================" << endl << endl;
            cout << " 请输入深度优先遍历的开始节点下标：";
            Vertex vt;
            cin >> vt;
            mg.DFS(vt, visit);
            cout << endl;
            cout << "=========================" << endl << endl;
            cout << " 请输入广度优先遍历的开始节点下标：";
            cin >> vt;
            mg.BFS(vt, visit);
            cout << endl;
            break;
        }
        case 3:{
            cout << endl;
            cout << "=========================" << endl << endl;
            Vertex vexnum;
            Arc arcnum;
            cout << " 请输入节点数：";
            cin >> vexnum;
            cout << " 请输入弧数：";
            cin >> arcnum;
            cout << endl;
            cout << "=========================" << endl << endl;
            cout << " 十字链表必为有向无权图 " << endl;
            cout << " 开始执行 Create 函数" << endl;
            cout << " 先输入各个节点的值(char型)" << endl;
            cout << " 随后按顺序输入 \"出节点下标 入节点下标\"" << endl;
            CLGraph cl;
            cl.Create(vexnum, arcnum);
            cout << "=========================" << endl << endl;
            cout << " 十字链表：" << endl;
            cl.Vertices_Output();
            cout << endl;
            cout << " 各节点的度：" << endl;
            cl.Degree_Output();
            cout << "=========================" << endl << endl;
            cout << " 请输入深度优先遍历的开始节点下标：";
            Vertex vt;
            cin >> vt;
            cl.DFS(vt, visit);
            cout << endl;
            cout << "=========================" << endl << endl;
            cout << " 请输入广度优先遍历的开始节点下标：";
            cin >> vt;
            cl.BFS(vt, visit);
            cout << endl;
            break;
        }
        default:{
            cout << " 指令未知！" << endl;
            break;
        }
    }
    system("pause");
    return 0;
}