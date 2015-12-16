//
//  PrefixFunction.cpp
//  Cheeky-Cheeky
//
//  Created by No_love_no_problem on 16.12.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#include "PrefixFunction.hpp"

void PrefixFunction::operator()(std::string &s){
    _input = s;
    _n = s.length();
    _data.resize(_n, 0);
    for (int i=1; i<_n; ++i) {
        int j = _data[i-1];
        while (j > 0 && s[i] != s[j])
            j = _data[j-1];
        if (s[i] == s[j])  ++j;
        _data[i] = j;
    }
}

std::ostream& operator <<(std::ostream& os, PrefixFunction& pref){
    for (int i = 0; i < pref._n; i++) {
        os << pref._data[i] << " ";
    }
    os << "\n";
    return os;
}

void PrefixFunction::printContinuation(){
    int cyclelength = 0;
    for (int i = (_n-1)*2/3; i<_n; i++) {
        if ((i%2)&&(_data[i] >= (i+1)/2)&&(_input[i/2] == _input[i])) {
            cyclelength = (i+1)/2;
            break;
        }
    }
    int j = _n - cyclelength*2;
    for (int i = 0; i < 8; i++) {
        std::cout << _input[j];
        j++;
        j%=cyclelength;
    }
    std::cout<< "...\n";
}
