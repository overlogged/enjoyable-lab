#include <iostream>
#include "ADT.hpp"

using namespace std;

Data(List)
	Enum(Nil)
	Mul(Cons,GeneralCon<int>,RecursiveCon<List>)
EndData(List,Nil,Cons)

void Show(List l)
{
	int x;
	List xs;
	With(l)
		Case(List,Nil)
			cout<<"end of the list.\n";
		Case(List,Cons,x,xs)
			cout<<x<<" ";
			Show(xs);
	EndWith()
}

int Length(List l)
{
	With(l)
		Case(List,Nil)
			return 0;
		Case(List,Cons,_,l)
			return Length(l)+1;
	EndWith()
}

int main()
{ 
	List l=ADT_List::Nil();
	for(int i=0;i<3;i++) l=ADT_List::Cons(i,l);
	Show(l);
	cout<<"Length:"<<Length(l)<<endl;
	return 0;
}
