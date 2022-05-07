#include <iostream>
#include "head/Graph.h"

using namespace std;

void visit(VertexType v){
    cout << v << " ";
}

int main(){
    system("clear");
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
            ALGraph al(gt);
            cout << " 开始执行 Create 函数" << endl;
            cout << " 先输入各个节点的值(char型)" << endl;
            cout << " 随后按顺序输入 \"出节点下标 入节点下标 权值\"" << endl;
            al.Create(vexnum, arcnum);
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
            break;
        }
        case 3:{
            break;
        }
        default:{
            cout << " 指令未知！" << endl;
            break;
        }
    }
    return 0;
}