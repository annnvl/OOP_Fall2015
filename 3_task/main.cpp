//
//  main.cpp
//  8-puzzle
//
//  Created by No_love_no_problem on 24.11.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#include <iostream>
#include "A_star.hpp"

int main() {
    int a[9];
    for (int i = 0; i<9; i++) {
        std::cin >> a[i];
    }
    State s;
    s.init(a);
    
    if (!s.isCountable()) {
        std::cout << "No";
        return 0;
    }
    
    std::cout << "Yes\n";
    std::stack<char> answer = solve(s);
    
    std::cout << answer.size() << "\n";
    
    while (!answer.empty()) {
        std::cout << answer.top() << " ";
        answer.pop();
    }
    return 0;
}
