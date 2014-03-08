all: dynlib

dynlib: dynlib.cpp dynlib.h
	$(CXX) $(CXXFLAGS) -I. dynlib.cpp -o dynlib
