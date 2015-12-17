//
//  Algo.cpp
//  Bricks
//
//  Created by No_love_no_problem on 17.12.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#include "Algo.hpp"

void Bricks::getconfig(const char *filename){
    std::ifstream in;
    in.open(filename);
    
    _G.AddVertex(0);    //начало
    _G.AddVertex(1);    //конец
    in >> _word;
    for (int i = 0; i < _word.length(); i++) {
        if (_letters.count(_word[i])) {
            _G[_letters[_word[i]]][1]++;
            continue;
        }
        int id = _G.AddVertex(_word[i]);
        _letters.insert(std::pair<char, int>(_word[i], id));
        _G.AddEdge(id, 1, 1);
    }
    
    //слово добавлено, добавим кубики
    std::string cube;
    int num = 1;    //номер кубика
    while (in >> cube) {
        int id = _G.AddVertex(num);
        _G.AddEdge(0, id, 1);
        for (int i = 0; i < cube.length(); i++) {
            if (_letters.count(cube[i])) {
                _G.AddEdge(id, _letters[cube[i]], 1);
            }
        }
        num++;
    }
    in.close();
}

void Bricks::FordFulkerson(){
    //_G.print();
    std::vector<std::vector<int> > f;
    for (int i = 0; i < _G.size(); i++) {
        f.push_back(std::vector<int>(_G.size(), 0));
    }
    int min;
    while ((min = _getpath(0, 1)) < INT_MAX) {
        int prev = 0;
        while (!_path.empty()) {
            int next = _path.top();
            _path.pop();
            f[prev][next]+=min;
            f[next][prev]-=min;
            _G[prev][next]-=min;
            _G[next][prev]+=min;
            prev = next;
            //_G.print();
        }
    }
    
    int sum = 0;
    for (int i : f[0]) {
        sum+=i;
    }
    if (sum < _word.length()) {
        std::cout << "No\n";
        return;
    }
    std::cout << "Yes\n";
    for (char c:_word) {
        for (int i=_letters[c]; i < f.size(); i++) {
            if (f[_letters[c]][i] == -1) {
                f[_letters[c]][i] = 0;
                std::cout << _G.getdata(i) << " ";
                break;
            }
        }
    }
}

int Bricks::_getpath(int i, int j){
    cycle.insert(i);
    for (auto it = _G[i].begin(); it != _G[i].end(); ++it) {
        if ((it->second <= 0)||(cycle.count(it->first))) {
            continue;
        }
        if (it->first == j) {
            _path.push(it->first);
            cycle.erase(i);
            return it->second;
        }
        int path = _getpath(it->first, j);
        if(path < INT_MAX){
            _path.push(it->first);
            cycle.erase(i);
            return std::min(path, it->second);
        }
    }
    cycle.erase(i);
    return INT_MAX;
}
