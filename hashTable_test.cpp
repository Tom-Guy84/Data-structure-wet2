#include <iostream>
#include "HashTable.h"
#include <cassert>

using namespace wet2_dast;

int main() {
    //hashtable tests will be here soon!
    HashTable<int> a(3);
    HashTable<int> b(3);
    a.print_array();
    b.print_array();
    Union(a,b);
   int * num_1 =new int(1);
   int * num_2 =new int(2);
   int * num_3=new int(3);
   int * num_4 =new int(4);
   int * num_5 =new int(5);
   a.insert_object(num_1,1) ;
   assert(a.find_object(1) !=nullptr);
   a.insert_object(num_2,2) ;
   b.insert_object(num_3,3) ;
   b.insert_object(num_4,4) ;
   try {
       b.insert_object(num_4,4);
   }
    catch(std::exception& e) {
        std::cout << "got 'em" << std::endl;
    }
    a.print_array();
    b.print_array();
    Union(a, b);
    assert(a.find_object(1) != nullptr);
    assert(a.find_object(2) != nullptr);
    assert(a.find_object(3) != nullptr);
    assert(a.find_object(4) != nullptr);
    try {
        assert(b.find_object(1) == nullptr);
        assert(b.find_object(2) == nullptr);
        assert(b.find_object(3) == nullptr);
        assert(b.find_object(4) == nullptr);
    }
    catch (HashTable<int>::exceptions &e) {
        std::cout << "???" << std::endl;
    }

    a.print_array();
    b.print_array();
    Union(b, a);
    a.print_array();
    b.print_array();
    assert(b.find_object(1) != nullptr);
    assert(b.find_object(2) != nullptr);
    assert(b.find_object(3) != nullptr);
    assert(b.find_object(4) != nullptr);
    try {
        assert(a.find_object(1) == nullptr);
        assert(a.find_object(2) == nullptr);
        assert(a.find_object(3) == nullptr);
        assert(a.find_object(4) == nullptr);
    }
    catch (HashTable<int>::exceptions &e) {
        std::cout << "???" << std::endl;
    }
    delete num_5;
    return 0;

}
