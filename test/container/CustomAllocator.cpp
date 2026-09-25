
/*


#include <sys/mman.h>
#include <stddef.h>
#include <string.h>

#define ALIGN 16
#define CHUNK_SIZE (1 << 20)   // 1 MB

typedef struct Block {
    size_t size;        // total block size, low bit = free flag
    struct Block* next;
    struct Block* prev;
} Block;

static Block* free_head = NULL;

static size_t align_up(size_t n) { return (n + ALIGN - 1) & ~(ALIGN - 1); }

static Block* request_chunk(size_t need) {
    size_t sz = need > CHUNK_SIZE ? align_up(need) : CHUNK_SIZE;
    Block* b = mmap(NULL, sz, PROT_READ | PROT_WRITE,
                    MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (b == MAP_FAILED) return NULL;
    b->size = sz;
    b->next = b->prev = NULL;
    return b;
}

static void insert_free(Block* b) {
    b->size |= 1;             // mark free
    b->next = free_head;
    b->prev = NULL;
    if (free_head) free_head->prev = b;
    free_head = b;
}

static void remove_free(Block* b) {
    if (b->prev) b->prev->next = b->next;
    else free_head = b->next;
    if (b->next) b->next->prev = b->prev;
    b->size &= ~1;            // mark allocated
}

void* my_alloc(size_t n) {
    size_t need = align_up(n + sizeof(Block));
    // first-fit search
    for (Block* b = free_head; b; b = b->next) {
        if ((b->size & ~1) >= need) {
            remove_free(b);
            return (char*)b + sizeof(Block);
        }
    }
    // no fit — get a new chunk
    Block* b = request_chunk(need);
    if (!b) return NULL;
    b->size &= ~1;            // allocated
    return (char*)b + sizeof(Block);
}

void my_free(void* p) {
    if (!p) return;
    Block* b = (Block*)((char*)p - sizeof(Block));
    insert_free(b);
    // naive coalescing omitted for brevity: check neighbors by address
}


*/