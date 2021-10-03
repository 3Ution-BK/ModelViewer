#ifndef MODELVIEWER_HASH_HASH_HPP_
#define MODELVIEWER_HASH_HASH_HPP_

#include "Utils/PreDefine.hpp"

#include <cstdint>

/**
 * \brief The namespace represent the hash functions.
 *
 * This namespace tend to provide fast hash functions for performance needs.
 *
 * std::hash doesn't provide the same algorithm across the compilers, it may
 * have different calculation speed. This class tend to provide the same hash
 * function algorithm across the compilers.
 *
 * \par Refactor:
 * We don't use inheritance in here as it will provide virtual table, which
 * might cause loads of cache misses. In such performance needs, we decide not
 * to use inheritance and let every class has the same code across the file.
 */
namespace Hash
{

/**
 * \brief FNV
 *
 * Fowler-Noll-Vo hash function.
 *
 * https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
 *
 * Use it as the fallback for MurmurHash2.
 */
namespace FNV
{

/**
 * \brief FNV1a
 *
 * FNV-1a implementation.
 *
 * \tparam type Any type.
 * \tparam prime Specified prime number.
 * \tparam offsetBasis Specified offset basis.
 */
template <typename type, size_t prime, size_t offsetBasis>
class FNV1a
{
public:
    size_t operator()(const type &x) const { return hashImpl(&x, sizeof(x)); }
    uint64_t operator()(type *x) const
    {
        auto pointer{reinterpret_cast<std::uintptr_t>(x)};
        return hashImpl(&pointer, sizeof(pointer));
    }

private:
    inline size_t hashImpl(unsigned char x, size_t hash) const
    {
        return (hash ^ x) * prime;
    }

    size_t hashImpl(const void *value, size_t bytes) const
    {
        if (!value || bytes == 0)
        {
            return 0;
        }

        size_t hash{offsetBasis};

        const unsigned char *data = static_cast<const unsigned char *>(value);

        while (bytes != 0)
        {
            hash = hashImpl(*data, hash);
            ++data;
            --bytes;
        }

        return hash;
    }
};

#if defined(PROGRAM_ENVIRONMENT_64BIT)

/**
 * \brief FNV1a64Bits
 *
 * Suited for 64bit architecture.
 * Covered by PROGRAM_ENVIRONMENT_64BIT macro to prevent the 32bit architecture
 * from compile it.
 *
 * \tparam type Any type.
 */
template <typename type>
using FNV1a64Bits = FNV1a<type, 0x00000100000001B3, 0xcbf29ce484222325>;

#endif

#if defined(PROGRAM_ENVIRONMENT_32BIT)

/**
 * \brief FNV1a32Bits
 *
 * Suited for 32bit architecture.
 * Covered by PROGRAM_ENVIRONMENT_32BIT macro to prevent the 64bit architecture
 * from compile it.
 *
 * \tparam type Any type.
 */
template <typename type>
using FNV1a32Bits = FNV1a<type, 0x01000193, 0x811c9dc5>;

#endif

} // namespace FNV

/**
 * \brief MurmurHash2
 *
 * MurmurHash2 function
 * https://en.wikipedia.org/wiki/MurmurHash
 *
 * Modified from https://github.com/aappleby/smhasher which declaims the
 * MurmurHash version is under public domain.
 */
namespace MurmurHash2
{

#if defined(PROGRAM_ENVIRONMENT_64BIT)

/**
 * \brief MurmurHash64A
 *
 * Suited for 64bit architecture.
 * Covered by PROGRAM_ENVIRONMENT_64BIT macro to prevent the 32bit architecture
 * from compile it.
 *
 * \tparam type Any type.
 * \tparam seed Specified seed number.
 */
template <typename type, uint64_t seed = 0>
class MurmurHash64A
{
public:
    uint64_t operator()(const type &x) const { return hashImpl(&x, sizeof(x)); }
    uint64_t operator()(type *x) const
    {
        auto pointer{reinterpret_cast<std::uintptr_t>(x)};
        return hashImpl(&pointer, sizeof(pointer));
    }

private:
    const uint64_t multiply = 0xc6a4a7935bd1e995LLU;
    const int rotate = 47;

    uint64_t hashImpl(const void *value, size_t bytes) const
    {
        uint64_t hash{seed ^ (bytes * multiply)};

        const uint64_t *buffer{static_cast<const uint64_t *>(value)};
        const uint64_t *end{buffer + (bytes / 8)};

        while (buffer != end)
        {
            const uint64_t *pointTo{++buffer};
            uint64_t key{*pointTo};

            key *= multiply;
            key ^= key >> rotate;
            key *= multiply;

            hash ^= key;
            hash *= multiply;
        }

        const unsigned char *data{
            reinterpret_cast<const unsigned char *>(buffer)};

        switch (bytes & 7)
        {
        case 7:
            hash ^= static_cast<uint64_t>(data[6]) << 48;
            PROGRAM_FALLTHROUGH;
        case 6:
            hash ^= static_cast<uint64_t>(data[5]) << 40;
            PROGRAM_FALLTHROUGH;
        case 5:
            hash ^= static_cast<uint64_t>(data[4]) << 32;
            PROGRAM_FALLTHROUGH;
        case 4:
            hash ^= static_cast<uint64_t>(data[3]) << 24;
            PROGRAM_FALLTHROUGH;
        case 3:
            hash ^= static_cast<uint64_t>(data[2]) << 16;
            PROGRAM_FALLTHROUGH;
        case 2:
            hash ^= static_cast<uint64_t>(data[1]) << 8;
            PROGRAM_FALLTHROUGH;
        case 1:
            hash ^= static_cast<uint64_t>(data[0]);
            hash *= multiply;
        };

        hash ^= hash >> rotate;
        hash *= multiply;
        hash ^= hash >> rotate;

        return hash;
    }
};

#endif

#if defined(PROGRAM_ENVIRONMENT_32BIT)

/**
 * \brief MurmurHash2
 *
 * Suited for 32bit architecture.
 * Covered by PROGRAM_ENVIRONMENT_64BIT macro to prevent the 64bit architecture
 * from compile it.
 *
 * \tparam type Any type.
 * \tparam seed Specified seed number.
 */

template <typename type, uint32_t seed = 0>
class MurmurHash2
{
public:
    uint64_t operator()(const type &x) const { return hashImpl(&x, sizeof(x)); }
    uint64_t operator()(type *x) const
    {
        auto pointer{reinterpret_cast<std::uintptr_t>(x)};
        return hashImpl(&pointer, sizeof(pointer));
    }

private:
    const uint32_t multiply = 0x5bd1e995;
    const int rotate = 24;

    uint64_t hashImpl(const void *value, size_t bytes) const
    {
        uint32_t hash{seed ^ bytes};
        const unsigned char *buffer{static_cast<const unsigned char *>(value)};

        while (bytes >= 4)
        {
            uint32_t key{*(reinterpret_cast<const uint32_t *>(buffer))};

            key *= multiply;
            key ^= key >> rotate;
            key *= multiply;

            hash *= multiply;
            hash ^= key;

            buffer += 4;
            bytes -= 4;
        }

        switch (bytes)
        {
        case 3:
            hash ^= buffer[2] << 16;
        case 2:
            hash ^= buffer[1] << 8;
        case 1:
            hash ^= buffer[0];
            hash *= multiply;
        }

        hash ^= hash >> 13;
        hash *= multiply;
        hash ^= hash >> 15;
        return hash;
    }
};

#endif

} // namespace MurmurHash2

/**
 * \class FastHash
 * \brief General hash function for fast calculation.
 *
 * \tparam type Any type.
 */

#if defined(PROGRAM_ENVIRONMENT_64BIT)

template <typename type>
using FastHash = MurmurHash2::MurmurHash64A<type>;

#else

template <typename type>
using FastHash = MurmurHash2::MurmurHash2<type>;

#endif

} // namespace Hash

#endif // MODELVIEWER_HASH_HASH_HPP_
