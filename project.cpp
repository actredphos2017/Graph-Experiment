#include <iostream>
#include "head/Graph.h"

using namespace std;

void visit(VertexType v){
    cout << v << " ";
}

int main(){
    system("cls");
    cout << "=========================" << endl << endl;
    cout << " 1.邻接表" << endl;
    cout << " 2.邻接矩阵" << endl;
    cout << " 3.十字链表" << endl;
    cout << " 4.邻接多重表" << endl;
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
            cout << "=========================" << endl << endl;
            if(gt == Directed){
                VertexType topo[vexnum];
                if(al.TopologicalSort(topo)){
                    cout << " 图的拓扑排序：" << endl;
                    for(auto i : topo)
                        cout << i << " ";
                    cout << endl;
                }else
                    cout << " 该有向图无拓扑排序" << endl;
            }else
                cout << " 无向图无拓扑排序" << endl;
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
            if(gt == Directed){
                cout << "=========================" << endl << endl;
                VertexType topo[vexnum];
                if(mg.TopologicalSort(topo)){
                    cout << " 拓扑排序：" << endl;
                    for(auto i : topo)
                        cout << i << " ";
                    cout << endl;
                }
                else
                    cout << " 该有向图无拓扑排序" << endl;
            }
            else
                cout << " 无向图无拓扑排序" << endl;
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
            cout << "=========================" << endl << endl;
            VertexType topo[vexnum];
            if(cl.TopologicalSort(topo)){
                cout << " 本图的拓扑序列：";
                for(auto i : topo)
                    cout << i << " ";
                cout << endl;
            }else
                cout << " 本图无拓扑序列" << endl;
            break;
        }
        case 4:{
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
            cout << " 邻接多重表必为无向图 " << endl;
            cout << " 开始执行 Create 函数" << endl;
            cout << " 先输入各个节点的值(char型)" << endl;
            cout << " 随后按顺序输入 \"出节点下标 入节点下标\"" << endl;
            MGraph mg(Disdirected);
            mg.Create(vexnum, arcnum, Unweighted);
            cout << "=========================" << endl << endl;
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
        default:{
            cout << " 指令未知！" << endl;
            break;
        }
    }
    system("pause");
    return 0;
}