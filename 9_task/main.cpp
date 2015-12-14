//
//  main.cpp
//  BadWords
//
//  Created by No_love_no_problem on 07.12.15.
//  Copyright © 2015 Anna Vlasova. All rights reserved.
//

#include "Bor.hpp"
#include <fstream>

int main(){
    std::ifstream in;
    std::ofstream out;
    in.open("/Users/no_love_no_problem/Documents/Xcode/BadWords/BadWords/stopwords.txt");
    std::string input;
    Bor stopwords;
    while (in >> input) {
        stopwords.addstring(input);
    }
    in.close();
    in.open("/Users/no_love_no_problem/Documents/Xcode/BadWords/BadWords/input.txt");
    out.open("/Users/no_love_no_problem/Documents/Xcode/BadWords/BadWords/output.txt");
    std::getline(in, input, '\n');
    out << stopwords.modify(input);
    while (std::getline(in, input, '\n')) {
        out << "\n" << stopwords.modify(input);
    }
    in.close();
    out.close();
    return 0;
}
