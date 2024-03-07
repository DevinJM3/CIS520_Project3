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

    bs->bitmap = bitmap_overlay(BITMAP_SIZE_BYTES * 8,  bs->data[BITMAP_START_BLOCK]);
    if(bs->bitmap == NULL){
        free(bs);
        return NULL;
    }

    if(block_store_request((block_store_t*)bs, BITMAP_START_BLOCK))   // If it can allocate the start block
        return (block_store_t*)bs;
    else{                                           // Unable to allocate the start block
        block_store_destroy((block_store_t*)bs); 
        return NULL;
    }
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
    if(bs == NULL)
        return SIZE_MAX;

    size_t available_index = bitmap_ffz(((block_store*)bs)->bitmap);    // Get the index of the next available block
    if(available_index == SIZE_MAX)
        return SIZE_MAX;
    
    if(block_store_request(bs, available_index))
        return available_index; // Index of newly allocated block
    else
        return SIZE_MAX;        // No more blocks left to allocate
}

bool block_store_request(block_store_t *const bs, const size_t block_id)
{
    if(bs == NULL || block_id > BLOCK_STORE_NUM_BLOCKS)     // If the block_store is invalid or the id is bigger than the max size
        return false;

    if(bitmap_test(((block_store*)bs)->bitmap, block_id))   // If the index block_id has been set in the bitmap (already allocated)
        return false;
    
    bitmap_set(((block_store*)bs)->bitmap, block_id);                       // Set the block_id bitmap
    return bitmap_test(((block_store*)bs)->bitmap, BITMAP_START_BLOCK);     // Return true if it was successfull, else false
}

void block_store_release(block_store_t *const bs, const size_t block_id)
{
    if(bs == NULL || block_id > BLOCK_STORE_NUM_BLOCKS)
        return;
    
    bitmap_reset(((block_store*)bs)->bitmap, block_id);
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
    return BLOCK_STORE_NUM_BLOCKS;
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