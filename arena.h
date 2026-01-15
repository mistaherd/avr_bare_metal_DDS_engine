#ifndef ARENA_H
#define ARENA_H
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#endif // ARENA_H

#ifdef ARENA_IMPLEMENTATION
typedef struct {
        uint8_t *base;// starting address of arena
        size_t size;
        size_t used;
}Arena;

Arena *arena_init(size_t size){
    Arena *arena=malloc(sizeof(Arena));
    if (!arena) return NULL;
    
    arena->base=malloc(size);
    if (!arena->base){
        free(arena);
        return NULL;
    }
    arena->size=size;
    arena->used=0;
    return arena;
}

void *arena_alloc(Arena *arena,size_t size){
    if (arena->used+size >arena->size){
        return NULL;
    }
    void *ptr=arena ->base +arena->used;
    arena->used +=size;
    return ptr;
}
void arena_reset(Arena *arena) {
    arena->used = 0;
}

// Destroy arena and free all memory
void free_arena(Arena *arena) {
    if (!arena) return;
    free(arena->base);
    free(arena);
}
#endif
