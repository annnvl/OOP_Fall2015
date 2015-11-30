//
//  Graph.h
//  Graph
//
//  Created by No_love_no_problem on 15.09.15.
//  Copyright (c) 2015 Anna Vlasova. All rights reserved.
//

#ifndef __Graph__Graph__
#define __Graph__Graph__

#include <list>
#include <stack>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

template<class VertexId>
class Graph {
public:
    class Vertex {
    public:
        Vertex(VertexId & id) {_id = id; _col = onstack = 0; index = lowlink = -1;};                                       //по умолчанию выршины белые
        
        bool iswhite() {return !_col;};
        bool isgrey()  {return (_col == 1);};
        bool isblack() {return (_col == 2);};
        
        void makewhite() {_col = 0;};
        void makeblack() {_col = 2;};
        void makegrey()  {_col = 1;};
        
        VertexId getid() {return _id;};
        
        friend class Graph;
        friend ostream& operator << (ostream& os, const Graph&);
        friend ostream& operator<<(ostream& os, Graph<int> & Gr);
        
        list<pair<VertexId, int> > _edges;
        int index;
        int lowlink;
        bool onstack;
    private:
        VertexId _id;
        int _col;                                                           //0 - белый, 1 - серый, 2 - черный
    };
    
    int _findvertex(VertexId& value){
        for (int i = 0; i < _vertexes.size(); i++) {
            if (_vertexes[i]._id == value) {
                return i;
            }
        }
        return -1;
    };
    
    typename list<pair<VertexId, int> >::iterator _findedge(VertexId& from, VertexId& to){
        int i = _findvertex(from);
        if(i==-1) throw -1;
        typename list<pair<VertexId, int> >::iterator ans = find_if(_vertexes[i]._edges.begin(), _vertexes[i]._edges.end(), [&to](pair<VertexId, int>& param){return (param.first == to);});
        if (ans == _vertexes[i]._edges.end()) throw -2;
        return ans;
    };
public:
    void AddVertex(VertexId& value){
        if (FindVertex(value)) {
            cout << "The vertex you want to add already exists";
            return;
        }
        _vertexes.push_back(Vertex(value));
    };
    void DeleteVertex(VertexId& value){
        int ind;
        if ((ind = _findvertex(value))==-1){
            cout << "The vertex you want to remove doesn't exists yet";
            return;
        }
        _vertexes.erase(ind);
        for (int i=0; i<_vertexes.size(); i++){
            _vertexes[i]._edges.remove_if([&value](pair<VertexId, int>& param){return (param.first() == value);});
        }
    };
    bool FindVertex(const VertexId& val) const{
        for (int i = 0; i < _vertexes.size(); i++) {
            if (_vertexes[i]._id == val) {
                return 1;
            }
        }
        return 0;
    };
    
    void AddEdge(VertexId& from, VertexId& to, int weight){
        if (!FindVertex(to)) {
            cout << "You want to add edge to the vertex that doesn't exists";
            return;
        }
        int i = _findvertex(from);
        if(i == -1){
            cout << "You want to add edge from the vertex that doesn't exists";
            return;
        }
        _vertexes[i]._edges.emplace_back(to, weight);
    };
    
    void DeleteEdge(VertexId& from, VertexId& to){
        try {
            typename list<pair<VertexId, int> >::iterator it = _findedge(from, to);
            _vertexes[_findvertex(from)].erase(it);
        } catch (int) {
            cout << "Cannot delete element that doesn't exists";
        }
    };
    bool FindEdge(VertexId& from, VertexId& to){
        try {
            typename list<pair<VertexId, int> >::iterator it = _findedge(from, to);
            return 1;
        } catch (int) {
            return 0;
        }
    };
    
    int GetWeight(VertexId& from, VertexId& to){
        try {
            typename list<pair<VertexId, int> >::iterator it = _findedge(from, to);
            return it->second;
        } catch (int) {
            throw;
            return 0;
        }
    };

    void Transpose(){
        vector<Vertex> copy(_vertexes);
        for (int i=0; i<sizeV(); i++) {
            _vertexes[i]._edges.clear();
        }
        for (int i=0; i<sizeV(); i++){
            int to = copy[i].getid();
            for (typename list<pair<VertexId, int> >::iterator it = copy[i]._edges.begin(); it != copy[i]._edges.end(); ++it) {
                AddEdge(it->first, to, it->second);
            }
        }
    };
    
    void print(){
        for (int i = 0; i < sizeV(); i++) {
            VertexId j = _vertexes[i].getid();
            if(_vertexes[i]._edges.empty()){
                cout << j << "\n";
                continue;
            }
            for(typename list<pair<VertexId, int> >::iterator it = _vertexes[i]._edges.begin(); it != _vertexes[i]._edges.end(); ++it){
                cout << j << "->" << it->first << "(" << it->second << ")\n";
            }
        }
    };
    
    
    int sizeV(){return _vertexes.size();};      //количество вершин
    int sizeE(){                                //количество ребер
        int res = 0;
        for (int i=0; i<_vertexes.size(); i++) {
            res += _vertexes[i]._edges.size();
        }
        return res;
    };
    vector<Vertex> _vertexes;
};

Graph<int>* randomgraph(int n, double p);

#endif /* defined(__Graph__Graph__) */
