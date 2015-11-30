//
//  A_star.hpp
//  8-puzzle
//
//  Created by No_love_no_problem on 24.11.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#ifndef A_star_hpp
#define A_star_hpp

#include <stdio.h>
#include "State.hpp"
#include <stack>
#include <algorithm>

class A_star{
public:
    A_star(State& s){
        _limit = s.getheuristic();
        _steps = 0;
        while (!_maker(s, 'n')) {
            _limit++;
        }
    };
    std::stack<char> _algorihtm;
private:
    bool _maker(State& s, char prev){                   //второй аргумент - предыдущий шаг, иначе можем уйти в бесконечную рекурсию
        if (_steps > _limit) {
            return 0;
        }
        if (s.getheuristic()==INT_MAX) {
            return 0;
        }
        if (!s.getheuristic()) {
            return 1;
        }
        std::vector<std::pair<State, char>> variants;
        if(prev != 'd'){
            variants.push_back(std::pair<State, char>(s.up().first, 'u'));
            if (variants[variants.size()-1].first.getheuristic() == INT_MAX) {
                variants.pop_back();
            }
        }
        if(prev != 'u'){
            variants.push_back(std::pair<State, char>(s.down().first, 'd'));
            if (variants[variants.size()-1].first.getheuristic() == INT_MAX) {
                variants.pop_back();
            }
        }
        if(prev != 'l'){
            variants.push_back(std::pair<State, char>(s.right().first, 'r'));
            if (variants[variants.size()-1].first.getheuristic() == INT_MAX) {
                variants.pop_back();
            }
        }
        if(prev != 'r'){
            variants.push_back(std::pair<State, char>(s.left().first, 'l'));
            if (variants[variants.size()-1].first.getheuristic() == INT_MAX) {
                variants.pop_back();
            }
        }
        std::sort(variants.begin(), variants.end(), [](std::pair<State, char> el1, std::pair<State, char> el2){return (el1.first.getheuristic() < el2.first.getheuristic());});
        for (int i = 0; i < variants.size(); i++) {
            _steps++;
            if (_maker(variants[i].first, variants[i].second)) {
                _algorihtm.push(variants[i].second);
                return 1;
            }
            _steps--;
        }
        return 0;
    };

    int _limit;
    int _steps;
};

std::stack<char> solve(State& s){
    A_star meth(s);
    return meth._algorihtm;
}

#endif /* A_star_hpp */
