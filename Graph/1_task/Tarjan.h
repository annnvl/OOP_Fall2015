//
//  Tarjan.h
//  Graph
//
//  Created by No_love_no_problem on 23.11.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#ifndef Tarjan_h
#define Tarjan_h

#include "Graph.h"
#include <cmath>

template<class VertexId>
class Tarjan_methods {
public:
    Tarjan_methods(Graph<VertexId>& Gr):G(Gr){
        _index=0;
    };
private:
    void _strongconnected(int i){
        G._vertexes[i].index = _index;
        G._vertexes[i].lowlink = _index;
        _index++;
        _componentstack.push(i);
        G._vertexes[i].onstack = 1;
        
        for(typename list<pair<VertexId, int> >::iterator it = G._vertexes[i]._edges.begin(); it != G._vertexes[i]._edges.end(); ++it){
            int number = G._findvertex(it->first);
            if (G._vertexes[number].index == -1){
                _strongconnected(number);
                G._vertexes[i].lowlink = min(G._vertexes[i].lowlink, G._vertexes[number].lowlink);
            }
            else if (G._vertexes[number].onstack) {
                G._vertexes[i].lowlink = min(G._vertexes[i].lowlink, G._vertexes[number].index);
            }
        }
        
        if (G._vertexes[i].lowlink == G._vertexes[i].index){
            list<VertexId> component;
            int j;
            while (true) {
                j = _componentstack.top();
                _componentstack.pop();
                G._vertexes[j].onstack = 0;
                component.push_front(G._vertexes[j].getid());
                if(i == j) break;
            }
            _answer.push_front(component);
        }
    }
    
    Graph<VertexId>& G;
    stack<int> _componentstack;
    int _index;
    list<list<VertexId> > _answer;
public:
    list<list<VertexId> > maker(){
        for (int i = 0; i < G.sizeV(); i++) {
            if(G._vertexes[i].index == -1){
                _strongconnected(i);
            }
        }
        return _answer;
    };
};

template<class VertexId>
list<list<VertexId> > Tarjan(Graph<VertexId>& G){
    Tarjan_methods<VertexId> meth(G);
    return meth.maker();
}

#endif /* Tarjan_h */
