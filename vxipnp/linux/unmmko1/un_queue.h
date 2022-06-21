#ifndef UN_QUEUE_H
#define UN_QUEUE_H

#include <vpptype.h>
#include <stdlib.h>
#include <stdbool.h>

//! Расширяемая очередь (FIFO)
typedef struct un_queue un_queue;

un_queue* un_queue_create(size_t element_size);
void un_queue_destroy(un_queue* queue);
void un_queue_clear(un_queue* queue);

size_t un_queue_size(un_queue* queue);
size_t un_queue_capacity(un_queue* queue);
void un_queue_shrink_to_size(un_queue* queue);
bool un_queue_get(un_queue* queue, size_t index, void* pointer_to_element);
bool un_queue_first(un_queue* queue, void* pointer_to_element);

bool un_queue_push_back(un_queue* queue, void* pointer_to_element);
bool un_queue_pop_first(un_queue* queue, void* pointer_to_element);

#endif // UN_QUEUE_H
