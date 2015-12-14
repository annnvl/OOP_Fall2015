//
//  Bor.cpp
//  BadWords
//
//  Created by No_love_no_problem on 07.12.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#include "Bor.hpp"

void Bor::addstring(std::string& s){
    int i = 0;
    for (int p = 0; p < s.length(); p++) {
        int j = -1;
        for(auto it = G[i].begin(); it != G[i].end(); ++it){
            if (it->second == s[p]) {
                j = it->first;
                break;
            }
        }
        if (j == -1) {
            j = G.AddVertex(info((p == s.length()-1), (!p)-1, p+1, (p == s.length()-1)?G.size():(p ? -1 : 0))); //изначально ссылок нет для всех, кроме сыновей корня и выходных ссылок на себя для выходных вершин
            G.AddEdge(i, j, s[p]);
            _parents[j] = i;
        }
        else if (p == s.length()-1){
            G.getdata(j).end = 1;
            G.getdata(j).suffout = j;
        }
        i = j;
    }
}

int Bor::getsufflink(int id){
    int ans = G.getdata(id).sufflink;
    if (ans > -1) {
        return ans;
    }
    int parlink = getsufflink(_parents[id]);
    char letter = G[_parents[id]][id];
    while (true) {
        int j = -1;
        for(auto it = G[parlink].begin(); it != G[parlink].end(); ++it){
            if (it->second == letter) {
                j = it->first;
                break;
            }
        }
        if (j > -1) {
            G.getdata(id).sufflink = j;
            return j;
        }
        if (!parlink) {
            G.getdata(id).sufflink = 0;
            return 0;
        }
        parlink = getsufflink(parlink);
    }
    return ans;
}

int Bor::exitable(int id){
    int ans = G.getdata(id).suffout;
    if (ans > -1) {
        return ans;
    }
    if (G.getdata(id).end) {
        G.getdata(id).suffout = id;
        return id;
    }
    ans = exitable(getsufflink(id));
    G.getdata(id).suffout = ans;
    return ans;
}

std::string Bor::modify(std::string s){
    int pos=0;              //позиция выхода
    int id = 0;             //вершина, в которой мы находимся
    for (int i=0; i<s.length(); i++){
        id = _push(id , s[i]);
        pos=exitable(id);
        if (pos) {
            int len = G.getdata(pos).reslen;
            if (_limit<10) {
                std::cout << _pos-len+1 << " ";
                _limit++;
            }
            s.erase(i-len+1, len);
            //i=i-len+1;
            for (int w=0; w<len; w++) {
                s.insert(i-len+1, "*");
            }
        }
        _pos++;
    }
    return s;
}

int Bor::_push(int id, char c){
    for (int i = id; true; i=getsufflink(i)) {
        int j = -1;
        for(auto it = G[i].begin(); it != G[i].end(); ++it){
            if (it->second == c) {
                j = it->first;
                break;
            }
        }
        if (j > -1) {
            return j;
        }
        if (!i) {
            return 0;
        }
    }
    return 0;
}
