#ifndef __DYNLIB_H
#define __DYNLIB_H

#include <assert.h>
#include <string>
#include <iostream>
#include <map>

#define EXPAND_PARAM0()
#define EXPAND_PARAM1(type0) type0 arg0
#define EXPAND_PARAM2(type0, type1) type0 arg0, type1 arg1
#define GET_MACRO(_0, _1, _2, NAME, ...) NAME
#define EXPAND_PARAM(...) GET_MACRO(_0, ##__VA_ARGS__, EXPAND_PARAM2, EXPAND_PARAM1, EXPAND_PARAM0)(__VA_ARGS__)

#define EXPAND_CALL0()
#define EXPAND_CALL1(type0) arg0
#define EXPAND_CALL2(type0, type1) arg0, arg1
#define EXPAND_CALL(...) GET_MACRO(_0, ##__VA_ARGS__, EXPAND_CALL2, EXPAND_CALL1, EXPAND_CALL0)(__VA_ARGS__)

#define Import(ret, name, ...) \
public:\
typedef ret (*name ## _func_ptr)(__VA_ARGS__);\
ret name(EXPAND_PARAM(__VA_ARGS__)) {\
std::map<std::string, void*>::iterator it = loadedSymbols.find(#name);\
name ## _func_ptr func = NULL;\
if (it == loadedSymbols.end()) {\
	func = (name ## _func_ptr)load(#name);\
	loadedSymbols.insert(std::pair<std::string, void*>(#name, (void*)func));\
} else {\
	func = (name ## _func_ptr)it->second;\
}\
assert(func != NULL);\
return func(EXPAND_CALL(__VA_ARGS__));\
}


class Library {
public:
	Library(std::string path) {
		std::cout << "Load library " << path << std::endl;
	}

protected:
	void* load(std::string symbol) {
		std::cout << "Load symbol " << symbol << std::endl;
		return NULL;
	}

	std::map<std::string, void*> loadedSymbols;
};

class FooLibrary : public Library {
public:
	FooLibrary(std::string path) : Library(path) {}

	Import(double, bar, int /* x */)
	Import(long, baz, int /* x */, int /* y */)
};

#endif
