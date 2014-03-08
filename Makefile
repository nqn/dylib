all: dynlib foolib

dynlib: dynlib.cpp dynlib.h
	$(CXX) $(CXXFLAGS) -I. dynlib.cpp -o dynlib

foolib: foolib.cpp
	$(CXX) $(CXXFLAGS) -fPIC -shared -nostartfiles -o foolib.dylib foolib.cpp
