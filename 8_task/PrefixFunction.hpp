//
//  PrefixFunction.hpp
//  Cheeky-Cheeky
//
//  Created by No_love_no_problem on 16.12.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#ifndef PrefixFunction_hpp
#define PrefixFunction_hpp

#include <string>
#include <iostream>
#include <vector>

class PrefixFunction {
public:
    void operator()(std::string& s);   //считает префикс-функцию для строки
    friend std::ostream& operator << (std::ostream& os, PrefixFunction& pref);
    void printContinuation();
private:
    std::vector<int> _data;
    int _n;
    std::string _input;
};

#endif /* PrefixFunction_hpp */
