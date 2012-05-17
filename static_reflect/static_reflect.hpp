#ifndef STATIC_REFLECT_H
#define STATIC_REFLECT_H
#include <string>
#include "if_c.hpp"
#include "is_same.hpp"
#define OFFSET(structure, member) ((size_t)&((structure*)(0))->member)
class End {};
/* this is a example class to illustrate the principle of reflect
 *
 */
template
<
    typename Namer,
    typename Container,
    typename Offs,
    typename HType,
    typename TType = End
>
struct Field
{
    typedef Container Memberof;
    typedef HType Type;
    typedef TType Next;
    const static size_t Size = sizeof(Type);
    const static size_t Offset = Offs::Offset;
    const static char* const  Name;
};
template<typename Namer,  typename Container, typename Offs, typename HType, typename TType>
const char* const Field<Namer, Container, Offs, HType, TType>::Name = Namer::Name;

struct Foo
{
    int mAttri1;
    char* mAttri2;
};

struct MetaFoo
{
    typedef Foo Klass;
    typedef End mCurrentType0;
    const static char* const Name;
    //Field 1 mAttri1
    struct AttributeName1 { const static char* const Name;};
    struct AttributeOffset1{ static const size_t  Offset; };

    typedef Field <AttributeName1, Klass, AttributeOffset1, int,  End> mCurrentType1;
    //Fileld 2 mAttr2
    struct AttributeName2 { const static char* const Name;};
    struct AttributeOffset2{ static const size_t  Offset = OFFSET(Klass, mAttri2); };
    typedef Field <AttributeName2, Klass, AttributeOffset2, char*,  mCurrentType1> mCurrentType2;
    typedef mCurrentType2 Attributes;
};

const size_t MetaFoo::AttributeOffset1::Offset =  OFFSET(Klass, mAttri1);
// const size_t MetaFoo::AttributeOffset2::Offset = OFFSET(Klass, mAttri2);
const  char* const MetaFoo::Name = "Foo";
const  char* const MetaFoo::AttributeName1::Name = "mAttri1";
const  char* const MetaFoo::AttributeName2::Name = "mAttri1";

template <class T>
struct SerializeBase
{
    static void Serialize(T* p, char* buffer) {}
};
#include <iostream>
template <class T>
struct Serializable
{
    static void Serialize(typename T::Memberof* p, char* s)
    {
        IfThenElse<
            !IsSame<typename T::Next, End>::Result,
            Serializable<typename T::Next>,
            SerializeBase<typename T::Memberof> >::Result::Serialize(p, s);

        typename T::Type *m = (typename T::Type*)((char*)p + T::Offset);

        std::cout << m << "-->" << T::Offset << std::endl;
    }
};

#endif /* GALAXY_ANTISPAM_REFLECT_STATIC_REFLECT_H */
