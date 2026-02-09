#pragma once

#include <Standard_TypeDef.hpp>

class Poly_CoherentTriangle;

class Poly_CoherentLink
{
public:
  Standard_EXPORT Poly_CoherentLink();

  inline Poly_CoherentLink(const int iNode0, const int iNode1)
      : myAttribute(nullptr)
  {
    myNode[0]         = iNode0;
    myNode[1]         = iNode1;
    myOppositeNode[0] = -1;
    myOppositeNode[1] = -1;
  }

  Standard_EXPORT Poly_CoherentLink(const Poly_CoherentTriangle& theTri, int iSide);

  inline int Node(const int ind) const { return myNode[ind & 0x1]; }

  inline int OppositeNode(const int ind) const { return myOppositeNode[ind & 0x1]; }

  inline void* GetAttribute() const { return myAttribute; }

  inline void SetAttribute(void* const theAtt) { myAttribute = theAtt; }

  inline bool IsEmpty() const noexcept { return myNode[0] < 0 || myNode[1] < 0; }

  inline void Nullify()
  {
    myNode[0]         = -1;
    myNode[1]         = -1;
    myOppositeNode[0] = -1;
    myOppositeNode[1] = -1;
  }

private:
  int   myNode[2];
  int   myOppositeNode[2];
  void* myAttribute;

  friend class Poly_CoherentTriangulation;
};
