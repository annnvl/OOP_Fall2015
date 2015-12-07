//
//  main.cpp
//  Graph
//
//  Created by No_love_no_problem on 15.09.15.
//  Copyright (c) 2015 Anna Vlasova. All rights reserved.
//

#define BOOST_TEST_MAIN MyModule
#include <boost/test/included/unit_test.hpp>
#include "Graph.h"
#include "Kosaraju.h"
#include "Tarjan.h"

BOOST_AUTO_TEST_SUITE( main_test_suite )

BOOST_AUTO_TEST_CASE(main_case) {
    for(int i = 5; i < 1000; i++){
        Graph<int>* gr = randomgraph(i, 0.007);
    
        list<list<int> > Kcomp = Kosaraju<int>(*gr);
        for (auto y = Kcomp.begin(); y != Kcomp.end(); y++) {
            y->sort();
        }
        Kcomp.sort([](list<int> a,list<int> b){return a.front() > b.front();});
        list<list<int> > Tcomp = Tarjan<int>(*gr);
        for (auto y = Tcomp.begin(); y != Tcomp.end(); y++) {
            y->sort();
        }
        Tcomp.sort([](list<int> a,list<int> b){return a.front() > b.front();});
    
        BOOST_CHECK(Kcomp == Tcomp);
    }
}

BOOST_AUTO_TEST_SUITE_END()
