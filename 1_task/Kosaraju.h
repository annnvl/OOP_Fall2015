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
#include <unordered_map>

template<class VertexId>
class Kosaraju_methods {
public:
    Kosaraju_methods(Graph<VertexId>& Gr):G(Gr){};
private:
    class colours{
    public:
        colours(){_col = 0;};
        bool iswhite() {return !_col;};
        bool isgrey()  {return (_col == 1);};
        bool isblack() {return (_col == 2);};
        
        void makewhite() {_col = 0;};
        void makeblack() {_col = 2;};
        void makegrey()  {_col = 1;};
    private:
        int _col;                                                //0 - белый, 1 - серый, 2 - черный
    };
    
    void DFSvisitToStack(int u){        //u - id вершины
        _labels[u].makegrey();
        for(auto j = G[u].begin(); j != G[u].end(); ++j){
            if (_labels[j->first].iswhite()) {
                DFSvisitToStack(j->first);
            }
        }
        _labels[u].makeblack();
        sortingStack.push(u);
    };
    
    void DFSvisitFromStack(int u, std::list<int>& ans){
        ans.push_back(u);
        _labels[u].makegrey();
        for(auto j = G[u].begin(); j != G[u].end(); ++j){
            if (_labels[j->first].iswhite()) {
                DFSvisitFromStack(j->first, ans);
            }
        }
        _labels[u].makeblack();
    };
public:
    std::list<std::list<int> > maker(){
        std::list<std::list<int> > answer;
        
        for (auto it = G.begin(); it != G.end(); ++it) {
            _labels.insert(std::pair<int, colours>(it->first, colours()));
        }
        
        _time = 0;
        for(auto it = G.begin(); it != G.end(); ++it){
            if (_labels[it->first].iswhite()) {
                DFSvisitToStack(it->first);
            }
        }
        
        G.Transpose();
        
        for (auto it = _labels.begin(); it != _labels.end(); ++it){
            it->second.makewhite();
        }
        
        while (!sortingStack.empty()) {
            if (_labels[sortingStack.top()].iswhite()){
                std::list<int> component;
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
    std::unordered_map<int, colours> _labels;       //id вершины, ее цвет
};

template<class VertexId>
std::list<std::list<VertexId> > Kosaraju(Graph<VertexId>& G){
    Kosaraju_methods<VertexId> meth(G);
    return meth.maker();
}

template<class VertexId>
void showComponents(std::list<std::list<int> >& components, Graph<VertexId> G){
    int i = 1;
    for (typename std::list<std::list<int > >::iterator it = components.begin(); it != components.end(); it++) {
        std::cout << i << " component:\n";
        for (typename std::list<int>::iterator insideIt = it->begin(); insideIt != it-> end(); insideIt++) {
            std::cout << G.getdata(*insideIt) << ", ";
        }
        std::cout << "\n";
        i++;
    }
}


#endif /* defined(__Graph__Algorithm__) */
