//
//  Algo.hpp
//  Bricks
//
//  Created by No_love_no_problem on 17.12.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#ifndef Algo_hpp
#define Algo_hpp

#include <fstream>
#include <map>
#include <set>
#include "Graph.hpp"

class Bricks {
public:
    void getconfig(const char* filename);
    void FordFulkerson();
private:
    int _getpath(int i, int j);    //найти путь с ненулевыми весами из i в j, возвращиет мин вес
    
    Graph<int> _G;     //собсна, граф кубиков и вершин
    std::string _word;      //слово
    std::map<char, int> _letters; //буква - id
    std::stack<int> _path;
    std::vector<std::vector<int> > f;
    std::set<int> cycle;
};

#endif /* Algo_hpp */
