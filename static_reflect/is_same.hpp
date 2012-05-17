#ifndef IS_SAME_H
#define IS_SAME_H
template<typename From, typename To>
class IsSame
{
public:
    enum {Result = false};
};

template<typename T>
class IsSame<T, T>
{
public:
    enum {Result = true};
};
#endif
