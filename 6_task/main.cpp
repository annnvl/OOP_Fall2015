//
//  main.cpp
//  Bricks
//
//  Created by No_love_no_problem on 01.12.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#include "Algo.hpp"

int main() {
    Bricks b;
    b.getconfig("/Users/no_love_no_problem/Documents/Xcode/Bricks/Bricks/input.txt");
    b.FordFulkerson();
    return 0;
}
