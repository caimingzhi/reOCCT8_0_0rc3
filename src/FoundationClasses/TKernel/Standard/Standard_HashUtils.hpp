#pragma once


#include <Standard_Macro.hpp>

#include <cstdint>
#include <cstddef>
#include <functional>
#include <type_traits>

namespace opencascade
{
//! Implementation of Murmur hash with autodetect of sizeof(size_t).
//!
//! The default value for the seed is optimal for general cases at a certain hash size.
namespace MurmurHash
{
uint32_t MurmurHash2A(const void* theKey, int theLen, uint32_t theSeed) noexcept;
uint64_t MurmurHash64A(const void* theKey, int theLen, uint64_t theSeed) noexcept;

template <typename T1, typename T = size_t>
typename std::enable_if<sizeof(T) == 8, uint64_t>::type hash_combine(
  const T1& theValue,
  const int theLen  = sizeof(T1),
  const T   theSeed = 0xA329F1D3A586ULL) noexcept
{
  return MurmurHash::MurmurHash64A(&theValue, theLen, theSeed);
}

template <typename T1, typename T = size_t>
typename std::enable_if<sizeof(T) != 8, T>::type hash_combine(
  const T1& theValue,
  const int theLen  = sizeof(T1),
  const T   theSeed = 0xc70f6907U) noexcept
{
  return static_cast<T>(MurmurHash::MurmurHash2A(&theValue, theLen, theSeed));
}

template <typename T = size_t>
constexpr T optimalSeed() noexcept
{
  return sizeof(T) == 8 ? static_cast<T>(0xA329F1D3A586ULL) : static_cast<T>(0xc70f6907U);
}
}; // namespace MurmurHash

//! Implementation of FNV-1a with autodetect of sizeof(size_t).
//! This function should work on unsigned char, otherwise it does not
//! correctly implement the FNV-1a algorithm.
//! The existing behaviour is retained for backwards compatibility.
//!
//! The default value for the seed is optimal for general cases at a certain hash size.
namespace FNVHash
{
uint32_t FNVHash1A(const void* theKey, int theLen, uint32_t theSeed) noexcept;
uint64_t FNVHash64A(const void* theKey, int theLen, uint64_t theSeed) noexcept;

template <typename T1, typename T = size_t>
static typename std::enable_if<sizeof(T) == 8, uint64_t>::type hash_combine(
  const T1& theValue,
  const int theLen  = sizeof(T1),
  const T   theSeed = 14695981039346656037ULL) noexcept
{
  return FNVHash::FNVHash64A(&theValue, theLen, theSeed);
}

template <typename T1, typename T = size_t>
static typename std::enable_if<sizeof(T) != 8, T>::type hash_combine(
  const T1& theValue,
  const int theLen  = sizeof(T1),
  const T   theSeed = 2166136261U) noexcept
{
  return static_cast<T>(FNVHash::FNVHash1A(&theValue, theLen, theSeed));
}

template <typename T = size_t>
constexpr T optimalSeed() noexcept
{
  return sizeof(T) == 8 ? static_cast<T>(14695981039346656037ULL) : static_cast<T>(2166136261U);
}
}; // namespace FNVHash

template <typename T1, typename T = size_t>
T hash(const T1& theValue) noexcept
{
  return opencascade::MurmurHash::hash_combine<T1, T>(theValue);
}

template <typename T1, typename T = size_t>
T hashBytes(const T1* theKey, int theLen) noexcept
{
  return opencascade::MurmurHash::hash_combine<T1, T>(*theKey, theLen);
}

template <typename T1, typename T = size_t>
T hash_combine(const T1& theValue, const int theLen, const T theSeed) noexcept
{
  return opencascade::MurmurHash::hash_combine<T1, T>(theValue, theLen, theSeed);
}
} // namespace opencascade
// Copyright (c) 2023 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <cstring>

namespace opencascade
{
namespace MurmurHash
{
namespace MurmurHashUtils
{
inline uint64_t shift_mix(uint64_t theV) noexcept
{
  return theV ^ (theV >> 47);
}

// Loads n bytes, where 1 <= n < 8
inline uint64_t load_bytes(const char* thePnt, int theNb) noexcept
{
  // Initialize result value
  uint64_t aResult = 0;

  // Use switch with fall-through for better performance and branch prediction
  switch (theNb)
  {
    case 7:
      aResult = (static_cast<uint64_t>(static_cast<unsigned char>(thePnt[6])) << 48) | aResult;
      [[fallthrough]];
    case 6:
      aResult = (static_cast<uint64_t>(static_cast<unsigned char>(thePnt[5])) << 40) | aResult;
      [[fallthrough]];
    case 5:
      aResult = (static_cast<uint64_t>(static_cast<unsigned char>(thePnt[4])) << 32) | aResult;
      [[fallthrough]];
    case 4:
      aResult = (static_cast<uint64_t>(static_cast<unsigned char>(thePnt[3])) << 24) | aResult;
      [[fallthrough]];
    case 3:
      aResult = (static_cast<uint64_t>(static_cast<unsigned char>(thePnt[2])) << 16) | aResult;
      [[fallthrough]];
    case 2:
      aResult = (static_cast<uint64_t>(static_cast<unsigned char>(thePnt[1])) << 8) | aResult;
      [[fallthrough]];
    case 1:
      aResult = static_cast<uint64_t>(static_cast<unsigned char>(thePnt[0])) | aResult;
      [[fallthrough]];
    default:
      break;
  }

  return aResult;
}

template <typename T>
inline T unaligned_load(const char* thePnt) noexcept
{
  T aRes;
  memcpy(&aRes, thePnt, sizeof(aRes));
  return aRes;
}
} // namespace MurmurHashUtils

//=================================================================================================

inline uint64_t MurmurHash64A(const void* theKey, int theLen, uint64_t theSeed) noexcept
{
  static constexpr uint64_t aMul = (((uint64_t)0xc6a4a793UL) << 32UL) + (uint64_t)0x5bd1e995UL;
  const char* const         aBuf = static_cast<const char*>(theKey);

  // Remove the bytes not divisible by the sizeof(uint64_t).  This
  // allows the main loop to process the data as 64-bit integers.
  const uint64_t    aLenAligned = theLen & ~(uint64_t)0x7;
  const char* const anEnd       = aBuf + aLenAligned;
  uint64_t          aHash       = theSeed ^ (theLen * aMul);
  for (const char* aPnt = aBuf; aPnt != anEnd; aPnt += 8)
  {
    const uint64_t aData =
      MurmurHashUtils::shift_mix(MurmurHashUtils::unaligned_load<uint64_t>(aPnt) * aMul) * aMul;
    aHash ^= aData;
    aHash *= aMul;
  }
  if ((theLen & 0x7) != 0)
  {
    const uint64_t data = MurmurHashUtils::load_bytes(anEnd, theLen & 0x7);
    aHash ^= data;
    aHash *= aMul;
  }
  aHash = MurmurHashUtils::shift_mix(aHash) * aMul;
  aHash = MurmurHashUtils::shift_mix(aHash);
  return aHash;
}

//=================================================================================================

inline uint32_t MurmurHash2A(const void* theKey, int theLen, uint32_t theSeed) noexcept
{
  constexpr uint32_t aMul  = 0x5bd1e995;
  uint32_t           aHash = theSeed ^ theLen;
  const char*        aBuf  = static_cast<const char*>(theKey);

  // Mix 4 bytes at a time into the hash.
  while (theLen >= 4)
  {
    uint32_t aKey = MurmurHashUtils::unaligned_load<uint32_t>(aBuf);
    aKey *= aMul;
    aKey ^= aKey >> 24;
    aKey *= aMul;
    aHash *= aMul;
    aHash ^= aKey;
    aBuf += 4;
    theLen -= 4;
  }

  uint32_t aKey;
  // Handle the last few bytes of the input array.
  switch (theLen)
  {
    case 3:
      aKey = static_cast<unsigned char>(aBuf[2]);
      aHash ^= aKey << 16;
      [[fallthrough]];
    case 2:
      aKey = static_cast<unsigned char>(aBuf[1]);
      aHash ^= aKey << 8;
      [[fallthrough]];
    case 1:
      aKey = static_cast<unsigned char>(aBuf[0]);
      aHash ^= aKey;
      aHash *= aMul;
  };

  // Do a few final mixes of the hash.
  aHash ^= aHash >> 13;
  aHash *= aMul;
  aHash ^= aHash >> 15;
  return aHash;
}
} // namespace MurmurHash

namespace FNVHash
{
//=================================================================================================

inline uint32_t FNVHash1A(const void* theKey, int theLen, uint32_t theSeed) noexcept
{
  const char* cptr = static_cast<const char*>(theKey);
  for (; theLen; --theLen)
  {
    theSeed ^= static_cast<uint32_t>(*cptr++);
    theSeed *= static_cast<uint32_t>(16777619UL);
  }
  return theSeed;
}

//=================================================================================================

inline uint64_t FNVHash64A(const void* theKey, int theLen, uint64_t theSeed) noexcept
{
  const char* cptr = static_cast<const char*>(theKey);
  for (; theLen; --theLen)
  {
    theSeed ^= static_cast<uint64_t>(*cptr++);
    theSeed *= static_cast<uint64_t>(1099511628211ULL);
  }
  return theSeed;
}
} // namespace FNVHash
} // namespace opencascade


