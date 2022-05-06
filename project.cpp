#include <iostream>
#include "head/vertex_map.h"

using namespace std;

/*
9 10
A
B
C
D
E
F
G
H
I
0 1 1
0 2 1
0 3 1
1 4 1
1 5 1
2 3 1
2 6 1
3 6 1
3 7 1
4 8 1
*/

void visit(VertexType v){
    cout << v << " ";
}

int main(){
    int vernum, arcnum;
    cin >> vernum >> arcnum;
    ALGraph al(Disdirected);
    al.Create(vernum, arcnum);
    al.Vertices_Output();
    al.Degree_Output();
    cout << "DFS: ";
    al.DFS(0, visit);
    cout << endl;
    cout << "BFS: ";
    al.BFS(0, visit);
    cout << endl;
    system("pause");
    return 0;
}