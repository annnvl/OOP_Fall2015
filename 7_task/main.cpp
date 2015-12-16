//
//  main.cpp
//  RMQ
//
//  Created by No_love_no_problem on 10.12.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#include <iostream>
#include <cmath>

class RMQ {
public:
    void operator()(double*& input, long& n){
        _data = new double[4*n];
        _input = input;
        _n=n*4;
        for (int i = 0; i<_n; i++) {
            _data[i] = -1;
        }
        _make(0, 0, n-1);
        n*=4;
        input = _data;
    };
    ~RMQ(){
        delete[] _input;
    };
    double min(long l, long r){
        if (l>r) {
            return INFINITY;
        }
        return _min(0, 0, _n/4-1, l, r-1);
    };
private:
    void _make(long now, long l, long r) {//now - текущая вершина, l и r - границы
        if (l == r)
            _data[now] = _input[l];
        else {
            long m = (l + r) / 2;
            _make(now*2+1, l, m);
            _make(now*2+2, m+1, r);
            _data[now] = std::min(_data[now*2+1], _data[now*2+2]);
        }
    };
    double _min(long now, long lg, long rg, long l, long r){   //lg, rg - что мы имеем; l, r - то, что надо
        if (l>r) {
            return INFINITY;
        }
        if((lg==l)&&(rg==r)){
            return _data[now];
        };
        long m = (lg+rg)/2;
        return std::min(_min(now*2+1, lg, m, l, std::min(r, m)), _min(now*2+2, m+1, rg, std::max(l, m+1), r));
    };
    double* _data;
    
    double* _input;
    long _n;
};

int main(int argc, const char * argv[]) {
    long n, r, l;
    std::cin >> n;
    double* input = new double[n];
    /*for (int i=0; i<n; i++) {
        std::cin >> input[i];
    }*/
    int k=1;
    for (int i=0; i<n; i++) {
        input[i]=rand()%1000 * k;
        k*=(-1);
    }
    for (int i=0; i<n; i++) {
        std::cout << input[i] << " ";
    }
    std::cout << "\n\n";
    RMQ rmq;
    rmq(input, n);
    for (int i=0; i<n; i++) {
        std::cout << input[i] << " ";
    }
    std::cin >> n;
    for (long i=0; i<n; i++) {
        std::cin >> l >> r;
        std::cout << rmq.min(l, r) << "\n";
    }
    delete[] input;
    return 0;
}
