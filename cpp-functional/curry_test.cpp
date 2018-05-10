#include "curry.h"
#include "old_curry.h"
#include <iostream>

using namespace std;

int fun(int x1,double x2,const char* x3) {
    cout<<x1<<" "<<x2<<" "<<x3<<endl;
    return 0;
}
    
int main() {
    auto f = make_curry(fun);
    auto f1 = f(42);
    f1(666,"hello world");
    auto f2 = f1(233);
    f1(233)("curry function");
    f2("hi");
    return 0;
}