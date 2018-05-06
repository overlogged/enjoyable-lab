#ifndef VAR_MATCH_H
#define VAR_MATCH_H

#include <type_traits>

#define TYPECHECK(a,b) (std::is_same<typename std::decay<a>::type,typename std::decay<b>::type>::value)
template<typename T1,typename T2,typename std::enable_if<TYPECHECK(T1,T2),int>::type=0>
bool var_match(T1 v1,T2&& v2)
{
	return v1==v2;
}
template<typename T1,typename T2,typename std::enable_if<TYPECHECK(T1,T2),int>::type=0>
bool var_match(T1 v1,T2& v2)
{
	return v2=v1,true;
}
template<typename T1,typename T2,typename std::enable_if<TYPECHECK(T1,T2)==false,int>::type=0>
bool var_match(T1 v1,T2 v2)
{
	return false;
}

#endif