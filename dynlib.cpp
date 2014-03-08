#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <string>

#include <dynlib.h>

using namespace std;

int main(int argc, char** argv) {
  FooLibrary foo("foo.so");
  double y = foo.bar(100);
	return EXIT_FAILURE;
}
