#include <iostream>
#include "var_match.hpp"

using namespace std;

int main()
{
    // match with rvalue
    // false
    if(var_match(2,1)) cout<<"2==1\n";
    else cout<<"2!=1\n";

    // true
    if(var_match(2,2)) cout<<"2==2\n";
    else cout<<"2!=2\n";

    // match with lvalue
    // always true
    int x=3;
    if(var_match(2,x)) cout<<"x="<<x<<endl;
    else cout<<"failed\n";

    // match with rvalue(made by move() function)
    // false
    x=2;
    if(var_match(4,move(x))) cout<<"4==2\n";
    else cout<<"4!=2\n";

    return 0;
}