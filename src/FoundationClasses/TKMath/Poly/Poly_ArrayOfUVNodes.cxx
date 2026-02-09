

#include <Poly_ArrayOfUVNodes.hpp>

Poly_ArrayOfUVNodes::Poly_ArrayOfUVNodes(const Poly_ArrayOfUVNodes& theOther)

  = default;

Poly_ArrayOfUVNodes::~Poly_ArrayOfUVNodes() = default;

Poly_ArrayOfUVNodes& Poly_ArrayOfUVNodes::Assign(const Poly_ArrayOfUVNodes& theOther)
{
  if (&theOther == this)
  {
    return *this;
  }

  if (myStride == theOther.myStride)
  {

    NCollection_AliasedArray::Assign(theOther);
    return *this;
  }

  if (mySize != theOther.mySize)
  {
    throw Standard_DimensionMismatch("Poly_ArrayOfUVNodes::Assign(), arrays have different sizes");
  }
  for (int anIter = 0; anIter < mySize; ++anIter)
  {
    const gp_Pnt2d aPnt = theOther.Value(anIter);
    SetValue(anIter, aPnt);
  }
  return *this;
}
