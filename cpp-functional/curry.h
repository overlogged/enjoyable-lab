#ifndef _CURRY_H_
#define _CURRY_H_

#include <functional>
#include <type_traits>

template <typename R> class curryfun;

template<typename R,typename...Arg>
auto trans_funtype(std::function<R(Arg...)> f){
    return curryfun<R(Arg...)>{f};
}

template<typename T>
auto make_curry(T& f){
    auto g = std::function(f);
    return trans_funtype(g);
}

template <typename R, typename...Args>
class curryfun<R(Args...)>{

public:
    std::function<R(Args...)> func;

private:
    template<typename...RestTs>
    constexpr static auto bind_rec(curryfun<R(RestTs...)> f) {
        return f;
    }    

    template<typename BindT,typename RestT,typename...BindTs,typename...RestTs>
    constexpr static auto bind_rec(curryfun<R(RestT,RestTs...)> f, BindT&& arg, BindTs&&...args) {
        auto step = curryfun<R(RestTs...)>(std::function<R(RestTs...)>([copyf=f,&arg](RestTs...rest_args) {
            return copyf.func(std::forward<BindT>(arg),rest_args...);
        }));
        if constexpr (sizeof...(BindTs) == 0) {
            return step;
        } else {
            return bind_rec(step,std::forward<BindTs>(args)...);
        }
    }

public:
    curryfun() = default;

    // template <typename F>
    // curryfun(const F& f) {
    //     func = f;
    // }

    curryfun(std::function<R(Args...)> f) {
        func = f;
    }

    template<typename...Ts>
    auto operator () (Ts&&...args) {
        auto bind_f = bind_rec(curryfun<R(Args...)>(func),std::forward<Ts>(args)...);
        if constexpr (sizeof...(Ts)==sizeof...(Args)) {
            return bind_f.func();
        } else {
            return bind_f;
        }
    }
};

#endif // CURRY_H_INCLUDED