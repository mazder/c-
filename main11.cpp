#include<iostream>
#include<signal.h>
#include<unistd.h>
#include<cassert>
#include<type_traits>
#include<vector>
#include<algorithm>
#include<utility>
#include<string>
#include<iomanip>

using namespace std;

// Dynamic memory

void dynamic_memory(){

    auto n = new int[10]; // allocate an array
    auto m = new int[3]{1,2,3}; // allocate and initialize an array

    assert(m[2]==3);
    delete[] n; // deallocate array
    delete[] m;
    cout<<"Dynamic Memory ... Passed"<<endl;
}

void type_traits_check(){
    int i=10;
    decltype(i) j = i*10;
    assert((is_same<decltype(i), decltype(j)>::value));

    auto f = [] (int a, int b) -> int
    {
        return a+b;
    };
    decltype(f) g =f;

    i=f(2,2);
    j=g(3,3);
    assert((is_same<decltype(f), decltype(g)>::value));
    cout<<i<<j<<endl;

    struct  A
    {
        double x;
    };
    const A* m;
    decltype(m->x) p = 10; // type of p is double (declared type)
    assert((is_same<decltype(m->x), decltype(p)>::value));
    decltype((m->x)) z = p; // type of z is const double& (lvalue expression)
    // The following gives error
    // assert((is_same<decltype(z), decltype(p)>::value)); 
    cout<<z<<endl;
    cout<<"Type checking ... Passed"<<endl;
}

void move_operation(){
    vector<string> v;
    string str="Mazder";
    cout<<str<<endl;
    v.push_back(move(str));
    
    cout<<quoted("The value of str")<<str<<endl;

    cout<<"Move checking ... Passed"<<endl;
}

void unique_pointer(){
    
    
    int* p = new int();
    *p=20;
    unique_ptr <int> u1;
    assert(p);
    assert(u1 == nullptr);
    assert(!u1);
    u1.reset(new int(10));
    assert(u1);
    assert(*u1 == 10);
    u1.reset(p);
    *u1 = 30;
    assert(*p==30);
    //u1.reset();
    //assert(u1==nullptr);
    assert(p!=nullptr);


    int *q = u1.get();
    unique_ptr<int> u2;
    // u2 = u1 ; // not allowed
    assert(u1!=nullptr);
    u2 = move(u1);
    assert(u1==nullptr);
    assert (u2.get() == q);


    cout<<"Unique pointer checking ... Passed"<<endl;
}







int main(int argc, char *agrv[]){

    cout<<"This program shows minimal new features of c++ 11."<<endl;
    dynamic_memory();
    type_traits_check();
    move_operation();
    unique_pointer();
    return 0;
}


