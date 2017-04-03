#ifndef _ADT_H_
#define _ADT_H_
#include <iostream>
#include <tuple>
#include <type_traits>
#include <boost/variant.hpp>

/* IsRecursive */
char IsRecursiveFun(...);
template<class T>int IsRecursiveFun(T a,decltype(&(T::Value)) p=0);
template<class T>struct IsRecursive{static const bool value=sizeof(IsRecursiveFun())==4;};

/* VarMatch */
typedef struct place_holder{char x;} place_holder;
place_holder _;
#define TYPECHECK(a,b) (std::is_same<typename std::decay<a>::type,typename std::decay<b>::type>::value)

/* Recursive Constructor */
class RecursiveIndicator{};
template<typename T>
class RecursiveCon
{
private:
	std::shared_ptr<T> data=0;
public:
	typedef T type;
	RecursiveCon(){}
	RecursiveCon(T* p):data(p){}
	RecursiveCon(const T& v)
	{
		data = std::shared_ptr<T>(new T);
		*data=v;
	}
	RecursiveCon(const RecursiveCon<T>& a):data(a.data){}

	T Value(){return *data;}
};

/* General Constructor */
template<typename T>
class GeneralCon
{
	T data;
public:
	GeneralCon(){}
	GeneralCon(T v):data(v){}
	T Value(){return data;}
};

/* TypeMul */
template<typename T1,typename...T>
class TypeMul:std::tuple<T1,T...>
{
private:
	typedef typename std::tuple<T1,T...> BaseType;
	const static int count=sizeof...(T)+1;
public:
	TypeMul(BaseType v):BaseType(v){}
	TypeMul(T1 v,T...args):std::tuple<T1,T...>(v,args...){}

	template<int x>
	auto Get()
	{
		return std::get<x>(*(BaseType*)(this));
	}

	template<typename MT1,typename MT2,typename...MT>
	bool Match(MT1&& v,MT2 && t,MT... args)
	{
		if(Match<MT2,MT...>(std::forward<MT2>(t),args...)==false) return false;
		return Get<count-sizeof...(args)-2>().Value()==v;
	}

	template<typename MT1,typename MT2,typename...MT>
	bool Match(MT1& v,MT2 && t,MT... args)
	{
		if(Match<MT2,MT...>(std::forward<MT2>(t),args...)==false) return false;
		return v=Get<count-sizeof...(args)-2>().Value(),true;
	}

	template<typename MT2,typename...MT>
	bool Match(place_holder& v,MT2 && t,MT... args)
	{
		if(Match<MT2,MT...>(std::forward<MT2>(t),args...)==false) return false;
		return true;
	}

	template<typename MT1>
	bool Match(MT1 && v)
	{
		return Get<count-1>().Value()==v;
	}

	template<typename MT1>
	bool Match(MT1 & v)
	{
		return v=Get<count-1>().Value(),true;
	}

	bool Match(place_holder & v)
	{
		return true;
	}

	bool Match()
	{
		return true;
	}
};
template<const char*(*f)()>
struct Arg
{
	Arg(){};

	bool Match(){return true;}
};

/* TypeAdd */
template<typename T1,typename...T>
class TypeAdd:public boost::variant<T1,T...>
{
private:
	typedef boost::variant<T1,T...> BaseClass;
public:
	template<typename MT>
	TypeAdd& operator = (const MT&v)
	{
		*(BaseClass*)(this)=v;
		return *this;
	}
	template<typename MT>
	TypeAdd(const MT&v):BaseClass(v){}
	TypeAdd(){}
};

#define Data(Name) namespace ADT_##Name{class Name;
#define Enum(Name) 														\
	const char* F##Name(){return #Name;}    							\
	typedef Arg<F##Name> Name;
#define Mul(Name,arg...) typedef TypeMul<arg> Name;
#define EndData(Name,arg...)               								\
	class Name:public TypeAdd<arg>										\
	{																	\
	public:																\
		Name(){}														\
		Name(auto v):TypeAdd<arg>(v){}									\
	};																	\
}																		\
typedef ADT_##Name::Name Name;

#define With(x) {auto& match_var=x;if(0){if(0){;
#define Case(Name,Type,arg...) }}else if(match_var.type()==typeid(ADT_##Name::Type)){	\
		auto data##Type=boost::get<ADT_List::Type>(match_var);							\
		if(data##Type.Match(arg)){;

#define Default() }}else{if(1){;
#define EndWith() }}}

#endif