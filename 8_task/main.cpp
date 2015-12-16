//
//  main.cpp
//  Cheeky-Cheeky
//
//  Created by No_love_no_problem on 16.12.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//
#include "PrefixFunction.hpp"

int main() {
    PrefixFunction pref;
    std::string s;
    int n;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> s;
        pref(s);
        pref.printContinuation();
    }
    return 0;
}
