dylib
=====

Dynamic library loading experiment. Provides a concise way of wiring up symbol loading.

Host code:

    class FooLibrary : public Library {
      public:
        FooLibrary(std::string path) : Library(path) {}
        Import(double /* return type */, bar, int /* x */)
        // Add as many Import's as you want.
    };
    ...
    FooLibrary foo("foolib.dylib");
    double y = foo.bar(100);
    ...

Library code:

    extern "C" {
      double FooLibrary__bar(int x);
    }
    double FooLibrary__bar(int x) {
      return 1.5 * x;
    }

### Build instructions

    $ make
    c++  -I. dylib.cpp -o dylib
    c++  -fPIC -shared -nostartfiles -o foolib.dylib foolib.cpp
    $ ./dylib
    Load library foolib.dylib
    Load symbol FooLibrary__bar
    Calling from library foo
    
