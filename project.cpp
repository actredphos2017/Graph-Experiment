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

int main(){
    int vernum, arcnum;
    cin >> vernum >> arcnum;
    ALGraph al(vernum,arcnum);
    al.output();
    return 0;
}