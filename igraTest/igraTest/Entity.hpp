#ifndef ENTITY_HPP

#define ENTITY_HPP

#include<unordered_map>
#include<memory>
#include<typeindex>


#include "Definitions.hpp"
#include "Component.hpp"



class Entity
{
private:

    std::unordered_multimap<std::type_index, std::shared_ptr<Component>> mem_components;

public:
    
    template<class T, typename = enable_if_t<is_base_of_v<Component, T>>>
    std::shared_ptr<T> AddComponent()
    {
        if (GetComponent<T>() != nullptr)throw std::invalid_argument("Component already exists.");

        std::cout << "Component added=" << std::endl;

        const std::shared_ptr<T>& ptr = std::dynamic_pointer_cast<T>(mem_components.insert(std::make_pair(std::type_index(typeid(T)), new T))->second);

        ptr->SetOwner(std::make_shared<Entity>(*this));

        return ptr;
    }
    /*
    template<class T, typename = enable_if_t<is_base_of_v<Component, T>>>
    std::shared_ptr<T> AddComponent()
    {
        return AddComponentImpl<T>()->SetOwner(std::shared_ptr<Entity>(this));
    }*/
    
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



#endif // !ENTITY_HPP

