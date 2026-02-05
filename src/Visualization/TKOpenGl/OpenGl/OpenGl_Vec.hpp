#pragma once

#include <NCollection_Vec2.hpp>

#include <Standard_TypeDef.hpp>

#include <NCollection_Vec3.hpp>

#include <NCollection_Vec4.hpp>

#include <NCollection_Mat4.hpp>

namespace OpenGl
{
  //! Tool class for selecting appropriate vector type.
  //! \tparam T Numeric data type
  template <class T>
  struct VectorType
  {
    // Not implemented
  };

  template <>
  struct VectorType<double>
  {
    typedef NCollection_Vec2<double> Vec2;
    typedef NCollection_Vec3<double> Vec3;
    typedef NCollection_Vec4<double> Vec4;
  };

  template <>
  struct VectorType<float>
  {
    typedef NCollection_Vec2<float> Vec2;
    typedef NCollection_Vec3<float> Vec3;
    typedef NCollection_Vec4<float> Vec4;
  };

  //! Tool class for selecting appropriate matrix type.
  //! \tparam T Numeric data type
  template <class T>
  struct MatrixType
  {
    // Not implemented
  };

  template <>
  struct MatrixType<double>
  {
    typedef NCollection_Mat4<double> Mat4;
  };

  template <>
  struct MatrixType<float>
  {
    typedef NCollection_Mat4<float> Mat4;
  };
} // namespace OpenGl
