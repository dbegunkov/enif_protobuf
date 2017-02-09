/*
 * Copyright (c) jg_513@163.com, https://github.com/jg513
 */

#ifndef ENIF_PROTO_CODEC_H_INCLUDED
#define ENIF_PROTO_CODEC_H_INCLUDED

#include "enif_protobuf.h"

#define MAX_UINT64_ENCODED_SIZE     10

typedef enum {
    WIRE_TYPE_VARINT = 0,
    WIRE_TYPE_64BIT = 1,
    WIRE_TYPE_LENGTH_PREFIXED = 2,
    /* "Start group" and "end group" wire types are unsupported. */
    WIRE_TYPE_32BIT = 5,
} wire_type_e;

static inline int16_t
swap_int16(int16_t value)
{
    return (value << 8) | ((value >> 8) & 0x00ff);
}

static inline uint16_t
swap_uint16(uint16_t value)
{
    return (value << 8) | (value >> 8);
}

static inline int32_t
swap_int32(int32_t value)
{
    return ((value & 0x000000ff) << 24) |
           ((value & 0x0000ff00) <<  8) |
           ((value & 0x00ff0000) >>  8) |
           ((value >> 24) & 0x000000ff);
}

static inline uint32_t
swap_uint32(uint32_t value)
{
    return ((value & 0x000000ff) << 24) |
           ((value & 0x0000ff00) <<  8) |
           ((value & 0x00ff0000) >>  8) |
           (value >> 24);
}

static inline int64_t
swap_int64(int64_t value)
{
    return ((value & 0x00000000000000ffUL) << 56) |
           ((value & 0x000000000000ff00UL) << 40) |
           ((value & 0x0000000000ff0000UL) << 24) |
           ((value & 0x00000000ff000000UL) <<  8) |
           ((value & 0x000000ff00000000UL) >>  8) |
           ((value & 0x0000ff0000000000UL) >> 24) |
           ((value & 0x00ff000000000000UL) >> 40) |
           ((value >> 56) & 0x00000000000000ffUL);
}

static inline uint64_t
swap_uint64(uint64_t value)
{
    return ((value & 0x00000000000000ffUL) << 56) |
           ((value & 0x000000000000ff00UL) << 40) |
           ((value & 0x0000000000ff0000UL) << 24) |
           ((value & 0x00000000ff000000UL) <<  8) |
           ((value & 0x000000ff00000000UL) >>  8) |
           ((value & 0x0000ff0000000000UL) >> 24) |
           ((value & 0x00ff000000000000UL) >> 40) |
           (value >> 56);
}

/*
 * encode
 */
ERL_NIF_TERM
encode(ErlNifEnv *env, ERL_NIF_TERM term, tdata_t *tdata);

/*
 * decode
 */

#endif