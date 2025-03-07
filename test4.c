#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

void busy_wait_5_seconds()
{
	clock_t start = clock();
	double duration = 5.0;

	while (((double)(clock() - start) / CLOCKS_PER_SEC) < duration) {
		// Busy wait (consume CPU)
	}
}

void idle_wait_5_seconds()
{
	sleep(5); // Idle wait (does not consume CPU)
}

void read_schedstat(pid_t pid, unsigned long *epoch_ticks,
		    unsigned long *used_cpus)
{
	FILE *file;
	char path[64];
	char buffer[1024];

	snprintf(path, sizeof(path), "/proc/%d/schedstat", pid);
	file = fopen(path, "r");
	if (!file) {
		perror("Failed to open schedstat");
		exit(EXIT_FAILURE);
	}

	fgets(buffer, sizeof(buffer), file);
	fclose(file);

	// Assuming schedstat contains epoch_ticks and used_cpus in expected format
	sscanf(buffer, "%lu %lu", epoch_ticks, used_cpus);
}

int main()
{
	cpu_set_t mask;
	pid_t pid = getpid();
	printf("Process ID: %d\n", pid);

	for (int i = 0; i < 4; i++) {
		CPU_ZERO(&mask);
		CPU_SET(i, &mask);
		sched_setaffinity(0, sizeof(mask), &mask);

		printf("\nSTART on CPU %d (Busy Wait)\n", i);

		unsigned long start_ticks, start_used_cpus, end_ticks,
			end_used_cpus;

		read_schedstat(pid, &start_ticks, &start_used_cpus);
		busy_wait_5_seconds();
		read_schedstat(pid, &end_ticks, &end_used_cpus);

		printf("Before: epoch_ticks=%lu, used_cpus=%lu\n", start_ticks,
		       start_used_cpus);
		printf("After:  epoch_ticks=%lu, used_cpus=%lu\n", end_ticks,
		       end_used_cpus);

		if (end_ticks > start_ticks &&
		    end_used_cpus != start_used_cpus) {
			printf("PASS: Busy waiting increased epoch_ticks and updated used_cpus.\n");
		} else {
			printf("FAIL: Busy waiting did not affect expected values!\n");
		}

		printf("\nSTART on CPU %d (Idle Wait)\n", i);

		read_schedstat(pid, &start_ticks, &start_used_cpus);
		idle_wait_5_seconds();
		read_schedstat(pid, &end_ticks, &end_used_cpus);

		printf("Before: epoch_ticks=%lu, used_cpus=%lu\n", start_ticks,
		       start_used_cpus);
		printf("After:  epoch_ticks=%lu, used_cpus=%lu\n", end_ticks,
		       end_used_cpus);

		if (end_ticks == start_ticks &&
		    end_used_cpus == start_used_cpus) {
			printf("PASS: Idle waiting did not change epoch_ticks or used_cpus.\n");
		} else {
			printf("FAIL: Idle waiting affected values unexpectedly!\n");
		}
	}

	return 0;
}
