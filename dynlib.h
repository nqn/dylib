#ifndef __DYNLIB_H
#define __DYNLIB_H

#include <string>

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
return name ## _func(EXPAND_CALL(__VA_ARGS__));\
}\
private:\
name ## _func_ptr name ## _func;


class Library {
public:
	Library(std::string path) {
	}
};

class FooLibrary : public Library {
public:
	FooLibrary(std::string& path) : Library(path) {}

	Import(double, bar, int /* x */)
	Import(long, baz, int /* x */, int /* y */)
};

// FooLibrary foo("foo.so");
// int y = foo.bar(x);

#endif
