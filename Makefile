all: dylib foolib

dylib: dylib.cpp dylib.h
	$(CXX) $(CXXFLAGS) -I. dylib.cpp -o dylib

foolib: foolib.cpp
	$(CXX) $(CXXFLAGS) -fPIC -shared -nostartfiles -o foolib.dylib foolib.cpp

.PHONY: clean
clean:
	-rm -rf dylib foolib.dylib
