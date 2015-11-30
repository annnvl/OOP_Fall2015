//
//  main.cpp
//  Graph
//
//  Created by No_love_no_problem on 15.09.15.
//  Copyright (c) 2015 Anna Vlasova. All rights reserved.
//

#include "Graph.h"
#include "Ford-Bellman.h"

int main() {
    int n, m, l;
    int a, b;
    std::cin >> n >> m;
    
    Graph<int> gr;
    
    for (int i=1; i<=n; i++){
        gr.AddVertex(i);
    }
    
    for (int i=0; i<m; i++) {
        std::cin >> a >> b >> l;
        gr.AddEdge(a, b, l);
    }
    
    vector<int> distances = Ford_Bellman(gr, 1);
    
    for (int i=0; i<n; i++){
        cout << distances[i] << " ";
    }
    
    return 0;
}
