extern "C" {
	double FooLibrary__bar(int x);
}

#include <stdio.h>

double FooLibrary__bar(int x) {
	printf("Calling from library foo\n");
	return 1.5 * x;
}
