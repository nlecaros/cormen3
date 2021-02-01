#include	<time.h>
#include	<stdlib.h>
#include	<stdio.h>

static void usage(char* s);
static void generate(int n);

int main(int argc, char** argv) {
	if (argc < 2) {
		usage(argv[0]);
		exit(0);
	}
	int num = strtod(argv[1], NULL);
	generate(num);
}

static void usage(char* s) {
	printf("Usage: %s <number-of-ints>\n", s);
}

static void generate(int num) {
	srand(time(NULL));
	while (num-->0) {
		printf("%d\n", rand());
	}
}

