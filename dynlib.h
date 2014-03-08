#ifndef __DYNLIB_H
#define __DYNLIB_H

#include <dlfcn.h>
#include <assert.h>
#include <string>
#include <iostream>
#include <map>
#include <cxxabi.h>

#define EXPAND_PARAM0()
#define EXPAND_PARAM1(type0) type0 arg0
#define EXPAND_PARAM2(type0, type1) type0 arg0, type1 arg1
#define GET_MACRO(_0, _1, _2, NAME, ...) NAME
#define EXPAND_PARAM(...) GET_MACRO(_0, ##__VA_ARGS__, EXPAND_PARAM2, EXPAND_PARAM1, EXPAND_PARAM0)(__VA_ARGS__)

#define EXPAND_CALL0()
#define EXPAND_CALL1(type0) arg0
#define EXPAND_CALL2(type0, type1) arg0, arg1
#define EXPAND_CALL(...) GET_MACRO(_0, ##__VA_ARGS__, EXPAND_CALL2, EXPAND_CALL1, EXPAND_CALL0)(__VA_ARGS__)

#define Import(ret, symbol, ...) \
public:\
typedef ret (*symbol ## _func_ptr)(__VA_ARGS__);\
ret symbol(EXPAND_PARAM(__VA_ARGS__)) {\
std::map<std::string, void*>::iterator it = loadedSymbols.find(#symbol);\
symbol ## _func_ptr func = NULL;\
if (it == loadedSymbols.end()) {\
	int status;\
	func = (symbol ## _func_ptr)load(std::string(abi::__cxa_demangle(typeid(*this).name(),0,0,&status)).append("__" #symbol));\
	loadedSymbols.insert(std::pair<std::string, void*>(#symbol, (void*)func));\
} else {\
	func = (symbol ## _func_ptr)it->second;\
}\
assert(func != NULL);\
return func(EXPAND_CALL(__VA_ARGS__));\
}


class Library {
public:
	Library(std::string path) {
		std::cout << "Load library " << path << std::endl;
		handle = dlopen(path.c_str(), RTLD_LAZY);
		if (!handle) {
			fprintf(stderr, "%s\n", dlerror());
			exit(EXIT_FAILURE);
		}

		dlerror();
	}

	~Library() {
		dlclose(handle);
	}

protected:
	void* load(std::string symbol) {
		std::cout << "Load symbol " << symbol << std::endl;
		void* sym = dlsym(handle, symbol.c_str());

		char* error = NULL;
		if ((error = dlerror()) != NULL)  {
			fprintf(stderr, "%s\n", error);
			return NULL;
		}

		return sym;
	}

	std::map<std::string, void*> loadedSymbols;
	void* handle;
};


#endif
