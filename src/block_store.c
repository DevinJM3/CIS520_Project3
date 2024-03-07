#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include "bitmap.h"
#include "block_store.h"
// include more if you need
typedef struct{
    bitmap_t *bitmap;
    uint8_t data[BLOCK_STORE_NUM_BLOCKS][BLOCK_SIZE_BYTES];
}block_store;

// You might find this handy.  I put it around unused parameters, but you should
// remove it before you submit. Just allows things to compile initially.
#define UNUSED(x) (void)(x)

block_store_t *block_store_create()
{
    block_store *bs = calloc(1, sizeof(block_store));   // Allocate the blockstore with 0 as the data
    if(bs == NULL)
        return NULL;

    bs->bitmap = bitmap_overlay(BLOCK_SIZE_BYTES * 8,  bs->data[BITMAP_START_BLOCK]);
    if(bs->bitmap == NULL){
        free(bs);
        return NULL;
    }
    
    return (block_store_t*)bs;
}

void block_store_destroy(block_store_t *const bs)
{
    if(bs == NULL)
        return;

    bitmap_destroy(((block_store*)bs)->bitmap); // Free the bitmap
    free(bs);                                   // Free the block_store
}
size_t block_store_allocate(block_store_t *const bs)
{
    UNUSED(bs);
    return 0;
}

bool block_store_request(block_store_t *const bs, const size_t block_id)
{
    UNUSED(bs);
    UNUSED(block_id);
    return false;
}

void block_store_release(block_store_t *const bs, const size_t block_id)
{
    UNUSED(bs);
    UNUSED(block_id);
}

size_t block_store_get_used_blocks(const block_store_t *const bs)
{
    UNUSED(bs);
    return 0;
}

size_t block_store_get_free_blocks(const block_store_t *const bs)
{
    UNUSED(bs);
    return 0;
}

size_t block_store_get_total_blocks()
{
    return 0;
}

size_t block_store_read(const block_store_t *const bs, const size_t block_id, void *buffer)
{
    UNUSED(bs);
    UNUSED(block_id);
    UNUSED(buffer);
    return 0;
}

size_t block_store_write(block_store_t *const bs, const size_t block_id, const void *buffer)
{
    UNUSED(bs);
    UNUSED(block_id);
    UNUSED(buffer);
    return 0;
}

block_store_t *block_store_deserialize(const char *const filename)
{
    UNUSED(filename);
    return NULL;
}

size_t block_store_serialize(const block_store_t *const bs, const char *const filename)
{
    UNUSED(bs);
    UNUSED(filename);
    return 0;
}