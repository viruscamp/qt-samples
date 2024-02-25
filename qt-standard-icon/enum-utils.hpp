/// [C++ 中如何优雅进行 enum 到 string 的转换 ？](https://zhuanlan.zhihu.com/p/680412313)

template<auto value>
constexpr auto enum_name()
{
    std::string_view name;
#if __GNUC__ || __clang__
    name = __PRETTY_FUNCTION__;
    std::size_t start = name.find('=') + 2;
    std::size_t end = name.size() - 1;
    name = std::string_view{ name.data() + start, end - start };
    start = name.rfind("::");
#elif _MSC_VER
    name = __FUNCSIG__;
    std::size_t start = name.find('<') + 1;
    std::size_t end = name.rfind(">(");
    name = std::string_view{ name.data() + start, end - start };
    start = name.rfind("::");
#endif
    return start == std::string_view::npos ? name : std::string_view{
            name.data() + start + 2, name.size() - start - 2
    };
}

template<typename T, std::size_t N = 0> 
constexpr auto enum_max()
{
    constexpr auto value = static_cast<T>(N);
    if constexpr (enum_name<value>().find(")") == std::string_view::npos)
        return enum_max<T, N + 1>();
    else
        return N;
}

template<typename T> requires std::is_enum_v<T>
constexpr auto enum_name(T value)
{
    constexpr auto num = enum_max<T>();
    constexpr auto names = []<std::size_t... Is>(std::index_sequence<Is...>)
    {
        return std::array<std::string_view, num>
        { 
            enum_name<static_cast<T>(Is)>()... 
        };
    }(std::make_index_sequence<num>{});
    return names[static_cast<std::size_t>(value)];
}
