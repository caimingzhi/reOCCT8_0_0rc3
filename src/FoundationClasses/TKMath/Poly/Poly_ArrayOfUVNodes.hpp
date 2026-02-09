#pragma once

#include <NCollection_AliasedArray.hpp>
#include <gp_Pnt2d.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_Macro.hpp>

class Poly_ArrayOfUVNodes : public NCollection_AliasedArray<>
{
public:
  Poly_ArrayOfUVNodes()
      : NCollection_AliasedArray((int)sizeof(gp_Pnt2d))
  {
  }

  Poly_ArrayOfUVNodes(int theLength)
      : NCollection_AliasedArray((int)sizeof(gp_Pnt2d), theLength)
  {
  }

  Standard_EXPORT Poly_ArrayOfUVNodes(const Poly_ArrayOfUVNodes& theOther);

  Poly_ArrayOfUVNodes(const gp_Pnt2d& theBegin, int theLength)
      : NCollection_AliasedArray(theBegin, theLength)
  {
  }

  Poly_ArrayOfUVNodes(const NCollection_Vec2<float>& theBegin, int theLength)
      : NCollection_AliasedArray(theBegin, theLength)
  {
  }

  Standard_EXPORT ~Poly_ArrayOfUVNodes();

  bool IsDoublePrecision() const { return myStride == (int)sizeof(gp_Pnt2d); }

  void SetDoublePrecision(bool theIsDouble)
  {
    if (myData != nullptr)
    {
      throw Standard_ProgramError(
        "Poly_ArrayOfUVNodes::SetDoublePrecision() should be called before allocation");
    }
    myStride = int(theIsDouble ? sizeof(gp_Pnt2d) : sizeof(NCollection_Vec2<float>));
  }

  Standard_EXPORT Poly_ArrayOfUVNodes& Assign(const Poly_ArrayOfUVNodes& theOther);

  Poly_ArrayOfUVNodes& Move(Poly_ArrayOfUVNodes& theOther)
  {
    NCollection_AliasedArray::Move(theOther);
    return *this;
  }

  Poly_ArrayOfUVNodes& operator=(const Poly_ArrayOfUVNodes& theOther) { return Assign(theOther); }

  Poly_ArrayOfUVNodes(Poly_ArrayOfUVNodes&& theOther) noexcept
      : NCollection_AliasedArray(std::move(theOther))
  {
  }

  Poly_ArrayOfUVNodes& operator=(Poly_ArrayOfUVNodes&& theOther) noexcept { return Move(theOther); }

public:
  inline gp_Pnt2d Value(int theIndex) const;

  inline void SetValue(int theIndex, const gp_Pnt2d& theValue);

  gp_Pnt2d operator[](int theIndex) const { return Value(theIndex); }
};

inline gp_Pnt2d Poly_ArrayOfUVNodes::Value(int theIndex) const
{
  if (myStride == (int)sizeof(gp_Pnt2d))
  {
    return NCollection_AliasedArray::Value<gp_Pnt2d>(theIndex);
  }
  else
  {
    const NCollection_Vec2<float>& aVec2 =
      NCollection_AliasedArray::Value<NCollection_Vec2<float>>(theIndex);
    return gp_Pnt2d(aVec2.x(), aVec2.y());
  }
}

inline void Poly_ArrayOfUVNodes::SetValue(int theIndex, const gp_Pnt2d& theValue)
{
  if (myStride == (int)sizeof(gp_Pnt2d))
  {
    NCollection_AliasedArray::ChangeValue<gp_Pnt2d>(theIndex) = theValue;
  }
  else
  {
    NCollection_Vec2<float>& aVec2 =
      NCollection_AliasedArray::ChangeValue<NCollection_Vec2<float>>(theIndex);
    aVec2.SetValues((float)theValue.X(), (float)theValue.Y());
  }
}
