#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <tuple>
#include <ostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <list>
#include "curry.h"

#define purefun(expr) ([=](auto var){return (expr);})
#define dirtyfun(expr) ([&](auto var){return (expr);})

template<class... TR,template <class...> class C,class... U>
decltype(auto) change_value_type(C<U...>)
{
    return C<TR...>{};
}

template<typename Q>
struct container:public Q
{
    using _Container = Q;
    using T=typename Q::value_type;

    container(){}

    container(const std::initializer_list<T>& lst)
    {
        for(auto& x:lst) this->insert(this->end(),x);
    }

    template<typename TR>
    using change_value_type_t = container<decltype(change_value_type<TR>(static_cast<Q>(0)))>;

    template<typename TR>
    decltype(auto) map(curryfun<TR(T)> curryfun)
    {
        change_value_type_t<TR> ret;
        for(auto& x:*this)
        {
            ret.insert(ret.end(),curryfun(x));
        }
        return ret;
    }

    template<typename TR>
    container<Q>& self_map(curryfun<TR(T)> curryfun)
    {
        for(auto& x:*this) x=curryfun(x);
        return *this;
    }

    container<Q> filter(curryfun<bool(T)> curryfun)
    {
        container<Q> ret;
        for(auto& x:*this)
        {
            if(curryfun(x)) ret.insert(ret.end(),x);
        }
        return ret;
    }

    decltype(auto) sort()
    {
        container<std::vector<T>> ret;
        ret.insert(ret.end(),this->begin(),this->end());
        std::sort(ret.begin(),ret.end());
        return ret;
    }

    container<Q>& self_sort()
    {
        std::sort(this->begin(),this->end());
        return *this;
    }

    decltype(auto) sort_by(curryfun<bool(const T&,const T&)> cmp)
    {
        container<std::vector<T>> ret;
        ret.insert(ret.end(),this->begin(),this->end());
        std::sort(ret.begin(),ret.end(),cmp);
        return ret;
    }    

    container<Q>& self_sort_by(curryfun<bool(const T&,const T&)> cmp)
    {
        std::sort(this->begin(),this->end(),cmp);
        return *this;
    }

    template<typename TR>
    TR foldl(curryfun<TR(TR,T)> curryfun,TR init)
    {
        for(auto& x:*this)
        {
            init = curryfun(init,x);
        }
        return init;
    }

    template<typename TR>
    TR foldl_with_index(curryfun<TR(TR,int,T)>,TR init)
    {
        int i=0;
        for(auto& x:*this)
        {
            init = curryfun(init,i++,x);
        }
        return init;
    }

    T sum()
    {
        T s;
        for(auto& x:*this) s+=x;
        return s;
    }

    T maximum()
    {
        T r;
        if(Q::empty()) return r;
        r=*Q::begin();
        for(auto& x:*this) r=x>r?x:r;
        return r;
    }

    T minimum()
    {
        T r;
        if(Q::empty()) return r;
        r=*Q::begin();
        for(auto& x:*this) r=x<r?x:r;
        return r;
    }


    std::pair<int,T> max_with_index()
    {
        T r;
        int i=0;
        int ret_i=-1;
        if(Q::empty()) return std::pair<int,T>(-1,r);
        r=*Q::begin();
        for(auto& x:*this)
        {
            if(x>r)
            {
                r=x;
                ret_i=i;
            }
            i++;
        }
        return std::pair<int,T>(ret_i,r);
    }

    std::pair<int,T> min_with_index()
    {
        T r;
        int i=0;
        int ret_i=-1;
        if(Q::empty()) return std::pair<int,T>(-1,r);
        r=*Q::begin();
        for(auto& x:*this)
        {
            if(x<r)
            {
                r=x;
                ret_i=i;
            }
            i++;
        }
        return std::pair<int,T>(ret_i,r);
    }
};

/*
template<typename A,typename B>
std::ostream& operator << (std::ostream& out,const std::pair<A,B>& p)
{
    return (out<<"("<<p.first<<","<<p.second<<")");
}
*/

template<typename A>
std::ostream& operator << (std::ostream& out,const container<A>& c)
{
    out<<"[";
    bool first=true;
    for(auto& x:c)
    {
        if(first) first=false;
        else out<<",";
        out<<x;
    }
    out<<"]";
    return out;
}

template<class C1,class C2>
decltype(auto) operator * (const container<C1>& a,const container<C2>& b)
{
    using pair_t=std::pair<typename C1::value_type,typename C2::value_type>;
    container<decltype(change_value_type<pair_t>(static_cast<C1>(0)))> ret;
    for(auto x:a) for(auto y:b)
    {
        pair_t c(x,y);
        ret.insert(ret.end(),c);
    }
    return ret;
}

template<class C1,class C2>
decltype(auto) zip (const container<C1>& a,const container<C2>& b)
{
    using pair_t=std::pair<typename C1::value_type,typename C2::value_type>;
    container<decltype(change_value_type<pair_t>(static_cast<C1>(0)))> ret;
    auto it_a=a.begin();
    auto it_b=b.begin();
    while(it_a!=a.end() && it_b != b.end())
    {
        pair_t c(*it_a++,*it_b++);
        ret.insert(ret.end(),c);
    }
    return ret;
}

template<class C>
decltype(auto) concat(const container<C>& a,const container<C>& b)
{
    container<C> c;
    c.insert(c.end(),a.begin(),a.end());
    c.insert(c.end(),b.begin(),b.end());
    return c;
}

template<typename T>
decltype(auto) range(const T& start,const T& end,const T& step=1)
{
    container<std::list<T>> ret;
    T s=start;
    while(s<end)
    {
        ret.insert(ret.end(),s+=step);
    }
    return ret;
}


template<typename A>
A read(std::string s)
{
    A ret;
    std::stringstream h(s);
    h>>ret;
    return ret;
}

#endif