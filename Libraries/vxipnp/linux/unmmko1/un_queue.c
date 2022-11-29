#include "un_queue.h"

#include <string.h>

#define DEFAULT_QUEUE_CAPACITY 10

typedef struct un_queue_impl {
    //! Размер одного элемента в байтах
    size_t element_size;
    //! Ёмкость очереди в количестве элементов
    size_t capacity;
    //! Позиция первого элемента (количество элементов, начиная с 0)
    size_t head;
    //! Размер очереди (количество элементов)
    size_t size;
    //! Память под элементы очереди
    char* data;
} un_queue_impl;

un_queue* un_queue_create(size_t element_size) {
    un_queue_impl* impl = (un_queue_impl*)malloc(sizeof(un_queue_impl));
    impl->element_size = element_size;
    impl->capacity = DEFAULT_QUEUE_CAPACITY;
    impl->head = 0;
    impl->size = 0;
    impl->data = NULL;
    if (0 != impl->element_size)
        impl->data = (char*)malloc((size_t)(impl->element_size * impl->capacity));

    return (un_queue*)impl;
}

void un_queue_destroy(un_queue* queue) {
    un_queue_impl* impl = (un_queue_impl*)queue;
    if (NULL == impl)
        return;

    free(impl->data);
    free(impl);
}

void un_queue_clear(un_queue* queue) {
    un_queue_impl* impl = (un_queue_impl*)queue;
    if (NULL == impl)
        return;

    impl->head = 0;
    impl->size = 0;
}

size_t un_queue_size(un_queue* queue) {
    un_queue_impl* impl = (un_queue_impl*)queue;
    return (NULL != impl) ? impl->size : 0;
}

size_t un_queue_capacity(un_queue* queue) {
    un_queue_impl* impl = (un_queue_impl*)queue;
    return (NULL != impl) ? impl->capacity : 0;
}

void un_queue_shrink_to_size(un_queue* queue) {
    un_queue_impl* impl = (un_queue_impl*)queue;
    if (NULL != impl && impl->size != impl->capacity) {
        char* shrank_data = (char*)malloc((size_t)(impl->element_size * impl->size));
        if (NULL == shrank_data)
            return;

        // Если данные переходят через конец массива, то копируем их по частям
        if (impl->head + impl->size > impl->capacity) {
            memcpy(shrank_data, impl->data + impl->head * impl->element_size,
                   (impl->capacity - impl->head) * impl->element_size);
            memcpy(shrank_data + (impl->capacity - impl->head) * impl->element_size, impl->data,
                   ((impl->head + impl->size) % impl->capacity) * impl->element_size);
        }
        // Иначе - можно за один раз скопировать
        else {
            memcpy(shrank_data, impl->data + impl->head * impl->element_size,
                   impl->size * impl->element_size);
        }

        free(impl->data);
        impl->head = 0;
        impl->data = shrank_data;
        impl->capacity = impl->size;
    }
}

bool un_queue_get(un_queue* queue, size_t index, void* pointer_to_element) {
    un_queue_impl* impl = (un_queue_impl*)queue;
    if (NULL == impl || NULL == pointer_to_element || index >= impl->size)
        return false;

    memcpy(pointer_to_element, impl->data + ((impl->head + index) % impl->capacity) * impl->element_size, impl->element_size);
    return true;
}

bool un_queue_first(un_queue* queue, void* pointer_to_element) {
    un_queue_impl* impl = (un_queue_impl*)queue;
    if (NULL == impl || NULL == pointer_to_element || 0 == impl->size)
        return false;

    memcpy(pointer_to_element, impl->data + impl->head * impl->element_size, impl->element_size);
    return true;
}

bool un_queue_push_back(un_queue* queue, void* pointer_to_element) {
    un_queue_impl* impl = (un_queue_impl*)queue;
    if (NULL == impl || NULL == pointer_to_element)
        return false;

    // Если недостаточно места для добавления нового элемента, то добавляем память
    if (impl->size == impl->capacity) {
        size_t increased_capacity = impl->capacity * 2;
        char* increased_data = (char*)malloc((size_t)(impl->element_size * increased_capacity));
        if (NULL == increased_data)
            return false;

        // Если данные переходят через конец массива, то копируем их по частям
        if (impl->head + impl->size > impl->capacity) {
            memcpy(increased_data, impl->data + impl->head * impl->element_size,
                   (impl->capacity - impl->head) * impl->element_size);
            memcpy(increased_data + (impl->capacity - impl->head) * impl->element_size, impl->data,
                   ((impl->head + impl->size) % impl->capacity) * impl->element_size);
        }
        // Иначе - можно за один раз скопировать
        else {
            memcpy(increased_data, impl->data + impl->head * impl->element_size,
                   impl->size * impl->element_size);
        }

        free(impl->data);
        impl->head = 0;
        impl->data = increased_data;
        impl->capacity = increased_capacity;
    }

    // Рассчитываем позицию для добавления элемента и делаем это
    {
        size_t index_to_insert = (impl->head + impl->size) % impl->capacity;
        memcpy(impl->data + (index_to_insert * impl->element_size), pointer_to_element, impl->element_size);
        ++impl->size;
    }

    return true;
}

bool un_queue_pop_first(un_queue* queue, void* pointer_to_element) {
    un_queue_impl* impl = (un_queue_impl*)queue;
    if (NULL == impl || 0 == impl->size)
        return false;

    if (NULL != pointer_to_element)
        memcpy(pointer_to_element, impl->data + impl->head * impl->element_size, impl->element_size);

    ++impl->head;
    --impl->size;

    if (impl->head == impl->capacity)
        impl->head = 0;

    return true;
}
