#pragma once

#include <NCollection_AliasedArray.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Vec3.hpp>
#include <Standard_Macro.hpp>

class Poly_ArrayOfNodes : public NCollection_AliasedArray<>
{
public:
  Poly_ArrayOfNodes()
      : NCollection_AliasedArray((int)sizeof(gp_Pnt))
  {
  }

  Poly_ArrayOfNodes(int theLength)
      : NCollection_AliasedArray((int)sizeof(gp_Pnt), theLength)
  {
  }

  Standard_EXPORT Poly_ArrayOfNodes(const Poly_ArrayOfNodes& theOther);

  Poly_ArrayOfNodes(const gp_Pnt& theBegin, int theLength)
      : NCollection_AliasedArray(theBegin, theLength)
  {
  }

  Poly_ArrayOfNodes(const NCollection_Vec3<float>& theBegin, int theLength)
      : NCollection_AliasedArray(theBegin, theLength)
  {
  }

  Standard_EXPORT ~Poly_ArrayOfNodes();

  bool IsDoublePrecision() const { return myStride == (int)sizeof(gp_Pnt); }

  void SetDoublePrecision(bool theIsDouble)
  {
    if (myData != nullptr)
    {
      throw Standard_ProgramError(
        "Poly_ArrayOfNodes::SetDoublePrecision() should be called before allocation");
    }
    myStride = int(theIsDouble ? sizeof(gp_Pnt) : sizeof(NCollection_Vec3<float>));
  }

  Standard_EXPORT Poly_ArrayOfNodes& Assign(const Poly_ArrayOfNodes& theOther);

  Poly_ArrayOfNodes& Move(Poly_ArrayOfNodes& theOther)
  {
    NCollection_AliasedArray::Move(theOther);
    return *this;
  }

  Poly_ArrayOfNodes& operator=(const Poly_ArrayOfNodes& theOther) { return Assign(theOther); }

  Poly_ArrayOfNodes(Poly_ArrayOfNodes&& theOther) noexcept
      : NCollection_AliasedArray(std::move(theOther))
  {
  }

  Poly_ArrayOfNodes& operator=(Poly_ArrayOfNodes&& theOther) noexcept { return Move(theOther); }

public:
  inline gp_Pnt Value(int theIndex) const;

  inline void SetValue(int theIndex, const gp_Pnt& theValue);

  gp_Pnt operator[](int theIndex) const { return Value(theIndex); }
};

inline gp_Pnt Poly_ArrayOfNodes::Value(int theIndex) const
{
  if (myStride == (int)sizeof(gp_Pnt))
  {
    return NCollection_AliasedArray::Value<gp_Pnt>(theIndex);
  }
  else
  {
    const NCollection_Vec3<float>& aVec3 =
      NCollection_AliasedArray::Value<NCollection_Vec3<float>>(theIndex);
    return gp_Pnt(aVec3.x(), aVec3.y(), aVec3.z());
  }
}

inline void Poly_ArrayOfNodes::SetValue(int theIndex, const gp_Pnt& theValue)
{
  if (myStride == (int)sizeof(gp_Pnt))
  {
    NCollection_AliasedArray::ChangeValue<gp_Pnt>(theIndex) = theValue;
  }
  else
  {
    NCollection_Vec3<float>& aVec3 =
      NCollection_AliasedArray::ChangeValue<NCollection_Vec3<float>>(theIndex);
    aVec3.SetValues((float)theValue.X(), (float)theValue.Y(), (float)theValue.Z());
  }
}
