#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void wait_5_seconds()
{
	clock_t start = clock();
	double duration = 5.0;

	while (((double)(clock() - start) / CLOCKS_PER_SEC) < duration) {
		// do nothing
	}
}

int main()
{
	cpu_set_t mask;

	pid_t pid = getpid();
	printf("%d\n", pid);

	FILE *file;
	char path[64];
	char buffer[1024];

	for (int i = 0; i < 4; i++) {
		CPU_ZERO(&mask);
		CPU_SET(i, &mask);
		sched_setaffinity(0, sizeof(mask), &mask);

		printf("START on CPU %d\n", i);
		wait_5_seconds();

		snprintf(path, sizeof(path), "/proc/%d/schedstat", pid);
		file = fopen(path, "r");
		fgets(buffer, sizeof(buffer), file);

		printf("%s", buffer);

		wait_5_seconds();

		fclose(file);
		printf("END\n");
	}
	return 0;
}