#ifndef DEFINITIONS_HPP

#define DEFINITIONS_HPP

#include<string>
#include<map>
#include "raylib.h"
#include<memory>

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

	std::map<std::string, std::string> pairs;

	void ChangeVariableByName(const std::string &name, const std::string &value)
	{
		pairs[name] = value;
	}
	void AddVariable(const std::string &name, const std::string  &value)
	{
		pairs.insert(std::make_pair(name, value));
	}
	void RemoveVariable(const std::string &name)
	{
		pairs.erase(name);
	}
};

struct Name_LinkedVariable_Tuple
{
public:

	std::map<std::string, std::shared_ptr<std::string>> pairs;

	void AddVariable(const std::string& name, const std::shared_ptr<std::string> &s_ptr)
	{
		pairs.insert(std::make_pair(name, s_ptr));
	}
	void RemoveVariable(const std::string& name)
	{
		pairs.erase(name);
	}
};


//c++ 17 standard
template< class Base, class Derived >
inline constexpr bool is_base_of_v = std::is_base_of<Base, Derived>::value;

template< bool B, class T = void >
using enable_if_t = typename std::enable_if<B, T>::type;

#endif // !DEFINITIONS_HPP

