//
//  RMQ.hpp
//  RMQ
//
//  Created by No_love_no_problem on 10.12.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#ifndef RMQ_hpp
#define RMQ_hpp

#include <cmath>

class RMQ {
public:
    void operator()(double*& input, int& n){
        _data = new double[4*n];
        _input = input;
        _make(1, 0, n-1);
        n*=4;
        _n=n;
        input = _data;
    };
    ~RMQ(){
        delete[] _input;
    };
    int min(int l, int r){
        if (l>r) {
            return -INFINITY;
        }
        return _min(1, 0, _n-1, l, r);
    };
private:
    void _make(int now, int l, int r) {//now - текущая вершина, l и r - границы
        if (l == r)
            _data[now] = _input[l];
        else {
            int m = (l + r) / 2;
            _make(now*2, l, m);
            _make(now*2+1, m+1, r);
            _data[now] = std::min(_data[now*2], _data[now*2+1]);
        }
    };
    int _min(int now, int lg, int rg, int l, int r){   //lg, rg - что мы имеем; l, r - то, что надо
        if (l>r) {
            return -INFINITY;
        }
        if((lg==l)&&(rg==r)){
            return _data[now];
        };
        int m = (lg+rg)/2;
        return std::min(_min(now*2, lg, m, l, std::min(r, m)), _min(now*2+1, m+1, rg, std::max(l, m+1), r));
    };
    double* _data;
    double* _input;
    int _n;
};

#endif /* RMQ_hpp */
