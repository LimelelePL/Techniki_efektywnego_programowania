
#include <iostream>

#include "SmartPointer/SmartPointer.h"
#include "Tree/Interface.h"
int main() {

    SmartPointer ptr (new int (10));
    cout<<"ptr : " << *ptr << endl;
    SmartPointer ptr1 = ptr;
    cout<<"ptr1 : " << *ptr1 << endl;
    SmartPointer ptr2 = std::move(ptr);
    cout<<"ptr1: " << *ptr1 << endl;


    Tree::resetCounters();
    Tree a;
    a.enter("+ 1 2");
    Tree b(a);
    Tree::printCounters();
    cout<<endl;

    Tree::resetCounters();
    Tree c;
    c.enter("* 3 4");
    Tree d;
    d = c;
    Tree::printCounters();
    cout<<endl;

    Tree::resetCounters();
    Tree t1; t1.enter("+ 1 2");
    Tree t2; t2.enter("* 3 4");
    Tree t3 = t1 + t2;
    Tree::printCounters();
    cout<<endl;

    Tree::resetCounters();
    Tree m1; m1.enter("+ 5 6");
    Tree m2; m2.enter("* 7 8");
    m1 = std::move(m2); // powinien użyć operator=(Tree&&)
    Tree::printCounters();
    cout << endl;


    Tree::resetCounters();
    Tree j; j.enter("+ 1 2");
    j.join("* 9 9");
    Tree::printCounters();
    cout << endl;


    //Interface interface;
    //interface.run();

}
