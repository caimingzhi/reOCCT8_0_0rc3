#pragma once

#include <NCollection_Vec2.hpp>

#include <Standard_TypeDef.hpp>

#include <NCollection_Vec3.hpp>

#include <NCollection_Vec4.hpp>

#include <NCollection_Mat4.hpp>
#include <Standard_Transient.hpp>
#include <TCollection_AsciiString.hpp>

struct Graphic3d_ValueInterface
{

  Standard_EXPORT virtual ~Graphic3d_ValueInterface();

  virtual size_t TypeID() const = 0;

  template <class T>
  T& As();

  template <class T>
  const T& As() const;
};

template <class T>
struct Graphic3d_UniformValueTypeID
{
};

template <>
struct Graphic3d_UniformValueTypeID<int>
{
  static const size_t ID = __LINE__;
};

template <>
struct Graphic3d_UniformValueTypeID<float>
{
  static const size_t ID = __LINE__;
};

template <>
struct Graphic3d_UniformValueTypeID<NCollection_Vec2<float>>
{
  static const size_t ID = __LINE__;
};

template <>
struct Graphic3d_UniformValueTypeID<NCollection_Vec3<float>>
{
  static const size_t ID = __LINE__;
};

template <>
struct Graphic3d_UniformValueTypeID<NCollection_Vec4<float>>
{
  static const size_t ID = __LINE__;
};

template <>
struct Graphic3d_UniformValueTypeID<NCollection_Vec2<int>>
{
  static const size_t ID = __LINE__;
};

template <>
struct Graphic3d_UniformValueTypeID<NCollection_Vec3<int>>
{
  static const size_t ID = __LINE__;
};

template <>
struct Graphic3d_UniformValueTypeID<NCollection_Vec4<int>>
{
  static const size_t ID = __LINE__;
};

template <class T>
struct Graphic3d_UniformValue : public Graphic3d_ValueInterface
{

  Graphic3d_UniformValue(const T& theValue)
      : Value(theValue)
  {
  }

  size_t TypeID() const override;

  T Value;
};

typedef Graphic3d_UniformValue<int> Graphic3d_UniformInt;

typedef Graphic3d_UniformValue<NCollection_Vec2<int>> Graphic3d_UniformVec2i;

typedef Graphic3d_UniformValue<NCollection_Vec3<int>> Graphic3d_UniformVec3i;

typedef Graphic3d_UniformValue<NCollection_Vec4<int>> Graphic3d_UniformVec4i;

typedef Graphic3d_UniformValue<float> Graphic3d_UniformFloat;

typedef Graphic3d_UniformValue<NCollection_Vec2<float>> Graphic3d_UniformVec2;

typedef Graphic3d_UniformValue<NCollection_Vec3<float>> Graphic3d_UniformVec3;

typedef Graphic3d_UniformValue<NCollection_Vec4<float>> Graphic3d_UniformVec4;

class Graphic3d_ShaderVariable : public Standard_Transient
{
public:
  Standard_EXPORT ~Graphic3d_ShaderVariable() override;

  Standard_EXPORT const TCollection_AsciiString& Name() const;

  Standard_EXPORT bool IsDone() const;

  Standard_EXPORT Graphic3d_ValueInterface* Value();

  template <class T>
  static Graphic3d_ShaderVariable* Create(const TCollection_AsciiString& theName,
                                          const T&                       theValue);

public:
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ShaderVariable, Standard_Transient)

protected:
  Standard_EXPORT Graphic3d_ShaderVariable(const TCollection_AsciiString& theName);

protected:
  TCollection_AsciiString myName;

  Graphic3d_ValueInterface* myValue;
};

template <class T>
inline T& Graphic3d_ValueInterface::As()
{
  Graphic3d_UniformValue<T>* aPtr = dynamic_cast<Graphic3d_UniformValue<T>*>(this);
  return aPtr->Value;
}

template <class T>
inline const T& Graphic3d_ValueInterface::As() const
{
  const Graphic3d_UniformValue<T>* aPtr = dynamic_cast<const Graphic3d_UniformValue<T>*>(this);
  return aPtr->Value;
}

template <class T>
inline size_t Graphic3d_UniformValue<T>::TypeID() const
{
  return Graphic3d_UniformValueTypeID<T>::ID;
}

template <class T>
inline Graphic3d_ShaderVariable* Graphic3d_ShaderVariable::Create(
  const TCollection_AsciiString& theName,
  const T&                       theValue)
{
  Graphic3d_ShaderVariable* theVariable = new Graphic3d_ShaderVariable(theName);
  theVariable->myValue                  = new Graphic3d_UniformValue<T>(theValue);
  return theVariable;
}
