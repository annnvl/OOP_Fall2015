//
//  Bor.hpp
//  BadWords
//
//  Created by No_love_no_problem on 07.12.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#ifndef Bor_hpp
#define Bor_hpp

#include <string>
#include "Graph.h"

class Bor {
public:
    Bor(){G.AddVertex(info());_pos=0; _limit=0;};
    void addstring(std::string&);
    std::string modify(std::string);   //возвращает позицию и подстроку с заменой
    void print(){G.print();};
    int size(){return G.size();};
private:
    int getsufflink(int id);
    int exitable(int id);   //является ли выходной и возвращиет ближайшую выходную
    struct info{
        info(){end=0; sufflink=0; reslen=0; suffout=0;};
        info(bool b, int i, int s, int so){end=b; sufflink=i; reslen=s; suffout=so;};
        bool end;//является ли конечной
        int sufflink;
        int reslen;         //длина строки
        int suffout;        //ближайшая выходная суффиксная ссылка
    };
    Graph<info> G;
    std::unordered_map<int, int> _parents;
    int _pos;
    int _limit;
    int _push(int id, char с); //проталкивание символа по бору
    //std::vector<int> _positions;
};

#endif /* Bor_hpp */
