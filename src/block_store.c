#include <stdio.h>
#include <stdint.h>
#include "bitmap.h"
#include "block_store.h"
// include more if you need

// You might find this handy.  I put it around unused parameters, but you should
// remove it before you submit. Just allows things to compile initially.
#define UNUSED(x) (void)(x)

typedef struct block{
    uint8_t block[BLOCK_SIZE_BYTES];
}block_t;

typedef struct block_store{
    block_t blocks[BLOCK_STORE_NUM_BLOCKS]; //storage for the block data
    bitmap_t *bitmap; //tracks blocks in use
}block_store_t;

block_store_t *block_store_create()
{
    //allocating mem for the struct
    block_store_t *bs = (block_store_t *)malloc(sizeof(block_store_t));
    //null check
    if(!bs){
        return NULL;
    }
    memset(bs, 0, sizeof(block_store_t));

    //initializing bitmap
    bs->bitmap = bitmap_create(BLOCK_STORE_NUM_BLOCKS);
    //if it fails...
    if(!bs->bitmap){
        free(bs);
        return NULL;
    }

    return bs;
}

void block_store_destroy(block_store_t *const bs)
{
    UNUSED(bs);
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