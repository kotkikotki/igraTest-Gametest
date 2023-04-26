#ifndef DEFINITIONS_HPP

#define DEFINITIONS_HPP

#include<string>
#include<map>
#include "raylib.h"
#include<memory>
#include<any>

#define SQRT2 1.41421356f

template<typename T> 
T max(T a, T b)
{
	return (a >= b) ? a : b;
}
template<typename T>
T min(T a, T b)
{
	return (a <= b) ? a : b;
}

struct TextureFilePath_ScrollingSpeed_Tuple
{
	std::string filePath = "";
	float scrollingSpeed = 0.f;
};

struct Texture_ScrollingSpeed_Tuple
{
	Texture2D texture = { 0 };
	float scrollingSpeed = 0.f;
};

struct Name_Variable_Tuple
{
public:

	std::map<std::string, std::any> pairs;

	bool HasVariable(const std::string& name)
	{
		return pairs.find(name) != pairs.end();
	}
	void ChangeVariableByName(const std::string &name, const std::any &value)
	{
		pairs[name] = value;
	}
	void AddVariable(const std::string &name, const std::any  &value)
	{
		pairs.insert(std::make_pair(name, value));
	}
	void RemoveVariable(const std::string &name)
	{
		pairs.erase(name);
	}
	const std::any& GetVariable(const std::string& name)
	{
		return pairs[name];
	}
};

struct Name_LinkedVariable_Tuple
{
public:

	std::map<std::string, std::shared_ptr<void>> pairs;

	bool HasVariable(const std::string& name)
	{
		return pairs.find(name) != pairs.end();
	}

	template<typename T>
	void ChangeVariableByName(const std::string& name, const std::shared_ptr<void>& s_ptr)
	{
		pairs[name] = s_ptr;
	}

	void AddVariable(const std::string& name, const std::shared_ptr<void> &s_ptr)
	{
		pairs.insert(std::make_pair(name, s_ptr));
	}
	void RemoveVariable(const std::string& name)
	{
		pairs.erase(name);
	}
	const std::shared_ptr<void>& GetVariablePtr(const std::string& name)
	{
		return pairs[name];
	}
	
	/*
	template<typename T>
	const T& GetVariable(const std::string& name)
	{
		return std::any_cast<T>(*std::static_pointer_cast<std::any>(pairs[name]));
	}*/
};


//c++ 17 standard
template< class Base, class Derived >
inline constexpr bool is_base_of_v = std::is_base_of<Base, Derived>::value;

template< bool B, class T = void >
using enable_if_t = typename std::enable_if<B, T>::type;

#endif // !DEFINITIONS_HPP

