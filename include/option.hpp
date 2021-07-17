#include <variant>
#include <optional>
#include <iostream>

template <typename T>
class Option {
    private:
    std::optional<T> m_opt;
    public:

    Option(T&& t) : m_opt(std::move(t)) { }
    Option(std::optional<T>&& t) : m_opt(std::move(t)) { }
    
    template <typename Fn>
    constexpr auto map(Fn&& f) {
        if(m_opt.has_value()) {
            return Option<decltype(f(m_opt.value()))>{std::move(f(m_opt.value()))};
        } else {
            return Option<decltype(f(m_opt.value()))>{std::nullopt};
        }
    }

    // todo(feature): implement and_then, which measured in TMP is *light years more cumbersome* to implement due to the
    // incredibly bad TMP features that exist in C++. I mean C++ still can't deduce the most simplistic return types of lambdas for instance, without having to clutter up
    // everything with long <type, type, type, type> stuff everywhere. Boo, c++. Boo. Rust is gaining on you.

    constexpr auto value() {
        return m_opt.value();
    }

    constexpr auto value_or(T&& t) {
        return m_opt.value_or(std::move(t));
    }
};

namespace optutil {

    /// Takes ownership of a std::optional and moves from and returns an Option<T> of same type T
    template <typename T>
    static constexpr auto take_option(std::optional<T>&& opt) {
        return Option<T>{std::move(opt)};
    }

    /// Creates a Option from a T, first passing T to the std::optional constructor
    template <typename T>
    static constexpr auto make_option(T&& opt) {
        return Option<T>{opt};
    }
}