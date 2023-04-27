#ifndef COMPONENT_HPP

#define COMPONENT_HPP

#include<iostream>
#include "Definitions.hpp"
#include "Entity.hpp"

class Entity;

class Component
{

     std::shared_ptr<Entity> owner;

public:
    virtual ~Component() = default;
    Component(const Component& r) = delete;
    
    
    virtual const std::shared_ptr<Entity>& GetOwner()
    {
        return owner;
    }

    virtual void SetOwner(const std::shared_ptr<Entity>& owner)
    {
        this->owner = owner;
    }
    //
protected:
    Component() = default;

};


#endif // !COMPONENT_HPP

