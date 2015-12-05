//
//  State.hpp
//  8-puzzle
//
//  Created by No_love_no_problem on 24.11.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#ifndef State_hpp
#define State_hpp

#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <utility>
#include <climits>

class State {
public:
    State(int input[]){
        if (input) {
            for (int i = 0 ; i < 9; i++) {
                _field[i] = input[i];
                if(!input[i]){
                    _pos = i;
                }
            }
            std::set<int> _linconflict;
            _heuristic = _countManhattanDistance();
            _heuristic += _countLinearConflict(_linconflict);
            _heuristic += _countAngularConflict(_linconflict);
        } else{
            _heuristic = INT_MAX;
        }
    }
    int getheuristic(){
        return _heuristic;
    };
    int getpos(int i, int j){
        return _field[i*3+j];
    };
    
    std::pair<State, bool> up(){
        if (_pos < 3) {
            return std::pair<State, bool>(State(0), 0);
        }
        int a[9];
        for (int i = 0 ; i < 9; i++){
            a[i] = _field[i];
        }
        std::swap(a[_pos], a[_pos-3]);
        return std::pair<State, bool>(State(a), 0);
    };
    std::pair<State, bool> down(){
        if (_pos > 5) {
            return std::pair<State, bool>(State(0), 0);
        }
        int a[9];
        for (int i = 0 ; i < 9; i++){
            a[i] = _field[i];
        }
        std::swap(a[_pos], a[_pos+3]);
        return std::pair<State, bool>(State(a), 0);
    };
    std::pair<State, bool> right(){
        if (_pos%3 == 2) {
            return std::pair<State, bool>(State(0), 0);
        }
        int a[9];
        for (int i = 0 ; i < 9; i++){
            a[i] = _field[i];
        }
        std::swap(a[_pos], a[_pos+1]);
        return std::pair<State, bool>(State(a), 0);
    };
    std::pair<State, bool> left(){
        if (!(_pos%3)) {
            return std::pair<State, bool>(State(0), 0);
        }
        int a[9];
        for (int i = 0 ; i < 9; i++){
            a[i] = _field[i];
        }
        std::swap(a[_pos], a[_pos-1]);
        return std::pair<State, bool>(State(a), 0);
    };
    
    bool isCountable(){
        if(((_pos/3)+_inversions())%2){
            return 0;
        }
        return 1;
    };
private:
    int _countManhattanDistance();
    int _countLinearConflict(std::set<int>&);
    int _countAngularConflict(std::set<int>&);
    int _angle(int, int, int, std::set<int>&);              //один конкретный угол
    
    int _inversions();                                  //количество инверсий в массиве
    
    int _field[9];
    int _pos;               //позиция, на которой стоит 0
    int _heuristic;
};

#endif /* State_hpp */
