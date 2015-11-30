//
//  Graph.cpp
//  Graph
//
//  Created by No_love_no_problem on 27.11.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#include "Graph.h"

Graph<int>* randomgraph(int n, double p){               //случайный граф на n вершинахс вероятностью ребра p
    std::srand(std::time(0));
    Graph<int>* answer = new Graph<int>;
    for (int i = 1; i <= n; i++) {
        answer->AddVertex(i);
    }
    for (int i = 1; i <= n ; i++) {
        for (int j = 1; j <= n; j++) {
            if (j == i) {
                continue;
            }
            if ((rand()%10000)<p*10000) {
                answer->AddEdge(i, j, rand()%100);
            }
        }
    }
    return answer;
}