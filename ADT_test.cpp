#include <iostream>
#include "ADT.hpp"

using namespace std;

/*
 * The defination of the type 'List'
 * usage:Data(typename)
 */
Data(List)
	Enum(Nil)										/* 'Enum' for constructors without any data */
	Mul(Cons,GeneralCon<int>,RecursiveCon<List>)	/* 'Mul' for multiplication types,
													'GeneralCon' for general constructors,
													'RecursiveCon' for recursive constructors */
EndData(List,Nil,Cons)
/*
 * usage:EndData(typename,Constructor1,...)
 */

void Show(List l)
{
	int x;
	List xs;
	/* pattern match with List l */
	With(l)
		Case(List,Cons,x,xs)				/* usage:Case(typename,constructor name,variables...) */
			cout<<x<<" ";
			Show(xs);
		Default()
			cout<<"end of the list.\n";
	EndWith()
}

int Length(List l)
{
	With(l)
		Case(List,Nil)
			return 0;
		Case(List,Cons,_,l)					/* '_' for placeholder */
			return Length(l)+1;
	EndWith()
}

int main()
{ 
	List l=ADT_List::Nil();						/* constructors are in the namespace ADT_typname */
	for(int i=0;i<3;i++) l=ADT_List::Cons(i,l);
	Show(l);
	cout<<"Length:"<<Length(l)<<endl;
	return 0;
}
