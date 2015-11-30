//
//  Ford-Bellman.h
//  Graph
//
//  Created by No_love_no_problem on 24.11.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#ifndef Ford_Bellman_h
#define Ford_Bellman_h

#include "Graph.h"

const int _max = 30000;

template<class VertexId>
class  Ford_Bellman_methods {                       //класс вспомогательных методов и данных
public:
    Ford_Bellman_methods(Graph<VertexId>& Gr):G(Gr),_answer(G.sizeV(), _max){};
    vector<int> maker(int i){
        _answer[i] = 0;
        while (true) {
            _flag = 0;
            for (int j = 0; j < G.sizeV(); j++) {
                for(typename list<pair<VertexId, int> >::iterator it = G._vertexes[j]._edges.begin(); it != G._vertexes[j]._edges.end(); ++it){
                    if (_answer[j] < _max) {
                        int k = G._findvertex(it->first);
                        if (_answer[k] > _answer[j] + it->second) {
                            _answer[k] = _answer[j] + it->second;
                            _flag = 1;
                        }
                    }
                }
            }
            if (!_flag) {
                break;
            }
        }
        return _answer;
    };
private:
    Graph<VertexId>& G;
    vector<int> _answer;
    int _flag;      //показывает, изменилось ли что-то на текущей фазе
};

template<class VertexId>
vector<int> Ford_Bellman(Graph<VertexId>& G, VertexId vert){
    Ford_Bellman_methods<VertexId> methods(G);
    return methods.maker(G._findvertex(vert));
}

#endif /* Ford_Bellman_h */
