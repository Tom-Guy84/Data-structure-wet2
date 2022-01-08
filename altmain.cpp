//
// Created by Tom Guy on 1/2/2022.
//

#include "AVLRankTree.h"
using namespace wet2_dast;

int main()
{
    AVLRankTree<int> tree;
    int *a = new int;
    *a = 4;
    int* c = new int;
    *c = 6;
    int *aaa = new int;
    *aaa = 333;
    int *ccc = new int;
    *ccc = 666;
    tree.insert(*a);
    int *b = tree.find(4);
    std::cout<<*b<<std::endl;
    tree.insert(*aaa);
    std::cout<<tree.between_to_places(c,ccc);
    return 0;
}