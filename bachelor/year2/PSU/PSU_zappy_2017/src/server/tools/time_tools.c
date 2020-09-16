/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <time.h>
#include <stdio.h>
#include "zappy_server_structs.h"

/**
 * update the timer by increasing last "checkpoint" by delta time
 * @param timer struct containing every needed information:
 * last_checkpoint.sec last_checkpoint.nsec and delta(nanoseconds)
 */

static void update_timer(zappy_timer_t *timer)
{
	if (timer->nano_seconds + timer->delta_size >= 1000000000) {
		timer->nano_seconds =
			(timer->nano_seconds + timer->delta_size) % 1000000000;
		timer->seconds += 1;
	} else {
		timer->nano_seconds += timer->delta_size;
	}
}

/**
 * checks if delta time has elapsed
 * @param timer the struct containing time information,
 * it is updated if the condition is true
 * @return 1 if time was elapsed, 0 otherwise
 */

int is_elapsed_time(zappy_timer_t *timer)
{
	struct timespec time;

	clock_gettime(CLOCK_MONOTONIC_RAW, &time);
	if (time.tv_sec != timer->seconds ||
		time.tv_nsec - timer->delta_size >= timer->nano_seconds) {
		update_timer(timer);
		return 1;
	}
	return 0;
}
