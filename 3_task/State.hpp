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

class State {                                       //состояние, в котором мы находимся
public:
    void init(int input[]){
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
    int getpos(int i, int j){               //позиция, в которой пустая клетка
        return _field[i*3+j];
    };
    
    State up(){
        State ans;
        if (_pos < 3) {
            return ans.init(0);
        }
        int a[9];
        for (int i = 0 ; i < 9; i++){
            a[i] = _field[i];
        }
        std::swap(a[_pos], a[_pos-3]);
        return ans.init(a);
    };
    State down(){
        State ans;
        if (_pos > 5) {
            return ans.init(0);
        }
        int a[9];
        for (int i = 0 ; i < 9; i++){
            a[i] = _field[i];
        }
        std::swap(a[_pos], a[_pos+3]);
        return ans.init(a);
    };
    State right(){
        State ans;
        if (_pos%3 == 2) {
            return ans.init(0);
        }
        int a[9];
        for (int i = 0 ; i < 9; i++){
            a[i] = _field[i];
        }
        std::swap(a[_pos], a[_pos+1]);
        return ans.init(a);
    };
    State left(){
        State ans;
        if (!(_pos%3)) {
            return ans.init(0);
        }
        int a[9];
        for (int i = 0 ; i < 9; i++){
            a[i] = _field[i];
        }
        std::swap(a[_pos], a[_pos-1]);
        return ans.init(a);
    };
    
    bool isCountable(){
        if(((_pos/3)+_inversions())%2){
            return 1;
        }
        return 0;
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
