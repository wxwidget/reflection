#ifndef ALICE_REFLECTION_HPP
#define ALICE_REFLECTION_HPP


#pragma warning (disable: 4786)
#pragma warning (disable: 4003)


#include <map>
#include <list>
#include <string>
#include <typeinfo>
#include <iostream>
#include <stdexcept>


//repeaters
#define REPEAT0(M, C, S)
#define REPEAT1(M, C, S)         S(1) M(1)
#define REPEAT2(M, C, S)         REPEAT1(M, C, S)  C(2) M(2)
#define REPEAT3(M, C, S)         REPEAT2(M, C, S)  C(3) M(3)
#define REPEAT4(M, C, S)         REPEAT3(M, C, S)  C(4) M(4)
#define REPEAT5(M, C, S)         REPEAT4(M, C, S)  C(5) M(5)
#define REPEAT6(M, C, S)         REPEAT5(M, C, S)  C(6) M(6)
#define REPEAT7(M, C, S)         REPEAT6(M, C, S)  C(7) M(7)
#define REPEAT8(M, C, S)         REPEAT7(M, C, S)  C(8) M(8)
#define REPEAT9(M, C, S)         REPEAT8(M, C, S)  C(9) M(9)
#define REPEAT10(M, C, S)        REPEAT9(M, C, S)  C(10) M(10)
#define REPEAT11(M, C, S)        REPEAT10(M, C, S) C(11) M(11)
#define REPEAT12(M, C, S)        REPEAT11(M, C, S) C(12) M(12)
#define REPEAT13(M, C, S)        REPEAT12(M, C, S) C(13) M(13)
#define REPEAT14(M, C, S)        REPEAT13(M, C, S) C(14) M(14)
#define REPEAT15(M, C, S)        REPEAT14(M, C, S) C(15) M(15)
#define REPEAT16(M, C, S)        REPEAT15(M, C, S) C(16) M(16)
#define REPEAT17(M, C, S)        REPEAT16(M, C, S) C(17) M(17)
#define REPEAT18(M, C, S)        REPEAT17(M, C, S) C(18) M(18)
#define REPEAT19(M, C, S)        REPEAT18(M, C, S) C(19) M(19)
#define REPEAT20(M, C, S)        REPEAT19(M, C, S) C(20) M(20)
#define REPEAT(N, M, C, S)       REPEAT##N(M, C, S)


//various defs needed for parameters
#define MAX_PARAMS       20
#define NOTHING(N)
#define COMMA(N)     ,
#define TEMPLATE_ARG(N)  class T##N
#define TYPE_ARG(N)      T##N
#define ARG(N)           T##N t##N
#define PARAM(N)         t##N
#define NOT_VIRTUAL


//calculates the offSet of a field
#define OFFSET(Class, Method)\
    ((unsigned long)(&((const Class *)0)->Method))


namespace alice
{
namespace reflection
{


//root of all Callables
struct Callable
{
    virtual ~Callable()
    {
    }
};


//Callable class macro with return type
#define CALLABLE(N)\
template <class R, class C REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)> \
struct Callable##N : public Callable {\
    typedef R (C::*MethodType)(REPEAT(N, TYPE_ARG, COMMA, NOTHING));\
    MethodType method;\
    Callable##N (MethodType m) : method(m) \
    {                                                       \
    }                                                       \
    R Invoke(C *object REPEAT(N, ARG, COMMA, COMMA)) const  \
    {\
        return (object->*method)(REPEAT(N, PARAM, COMMA, NOTHING));\
    }\
};


//Callable class macro with return type and const type
#define CALLABLE_CONST(N)\
template <class R, class C REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)> \
struct CallableConst##N : public Callable {\
    typedef R (C::*MethodType)(REPEAT(N, TYPE_ARG, COMMA, NOTHING)) const;\
    MethodType method;\
    CallableConst##N (MethodType m) : method(m) \
    {\
    }\
    R Invoke(C *object REPEAT(N, ARG, COMMA, COMMA)) const \
    {\
        return (object->*method)(REPEAT(N, PARAM, COMMA, NOTHING));\
    }\
};


//Callable class macro with void return type
#define CALLABLE_VOID(N)\
template <class C REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)> struct CallableVoid##N : public Callable {\
    typedef void (C::*MethodType)(REPEAT(N, TYPE_ARG, COMMA, NOTHING));\
    MethodType method;\
    CallableVoid##N (MethodType m) : method(m) \
    {\
    }\
    void Invoke(C *object REPEAT(N, ARG, COMMA, COMMA)) const \
    {\
        (object->*method)(REPEAT(N, PARAM, COMMA, NOTHING));\
    }\
};


//Callable class macro with void return type and const type
#define CALLABLE_CONST_VOID(N)\
template <class C REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)> struct CallableConstVoid##N  : public Callable {\
    typedef void (C::*MethodType)(REPEAT(N, TYPE_ARG, COMMA, NOTHING)) const;\
    MethodType method;\
    CallableConstVoid##N (MethodType m) : method(m) {\
    }\
    void Invoke(C *object REPEAT(N, ARG, COMMA, COMMA)) const {\
        (object->*method)(REPEAT(N, PARAM, COMMA, NOTHING));\
    }\
};


//static Callable class macro with return type
#define STATIC_CALLABLE(N)\
template <class R REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)> struct StaticCallable##N  : public Callable {\
    typedef R (*MethodType)(REPEAT(N, TYPE_ARG, COMMA, NOTHING));\
    MethodType method;\
    StaticCallable##N (MethodType m) : method(m) {\
    }\
    R Invoke(REPEAT(N, ARG, COMMA, NOTHING)) const {\
        return (*method)(REPEAT(N, PARAM, COMMA, NOTHING));\
    }\
};


//void version for 0 params
struct StaticCallableVoid0 : public Callable
{
    typedef void (*MethodType)();
    MethodType method;
    StaticCallableVoid0(MethodType m) : method(m)
    {
    }
    void Invoke() const
    {
        (*method)();
    }
};


//void version
#define STATIC_CALLABLE_VOID(N)\
template <REPEAT(N, TEMPLATE_ARG, COMMA, NOTHING)> struct StaticCallableVoid##N  : public Callable {\
    typedef void (*MethodType)(REPEAT(N, TYPE_ARG, COMMA, NOTHING));\
    MethodType method;\
    StaticCallableVoid##N (MethodType m) : method(m) {\
    }\
    void Invoke(REPEAT(N, ARG, COMMA, NOTHING)) const {\
        (*method)(REPEAT(N, PARAM, COMMA, NOTHING));\
    }\
};


//define Callables
CALLABLE(0);
CALLABLE(1);
CALLABLE(2);
CALLABLE(3);
CALLABLE(4);
CALLABLE(5);
CALLABLE(6);
CALLABLE(7);
CALLABLE(8);
CALLABLE(9);
CALLABLE(10);
CALLABLE(11);
CALLABLE(12);
CALLABLE(13);
CALLABLE(14);
CALLABLE(15);
CALLABLE(16);
CALLABLE(17);
CALLABLE(18);
CALLABLE(19);
CALLABLE(20);


//define const Callables
CALLABLE_CONST(0);
CALLABLE_CONST(1);
CALLABLE_CONST(2);
CALLABLE_CONST(3);
CALLABLE_CONST(4);
CALLABLE_CONST(5);
CALLABLE_CONST(6);
CALLABLE_CONST(7);
CALLABLE_CONST(8);
CALLABLE_CONST(9);
CALLABLE_CONST(10);
CALLABLE_CONST(11);
CALLABLE_CONST(12);
CALLABLE_CONST(13);
CALLABLE_CONST(14);
CALLABLE_CONST(15);
CALLABLE_CONST(16);
CALLABLE_CONST(17);
CALLABLE_CONST(18);
CALLABLE_CONST(19);
CALLABLE_CONST(20);


//define void Callables
CALLABLE_VOID(0);
CALLABLE_VOID(1);
CALLABLE_VOID(2);
CALLABLE_VOID(3);
CALLABLE_VOID(4);
CALLABLE_VOID(5);
CALLABLE_VOID(6);
CALLABLE_VOID(7);
CALLABLE_VOID(8);
CALLABLE_VOID(9);
CALLABLE_VOID(10);
CALLABLE_VOID(11);
CALLABLE_VOID(12);
CALLABLE_VOID(13);
CALLABLE_VOID(14);
CALLABLE_VOID(15);
CALLABLE_VOID(16);
CALLABLE_VOID(17);
CALLABLE_VOID(18);
CALLABLE_VOID(19);
CALLABLE_VOID(20);


//define const void Callables
CALLABLE_CONST_VOID(0);
CALLABLE_CONST_VOID(1);
CALLABLE_CONST_VOID(2);
CALLABLE_CONST_VOID(3);
CALLABLE_CONST_VOID(4);
CALLABLE_CONST_VOID(5);
CALLABLE_CONST_VOID(6);
CALLABLE_CONST_VOID(7);
CALLABLE_CONST_VOID(8);
CALLABLE_CONST_VOID(9);
CALLABLE_CONST_VOID(10);
CALLABLE_CONST_VOID(11);
CALLABLE_CONST_VOID(12);
CALLABLE_CONST_VOID(13);
CALLABLE_CONST_VOID(14);
CALLABLE_CONST_VOID(15);
CALLABLE_CONST_VOID(16);
CALLABLE_CONST_VOID(17);
CALLABLE_CONST_VOID(18);
CALLABLE_CONST_VOID(19);
CALLABLE_CONST_VOID(20);


//static Callable classes
STATIC_CALLABLE(0)
STATIC_CALLABLE(1)
STATIC_CALLABLE(2)
STATIC_CALLABLE(3)
STATIC_CALLABLE(4)
STATIC_CALLABLE(5)
STATIC_CALLABLE(6)
STATIC_CALLABLE(7)
STATIC_CALLABLE(8)
STATIC_CALLABLE(9)
STATIC_CALLABLE(10)
STATIC_CALLABLE(11)
STATIC_CALLABLE(12)
STATIC_CALLABLE(13)
STATIC_CALLABLE(14)
STATIC_CALLABLE(15)
STATIC_CALLABLE(16)
STATIC_CALLABLE(17)
STATIC_CALLABLE(18)
STATIC_CALLABLE(19)
STATIC_CALLABLE(20)
STATIC_CALLABLE_VOID(1)
STATIC_CALLABLE_VOID(2)
STATIC_CALLABLE_VOID(3)
STATIC_CALLABLE_VOID(4)
STATIC_CALLABLE_VOID(5)
STATIC_CALLABLE_VOID(6)
STATIC_CALLABLE_VOID(7)
STATIC_CALLABLE_VOID(8)
STATIC_CALLABLE_VOID(9)
STATIC_CALLABLE_VOID(10)
STATIC_CALLABLE_VOID(11)
STATIC_CALLABLE_VOID(12)
STATIC_CALLABLE_VOID(13)
STATIC_CALLABLE_VOID(14)
STATIC_CALLABLE_VOID(15)
STATIC_CALLABLE_VOID(16)
STATIC_CALLABLE_VOID(17)
STATIC_CALLABLE_VOID(18)
STATIC_CALLABLE_VOID(19)
STATIC_CALLABLE_VOID(20)


//macro of a inline method that accepts a method pointer and creates a Callable for it
#define CREATE_CALLABLE(N)\
    template <class C REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)> \
    static inline Callable##N <R, C REPEAT(N, TYPE_ARG, COMMA, COMMA)> \
        *Create(R (C::*method)(REPEAT(N, TYPE_ARG, COMMA, NOTHING))) \
    {\
        return new Callable##N <R, C REPEAT(N, TYPE_ARG, COMMA, COMMA)>(method);\
    }


//macro of a inline method that accepts a method pointer and Creates a const Callable for it
#define CREATE_CALLABLE_CONST(N)\
    template <class C REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)> static inline CallableConst##N <R, C REPEAT(N, TYPE_ARG, COMMA, COMMA)> *Create(R (C::*method)(REPEAT(N, TYPE_ARG, COMMA, NOTHING)) const) {\
        return new CallableConst##N <R, C REPEAT(N, TYPE_ARG, COMMA, COMMA)>(method);\
    }


//void version
#define CREATE_CALLABLE_VOID(N)\
    template <class C REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)> static inline CallableVoid##N <C REPEAT(N, TYPE_ARG, COMMA, COMMA)> *Create(void (C::*method)(REPEAT(N, TYPE_ARG, COMMA, NOTHING))) {\
        return new CallableVoid##N <C REPEAT(N, TYPE_ARG, COMMA, COMMA)>(method);\
    }


//const void version
#define CREATE_CALLABLE_CONST_VOID(N)\
    template <class C REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)> static inline CallableConstVoid##N <C REPEAT(N, TYPE_ARG, COMMA, COMMA)> *Create(void (C::*method)(REPEAT(N, TYPE_ARG, COMMA, NOTHING)) const) {\
        return new CallableConstVoid##N <C REPEAT(N, TYPE_ARG, COMMA, COMMA)>(method);\
    }


//macro to Create a static Callable
#define CREATE_STATIC_CALLABLE(N)\
    template <class R REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)> \
    static inline StaticCallable##N <R REPEAT(N, TYPE_ARG, COMMA, COMMA)> \
    *Create(R (*method)(REPEAT(N, TYPE_ARG, COMMA, NOTHING))) \
    {\
        return new StaticCallable##N <R REPEAT(N, TYPE_ARG, COMMA, COMMA)>(method);\
    }


//void version for 0 params
#define CREATE_STATIC_CALLABLE_VOID0\
    static inline StaticCallableVoid0 *Create(void (*method)()) \
    {\
        return new StaticCallableVoid0(method);\
    }


//void version
#define CREATE_STATIC_CALLABLE_VOID(N)\
    template <REPEAT(N, TEMPLATE_ARG, COMMA, NOTHING)>  \
    static inline StaticCallableVoid##N <REPEAT(N, TYPE_ARG, COMMA, NOTHING)> \
    *Create(void (*method)(REPEAT(N, TYPE_ARG, COMMA, NOTHING))) \
    { \
        return new StaticCallableVoid##N <REPEAT(N, TYPE_ARG, COMMA, NOTHING)>(method);\
    }


//factory method for non-voids
template <class R> struct CallableFactory
{
    CREATE_CALLABLE(0)
    CREATE_CALLABLE(1)
    CREATE_CALLABLE(2)
    CREATE_CALLABLE(3)
    CREATE_CALLABLE(4)
    CREATE_CALLABLE(5)
    CREATE_CALLABLE(6)
    CREATE_CALLABLE(7)
    CREATE_CALLABLE(8)
    CREATE_CALLABLE(9)
    CREATE_CALLABLE(10)
    CREATE_CALLABLE(11)
    CREATE_CALLABLE(12)
    CREATE_CALLABLE(13)
    CREATE_CALLABLE(14)
    CREATE_CALLABLE(15)
    CREATE_CALLABLE(16)
    CREATE_CALLABLE(17)
    CREATE_CALLABLE(18)
    CREATE_CALLABLE(19)
    CREATE_CALLABLE(20)
    CREATE_CALLABLE_CONST(0)
    CREATE_CALLABLE_CONST(1)
    CREATE_CALLABLE_CONST(2)
    CREATE_CALLABLE_CONST(3)
    CREATE_CALLABLE_CONST(4)
    CREATE_CALLABLE_CONST(5)
    CREATE_CALLABLE_CONST(6)
    CREATE_CALLABLE_CONST(7)
    CREATE_CALLABLE_CONST(8)
    CREATE_CALLABLE_CONST(9)
    CREATE_CALLABLE_CONST(10)
    CREATE_CALLABLE_CONST(11)
    CREATE_CALLABLE_CONST(12)
    CREATE_CALLABLE_CONST(13)
    CREATE_CALLABLE_CONST(14)
    CREATE_CALLABLE_CONST(15)
    CREATE_CALLABLE_CONST(16)
    CREATE_CALLABLE_CONST(17)
    CREATE_CALLABLE_CONST(18)
    CREATE_CALLABLE_CONST(19)
    CREATE_CALLABLE_CONST(20)
};


//factory method for non-voids
template <> struct CallableFactory<void>
{
    CREATE_CALLABLE_VOID(0)
    CREATE_CALLABLE_VOID(1)
    CREATE_CALLABLE_VOID(2)
    CREATE_CALLABLE_VOID(3)
    CREATE_CALLABLE_VOID(4)
    CREATE_CALLABLE_VOID(5)
    CREATE_CALLABLE_VOID(6)
    CREATE_CALLABLE_VOID(7)
    CREATE_CALLABLE_VOID(8)
    CREATE_CALLABLE_VOID(9)
    CREATE_CALLABLE_VOID(10)
    CREATE_CALLABLE_VOID(11)
    CREATE_CALLABLE_VOID(12)
    CREATE_CALLABLE_VOID(13)
    CREATE_CALLABLE_VOID(14)
    CREATE_CALLABLE_VOID(15)
    CREATE_CALLABLE_VOID(16)
    CREATE_CALLABLE_VOID(17)
    CREATE_CALLABLE_VOID(18)
    CREATE_CALLABLE_VOID(19)
    CREATE_CALLABLE_VOID(20)
    CREATE_CALLABLE_CONST_VOID(0)
    CREATE_CALLABLE_CONST_VOID(1)
    CREATE_CALLABLE_CONST_VOID(2)
    CREATE_CALLABLE_CONST_VOID(3)
    CREATE_CALLABLE_CONST_VOID(4)
    CREATE_CALLABLE_CONST_VOID(5)
    CREATE_CALLABLE_CONST_VOID(6)
    CREATE_CALLABLE_CONST_VOID(7)
    CREATE_CALLABLE_CONST_VOID(8)
    CREATE_CALLABLE_CONST_VOID(9)
    CREATE_CALLABLE_CONST_VOID(10)
    CREATE_CALLABLE_CONST_VOID(11)
    CREATE_CALLABLE_CONST_VOID(12)
    CREATE_CALLABLE_CONST_VOID(13)
    CREATE_CALLABLE_CONST_VOID(14)
    CREATE_CALLABLE_CONST_VOID(15)
    CREATE_CALLABLE_CONST_VOID(16)
    CREATE_CALLABLE_CONST_VOID(17)
    CREATE_CALLABLE_CONST_VOID(18)
    CREATE_CALLABLE_CONST_VOID(19)
    CREATE_CALLABLE_CONST_VOID(20)
};


//factory method for static non-voids
template <class C> struct StaticCallableFactory
{
    CREATE_STATIC_CALLABLE(0)
    CREATE_STATIC_CALLABLE(1)
    CREATE_STATIC_CALLABLE(2)
    CREATE_STATIC_CALLABLE(3)
    CREATE_STATIC_CALLABLE(4)
    CREATE_STATIC_CALLABLE(5)
    CREATE_STATIC_CALLABLE(6)
    CREATE_STATIC_CALLABLE(7)
    CREATE_STATIC_CALLABLE(8)
    CREATE_STATIC_CALLABLE(9)
    CREATE_STATIC_CALLABLE(10)
    CREATE_STATIC_CALLABLE(11)
    CREATE_STATIC_CALLABLE(12)
    CREATE_STATIC_CALLABLE(13)
    CREATE_STATIC_CALLABLE(14)
    CREATE_STATIC_CALLABLE(15)
    CREATE_STATIC_CALLABLE(16)
    CREATE_STATIC_CALLABLE(17)
    CREATE_STATIC_CALLABLE(18)
    CREATE_STATIC_CALLABLE(19)
    CREATE_STATIC_CALLABLE(20)
};


//factory method for static voids
template <> struct StaticCallableFactory<void>
{
    CREATE_STATIC_CALLABLE_VOID0
    CREATE_STATIC_CALLABLE_VOID(1)
    CREATE_STATIC_CALLABLE_VOID(2)
    CREATE_STATIC_CALLABLE_VOID(3)
    CREATE_STATIC_CALLABLE_VOID(4)
    CREATE_STATIC_CALLABLE_VOID(5)
    CREATE_STATIC_CALLABLE_VOID(6)
    CREATE_STATIC_CALLABLE_VOID(7)
    CREATE_STATIC_CALLABLE_VOID(8)
    CREATE_STATIC_CALLABLE_VOID(9)
    CREATE_STATIC_CALLABLE_VOID(10)
    CREATE_STATIC_CALLABLE_VOID(11)
    CREATE_STATIC_CALLABLE_VOID(12)
    CREATE_STATIC_CALLABLE_VOID(13)
    CREATE_STATIC_CALLABLE_VOID(14)
    CREATE_STATIC_CALLABLE_VOID(15)
    CREATE_STATIC_CALLABLE_VOID(16)
    CREATE_STATIC_CALLABLE_VOID(17)
    CREATE_STATIC_CALLABLE_VOID(18)
    CREATE_STATIC_CALLABLE_VOID(19)
    CREATE_STATIC_CALLABLE_VOID(20)
};


//Callable generator
#define CALLABLE_GENERATOR(N)\
    template <class R, class C REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)> \
    inline Callable *CreateCallable(R (C::*method)(REPEAT(N, TYPE_ARG, COMMA, NOTHING))) \
    {\
        return CallableFactory<R>::Create(method);\
    }


//const Callable generator
#define CALLABLE_GENERATOR_CONST(N)\
    template <class R, class C REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)>   \
    inline Callable *CreateCallable(R (C::*method)(REPEAT(N, TYPE_ARG, COMMA, NOTHING)) const) \
    {                                                                   \
        return CallableFactory<R>::Create(method);                      \
    }


//static Callable generator
#define STATIC_CALLABLE_GENERATOR(N)\
    template <class R REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)>            \
    inline Callable *CreateStaticCallable(R (*method)(REPEAT(N, TYPE_ARG, COMMA, NOTHING))) \
    {                                                                   \
        return StaticCallableFactory<R>::Create(method);                \
    }


//generators
CALLABLE_GENERATOR(0)
CALLABLE_GENERATOR(1)
CALLABLE_GENERATOR(2)
CALLABLE_GENERATOR(3)
CALLABLE_GENERATOR(4)
CALLABLE_GENERATOR(5)
CALLABLE_GENERATOR(6)
CALLABLE_GENERATOR(7)
CALLABLE_GENERATOR(8)
CALLABLE_GENERATOR(9)
CALLABLE_GENERATOR(10)
CALLABLE_GENERATOR(11)
CALLABLE_GENERATOR(12)
CALLABLE_GENERATOR(13)
CALLABLE_GENERATOR(14)
CALLABLE_GENERATOR(15)
CALLABLE_GENERATOR(16)
CALLABLE_GENERATOR(17)
CALLABLE_GENERATOR(18)
CALLABLE_GENERATOR(19)
CALLABLE_GENERATOR(20)
CALLABLE_GENERATOR_CONST(0)
CALLABLE_GENERATOR_CONST(1)
CALLABLE_GENERATOR_CONST(2)
CALLABLE_GENERATOR_CONST(3)
CALLABLE_GENERATOR_CONST(4)
CALLABLE_GENERATOR_CONST(5)
CALLABLE_GENERATOR_CONST(6)
CALLABLE_GENERATOR_CONST(7)
CALLABLE_GENERATOR_CONST(8)
CALLABLE_GENERATOR_CONST(9)
CALLABLE_GENERATOR_CONST(10)
CALLABLE_GENERATOR_CONST(11)
CALLABLE_GENERATOR_CONST(12)
CALLABLE_GENERATOR_CONST(13)
CALLABLE_GENERATOR_CONST(14)
CALLABLE_GENERATOR_CONST(15)
CALLABLE_GENERATOR_CONST(16)
CALLABLE_GENERATOR_CONST(17)
CALLABLE_GENERATOR_CONST(18)
CALLABLE_GENERATOR_CONST(19)
CALLABLE_GENERATOR_CONST(20)
STATIC_CALLABLE_GENERATOR(0)
STATIC_CALLABLE_GENERATOR(1)
STATIC_CALLABLE_GENERATOR(2)
STATIC_CALLABLE_GENERATOR(3)
STATIC_CALLABLE_GENERATOR(4)
STATIC_CALLABLE_GENERATOR(5)
STATIC_CALLABLE_GENERATOR(6)
STATIC_CALLABLE_GENERATOR(7)
STATIC_CALLABLE_GENERATOR(8)
STATIC_CALLABLE_GENERATOR(9)
STATIC_CALLABLE_GENERATOR(10)
STATIC_CALLABLE_GENERATOR(11)
STATIC_CALLABLE_GENERATOR(12)
STATIC_CALLABLE_GENERATOR(13)
STATIC_CALLABLE_GENERATOR(14)
STATIC_CALLABLE_GENERATOR(15)
STATIC_CALLABLE_GENERATOR(16)
STATIC_CALLABLE_GENERATOR(17)
STATIC_CALLABLE_GENERATOR(18)
STATIC_CALLABLE_GENERATOR(19)
STATIC_CALLABLE_GENERATOR(20)


/** Pseudo-class used when a class does not inherit from another class. It
    can not be instantiated.
 */
class Class;
class NullClass
{
public:
    static const Class *GetClassStaticPtr()
    {
        return 0;
    }
private:
    NullClass() {}
    ~NullClass() {}
};


//Property handler base
struct PropertyBase
{
    virtual ~PropertyBase()
    {
    }
};


//Property handler
template <class T> struct PropertyHandler : public PropertyBase
{
    //Get
    virtual T Get(const void *object) const = 0;

    //Set
    virtual void Set(void *object, T value) const = 0;
};


//Property handler class
template <class C, class T> struct PropertyInner : public PropertyHandler<T>
{
    //type of Getters/Setters
    typedef T(C::*Getter)() const;
    typedef void (C::*Setter)(T);

    //pointer to member Getters/Setters
    Getter getter;
    Setter setter;

    //default constructor
    PropertyInner(Getter g, Setter s) : getter(g), setter(s)
    {
    }

    //Get
    virtual T Get(const void *object) const
    {
        const C *o = (const C *)(object);
        return (o->*getter)();
    }

    //Set
    virtual void Set(void *object, T value) const
    {
        C *o = (C *)(object);
        (o->*setter)(value);
    }
};


//declares a method
#define METHOD0(ACCESS_ATTR, VIRTUAL, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)\
private:\
    struct method_##METHOD_NAME \
    {\
        method_##METHOD_NAME () \
        {\
            static alice::reflection::RegisterMethod reg(CreateCallable(&ClassType::METHOD_NAME), GetClassStaticPtr(), ACCESS_##ACCESS_ATTR, #RETURN_TYPE, #METHOD_NAME, #METHOD_ARGS, #VIRTUAL);\
        }\
    } method_##METHOD_NAME ;\
    friend struct method_##METHOD_NAME ;\
ACCESS_ATTR :\
    VIRTUAL RETURN_TYPE METHOD_NAME METHOD_ARGS


//macro that defines an 'Invoke' method with a return type
#define INVOKE(N)\
    template <class R, class C REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)> \
    void Invoke(R &result, C *object REPEAT(N, ARG, COMMA, COMMA)) const \
    {\
        if (mAccess != ACCESS_PUBLIC) throw IllegalAccessError(mName);\
        typedef const Callable##N <R, C REPEAT(N, TYPE_ARG, COMMA, COMMA)> CallableType1;\
        typedef const CallableConst##N <R, C REPEAT(N, TYPE_ARG, COMMA, COMMA)> CallableType2;\
        CallableType1 *cb1 = dynamic_cast<CallableType1 *>(mCallable);\
        if (cb1) \
        {\
            result = cb1->Invoke(object REPEAT(N, PARAM, COMMA, COMMA));\
            return;\
        }\
        CallableType2 *cb2 = dynamic_cast<CallableType2 *>(mCallable);\
        if (cb2) \
        {\
            result = cb2->Invoke(object REPEAT(N, PARAM, COMMA, COMMA));\
            return;\
        }\
        throw TypeMismatchError(mName);\
    }


//macro that defines an 'Invoke' method without a return type
#define INVOKE_VOID(N)\
    template <class C REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)> \
    void InvokeVoid(C *object REPEAT(N, ARG, COMMA, COMMA)) const \
    {\
        if (mAccess != ACCESS_PUBLIC) throw IllegalAccessError(mName);\
        typedef const CallableVoid##N <C REPEAT(N, TYPE_ARG, COMMA, COMMA)> CallableType1;\
        typedef const CallableConstVoid##N <C REPEAT(N, TYPE_ARG, COMMA, COMMA)> CallableType2;\
        CallableType1 *cb1 = dynamic_cast<CallableType1 *>(mCallable);\
        if (cb1) {\
            cb1->Invoke(object REPEAT(N, PARAM, COMMA, COMMA));\
            return;\
        }\
        CallableType2 *cb2 = dynamic_cast<CallableType2 *>(mCallable);\
        if (cb2) {\
            cb2->Invoke(object REPEAT(N, PARAM, COMMA, COMMA));\
            return;\
        }\
        throw TypeMismatchError(mName);\
    }


//static Invoke void method with 0 params
#define STATIC_INVOKE0\
    template <class R> \
    inline void Invoke(R &result) const {\
        if (mAccess != ACCESS_PUBLIC) throw IllegalAccessError(mName);\
        typedef const StaticCallable0<R> CallableType;\
        CallableType *cb = dynamic_cast<CallableType *>(mCallable);\
        if (cb) {\
            result = cb->Invoke();\
            return;\
        }\
        throw TypeMismatchError(mName);\
    }


//static Invoke non-void method
#define STATIC_INVOKE(N)\
    template <class R REPEAT(N, TEMPLATE_ARG, COMMA, COMMA)> \
    void Invoke(R &result REPEAT(N, ARG, COMMA, COMMA)) const {\
        if (mAccess != ACCESS_PUBLIC) throw IllegalAccessError(mName);\
        typedef const StaticCallable##N <R REPEAT(N, TYPE_ARG, COMMA, COMMA)> CallableType;\
        CallableType *cb = dynamic_cast<CallableType *>(mCallable);\
        if (cb) {\
            result = cb->Invoke(REPEAT(N, PARAM, COMMA, NOTHING));\
            return;\
        }\
        throw TypeMismatchError(mName);\
    }


//static Invoke void method with 0 params
#define STATIC_INVOKE_VOID0\
    inline void InvokeVoid() const {\
        if (mAccess != ACCESS_PUBLIC) throw IllegalAccessError(mName);\
        typedef const StaticCallableVoid0 CallableType;\
        CallableType *cb = dynamic_cast<CallableType *>(mCallable);\
        if (cb) {\
            cb->Invoke();\
            return;\
        }\
        throw TypeMismatchError(mName);\
    }


//static Invoke void method
#define STATIC_INVOKE_VOID(N)\
    template <REPEAT(N, TEMPLATE_ARG, COMMA, NOTHING)> \
    void InvokeVoid(REPEAT(N, ARG, COMMA, NOTHING)) const {\
        if (mAccess != ACCESS_PUBLIC) throw IllegalAccessError(mName);\
        typedef const StaticCallableVoid##N <REPEAT(N, TYPE_ARG, COMMA, NOTHING)> CallableType;\
        CallableType *cb = dynamic_cast<CallableType *>(mCallable);\
        if (cb) {\
            cb->Invoke(REPEAT(N, PARAM, COMMA, NOTHING));\
            return;\
        }\
        throw TypeMismatchError(mName);\
    }


/** the CLASS macro is used to declare reflection support in a class. It must
    be placed on the public part of the class.
    @param CLASS_NAME name of this class.
    @param SUPER_CLASS_NAME name of the super class; if there is no base class,
           pass NullClass.
 */
#define CLASS(CLASS_NAME, SUPER_CLASS_NAME)\
private:\
    typedef CLASS_NAME ClassType;\
    static const alice::reflection::Class *GetClassStaticPtr() {\
        static alice::reflection::Class _class(#CLASS_NAME, SUPER_CLASS_NAME::GetClassStaticPtr());\
        return &_class;\
    }\
public:\
    static const alice::reflection::Class &GetClassStatic() {\
        return *CLASS_NAME::GetClassStaticPtr();\
    }\
    virtual const alice::reflection::Class &GetClass() const {\
        return *CLASS_NAME::GetClassStaticPtr();\
    }


/** The FIELD macro is used to declare a reflected field.
    @param ACCESS_ATTR access attribute (public, protected or private)
    @param FIELD_TYPE type of the field
    @param FIELD_NAME name of the field
 */
#define FIELD(ACCESS_ATTR, FIELD_TYPE, FIELD_NAME)\
private:\
    struct field_##FIELD_NAME {\
        field_##FIELD_NAME () {\
            static alice::reflection::RegisterField reg(OFFSET(ClassType, FIELD_NAME), typeid(FIELD_TYPE), GetClassStaticPtr(), ACCESS_##ACCESS_ATTR, #FIELD_TYPE, #FIELD_NAME);\
        }\
    } field_##FIELD_NAME ;\
    friend struct field_##FIELD_NAME ;\
ACCESS_ATTR :\
    FIELD_TYPE FIELD_NAME


/** The STATIC_FIELD macro is used to declare a reflected static field.
    @param ACCESS_ATTR access attribute (public, protected or private)
    @param FIELD_TYPE type of the field
    @param FIELD_NAME name of the field
 */
#define STATIC_FIELD(ACCESS_ATTR, FIELD_TYPE, FIELD_NAME)\
private:\
    struct static_field_##FIELD_NAME {\
        static_field_##FIELD_NAME () {\
            static alice::reflection::RegisterStaticField reg((void *)&FIELD_NAME, typeid(FIELD_TYPE), GetClassStaticPtr(), ACCESS_##ACCESS_ATTR, #FIELD_TYPE, #FIELD_NAME);\
        }\
    } static_field_##FIELD_NAME ;\
    friend struct static_field_##FIELD_NAME ;\
ACCESS_ATTR :\
    static FIELD_TYPE FIELD_NAME


/** The METHOD macro is used to declare a reflected method.
    @param ACCESS_ATTR access attribute (public, protected or private)
    @param RETURN_TYPE the return type of the method
    @param METHOD_NAME name of the method
    @param METHOD_ARGS the method's arguments enclosed in parentheses
 */
#define METHOD(ACCESS_ATTR, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)\
    METHOD0(ACCESS_ATTR, NOT_VIRTUAL, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)


/** The VIRTUAL_METHOD macro is used to declare a reflected method that is
    virtual, i.e. can be overloaded by subclasses.
    @param ACCESS_ATTR access attribute (public, protected or private)
    @param VIRTUAL pass virtual or no_virtual
    @param RETURN_TYPE the return type of the method
    @param METHOD_NAME name of the method
    @param METHOD_ARGS the method's arguments enclosed in parentheses
 */
#define VIRTUAL_METHOD(ACCESS_ATTR, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)\
    METHOD0(ACCESS_ATTR, virtual, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)


/** The STATIC_METHOD macro is used to declare a reflected static method.
    @param ACCESS_ATTR access attribute (public, protected or private)
    @param RETURN_TYPE the return type of the method
    @param METHOD_NAME name of the method
    @param METHOD_ARGS the method's arguments enclosed in parentheses
 */
#define STATIC_METHOD(ACCESS_ATTR, RETURN_TYPE, METHOD_NAME, METHOD_ARGS)\
private:\
    struct static_method_##METHOD_NAME {\
        static_method_##METHOD_NAME () {\
            static alice::reflection::RegisterStaticMethod reg(CreateStaticCallable(&ClassType::METHOD_NAME), GetClassStaticPtr(), ACCESS_##ACCESS_ATTR, #RETURN_TYPE, #METHOD_NAME, #METHOD_ARGS);\
        }\
    } static_method_##METHOD_NAME ;\
    friend struct static_method_##METHOD_NAME ;\
ACCESS_ATTR :\
    static RETURN_TYPE METHOD_NAME METHOD_ARGS


/** The Property macro is used to declare an object's property. When used,
    the class must have two private methods in the form of TYPE Get()/void Set(TYPE)
    for Setting and Getting the Property. By using this macro, the object
    Gets a Property interface for managing the value is if it was a field.
    Arithmetic and other operators work as expected. The defined Property
    is reflected: it can be examined and Set in run-time. Properties do
    not define an access attribute: there are always public. The Property
    does not add any extra bytes to the class, besides those needed for reflection.
    @param TYPE type of the Property
    @param NAME name of the Property
 */
#define PROPERTY(TYPE, NAME)\
private:\
    template <class T> class Property##NAME {\
    public:\
        typedef Property##NAME<T> Type;\
        Property##NAME<T>() {\
            static alice::reflection::RegisterProperty reg(new PropertyInner<ClassType, T>(&ClassType::Get##NAME, &ClassType::Set##NAME), GetClassStaticPtr(), #TYPE, #NAME);\
        }\
        inline TYPE Get() const {\
            return owner()->Get##NAME();\
        }\
        inline void Set(TYPE value) {\
            owner()->Set##NAME(value);\
        }\
        inline operator TYPE () const {\
            return Get();\
        }\
        inline bool operator == (TYPE value) const {\
            return Get() == value;\
        }\
        inline bool operator != (TYPE value) const {\
            return Get() != value;\
        }\
        inline bool operator < (TYPE value) const {\
            return Get() < value;\
        }\
        inline bool operator > (TYPE value) const {\
            return Get() > value;\
        }\
        inline bool operator <= (TYPE value) const {\
            return Get() <= value;\
        }\
        inline bool operator >= (TYPE value) const {\
            return Get() >= value;\
        }\
        inline Type &operator = (TYPE value) {\
            Set(value);\
            return *this;\
        }\
        inline Type &operator = (const Type &prop) {\
            if (&prop != this) Set(prop.Get());\
            return *this;\
        }\
        inline Type &operator += (TYPE value) {\
            Set(Get() + value);\
            return *this;\
        }\
        inline Type &operator -= (TYPE value) {\
            Set(Get() - value);\
            return *this;\
        }\
        inline Type &operator *= (TYPE value) {\
            Set(Get() * value);\
            return *this;\
        }\
        inline Type &operator /= (TYPE value) {\
            Set(Get() / value);\
            return *this;\
        }\
        inline Type &operator %= (TYPE value) {\
            Set(Get() % value);\
            return *this;\
        }\
        inline Type &operator <<= (int bits) {\
            Set(Get() << bits);\
            return *this;\
        }\
        inline Type &operator >>= (int bits) {\
            Set(Get() >> bits);\
            return *this;\
        }\
        inline Type &operator &= (TYPE value) {\
            Set(Get() & value);\
            return *this;\
        }\
        inline Type &operator |= (TYPE value) {\
            Set(Get() | value);\
            return *this;\
        }\
        inline Type &operator ^= (TYPE value) {\
            Set(Get() ^ value);\
            return *this;\
        }\
        inline TYPE operator ~() {\
            return ~Get();\
        }\
        inline TYPE operator ++() {\
            TYPE val = Get();\
            Set(val + 1);\
            return val;\
        }\
        inline TYPE operator ++(int i) {\
            TYPE val = Get();\
            Set(val + 1);\
            return Get();\
        }\
        inline TYPE operator --() {\
            TYPE val = Get();\
            Set(val - 1);\
            return val;\
        }\
        inline TYPE operator --(int i) {\
            TYPE val = Get();\
            Set(val - 1);\
            return Get();\
        }\
    private:\
        ClassType *owner() {\
            return (ClassType *)(((const char *)this) - OFFSET(ClassType, NAME));\
        }\
        const ClassType *owner() const {\
            return (const ClassType *)(((const char *)this) - OFFSET(ClassType, NAME));\
        }\
    };\
    friend class Property##NAME< TYPE >;\
public:\
    Property##NAME< TYPE > NAME


/** access type enumeration
 */
enum ACCESS_TYPE
{
    ///public access
    ACCESS_PUBLIC,

    ///protected access
    ACCESS_PROTECTED,

    ///private access
    ACCESS_PRIVATE
};


//access synonyms used in reflection
#define ACCESS_public        ACCESS_PUBLIC
#define ACCESS_protected     ACCESS_PROTECTED
#define ACCESS_private       ACCESS_PRIVATE


class Class;
/** Exception thrown when there is a type mismatch.
 */
class TypeMismatchError : public std::runtime_error
{
public:
    /** the default constructor
        @param what the item that caused the error
     */
    TypeMismatchError(const std::string &what) : runtime_error(what)
    {
    }
};


/** Exception thrown when there is an illegal access error.
 */
class IllegalAccessError : public std::runtime_error
{
public:
    /** the default constructor
        @param what the item that caused the error
     */
    IllegalAccessError(const std::string &what) : runtime_error(what)
    {
    }
};


/** Exception thrown when an unknown field has been requested.
 */
class UnknownFieldError : public std::runtime_error
{
public:
    /** the default constructor
        @param what the item that caused the error
     */
    UnknownFieldError(const std::string &what) : runtime_error(what)
    {
    }
};


/** Exception thrown when an unknown method has been requested.
 */
class UnknownMethodError : public std::runtime_error
{
public:
    /** the default constructor
        @param what the item that caused the error
     */
    UnknownMethodError(const std::string &what) : runtime_error(what)
    {
    }
};


/** Exception thrown when an unknown Property has been requested.
 */
class UnknownPropertyError : public std::runtime_error
{
public:
    /** the default constructor
        @param what the item that caused the error
     */
    UnknownPropertyError(const std::string &what) : runtime_error(what)
    {
    }
};


/** Exception thrown when there the superclass of a class was asked to be
    returned but there was no superclass.
 */
class SuperClassError : public std::runtime_error
{
public:
    /** the default constructor
        @param what the item that caused the error
     */
    SuperClassError(const std::string &what) : runtime_error(what)
    {
    }
};

/** The StaticField class represents an object's static field.
 */
class StaticField
{
public:
    /** returns the class that the member is declared into.
        @return the class that the member is declared into.
     */
    const Class& GetClass() const
    {
        return *mClass;
    }

    /** returns the field's access.
        @return the field's access.
     */
    const ACCESS_TYPE GetAccess() const
    {
        return mAccess;
    }

    /** returns the field's type.
        @return the field's type.
     */
    const char* GetType() const
    {
        return mType;
    }

    /** returns the field's name.
        @return the field's name.
     */
    const char* GetName() const
    {
        return mName;
    }

    /** retrieves the static field's value.
        @param value variable to store the value of the field
        @exception TypeMismatchError thrown if the object is of invalid class or
                   the value is of the wrong type.
     */
    template <class Value> void Get(Value &value) const
    {
        if(mAccess != ACCESS_PUBLIC) throw IllegalAccessError(mName);
        if(typeid(Value) != mTypeinfo) throw TypeMismatchError("value");
        value = *(const Value *)(mAddress);
    }

    /** Sets the static field's value.
        @param value new value of the field
        @exception TypeMismatchError thrown if the object is of invalid class or
                   the value is of the wrong type.
        @exception IllegalAccessError thrown if the field's access is not public.
     */
    template <class Value> void Set(const Value &value) const
    {
        if(mAccess != ACCESS_PUBLIC) throw IllegalAccessError(mName);
        if(typeid(Value) != mTypeinfo) throw TypeMismatchError("value");
        *(Value *)(mAddress) = value;
    }

private:
    const std::type_info &mTypeinfo;
    const Class *mClass;
    enum ACCESS_TYPE mAccess;
    const char *mType;
    const char *mName;
    void *mAddress;

    //default constructor
    StaticField(void *address, const std::type_info &typeinfo, const Class *pclass, ACCESS_TYPE access, const char *type, const char *name) :
        mAddress(address),
        mTypeinfo(typeinfo),
        mClass(pclass),
        mAccess(access),
        mType(type),
        mName(name)
    {
    }

    friend class Class;
    friend struct RegisterStaticField;
};


/** The Method class represents an object's method.
 */
class Method
{
public:
    ///destructor
    ~Method()
    {
        if(mCallable) delete mCallable;
    }

    /** returns the class that the member is declared into.
        @return the class that the member is declared into.
     */
    const Class &GetClass() const
    {
        return *mClass;
    }

    /** returns the method's access.
        @return the method's access.
     */
    const ACCESS_TYPE GetAccess() const
    {
        return mAccess;
    }

    /** returns the method's type (return type).
        @return the method's type.
     */
    const char *GetType() const
    {
        return mType;
    }

    /** returns the method's name.
        @return the method's name.
     */
    const char *GetName() const
    {
        return mName;
    }

    /** returns the method's id (name + arguments).
        @return the method's name.
     */
    const char *GetId() const
    {
        return mId.c_str();
    }

    /** returns the method's arguments.
        @return the method's arguments.
     */
    const char *GetArgs() const
    {
        return mArgs;
    }

    /** returns true if the method is virtual.
        @return true if the method is virtual.
     */
    bool IsVirtual() const
    {
        return mVirtual;
    }

    /** Invokes a method that has a result
        @param result optional variable to store the result (if the method is non-void)
        @param object object to execute the method of
        @param t1...tn parameters of the invocation
        @exception IllegalAccessError if the method is not public
        @exception TypeMismatchError if the method has different arguments than
                   the ones passed to it
     */
    INVOKE(0)
    INVOKE(1)
    INVOKE(2)
    INVOKE(3)
    INVOKE(4)
    INVOKE(5)
    INVOKE(6)
    INVOKE(7)
    INVOKE(8)
    INVOKE(9)
    INVOKE(10)
    INVOKE(11)
    INVOKE(12)
    INVOKE(13)
    INVOKE(14)
    INVOKE(15)
    INVOKE(16)
    INVOKE(17)
    INVOKE(18)
    INVOKE(19)
    INVOKE(20)

    /** Invokes a method that 'returns' void
        @param object object to execute the method of
        @param t1...tn parameters of the invocation
        @exception IllegalAccessError if the method is not public
        @exception TypeMismatchError if the method has different arguments than
                   the ones passed to it
     */
    INVOKE_VOID(0)
    INVOKE_VOID(1)
    INVOKE_VOID(2)
    INVOKE_VOID(3)
    INVOKE_VOID(4)
    INVOKE_VOID(5)
    INVOKE_VOID(6)
    INVOKE_VOID(7)
    INVOKE_VOID(8)
    INVOKE_VOID(9)
    INVOKE_VOID(10)
    INVOKE_VOID(11)
    INVOKE_VOID(12)
    INVOKE_VOID(13)
    INVOKE_VOID(14)
    INVOKE_VOID(15)
    INVOKE_VOID(16)
    INVOKE_VOID(17)
    INVOKE_VOID(18)
    INVOKE_VOID(19)
    INVOKE_VOID(20)

private:
    const Class *mClass;
    enum ACCESS_TYPE mAccess;
    std::string mId;
    const char *mType;
    const char *mName;
    const char *mArgs;
    Callable *mCallable;
    bool mVirtual: 1;

    //default constructor
    Method(const Class *pclass, ACCESS_TYPE access, const char *type, const char *name, const char *args, bool virt) :
        mClass(pclass),
        mAccess(access),
        mType(type),
        mName(name),
        mArgs(args),
        mVirtual(virt),
        mCallable(0),
        mId(name)
    {
        mId += args;
    }

    friend class Class;
    friend struct RegisterMethod;
};


/** The StaticMethod class represents an object's static method.
 */
class StaticMethod
{
public:
    ///destructor
    ~StaticMethod()
    {
        if(mCallable) delete mCallable;
    }

    /** returns the class that the member is declared into.
        @return the class that the member is declared into.
     */
    const Class &GetClass() const
    {
        return *mClass;
    }

    /** returns the method's access.
        @return the method's access.
     */
    const ACCESS_TYPE GetAccess() const
    {
        return mAccess;
    }

    /** returns the method's type (return type).
        @return the method's type.
     */
    const char *GetType() const
    {
        return mType;
    }

    /** returns the method's name.
        @return the method's name.
     */
    const char *GetName() const
    {
        return mName;
    }

    /** returns the method's id (name + arguments).
        @return the method's name.
     */
    const char *GetId() const
    {
        return mId.c_str();
    }

    /** returns the method's arguments.
        @return the method's arguments.
     */
    const char *GetArgs() const
    {
        return mArgs;
    }

    /** Invokes the non-void method
        @param result optional variable to store the result (if the method is non-void)
        @param t1...tn parameters of the invocation
        @exception IllegalAccessError if the method is not public
        @exception TypeMismatchError if the method has different arguments than
                   the ones passed to it
     */
    STATIC_INVOKE0
    STATIC_INVOKE(1)
    STATIC_INVOKE(2)
    STATIC_INVOKE(3)
    STATIC_INVOKE(4)
    STATIC_INVOKE(5)
    STATIC_INVOKE(6)
    STATIC_INVOKE(7)
    STATIC_INVOKE(8)
    STATIC_INVOKE(9)
    STATIC_INVOKE(10)
    STATIC_INVOKE(11)
    STATIC_INVOKE(12)
    STATIC_INVOKE(13)
    STATIC_INVOKE(14)
    STATIC_INVOKE(15)
    STATIC_INVOKE(16)
    STATIC_INVOKE(17)
    STATIC_INVOKE(18)
    STATIC_INVOKE(19)
    STATIC_INVOKE(20)

    /** Invokes the void method
        @param t1...tn parameters of the invocation
        @exception IllegalAccessError if the method is not public
        @exception TypeMismatchError if the method has different arguments than
                   the ones passed to it
     */
    STATIC_INVOKE_VOID0
    STATIC_INVOKE_VOID(1)
    STATIC_INVOKE_VOID(2)
    STATIC_INVOKE_VOID(3)
    STATIC_INVOKE_VOID(4)
    STATIC_INVOKE_VOID(5)
    STATIC_INVOKE_VOID(6)
    STATIC_INVOKE_VOID(7)
    STATIC_INVOKE_VOID(8)
    STATIC_INVOKE_VOID(9)
    STATIC_INVOKE_VOID(10)
    STATIC_INVOKE_VOID(11)
    STATIC_INVOKE_VOID(12)
    STATIC_INVOKE_VOID(13)
    STATIC_INVOKE_VOID(14)
    STATIC_INVOKE_VOID(15)
    STATIC_INVOKE_VOID(16)
    STATIC_INVOKE_VOID(17)
    STATIC_INVOKE_VOID(18)
    STATIC_INVOKE_VOID(19)
    STATIC_INVOKE_VOID(20)

private:
    const Class *mClass;
    enum ACCESS_TYPE mAccess;
    std::string mId;
    const char *mType;
    const char *mName;
    const char *mArgs;
    Callable *mCallable;

    //default constructor
    StaticMethod(const Class *pclass, ACCESS_TYPE access, const char *type, const char *name, const char *args) :
        mClass(pclass),
        mAccess(access),
        mType(type),
        mName(name),
        mArgs(args),
        mCallable(0),
        mId(name)
    {
        mId += args;
    }

    friend class Class;
    friend struct RegisterStaticMethod;
};


/** The Field class represents an object's field.
 */
class Field
{
public:
    /** returns the class that the member is declared into.
        @return the class that the member is declared into.
     */
    const Class &GetClass() const
    {
        return *mClass;
    }

    /** returns the field's access.
        @return the field's access.
     */
    const ACCESS_TYPE GetAccess() const
    {
        return mAccess;
    }

    /** returns the field's type.
        @return the field's type.
     */
    const char *GetType() const
    {
        return mType;
    }

    /** returns the field's name.
        @return the field's name.
     */
    const char *GetName() const
    {
        return mName;
    }

    /** retrieves the field of the given object.
        @param result variable to store the result of the field
        @param object object to Set the field of
        @exception TypeMismatchError thrown if the object is of invalid class or
                   the result is of the wrong type.
     */
    template <class Object, class Value> void Get(Value &result, Object *object) const;

    /** Sets the field of the given object.
        @param object object to Set the field of
        @param value new value of the field
        @exception TypeMismatchError thrown if the object is of invalid class or
                   the value is of the wrong type.
        @exception IllegalAccessError thrown if the field's access is not public.
     */
    template <class Object, class Value> void Set(Object *object, const Value &value) const;


private:
    const std::type_info &mTypeinfo;
    const Class *mClass;
    enum ACCESS_TYPE mAccess;
    const char *mType;
    const char *mName;
    unsigned long mOffset;

    //default constructor
    Field(unsigned long offSet, const std::type_info &typeinfo, const Class *pclass, ACCESS_TYPE access, const char *type, const char *name) :
        mOffset(offSet),
        mTypeinfo(typeinfo),
        mClass(pclass),
        mAccess(access),
        mType(type),
        mName(name)
    {
    }

    friend class Class;
    friend struct RegisterField;
};


/** The Property class holds information about an object's property.
 */
class Property
{
public:
    ///destructor
    ~Property()
    {
        if(mHandler) delete mHandler;
    }

    /** returns the class that the member is declared into.
        @return the class that the member is declared into.
     */
    const Class &GetClass() const
    {
        return *mClass;
    }

    /** returns the Property's type.
        @return the Property's type.
     */
    const char *GetType() const
    {
        return mType;
    }

    /** returns the Property's name.
        @return the Property's name.
     */
    const char *GetName() const
    {
        return mName;
    }

    /** returns the value of the Property
        @param result result to store the value to
        @param object object to Get the Property of
        @exception TypeMismatchError thrown if there is a type mismatch
     */
    template <class Object, class Value> void Get(Value &result, const Object *object) const;
    /** Sets the Property's value
        @param object object to Set the Property of
        @param value value of the object
        @exception TypeMismatchError thrown if there is a type mismatch
     */
    template <class Object, class Value> void Set(Object *object, const Value &value) const;


private:
    const char *mType;
    const char *mName;
    PropertyBase *mHandler;
    const Class *mClass;

    //default constructor
    Property(const Class *pclass, const char *type, const char *name) :
        mClass(pclass),
        mType(type),
        mName(name),
        mHandler(0)
    {
    }

    friend class Class;
    friend struct RegisterProperty;
};
class Class
{
public:
    ///type of list of fields
    typedef std::list<Field> FieldList;

    ///type of list of static fields
    typedef std::list<StaticField> StaticFieldList;

    ///type of list of methods
    typedef std::list<Method> MethodList;

    ///type of list of static methods
    typedef std::list<StaticMethod> StaticMethodList;

    ///type of list of properties
    typedef std::list<Property> PropertyList;

    //the default constructor
    Class(const char *name, const Class *super) :
        mName(name),
        mSuper(super)
    {
    }

    /** returns the class name
        @return the class name
     */
    const char *GetName() const
    {
        return mName;
    }

    /** checks if the class has a superclass
        @return true if the class has a superclass
     */
    const bool HasSuper() const
    {
        return mSuper != 0;
    }

    /** returns the superclass of the class
        @return the superclass of the class; the superclass must not be null
        @exception SuperClassError thrown if there is no super class
     */
    const Class &GetSuper() const
    {
        if(!mSuper) throw SuperClassError(mName);
        return *mSuper;
    }

    /** returns the collection of fields
        @return the collection of fields
     */
    const FieldList &GetFields() const
    {
        return mFields;
    }

    /** returns the collection of static fields
        @return the collection of static fields
     */
    const StaticFieldList &GetStaticFields() const
    {
        return mStaticFields;
    }

    /** returns the list of methods
        @return the list of methods
     */
    const MethodList &GetMethods() const
    {
        return mMethods;
    }

    /** returns the collection of static methods
        @return the collection of static methods
     */
    const StaticMethodList &GetStaticMethods() const
    {
        return mStaticMethods;
    }

    /** returns the collection of properties
        @return the collection of properties
     */
    const PropertyList &GetProperties() const
    {
        return mProperties;
    }

    /** checks if this class is a base class of the given class.
        @param cl class to check against
        @return true if this class is a base class of the given class.
     */
    bool IsBase(const Class &cl) const
    {
        for(const Class *c = cl.mSuper; c; c = c->mSuper)
        {
            if(c == this) return true;
        }
        return false;
    }

    /** checks if this class is the super class of the given class.
        @param cl class to check against
        @return true if this class is the super class of the given class.
     */
    bool IsSuper(const Class &cl) const
    {
        return cl.mSuper == this;
    }

    /** checks if this class is the same as given class
        @param cl class to check against
     */
    bool IsSame(const Class &cl) const
    {
        return &cl == this;
    }

    /** checks if the given class is relative to this class. In other words,
        it checks if this class is a base class of the given class, or if they
        are the same class or the given class is a base class of this class.
        @param cl class to check against
        @return true if this class is a base class of the given class or the
                same class.
     */
    bool IsRelative(const Class &cl) const
    {
        return IsSame(cl) || IsBase(cl) || cl.IsBase(*this);
    }

    /** returns field from name
        @param name name of the field to search for
        @param searchSuper if true, super classes are searched if this class does not have the requested member
        @return the field of given name
        @exception UnknownFieldError
     */
    const Field &GetField(const char *name, bool searchSuper = true) const
    {
        FieldMap::const_iterator it = mFieldMap.find(name);
        if(it == mFieldMap.end())
        {
            if(searchSuper && mSuper) return mSuper->GetField(name, true);
            throw UnknownFieldError(name);
        }
        return *it->second;
    }

    /** returns static field from name
        @param name name of the field to search for
        @param searchSuper if true, super classes are searched if this class does not have the requested member
        @return the field of given name
        @exception UnknownFieldError
     */
    const StaticField &GetStaticField(const char *name, bool searchSuper = true) const
    {
        StaticFieldMap::const_iterator it = mStaticFieldMap.find(name);
        if(it == mStaticFieldMap.end())
        {
            if(searchSuper && mSuper) return mSuper->GetStaticField(name, true);
            throw UnknownFieldError(name);
        }
        return *it->second;
    }

    /** returns method from name
        @param name name of the method to search for
        @param searchSuper if true, super classes are searched if this class does not have the requested member
        @return the method of given id
        @exception UnknownMethodError
     */
    const Method &GetMethod(const char *name, bool searchSuper = true) const
    {
        MethodMap::const_iterator it = mMethodMap.find(name);
        if(it == mMethodMap.end())
        {
            if(searchSuper && mSuper) return mSuper->GetMethod(name, true);
            throw UnknownMethodError(name);
        }
        return *it->second;
    }

    /** returns static method from name
        @param name name of the method to search for
        @param searchSuper if true, super classes are searched if this class does not have the requested member
        @return the method of given name
        @exception UnknownMethodError
     */
    const StaticMethod &GetStaticMethod(const char *name, bool searchSuper = true) const
    {
        StaticMethodMap::const_iterator it = mStaticMethodMap.find(name);
        if(it == mStaticMethodMap.end())
        {
            if(searchSuper && mSuper) return mSuper->GetStaticMethod(name, true);
            throw UnknownMethodError(name);
        }
        return *it->second;
    }

    /** returns Property from name
        @param name name of the Property to search for
        @param searchSuper if true, super classes are searched if this class does not have the requested member
        @return the Property of given name
        @exception UnknownPropertyError
     */
    const Property &GetProperty(const char *name, bool searchSuper = true) const
    {
        PropertyMap::const_iterator it = mPropertyMap.find(name);
        if(it == mPropertyMap.end())
        {
            if(searchSuper && mSuper) return mSuper->GetProperty(name, true);
            throw UnknownPropertyError(name);
        }
        return *it->second;
    }

private:
    typedef std::map<std::string, Field *> FieldMap;
    typedef std::map<std::string, StaticField *> StaticFieldMap;
    typedef std::map<std::string, Method *> MethodMap;
    typedef std::map<std::string, StaticMethod *> StaticMethodMap;
    typedef std::map<std::string, Property *> PropertyMap;
    const char *mName;
    const Class *mSuper;
    FieldList mFields;
    FieldMap mFieldMap;
    StaticFieldList mStaticFields;
    StaticFieldMap mStaticFieldMap;
    MethodList mMethods;
    MethodMap mMethodMap;
    StaticMethodList mStaticMethods;
    StaticMethodMap mStaticMethodMap;
    PropertyList mProperties;
    PropertyMap mPropertyMap;

    //adds a field
    void _addField(const Field &field)
    {
        mFields.push_back(field);
        mFieldMap[field.mName] = &mFields.back();
    }

    //adds a static field
    void _addStaticField(const StaticField &field)
    {
        mStaticFields.push_back(field);
        mStaticFieldMap[field.mName] = &mStaticFields.back();
    }

    //adds a method
    void _addMethod(const Method &method, Callable *cb)
    {
        mMethods.push_back(method);
        Method &m = mMethods.back();
        m.mCallable = cb;
        mMethodMap[method.mName] = &m;
    }

    //adds a static method
    void _addStaticMethod(const StaticMethod &method, Callable *cb)
    {
        mStaticMethods.push_back(method);
        StaticMethod &m = mStaticMethods.back();
        m.mCallable = cb;
        mStaticMethodMap[method.mName] = &m;
    }

    //adds a Property
    void _addProperty(const Property &prop, PropertyBase *handler)
    {
        mProperties.push_back(prop);
        Property &p = mProperties.back();
        p.mHandler = handler;
        mPropertyMap[prop.mName] = &p;
    }

    friend struct RegisterField;
    friend struct RegisterStaticField;
    friend struct RegisterMethod;
    friend struct RegisterStaticMethod;
    friend struct RegisterProperty;
};

template <class Object, class Value>
void Property::Get(Value &result, const Object *object) const
{
    if(!mClass->IsRelative(object->GetClass())) throw TypeMismatchError("object");
    typedef const PropertyHandler<Value> PropertyType;
    PropertyType *prop = dynamic_cast<PropertyType *>(mHandler);
    if(!prop) throw TypeMismatchError(mName);
    result = prop->Get((const void *)object);
}

template <class Object, class Value>
void Property::Set(Object *object, const Value &value) const
{
    if(!mClass->IsRelative(object->GetClass())) throw TypeMismatchError("object");
    typedef const PropertyHandler<Value> PropertyType;
    PropertyType *prop = dynamic_cast<PropertyType *>(mHandler);
    if(!prop) throw TypeMismatchError(mName);
    prop->Set((void *)object, value);
}

template <class Object, class Value>
void Field::Get(Value &result, Object *object) const
{
    if(mAccess != ACCESS_PUBLIC) throw IllegalAccessError(mName);
    if(!mClass->IsRelative(object->GetClass())) throw TypeMismatchError("object");
    if(typeid(Value) != mTypeinfo) throw TypeMismatchError("result");
    result = *(const Value *)(((const char *)object) + mOffset);
}

template <class Object, class Value>
void Field::Set(Object *object, const Value &value) const
{
    if(mAccess != ACCESS_PUBLIC) throw IllegalAccessError(mName);
    if(!mClass->IsRelative(object->GetClass())) throw TypeMismatchError("object");
    if(typeid(Value) != mTypeinfo) throw TypeMismatchError("value");
    *(Value *)(((char *)object) + mOffset) = value;
}


//internal class for registering a field
struct RegisterField
{
    RegisterField(unsigned long offSet, const std::type_info &typeinfo, const Class *pclass, enum ACCESS_TYPE access, const char *type, const char *name)
    {
        Field field(offSet, typeinfo, pclass, access, type, name);
        ((Class *)pclass)->_addField(field);
    }
};


//internal class for registering a static field
struct RegisterStaticField
{
    RegisterStaticField(void *address, const std::type_info &typeinfo, const Class *pclass, enum ACCESS_TYPE access, const char *type, const char *name)
    {
        StaticField field(address, typeinfo, pclass, access, type, name);
        ((Class *)pclass)->_addStaticField(field);
    }
};


//internal class for registering a method
struct RegisterMethod
{
    RegisterMethod(Callable *cb, const Class *pclass, enum ACCESS_TYPE access, const char *type, const char *name, const char *args, const char *virt)
    {
        Method method(pclass, access, type, name, args, virt[0] == 'v' ? true : false);
        ((Class *)pclass)->_addMethod(method, cb);
    }
};


//internal class for registering a static method
struct RegisterStaticMethod
{
    RegisterStaticMethod(Callable *cb, const Class *pclass, enum ACCESS_TYPE access, const char *type, const char *name, const char *args)
    {
        StaticMethod method(pclass, access, type, name, args);
        ((Class *)pclass)->_addStaticMethod(method, cb);
    }
};


//internal class for registering a Property
struct RegisterProperty
{
    RegisterProperty(PropertyBase *handler, const Class *pclass, const char *type, const char *name)
    {
        Property property(pclass, type, name);
        ((Class *)pclass)->_addProperty(property, handler);
    }
};


}
}


///alias to Null class for reflection
using alice::reflection::NullClass ;


/** operator that outputs the access type to the given stream
    @param str stream to output the access to
    @param access access type to output
    @return the given stream
    @exception std::range_error thrown if the access value is invalid
 */
inline std::ostream &operator << (std::ostream &str, alice::reflection::ACCESS_TYPE access)
{
    switch(access)
    {
    case alice::reflection::ACCESS_PUBLIC:
        str << "public";
        break;

    case alice::reflection::ACCESS_PROTECTED:
        str << "protected";
        break;

    case alice::reflection::ACCESS_PRIVATE:
        str << "private";
        break;

    default:
        throw std::range_error("access");
    }

    return str;
}

#endif //
