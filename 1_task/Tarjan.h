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
    class info{
        int index;
        int lowlink;
        bool stack;
    public:
        info(){index=lowlink=-1; stack=0;};
        void setindex(int ind){index=ind;};
        void setlowlink(int ind){lowlink=ind;};
        int getindex(){return index;};
        int getlowlink(){return lowlink;};
        void tostack(){stack=1;};
        bool onstack(){return stack;};
        void fromstack(){stack=0;};
    };
    void _strongconnected(int i){
        _labels[i].setindex(_index);
        _labels[i].setlowlink(_index);
        _index++;
        _componentstack.push(i);
        _labels[i].tostack();
        
        for(auto it = G[i].begin(); it != G[i].end(); ++it){
            int number = it->first;
            if (_labels[number].getindex() == -1){
                _strongconnected(number);
                _labels[i].setlowlink(std::min(_labels[i].getlowlink(), _labels[number].getlowlink()));
            }
            else if (_labels[number].onstack()) {
                _labels[i].setlowlink(std::min(_labels[i].getlowlink(), _labels[number].getindex()));
            }
        }
        
        if (_labels[i].getlowlink() == _labels[i].getindex()){
            std::list<int> component;
            int j;
            while (true) {
                j = _componentstack.top();
                _componentstack.pop();
                _labels[j].fromstack();
                component.push_front(j);
                if(i == j) break;
            }
            _answer.push_back(component);
        }
    }
    
    Graph<VertexId>& G;
    std::stack<int> _componentstack;
    int _index;
    std::list<std::list<int> > _answer;
    std::unordered_map<int, info> _labels;
public:
    std::list<std::list<int> > maker(){
        for (auto it = G.begin(); it != G.end(); ++it) {
            _labels.insert(std::pair<int, info>(it->first, info()));
        }
        
        for (auto it = G.begin(); it != G.end(); ++it) {
            if(_labels[it->first].getindex() == -1){
                _strongconnected(it->first);
            }
        }
        return _answer;
    };
};

template<class VertexId>
std::list<std::list<int> > Tarjan(Graph<VertexId>& G){
    Tarjan_methods<VertexId> meth(G);
    return meth.maker();
}

#endif /* Tarjan_h */
