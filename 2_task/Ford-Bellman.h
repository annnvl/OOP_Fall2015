//
//  Ford-Bellman.h
//  Graph
//
//  Created by No_love_no_problem on 24.11.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#ifndef Ford_Bellman_h
#define Ford_Bellman_h

const int _max = 30000;

template<class VertexId>
class  Ford_Bellman_methods {
public:
    Ford_Bellman_methods(Graph<VertexId>& Gr):G(Gr),_answer(G.size(), _max){};
    std::vector<int> maker(int j){
        _answer[j] = 0;
        while (true) {
            _flag = 0;
            for (auto it = G.begin(); it != G.end(); ++it) {
                for(auto i = it->second.begin(); i != it->second.end(); ++i){
                    if (_answer[it->first] < _max) {
                        int k = i->first;
                        if (_answer[k] > (_answer[it->first] + i->second)) {
                            _answer[k] = _answer[it->first] + i->second;
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
    std::vector<int> _answer;
    int _flag;      //показывает, изменилось ли что-то на текущей фазе
};

template<class VertexId>
std::vector<int> Ford_Bellman(Graph<VertexId>& G, VertexId vert){
    Ford_Bellman_methods<VertexId> meth(G);
    int id = G.getid(vert);
    return meth.maker(id);
}

#endif /* Ford_Bellman_h */
