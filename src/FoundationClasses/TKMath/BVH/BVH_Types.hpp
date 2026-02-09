#pragma once

#define _BVH_USE_STD_VECTOR_

#include <vector>

#include <Bnd_Box.hpp>
#include <NCollection_Mat4.hpp>
#include <NCollection_Vec2.hpp>
#include <NCollection_Vec3.hpp>
#include <NCollection_Vector.hpp>
#include <Standard_OStream.hpp>
#include <Standard_Type.hpp>

#if defined(_BVH_USE_STD_VECTOR_) && defined(_MSC_VER) && !defined(__INTEL_COMPILER)
  #define _STD_VECTOR_SHRINK
#endif

namespace BVH
{

  template <class T, int N>
  struct VectorType
  {
  };

  template <class T>
  struct VectorType<T, 1>
  {
    typedef T Type;
  };

  template <class T>
  struct VectorType<T, 2>
  {
    typedef NCollection_Vec2<T> Type;
  };

  template <class T>
  struct VectorType<T, 3>
  {
    typedef NCollection_Vec3<T> Type;
  };

  template <class T>
  Bnd_Box ToBndBox(const T& theMin, const T& theMax)
  {
    return Bnd_Box(gp_Pnt(theMin, 0., 0.), gp_Pnt(theMax, 0., 0.));
  }

  template <class T>
  Bnd_Box ToBndBox(const NCollection_Vec2<T>& theMin, const NCollection_Vec2<T>& theMax)
  {
    return Bnd_Box(gp_Pnt(theMin.x(), theMin.y(), 0.), gp_Pnt(theMax.x(), theMax.y(), 0.));
  }

  template <class T>
  Bnd_Box ToBndBox(const NCollection_Vec3<T>& theMin, const NCollection_Vec3<T>& theMax)
  {
    return Bnd_Box(gp_Pnt(theMin.x(), theMin.y(), theMin.z()),
                   gp_Pnt(theMax.x(), theMax.y(), theMax.z()));
  }

  template <class T>
  Bnd_Box ToBndBox(const NCollection_Vec4<T>& theMin, const NCollection_Vec4<T>& theMax)
  {
    return Bnd_Box(gp_Pnt(theMin.x(), theMin.y(), theMin.z()),
                   gp_Pnt(theMax.x(), theMax.y(), theMax.z()));
  }

  template <class T>
  struct VectorType<T, 4>
  {
    typedef NCollection_Vec4<T> Type;
  };

  template <class T, int N>
  struct MatrixType
  {
  };

  template <class T>
  struct MatrixType<T, 4>
  {
    typedef NCollection_Mat4<T> Type;
  };

  template <class T, int N = 1>
  struct ArrayType
  {
#ifndef _BVH_USE_STD_VECTOR_
    typedef NCollection_Vector<typename VectorType<T, N>::Type> Type;
#else
    typedef std::vector<typename VectorType<T, N>::Type> Type;
#endif
  };
} // namespace BVH

typedef BVH::VectorType<int, 2>::Type BVH_Vec2i;

typedef BVH::VectorType<int, 3>::Type BVH_Vec3i;

typedef BVH::VectorType<int, 4>::Type BVH_Vec4i;

typedef BVH::ArrayType<int, 2>::Type BVH_Array2i;

typedef BVH::ArrayType<int, 3>::Type BVH_Array3i;

typedef BVH::ArrayType<int, 4>::Type BVH_Array4i;

typedef BVH::VectorType<float, 2>::Type BVH_Vec2f;

typedef BVH::VectorType<float, 3>::Type BVH_Vec3f;

typedef BVH::VectorType<float, 4>::Type BVH_Vec4f;

typedef BVH::ArrayType<float, 2>::Type BVH_Array2f;

typedef BVH::ArrayType<float, 3>::Type BVH_Array3f;

typedef BVH::ArrayType<float, 4>::Type BVH_Array4f;

typedef BVH::VectorType<double, 2>::Type BVH_Vec2d;

typedef BVH::VectorType<double, 3>::Type BVH_Vec3d;

typedef BVH::VectorType<double, 4>::Type BVH_Vec4d;

typedef BVH::ArrayType<double, 2>::Type BVH_Array2d;

typedef BVH::ArrayType<double, 3>::Type BVH_Array3d;

typedef BVH::ArrayType<double, 4>::Type BVH_Array4d;

typedef BVH::MatrixType<float, 4>::Type BVH_Mat4f;

typedef BVH::MatrixType<double, 4>::Type BVH_Mat4d;

namespace BVH
{

  template <class T, int N>
  struct VecComp
  {
  };

  template <class T>
  struct VecComp<T, 2>
  {
    typedef typename BVH::VectorType<T, 2>::Type BVH_Vec2t;

    static constexpr T Get(const BVH_Vec2t& theVec, const int theAxis)
    {
      return theAxis == 0 ? theVec.x() : theVec.y();
    }
  };

  template <class T>
  struct VecComp<T, 3>
  {
    typedef typename BVH::VectorType<T, 3>::Type BVH_Vec3t;

    static constexpr T Get(const BVH_Vec3t& theVec, const int theAxis)
    {
      return theAxis == 0 ? theVec.x() : (theAxis == 1 ? theVec.y() : theVec.z());
    }
  };

  template <class T>
  struct VecComp<T, 4>
  {
    typedef typename BVH::VectorType<T, 4>::Type BVH_Vec4t;

    static constexpr T Get(const BVH_Vec4t& theVec, const int theAxis)
    {
      return theAxis == 0 ? theVec.x()
                          : (theAxis == 1 ? theVec.y() : (theAxis == 2 ? theVec.z() : theVec.w()));
    }
  };

  template <class T, int N = 1>
  struct Array
  {
    typedef typename BVH::ArrayType<T, N>::Type BVH_ArrayNt;

    static inline const typename BVH::VectorType<T, N>::Type& Value(const BVH_ArrayNt& theArray,
                                                                    const int          theIndex)
    {
#ifdef _BVH_USE_STD_VECTOR_
      return theArray[theIndex];
#else
      return theArray.Value(theIndex);
#endif
    }

    static inline typename BVH::VectorType<T, N>::Type& ChangeValue(BVH_ArrayNt& theArray,
                                                                    const int    theIndex)
    {
#ifdef _BVH_USE_STD_VECTOR_
      return theArray[theIndex];
#else
      return theArray.ChangeValue(theIndex);
#endif
    }

    static inline void Append(BVH_ArrayNt&                                theArray,
                              const typename BVH::VectorType<T, N>::Type& theElement)
    {
#ifdef _BVH_USE_STD_VECTOR_
      theArray.push_back(theElement);
#else
      theArray.Append(theElement);
#endif
    }

    static inline int Size(const BVH_ArrayNt& theArray)
    {
#ifdef _BVH_USE_STD_VECTOR_
      return static_cast<int>(theArray.size());
#else
      return static_cast<int>(theArray.Size());
#endif
    }

    static inline void Clear(BVH_ArrayNt& theArray)
    {
#ifdef _BVH_USE_STD_VECTOR_
      theArray.clear();
#else
      theArray.Clear();
#endif
    }

    static inline void Reserve(BVH_ArrayNt& theArray, const int theCount)
    {
#ifdef _BVH_USE_STD_VECTOR_
      if (Size(theArray) == theCount)
      {
  #ifdef _STD_VECTOR_SHRINK
        theArray.shrink_to_fit();
  #endif
      }
      else
      {
        theArray.reserve(theCount);
      }
#else

#endif
    }
  };

  template <class T>
  static inline constexpr int IntFloor(const T theValue)
  {
    const int aRes = static_cast<int>(theValue);

    return aRes - static_cast<int>(aRes > theValue);
  }
} // namespace BVH
