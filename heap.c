// Beatriz Torres Archundia
// CPSC 351 - 08
// 10.01.24
// btorre0@csu.fullerton.edu
// Github Username: Btorre0

#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

#define KEY_NOT_PRESENT -1

heap_t *heap_create(int capacity) {
    heap_t *heapCreate = (heap_t *)malloc(sizeof(heap_t));
    heapCreate->data = (heap_node_t *)malloc(capacity * sizeof(heap_node_t));
    heapCreate->size = 0;
    heapCreate->capacity = capacity;
    return heapCreate;
}
// free memory and allocate
void heap_free(heap_t *heap) {
    free(heap->data);
    free(heap);
}

unsigned int heap_size(heap_t *heap) { return heap->size; }

// complete the all empty ones
unsigned int heap_parent(unsigned int index) { return ((index - 1) / 2); }

unsigned int heap_left_child(unsigned int index) { return ((index * 2) + 1); }

unsigned int heap_right_child(unsigned int index) { return ((index * 2) + 2); }

unsigned int heap_level(unsigned int index) {
    unsigned int level = 0;
    while (index > 0) {
        index = (index - 1) / 2;
        level++;
    }
    return level;
}

void heap_print(heap_t *heap) {
    for (int ix = 0; ix < heap_size(heap); ix++) {
        printf("%3d - %3d : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix,
               heap->data[ix].key);
    }
    printf("\n");
}

void heap_swap(heap_t *heap, int index1, int index2) {
    heap_node_t swapping = heap->data[index1];
    heap->data[index1] = heap->data[index2];
    heap->data[index2] = swapping;
}

// swap index to parent, parent to temp, return heap, parent
void heap_bubble_up(heap_t *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (heap->data[index].key < heap->data[parent].key) {
            heap_swap(heap, index, parent);
            index = parent;
        } else {
            break;
        }
    }
}

void heap_bubble_down(heap_t *heap, int index) {
    int rightchild = (2 * index) + 2;
    int leftchild = (2 * index) + 1;

    int placeHolder = index;

    if ((leftchild < heap_size(heap)) &&
        (heap->data[leftchild].key < heap->data[placeHolder].key)) {
        placeHolder = leftchild;
    }

    if (rightchild < heap_size(heap)) {
        placeHolder = rightchild;
    }

    if ((placeHolder != index) &&
        (heap->data[rightchild].key < heap->data[placeHolder].key)) {
        heap_swap(heap, index, placeHolder);
        heap_bubble_down(heap, placeHolder);
    }
}

void heap_insert(heap_t *heap, heap_key_t key, heap_value_t data) {
    if (heap_size(heap) == heap->capacity) {
        return;
    }

    heap->data[heap_size(heap)].key = key;
    heap->data[heap_size(heap)].value = data;
    heap->size++;

    heap_bubble_up(heap, heap_size(heap) - 1);
}

heap_value_t heap_remove_min(heap_t *heap) {
    if (heap_size(heap) == 0) {
        return NULL;
    }

    heap_value_t min = heap->data[0].value;

    heap->size--;

    // move last element to the root
    heap->data[0] = heap->data[heap_size(heap)];

    // then bubble it down to its correct position
    heap_bubble_down(heap, 0);

    return min;
}