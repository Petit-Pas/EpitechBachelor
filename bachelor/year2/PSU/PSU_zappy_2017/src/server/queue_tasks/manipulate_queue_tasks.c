/*
** EPITECH PROJECT, 2021
** zappy_linked
** File description:
** internal functions
*/

#include <stdlib.h>
#include <memory.h>
#include <stdio.h>
#include "zappy_server_structs.h"

/**
 * push a task in the task queue
 * @param queue the task quue
 * @param task the task to push
 * @return -1 if the task was full, 0 otherwise
 */

int push_task(queue_tasks_t *queue, task_t *task)
{
	if (queue->size == MAX_QUEUE_SIZE)
		return -1;
	memcpy(&queue->tasks[queue->size], task, sizeof(task_t));
	queue->size += 1;
	return 0;
}

/**
 * gets a pointer to the first task to achieve
 * @param queue que task queue
 * @return a pointer to the wanted task
 */

task_t *get_head_queue(queue_tasks_t *queue)
{
	return &(queue->tasks[0]);
}

/**
 * remove the first element of the task
 * @param queue the task queue
 */

void pop_task(queue_tasks_t *queue)
{
	free(queue->tasks[0].additional_informations);
	for (int i = 0; i != MAX_QUEUE_SIZE - 1; i++)
		memcpy(&queue->tasks[i], &queue->tasks[i + 1], sizeof(task_t));
	memset(&queue->tasks[MAX_QUEUE_SIZE - 1], 0, sizeof(task_t));
	queue->size -= 1;
}
