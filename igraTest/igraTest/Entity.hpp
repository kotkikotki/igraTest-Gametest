#ifndef ENTITY_H

#define ENTITY_H

#include<map>
#include<memory>
#include<typeindex>


#include "Definitions.hpp"
#include "Component.h"



class Entity
{
private:
    std::multimap<std::type_index, std::shared_ptr<Component>> mem_components;

public:
    
    /*template<class T, typename = enable_if_t<is_base_of_v<Component, T>>>
    void AddComponent()
    {
        if (GetComponent<T>() != nullptr)throw std::invalid_argument("Component already exists.");

        std::dynamic_pointer_cast<T>(mem_components.insert(std::make_pair(std::type_index(typeid(T)), new T))->second);
        //
        std::cout << "Component added=" << std::endl;
    }*/

    template<class T, typename = enable_if_t<is_base_of_v<Component, T>>>
    std::shared_ptr<T> AddComponent()
    {
        if (GetComponent<T>() != nullptr)throw std::invalid_argument("Component already exists.");

        std::cout << "Component added=" << std::endl;

        return std::dynamic_pointer_cast<T>(mem_components.insert(std::make_pair(std::type_index(typeid(T)), new T))->second);
        //
        
        
    }
    
    template<class T, typename = enable_if_t<is_base_of_v<Component, T>>>
    std::shared_ptr<T> GetComponent()
    {
        auto itr = mem_components.find(std::type_index(typeid(T)));
        if (itr == mem_components.end()) return std::shared_ptr<T>(nullptr);
        return std::dynamic_pointer_cast<T>(itr->second);
    }

    template<class T, typename = enable_if_t<is_base_of_v<Component, T>>>
    bool HasComponent()
    {
        if (GetComponent<T>() == nullptr)return false;
        return true;
    }

    template<class T, typename = enable_if_t<is_base_of_v<Component, T>>>
    std::type_index GetComponentTypeIndex()
    {
        auto itr = mem_components.find(std::type_index(typeid(T)));
        if (itr == mem_components.end()) return std::type_index(typeid(nullptr));
        return itr->first;
    }
    
    template<class T, typename = enable_if_t<is_base_of_v<Component, T>>>
    void RemoveComponent()
    {
        const std::type_index &ti = GetComponentTypeIndex<T>();
        if (ti == std::type_index(typeid(nullptr))) throw std::invalid_argument("Component doesn't exist.");
        mem_components.erase(ti);
        //
        std::cout << "Component removed=" << std::endl;
    }
    
};



#endif // !ENTITY_H
