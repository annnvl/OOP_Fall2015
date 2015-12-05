//
//  State.cpp
//  8-puzzle
//
//  Created by No_love_no_problem on 24.11.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#include "State.hpp"

int State::_countManhattanDistance(){
    int _M = 0;
    for (int i = 0; i < 9 ; i++) {
        if (_field[i]) {
            _M += abs(i-_field[i]+1);
        }
    }
    return _M;
}

int State::_countLinearConflict(std::set<int>& _linconflict){
    int _L = 0;
    std::vector<int> inversions;                  //в нем хранятся предыдущие цифры, стоящие в своей строке/столбце
    for (int i = 0; i < 9; i++) {                       //по строкам
        if (!_field[i]) {
            continue;
        }
        if (!(i%3)) {
            inversions.clear();                  //переход на новую строку
        }
        if ((_field[i] - 1)/3 == i/3) {             //в своей строке
            for (int y:inversions) {
                if (y > _field[i]) {
                    _L+=2;
                    _linconflict.insert(y);
                    _linconflict.insert(_field[i]);
                }
            }
            inversions.push_back(_field[i]);
        }
    }
    for (int k = 0; k < 3; k++) {                       //по столбцам
        inversions.clear();
        for (int j=0; j<3; j++) {
            int i = k + j*3;
            if (!_field[i]) {
                continue;
            }
            if ((_field[i] - 1)%3 == i%3) {             //в своем столбце
                for (int y:inversions) {
                    if (y > _field[i]) {
                        _L+=2;
                        _linconflict.insert(y);
                        _linconflict.insert(_field[i]);
                    }
                }
                inversions.push_back(_field[i]);
            }
        }
    }
    return _L;
}

int State::_countAngularConflict(std::set<int>& _linconflict){
    int _A = 0;
    _A+=_angle(1, 3, 0, _linconflict);
    _A+=_angle(1, 5, 2, _linconflict);
    _A+=_angle(3, 7, 6, _linconflict);
    return _A;
    
}

int State::_angle(int i, int j, int k, std::set<int>& _linconflict){
    if (!(_field[i] && _field[j] && _field[k])) {
        return 0;
    }
    if ((_field[i]==(i+1))&&(_field[j]==(j+1))&&(_field[k]!=(k+1))) {
        if (_linconflict.count(_field[i])||_linconflict.count(_field[j])||_linconflict.count(_field[k])) {
            return 0;
        }
        return 2;
    }
    return 0;
}

int State::_inversions(){
    int a[8];
    int j = 0;
    for (int i = 0; i<9; i++) {
        if (_field[i] != 0) {
            a[j] = _field[i];
            j++;
        }
    }
    int answer = 0;
    for (int i = 1; i < 8; i++) {
        j = 0;
        while (a[j] < a[i]) {
            j++;
        }
        if (i != j) {
            int k = a[i];
            for (int l=i; l > j; l--) {
                std::swap(a[l], a[l-1]);
            }
            a[j] = k;
        }
        answer+=(i-j);
    }
   // std::cout << answer << " ";
    return answer;
}