
    int vernum, arcnum;
    cin >> vernum >> arcnum;
    ALGraph al;
    al.Vertices_Output();
    al.Degree_Output();
    cout << "DFS: ";
    al.DFS(0, visit);
    cout << endl;
    cout << "BFS: ";
    al.BFS(0, visit);
    cout << endl;
    system("pause");