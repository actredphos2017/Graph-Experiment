#pragma once

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

void ALGraph::Create(Vertex _vexnum, Arc _arcnum){
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
                this->vertices[x].arcs.push_back(ALGraph_ArcNode(y, w));
                this->converse_vertices[y].arcs.push_back(ALGraph_ArcNode(x, w));
                hash[x][y] = true;
            }
        }
    else
        for(Arc i = 0; i < this->arcnum; i ++){
            cin >> x >> y >> w;
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

void MGraph::Create(Vertex _vexnum, int _arcnum){
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

OLGraph_ArcNode::OLGraph_ArcNode(Vertex _tailvex, Vertex _headvex){
    this->tailvex = _tailvex;
    this->headvex = _headvex;
    this->hlink = NULL;
    this->tlink = NULL;
}

OLGraph_ArcNode* OLGraph_VNode::hfind(Vertex _headvex){ //判断出度是否存在
    OLGraph_ArcNode* p = this->firstin;
    while(p){
        if(p->headvex == _headvex)
            break;
        p = p->hlink;
    }
    return p;
}

OLGraph_ArcNode* OLGraph_VNode::tfind(Vertex _tailvex){ //判断入度是否存在
    OLGraph_ArcNode* p = this->firstout;
    while(p){
        if(p->tailvex == _tailvex)
            break;
        p = p->tlink;
    }
    return p;
}

void OLGraph_VNode::add_tail(OLGraph_ArcNode* _tp){ //添加入度
    if(!this->firstin)
        firstin = _tp;
    else{
        OLGraph_ArcNode* p = this->firstin;
        while(p->tlink)
            p = p->tlink;
        p->tlink = _tp;
    }
}

void OLGraph_VNode::add_head(OLGraph_ArcNode* _hp){ //添加出度
    if(!this->firstout)
        firstout = _hp;
    else{
        OLGraph_ArcNode* p = this->firstout;
        while(p->hlink)
            p = p->hlink;
        p->hlink = _hp;
    }
}

void OLGraph_VNode::add_arc(Vertex _headvex){
    if(this->hfind(_headvex))
        return;
    OLGraph_ArcNode *p = this->tfind(_headvex);
    p = p ? p : new OLGraph_ArcNode(this->loc, _headvex);
    this->add_head(p);
    this->father->vertices[_headvex].add_tail(p);
}

OLGraph::OLGraph(){
    this->vexnum = 0;
    this->arcnum = 0;
    this->visited = NULL;
}

void OLGraph::Create(Vertex _vexnum, Arc _arcnum){
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

void OLGraph::Reset_Visited(){
    for(Vertex i = 0; i < vexnum; i ++)
        visited[i] = false;
}

Vertex OLGraph::out_degree(Vertex v){
    Vertex res = 0;
    OLGraph_ArcNode* p = this->vertices[v].firstout;
    while(p){
        res ++;
        p = p->hlink;
    }
    return res;
}

Vertex OLGraph::in_degree(Vertex v){
    Vertex res = 0;
    OLGraph_ArcNode* p = this->vertices[v].firstin;
    while(p){
        res ++;
        p = p->tlink;
    }
    return res;
}

void OLGraph::Degree_Output(){
    for(Vertex i = 0; i < this->vexnum; i ++)
        cout << this->vertices[i].data << "'s Degree: " << this->out_degree(i) << endl;
    cout << endl;
}