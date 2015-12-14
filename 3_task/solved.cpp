//
//  main.cpp
//  8-puzzle
//
//  Created by No_love_no_problem on 24.11.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <vector>
#include <set>
#include <utility>
#include <climits>
#include <stack>
#include <algorithm>

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

bool pred(std::pair<State, char> el1, std::pair<State, char> el2){return (el1.first.getheuristic() < el2.first.getheuristic());}

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
            for (size_t o=0; o<inversions.size(); o++) {
                int y = inversions[o];
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
                for (int q=0; q<inversions.size(); q++) {
                    int y =inversions[q];
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
    return answer;
}

class Comparator {
public:
    bool operator()(const State& one,const State& another)const{
        if ((one.getsteps()+one.getheuristic()) > (another.getsteps()+another.getheuristic())) {
            return 1;
        }
        return 0;
    };
};

class A_star{
public:
    void getanswer(State& s){
        _limit = s.getheuristic();
        _steps = 0;
        _opened.insert(s);
        while (!_maker(s)) {
            _limit++;
        }
    };
    std::string answer;
private:
    bool _maker(State& s){
        if (_steps > _limit) {
            return 0;
        }
        if (s.getheuristic()==INT_MAX) {
            return 0;
        }
        if (!s.getheuristic()) {
            answer = s.getpath();
            return 1;
        }
        char prev = s.getlast();
        State newst = s.right();
        if (prev != 'l') {
            newst = s.right();
            int i = _opened.count(newst);
            if ((newst.getheuristic() != INT_MAX)&&(_opened.count(newst))) {
                variants.push(newst);
                _opened.insert(newst);
            }
        }
        if (prev != 'r') {
            newst = s.left();
            if ((newst.getheuristic() != INT_MAX)&&(_opened.count(newst))) {
                variants.push(newst);
                _opened.insert(newst);
            }
        }
        if (prev != 'd') {
            newst = s.up();
            if ((newst.getheuristic() != INT_MAX)&&(_opened.count(newst))) {
                variants.push(newst);
                _opened.insert(newst);
            }
        }
        if (prev != 'u') {
            newst = s.down();
            if ((newst.getheuristic() != INT_MAX)&&(_opened.count(newst))) {
                variants.push(newst);
                _opened.insert(newst);
            }
        }
        while (!variants.empty()) {
            newst = variants.top();
            variants.pop();
            _steps++;
            if (_maker(newst)) {
                return 1;
            }
            _steps--;
        }
        return 0;
    };
    
    int _limit;
    int _steps;
    std::priority_queue<State, std::vector<State>, Comparator> variants;
    std::set<State, Comparator> _opened;      //просмотренные вершины
};

std::string solve(State& s){
    A_star meth;
    meth.getanswer(s);
    return meth.answer;
}

int main() {
    int a[9];
    for (int i = 0; i<9; i++) {
        std::cin >> a[i];
    }
    State s(a);

    if (!s.isCountable()) {
        std::cout << "No\n";
        return 0;
    }

    std::cout << "Yes\n";
    std::stack<char> answer = solve(s);

    std::cout << answer.size() << "\n";
    /*
     while (!answer.empty()) {
     std::cout << answer.top() << " ";
     answer.pop();
     }*/
    return 0;
}
