#include "static_reflect.hpp"

int main(int args, char** argv)
{
    Foo foo = {100, "help"};
    static const size_t a =  OFFSET(Foo, mAttri1);
    Serializable<MetaFoo::Attributes>::Serialize(&foo, 0);
    return 0;
}
