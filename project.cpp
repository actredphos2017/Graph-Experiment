#include <iostream>
#include "head/Graph.h"

using namespace std;

void visit(VertexType v){
    cout << v << " ";
}

int main(){
    system("cls");
    cout << "=========================" << endl << endl;
    cout << " 1.�ڽӱ�" << endl;
    cout << " 2.�ڽӾ���" << endl;
    cout << " 3.ʮ������" << endl;
    cout << " 4.�ڽӶ��ر�" << endl;
    cout << endl << " ѡ�񴴽���������ͣ�";
    int choice;
    cin >> choice;
    switch(choice){
        case 1:{
            cout << endl;
            cout << "=========================" << endl << endl;
            Vertex vexnum;
            Arc arcnum;
            cout << " ������ڵ�����";
            cin >> vexnum;
            cout << " �����뻡����";
            cin >> arcnum;
            cout << endl;
            cout << "=========================" << endl << endl;
            cout << " �Ƿ�Ϊ����ͼ��(Y/N) ";
            char tc;
            while(1){
                cin >> tc;
                if(tc == 'y' || tc == 'Y' || tc == 'N' || tc == 'n')
                    break;
            }
            GraphType gt = (tc == 'Y' || tc == 'y') ? Directed : Disdirected;
            cout << endl;
            cout << " ���Ƿ���Ȩ��(Y/N) ";
            while(1){
                cin >> tc;
                if(tc == 'y' || tc == 'Y' || tc == 'N' || tc == 'n')
                    break;
            }
            ArcType at = (tc == 'Y' || tc == 'y') ? Weighted : Unweighted;
            ALGraph al(gt);
            cout << " ��ʼִ�� Create ����" << endl;
            cout << " ����������ڵ��ֵ(char��)" << endl;
            if(at == Weighted)
                cout << " ���˳������ \"���ڵ��±� ��ڵ��±� Ȩֵ\"" << endl;
            else
                cout << " ���˳������ \"���ڵ��±� ��ڵ��±�\"" << endl;
            al.Create(vexnum, arcnum, at);
            cout << "=========================" << endl << endl;
            cout << " �ڽӱ�" << endl;
            al.Vertices_Output();
            cout << endl;
            cout << " ���ڵ�Ķȣ�" << endl;
            al.Degree_Output();
            cout << "=========================" << endl << endl;
            cout << " ������������ȱ����Ŀ�ʼ�ڵ��±꣺";
            Vertex vt;
            cin >> vt;
            al.DFS(vt, visit);
            cout << endl;
            cout << "=========================" << endl << endl;
            cout << " �����������ȱ����Ŀ�ʼ�ڵ��±꣺";
            cin >> vt;
            al.BFS(vt, visit);
            cout << endl;
            cout << "=========================" << endl << endl;
            if(gt == Directed){
                VertexType topo[vexnum];
                if(al.TopologicalSort(topo)){
                    cout << " ͼ����������" << endl;
                    for(auto i : topo)
                        cout << i << " ";
                    cout << endl;
                }else
                    cout << " ������ͼ����������" << endl;
            }else
                cout << " ����ͼ����������" << endl;
            break;
        }
        case 2:{
            cout << endl;
            cout << "=========================" << endl << endl;
            Vertex vexnum;
            Arc arcnum;
            cout << " ������ڵ�����";
            cin >> vexnum;
            cout << " �����뻡����";
            cin >> arcnum;
            cout << endl;
            cout << "=========================" << endl << endl;
            cout << " �Ƿ�Ϊ����ͼ��(Y/N) ";
            char tc;
            while(1){
                cin >> tc;
                if(tc == 'y' || tc == 'Y' || tc == 'N' || tc == 'n')
                    break;
            }
            GraphType gt = (tc == 'Y' || tc == 'y') ? Directed : Disdirected;
            MGraph mg(gt);
            cout << " �Ƿ�Ϊ��Ȩ��(Y/N) ";
            while(1){
                cin >> tc;
                if(tc == 'y' || tc == 'Y' || tc == 'N' || tc == 'n')
                    break;
            }
            ArcType at = (tc == 'Y' || tc == 'y') ? Weighted : Unweighted;
            cout << " ��ʼִ�� Create ����" << endl;
            cout << " ����������ڵ��ֵ(char��)" << endl;
            if(at == Weighted)
                cout << " ���˳������ \"���ڵ��±� ��ڵ��±� Ȩֵ\"" << endl;
            else
                cout << " ���˳������ \"���ڵ��±� ��ڵ��±�\"" << endl;
            mg.Create(vexnum, arcnum, at);
            cout << "=========================" << endl << endl;
            cout << " �ڽӾ���" << endl;
            mg.Vertices_Output();
            cout << endl;
            cout << " ���ڵ�Ķȣ�" << endl;
            mg.Degree_Output();
            cout << "=========================" << endl << endl;
            cout << " ������������ȱ����Ŀ�ʼ�ڵ��±꣺";
            Vertex vt;
            cin >> vt;
            mg.DFS(vt, visit);
            cout << endl;
            cout << "=========================" << endl << endl;
            cout << " �����������ȱ����Ŀ�ʼ�ڵ��±꣺";
            cin >> vt;
            mg.BFS(vt, visit);
            cout << endl;
            if(gt == Directed){
                cout << "=========================" << endl << endl;
                VertexType topo[vexnum];
                if(mg.TopologicalSort(topo)){
                    cout << " ��������" << endl;
                    for(auto i : topo)
                        cout << i << " ";
                    cout << endl;
                }
                else
                    cout << " ������ͼ����������" << endl;
            }
            else
                cout << " ����ͼ����������" << endl;
            break;
        }
        case 3:{
            cout << endl;
            cout << "=========================" << endl << endl;
            Vertex vexnum;
            Arc arcnum;
            cout << " ������ڵ�����";
            cin >> vexnum;
            cout << " �����뻡����";
            cin >> arcnum;
            cout << endl;
            cout << "=========================" << endl << endl;
            cout << " ʮ�������Ϊ������Ȩͼ " << endl;
            cout << " ��ʼִ�� Create ����" << endl;
            cout << " ����������ڵ��ֵ(char��)" << endl;
            cout << " ���˳������ \"���ڵ��±� ��ڵ��±�\"" << endl;
            CLGraph cl;
            cl.Create(vexnum, arcnum);
            cout << "=========================" << endl << endl;
            cout << " ���ڵ�Ķȣ�" << endl;
            cl.Degree_Output();
            cout << "=========================" << endl << endl;
            cout << " ������������ȱ����Ŀ�ʼ�ڵ��±꣺";
            Vertex vt;
            cin >> vt;
            cl.DFS(vt, visit);
            cout << endl;
            cout << "=========================" << endl << endl;
            cout << " �����������ȱ����Ŀ�ʼ�ڵ��±꣺";
            cin >> vt;
            cl.BFS(vt, visit);
            cout << endl;
            cout << "=========================" << endl << endl;
            VertexType topo[vexnum];
            if(cl.TopologicalSort(topo)){
                cout << " ��ͼ���������У�";
                for(auto i : topo)
                    cout << i << " ";
                cout << endl;
            }else
                cout << " ��ͼ����������" << endl;
            break;
        }
        case 4:{
            cout << endl;
            cout << "=========================" << endl << endl;
            Vertex vexnum;
            Arc arcnum;
            cout << " ������ڵ�����";
            cin >> vexnum;
            cout << " �����뻡����";
            cin >> arcnum;
            cout << endl;
            cout << "=========================" << endl << endl;
            cout << " �ڽӶ��ر��Ϊ����ͼ " << endl;
            cout << " ��ʼִ�� Create ����" << endl;
            cout << " ����������ڵ��ֵ(char��)" << endl;
            cout << " ���˳������ \"���ڵ��±� ��ڵ��±�\"" << endl;
            MGraph mg(Disdirected);
            mg.Create(vexnum, arcnum, Unweighted);
            cout << "=========================" << endl << endl;
            cout << " ���ڵ�Ķȣ�" << endl;
            mg.Degree_Output();
            cout << "=========================" << endl << endl;
            cout << " ������������ȱ����Ŀ�ʼ�ڵ��±꣺";
            Vertex vt;
            cin >> vt;
            mg.DFS(vt, visit);
            cout << endl;
            cout << "=========================" << endl << endl;
            cout << " �����������ȱ����Ŀ�ʼ�ڵ��±꣺";
            cin >> vt;
            mg.BFS(vt, visit);
            cout << endl;
            break;
        }
        default:{
            cout << " ָ��δ֪��" << endl;
            break;
        }
    }
    system("pause");
    return 0;
}