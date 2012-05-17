#include "reflection.hpp"


/*****************************************************************************
    MAIN
 *****************************************************************************/


#include <list>
#include <string>
#include <iostream>
using namespace std;
using namespace alice::reflection;


void print_class(const Class &pclass)
{
    cout << "class name = " << pclass.GetName() << endl;

    cout << "superclass = ";
    if (pclass.HasSuper()) cout << pclass.GetSuper().GetName();
    else cout << "none";
    cout << endl;

    cout << "fields:\n";
    for(Class::FieldList::const_iterator itField = pclass.GetFields().begin();
        itField != pclass.GetFields().end();
        ++itField)
    {
        const Field &field = *itField;
        cout << "    " << field.GetAccess() << " " << field.GetType() << " " << field.GetName() << endl;
    }

    cout << "static fields:\n";
    for(Class::StaticFieldList::const_iterator itStaticField = pclass.GetStaticFields().begin();
        itStaticField != pclass.GetStaticFields().end();
        ++itStaticField)
    {
        const StaticField &field = *itStaticField;
        cout << "    " << field.GetAccess() << " " << field.GetType() << " " << field.GetName() << endl;
    }

    cout << "methods:\n";
    for(Class::MethodList::const_iterator itMethod = pclass.GetMethods().begin();
        itMethod != pclass.GetMethods().end();
        ++itMethod)
    {
        const Method &method = *itMethod;
        cout << "    " << method.GetAccess();
        if (method.IsVirtual()) cout << " " << "virtual";
        cout << " " << method.GetType() << " " << method.GetName() << method.GetArgs() << endl;
    }

    cout << "properties:\n";
    for(Class::PropertyList::const_iterator itProperty = pclass.GetProperties().begin();
        itProperty != pclass.GetProperties().end();
        ++itProperty)
    {
        const Property &property = *itProperty;
        cout << "    " << property.GetType() << " " << property.GetName() << endl;
    }

    cout << "\n-----------------------------------------------------------\n";
}


class Foo {
public:
    CLASS(Foo, NullClass);

    PROPERTY(int, Length);

    METHOD(public, void, action, ()) {
        cout << "Foo::action();\n";
    }

    METHOD(public, void, action1, (int i, int j)) {
        cout << "Foo::action1(" << i << ");\n";
    }

    STATIC_METHOD(public, int, get_code, ()) {
        cout << "Foo::Get_code();\n";
        return 1;
    }

    STATIC_METHOD(public, int, get_code1, (int i)) {
        cout << "Foo::Get_code1(" << i << ");\n";
        return i + 1;
    }

    STATIC_METHOD(public, void, print_code, ()) {
        cout << "Foo::print_code();\n";
    }

    STATIC_METHOD(public, void, print_code1, (int i)) {
        cout << "Foo::print_code1(" << i << ");\n";
    }

    Foo() {
        m_length = 0;
    }
private:
    int m_length;

    int GetLength() const {
        cout << "get_length();\n";
        return m_length;
    }

    void SetLength(int l) {
        cout << "set_length(" << l << ");\n";
        m_length = l;
    }
};


class Bar {
public:
    CLASS(Bar, NullClass);
};


int main()
{
    Foo foo1;
    const Class &foo_class = foo1.GetClass();
    print_class(foo_class);

    getchar();
    return 0;
}
