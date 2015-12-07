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
#include <unordered_map>
#include <unordered_set>

template <class VertexId>
class Graph {
public:
    Graph(){
        _maxid = 0;
    };
    
    class Edges{
    public:
        class iterator{
        public:
            iterator(typename std::unordered_map<int, int>::iterator it){
                _pointer = it;
            };
            std::pair<int, int> operator*(){
                return std::pair<int, int>(*_pointer);
            };
            std::pair<int, int>* operator->(){
                std::pair<int, int>* it = new std::pair<int, int>(_pointer->first, _pointer->second);
                return it;
            };
            iterator operator++(){
                _pointer++;
                return _pointer;
            };
            bool operator!=(const iterator it){
                return (_pointer != it._pointer);
            };
        private:
            typename std::unordered_map<int, int>::iterator _pointer;
        };
        iterator begin(){
            return iterator(_edges.begin());
        };
        iterator end(){
            return iterator(_edges.end());
        };
        void insert(int id, int weight){
            _edges.insert(std::pair<int, int>(id, weight));
        };
        void erase(int id){
            _edges.erase(id);
        };
        void clear(){
            _edges.clear();
        };
    private:
        std::unordered_map<int, int> _edges;
    };
    
    void AddVertex(VertexId newvert){
        int id = _maxid;
        _maxid++;
        _data.insert(std::pair<int, VertexId>(id, newvert));
        _vertexes.insert(std::pair<int, Edges>(id, Edges()));
    };
    void AddEdge(int idfrom, int idto, int weight){
        _vertexes[idfrom].insert(idto, weight);
    };
    void DeleteVertex(int id){
        _data.erase(id);
        for (auto i = _vertexes.begin(); i != _vertexes.end(); i++) {
            for (auto j = i->second.begin(); i != i->second.end(); j++) {
                if(*j == id){
                    i->second.erase(j);
                }
            }
        }
    };
    void DeleteEdge(int idfrom, int idto){
        _vertexes[idfrom].erase(idto);
    };
    
    int getid(VertexId elem){
        for (auto i = _data.begin(); i != _data.end; i++) {
            if(i->second == elem){
                return i->first;
            }
        }
        return -1;
    };
    
    VertexId& getdata(int id){
        return _data[id];
    };
    
    class iterator{
    public:
        iterator(typename std::unordered_map<int, Edges>::iterator it){
            _pointer = it;
        };
        std::pair<int, Edges> operator*(){
            return std::pair<int, Edges>(*_pointer);
        };
        std::pair<int, Edges>* operator->(){
            std::pair<int, Edges>* it = new std::pair<int, Edges>(_pointer->first, _pointer->second);
            return it;
        };
        iterator operator++(){
            _pointer++;
            return _pointer;
        };
        bool operator!=(const iterator it){
            return (_pointer != it._pointer);
        };
    private:
        typename std::unordered_map<int, Edges>::iterator _pointer;
    };
    
    iterator findvertex(int id){
        return _vertexes.find();
    };
    
    iterator begin(){
        return iterator(_vertexes.begin());
    };
    iterator end(){
        return iterator(_vertexes.end());
    };
    int size(){
        return _vertexes.size();
    };
    
    void Transpose(){
        std::unordered_map<int, Edges> copy(_vertexes);
        for (auto y=_vertexes.begin(); y!=_vertexes.end(); ++y) {
            y->second.clear();
        }
        for (auto y:copy){
            for (auto z:y.second) {
                AddEdge(z.first, y.first, z.second);
            }
        }
    };
    
    void print(){
        for (auto y:_vertexes) {
            std::cout << y.first << " -> ";
            for (auto z=y.second.begin(); z != y.second.end(); ++z) {
                std::cout << z->first << " ";
            }
            std::cout << "\n";
        }
    };
    
    Edges& operator[](int i){
        return _vertexes[i];
    };
    
private:
    std::unordered_map<int, Edges> _vertexes;
    std::unordered_map<int, VertexId> _data;
    int _maxid;
};
Graph<int>* randomgraph(int n, double p);

#endif /* defined(__Graph__Graph__) */
