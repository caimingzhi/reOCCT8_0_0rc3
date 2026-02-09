#include <Graphic3d_ShaderVariable.hpp>

IMPLEMENT_STANDARD_RTTIEXT(Graphic3d_ShaderVariable, Standard_Transient)

template struct Graphic3d_UniformValue<int>;
template struct Graphic3d_UniformValue<float>;
template struct Graphic3d_UniformValue<NCollection_Vec2<float>>;
template struct Graphic3d_UniformValue<NCollection_Vec3<float>>;
template struct Graphic3d_UniformValue<NCollection_Vec4<float>>;
template struct Graphic3d_UniformValue<NCollection_Vec2<int>>;
template struct Graphic3d_UniformValue<NCollection_Vec3<int>>;
template struct Graphic3d_UniformValue<NCollection_Vec4<int>>;

Graphic3d_ValueInterface::~Graphic3d_ValueInterface() = default;

Graphic3d_ShaderVariable::Graphic3d_ShaderVariable(const TCollection_AsciiString& theName)
    : myName(theName),
      myValue(nullptr)
{
}

Graphic3d_ShaderVariable::~Graphic3d_ShaderVariable()
{
  delete myValue;
}

bool Graphic3d_ShaderVariable::IsDone() const
{
  return !myName.IsEmpty() && (myValue != nullptr);
}

const TCollection_AsciiString& Graphic3d_ShaderVariable::Name() const
{
  return myName;
}

Graphic3d_ValueInterface* Graphic3d_ShaderVariable::Value()
{
  return myValue;
}
