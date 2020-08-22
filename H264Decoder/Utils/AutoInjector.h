#pragma once

namespace AutoInjector
{
    template<typename ...T>
    struct TypePack
    {
    private:

        template<typename Map, typename CurT, typename ...TCreator>
        static inline void RegisterTypesImpl(Map&& map)
        {
            map[CurT::eType] = CurT{};
            if constexpr (sizeof...(TCreator) != 0)
            {
                RegisterTypesImpl<Map, TCreator...>(std::forward<Map>(map));
            }

        }
    public:
        template<typename Map>
        static inline void RegisterTypes(Map&& map)
        {
            RegisterTypesImpl<Map, T...>(std::forward<Map>(map));
        }

    };

    template<typename SrcType, typename ...T>
    struct Injector
    {
    private:
        std::tuple<T...> tup;
    public:
        Injector() = delete;

        template<typename ...Args>
        explicit Injector(Args&&... args) : tup(args...)
        {

        }

        template<typename InjectTo, typename = std::enable_if_t<!std::is_convertible_v<SrcType, InjectTo>>>
        operator InjectTo() const
        {
            return std::get<InjectTo>(tup);
        }

        template<typename InjectTo, typename = std::enable_if_t<!std::is_convertible_v<SrcType, InjectTo>>>
        constexpr operator InjectTo& ()&
        {
            return std::get<InjectTo&>(tup);
        }

    };

    template<typename SrcType, typename ...T>
    constexpr auto makeInjector(T&&... args)
    {
        return Injector<SrcType, T...>(args...);
    }


    template<size_t N, typename TSrc>
    struct PlaceHolder
    {
        template<typename T, typename = std::enable_if_t<!std::is_convertible_v<TSrc, T>>>
        constexpr operator T() const
        {
            return std::declval<T>();
        }

        template<typename T, typename = std::enable_if_t<!std::is_convertible_v<TSrc, T>>>
        constexpr operator T& ()&
        {
            return std::declval<T&>();
        }
    };

    template<typename T, typename BoolType, size_t Num, size_t I, size_t ...N>
    struct NumberParamsToConstructImpl
    {
        static constexpr size_t Val = NumberParamsToConstructImpl<T, typename std::is_constructible<T, PlaceHolder<N, T>&...>::type, Num - 1, N...>::Val;
    };

    template<typename T, typename BoolType>
    struct DefaultConstructibleChecker
    {
        static constexpr size_t Val = 0;
    };

    template<typename T>
    struct DefaultConstructibleChecker<T, std::true_type>
    {
        static constexpr size_t Val = 0;
    };

    template<typename T>
    struct DefaultConstructibleChecker<T, std::false_type>
    {
        static constexpr size_t Val = 999;
    };

    template<typename T, size_t Num, size_t I>
    struct NumberParamsToConstructImpl<T, std::false_type, Num, I>
    {
        static constexpr size_t Val = DefaultConstructibleChecker<T, typename std::is_default_constructible<T>::type>::Val;
    };

    template<typename T, size_t Num, size_t I>
    struct NumberParamsToConstructImpl<T, std::true_type, Num, I>
    {
        static constexpr size_t Val = Num;
    };

    template<typename T, size_t Num, size_t I, size_t ...N>
    struct NumberParamsToConstructImpl<T, std::true_type, Num, I, N...>
    {
        static constexpr size_t Val = Num;
    };

    template<typename T, size_t Cur, size_t I, size_t ...N>
    constexpr auto numberParamsToConstructImpl(std::index_sequence<I, N...>)
    {
        return NumberParamsToConstructImpl<T, typename std::is_constructible<T, PlaceHolder<N, T>&...>::type, Cur, I, N...>::Val;
    };

    template<typename T, size_t Cur>
    constexpr auto numberParamsToConstruct()
    {
        return numberParamsToConstructImpl<T, Cur>(std::make_index_sequence<Cur>{});
    };

    template<typename T, typename TInjector, size_t ...N>
    T* createObjectPtr(TInjector&& injector, std::index_sequence<N...>)
    {
        return new T((N, injector)...);
    }

    template<size_t Probe, typename EnumType, EnumType type, typename T, typename ...TServices>
    struct ObjectCreator
    {
        static constexpr EnumType eType = type;

        std::shared_ptr<std::uint8_t> operator()(TServices&&... args)
        {
            constexpr auto nParams = numberParamsToConstruct<T, Probe>();
            static_assert(nParams <= Probe, "not constructible");
            std::make_index_sequence<nParams> indeies;
            auto injector = makeInjector<T>(args...);
            return std::shared_ptr<std::uint8_t>(reinterpret_cast<std::uint8_t*>(createObjectPtr<T>(injector, indeies)), [](std::uint8_t* ptr)
                {
                    auto obj = reinterpret_cast<T*>(ptr);
                    delete obj;
                });
        }
    };

}

