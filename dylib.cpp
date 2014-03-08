#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string>

#include <dylib.h>

using namespace std;

class FooLibrary : public Library {
  public:
    FooLibrary(std::string path) : Library(path) {}

    Import(double, bar, int /* x */)
    Import(long, baz, int /* x */, int /* y */)
};

int main(int argc, char** argv) {
  FooLibrary foo("foolib.dylib");
  double y = foo.bar(100);
  return EXIT_SUCCESS;
}
