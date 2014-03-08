dylib
=====

Dynamic library loading experiment. Provides a concise way of wiring up symbol loading.

Host code:

    class FooLibrary : public Library {
      public:
        FooLibrary(std::string path) : Library(path) {}
        Import(double, bar, int /* x */)
        Import(long, baz, int /* x */, int /* y */)
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
    c++  -I. dynlib.cpp -o dynlib
    c++  -fPIC -shared -nostartfiles -o foolib.dylib foolib.cpp
    $ ./dynlib
    Load library foolib.dylib
    Load symbol FooLibrary__bar
    Calling from library foo
    
