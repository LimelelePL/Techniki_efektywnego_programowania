#include <iostream>

#include "Interface.h"
#include "Tree.h"

int main() {

    Interface interface;
    interface.run();
    // cout << "==== TEST 0: naprawa +++  ====" << endl;
    // Tree t0;
    // t0.enter("+ + +");
    // t0.print(); // + + + 1 1 1 1
    // cout << endl << endl;
    //
    // cout << "==== TEST 01: naprawa +1  ====" << endl;
    // Tree t01;
    // t01.enter("+ 1 1 1"); // + 1 1
    // t01.print();
    // cout << endl << endl;
    //
    // cout << "==== TEST 1: enter + print ====" << endl;
    // Tree t1;
    // t1.enter("+ 3 4");
    // t1.print();   // + 3 4
    // cout << endl << endl;
    //
    // cout << "==== TEST 2: zmienne + vars() ====" << endl;
    // Tree t2;
    // t2.enter("+ a * b 3");
    // t2.print();    // + a * b 3
    // cout << endl;
    // t2.vars();     // a b
    // cout << endl << endl;
    //
    // cout << "==== TEST 3: compute ====" << endl;
    // Tree t3;
    // t3.enter("+ * a 2 sin b");
    // t3.print();
    // cout << endl;
    //
    // vector<double> vals3 = {5, 3};  // a=5, b=3
    // t3.comp(vals3); // wynik: 10.1411
    // cout << endl;
    //
    // cout << "==== TEST 4: operator+ podstawowy ====" << endl;
    // Tree t4;
    // Tree t5;
    // t4.enter("+ a b");
    // t5.enter("* 2 3");
    //
    // Tree t6 = t4 + t5;
    // t6.print();   // + b * 2 3
    // cout << endl << endl;
    //
    // cout << "==== TEST 5: operator+ gdy root jest lisciem ====" << endl;
    // Tree t7;
    // Tree t8;
    // t7.enter("a");
    // t8.enter("b");
    //
    // Tree t9 = t7 + t8;
    // t9.print();   // b
    // cout << endl << endl;
    //
    // cout << "==== TEST 6: join ====" << endl;
    // Tree t10;
    // t10.enter("+ a b");
    // t10.join("* 2 2");
    //
    // t10.print();   // + b * 2 2
    // cout << endl << endl;
    //
    // cout << "==== TEST 7: comp po join ====" << endl;
    // Tree t11;
    // t11.enter("+ a b 3");
    // t11.print();
    //
    // t11.join("+ 1 1");
    // t11.print();   // + a 3 + 1 1
    // cout << endl;
    //
    // vector<double> vals11 = {4}; // b=4
    // t11.comp(vals11); // wynik = 4 + (1+1) = 6
    // cout << endl;
    //
    // cout << "==== TEST 8: operator+ z pustym drzewem ====" << endl;
    // Tree t12;
    // Tree t13;
    // t12.enter("+ 1 2");
    //
    // Tree t14 = t13 + t12;
    // t14.print();   // + 1 2
    // cout << endl << endl;
    //
    // cout << "==== TEST 9: join na pustym drzewie ====" << endl;
    // Tree t15;
    // t15.join("+ 2 2");
    // t15.print();  // + 2 2
    // cout << endl << endl;
    //
    // cout << "==== TEST 10: wiele operatorow + ====" << endl;
    // Tree a, b, c;
    // a.enter("+ x 1");
    // b.enter("+ y 2");
    // c.enter("+ z 3");
    //
    // Tree r = a + b;
    // r.print();
    // cout<<endl;
    // r = r + c;
    // r.print();  // x x y 2 + z 3
    // cout << endl << endl;
    //
    // cout << "==== TEST 11: gleboka rekursja ====" << endl;
    // Tree longTree;
    // longTree.enter("+ + + 1 1 1 1");
    // longTree.print();
    // cout << endl;
    // vector<double> vlong; // brak zmiennych
    // longTree.comp(vlong);
    // cout << endl << endl;
    //
    //
    // cout<<"==== TEST 12: NIEPOPRAWNA NAZWA ZMIENNEJ - ZMIANA NA LICZBE ====" <<endl;
    // Tree t123;
    // t123.enter("+ &3 a");
    // vector<double> vt123 = {1};
    // t123.comp(vt123);
    //
    // cout<<"==== TEST 14: NIEPOPRAWNA NAZWA ZMIENNEJ ====" <<endl;
    // Tree t1234;
    // t1234.enter("+ &$ a");
    //
    // cout<<"==== TEST 15: NIEPOPRAWNA LICZBBA ====" <<endl;
    // Tree t12345;
    // t12345.enter("+ 1.1 a");
    // vector<double> vt12345 = {1};
    // t12345.comp(vt12345);
    //
    // cout<<"==== TEST 15: duzo zmiennych a ====" <<endl;
    // Tree ta1;
    // ta1.enter("+ + a a + a a");
    // ta1.print();
    // cout<<"vars () "<<endl;
    // ta1.vars();
    // cout<<"compute 1 "<<endl;
    // vector<double> ta1v = {1};
    // ta1.comp(ta1v);
    //
    // cout<<"==== TEST 15: duzo zmiennych a i b ====" <<endl;
    // Tree ta2;
    // ta2.enter("+ + a a + b b  ");
    // ta2.print();
    // cout<<"vars () "<<endl;
    // ta2.vars();
    // cout<<"comp 1,2 "<<endl;
    // vector<double> ta2v = {1,2};
    // ta2.comp(ta2v);
    //
    // cout << "==== TESTY ZAKOŃCZONE ====" << endl;
    // return 0;
}
