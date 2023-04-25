#ifndef COMPONENT_HPP

#define COMPONENT_HPP

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


#endif // !COMPONENT_HPP

