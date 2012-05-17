#ifndef IF_THEN_ELSE_H
#define IF_THEN_ELSE_H

//main template
template <bool condition, class Then, class Else>
struct IfThenElse
{
    typedef Then Result;
};
//false specialization
template <class Then, class Else>
struct IfThenElse<false, Then, Else>
{
    typedef Else Result;
};

#endif
