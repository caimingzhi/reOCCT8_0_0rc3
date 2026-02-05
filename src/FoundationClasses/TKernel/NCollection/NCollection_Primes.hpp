#pragma once

#include <Standard_Macro.hpp>

//! Namespace provides a collection of prime numbers.
//!
//! This namespace is used to store a collection of prime numbers that are used as
//! consecutive steps for the size of an array of buckets in a map. The prime
//! numbers are chosen to minimize the probability of having the same hash codes
//! for different map items. The namespace also provides a method to find the next
//! prime number greater than or equal to a given number.
//!
//! The following are Pierpont primes, prime numbers of the form 2^u * 3^v + 1:
//! 101, 1009, 2003, 5003, 10007, 20011, 37003, 57037, 65003, 100019, 209953, 472393,
//! 995329, 2359297, 4478977, 9437185, 17915905, 35831809, 71663617, 150994945,
//! 301989889, 573308929, 1019215873, 2038431745
namespace NCollection_Primes
{
  //! Returns the next prime number greater than or equal to theN.
  //! If theN exceeds the largest available prime, returns theN + 1.
  Standard_EXPORT int NextPrimeForMap(const int theN) noexcept;
}; // namespace NCollection_Primes
