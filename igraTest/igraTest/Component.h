#ifndef COMPONENT_H

#define COMPONENT_H

#include<iostream>
#include "Definitions.hpp"


class Component
{

public:
    virtual ~Component() = default;
    Component(const Component& r) = delete;
protected:
    Component() = default;

};


#endif // !COMPONENT_H

