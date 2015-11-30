//
//  Algorithm.h
//  Graph
//
//  Created by No_love_no_problem on 15.09.15.
//  Copyright (c) 2015 Anna Vlasova. All rights reserved.
//

#ifndef __Graph__Kosaraju__
#define __Graph__Kosaraju__
#include "Graph.h"
#include <stack>

template<class VertexId>
class Kosaraju_methods {                //класс вспомогательных методов и данних
public:
    Kosaraju_methods(Graph<VertexId>& Gr):G(Gr){};
private:
    void DFSvisitToStack(int u){                            //u - № исследуемой вершины
        G._vertexes[u].makegrey();
        for (typename list<pair<VertexId, int> >::iterator i = G._vertexes[u]._edges.begin(); i != G._vertexes[u]._edges.end(); i++) {
            int j = G._findvertex(i->first);
            if (G._vertexes[j].iswhite()) {
                DFSvisitToStack(j);
            }
        }
        G._vertexes[u].makeblack();
        sortingStack.push(u);
    };
    
    void DFSvisitFromStack(int u, list<VertexId>& ans){
        ans.push_back(G._vertexes[u].getid());
        G._vertexes[u].makegrey();
        for (typename list<pair<VertexId, int> >::iterator i = G._vertexes[u]._edges.begin(); i != G._vertexes[u]._edges.end(); i++) {
            int j = G._findvertex(i->first);
            if (G._vertexes[j].iswhite()) {
                DFSvisitFromStack(j, ans);
            }
        }
        G._vertexes[u].makeblack();
    };
public:
    list<list<VertexId> > maker(){
        list<list<VertexId> > answer;
        
        int i;
        for(i = 0; i < G.sizeV(); i++){
            G._vertexes[i].makewhite();
        }
        _time = 0;
        for(i = 0; i < G.sizeV(); i++){
            if (G._vertexes[i].iswhite()) {
                DFSvisitToStack(i);
            }
        }
        
        G.Transpose();
        
        for(i = 0; i < G.sizeV(); i++){
            G._vertexes[i].makewhite();
        }
        
        while (!sortingStack.empty()) {
            if (G._vertexes[sortingStack.top()].iswhite()){
                list<VertexId> component;
                DFSvisitFromStack(sortingStack.top(), component);
                answer.push_front(component);
            }
            sortingStack.pop();
        }
        
        return answer;

    };
private:
    Graph<VertexId>& G;
    std::stack<int> sortingStack; //чтобы пройти вершины в порядке убывания времени выхода (в стеке - индексы вершин в векторе _vertexes)
    int _time;
    
};

template<class VertexId>
list<list<VertexId> > Kosaraju(Graph<VertexId>& G){
    Kosaraju_methods<VertexId> methods(G);
    return methods.maker();
}

template<class VertexId>
void showComponents(list<list<VertexId> >& components){         //печатает компоненты
    int i = 1;
    for (typename list<list<VertexId > >::iterator it = components.begin(); it != components.end(); it++) {
        std::cout << i << " component:\n";
        for (typename list<VertexId>::iterator insideIt = it->begin(); insideIt != it-> end(); insideIt++) {
            std::cout << *insideIt << ", ";
        }
        std::cout << "\n";
        i++;
    }
}


#endif /* defined(__Graph__Algorithm__) */
