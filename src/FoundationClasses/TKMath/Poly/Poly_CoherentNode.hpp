#pragma once

#include <gp_XYZ.hpp>
#include <Poly_CoherentTriPtr.hpp>
#include <Precision.hpp>

class NCollection_BaseAllocator;

class Poly_CoherentNode : public gp_XYZ
{
public:
  inline Poly_CoherentNode()
      : gp_XYZ(0., 0., 0.),
        myTriangles(nullptr),
        myIndex(-1)
  {
    myUV[0] = Precision::Infinite();
    myUV[1] = Precision::Infinite();
  }

  inline Poly_CoherentNode(const gp_XYZ& thePnt)
      : gp_XYZ(thePnt),
        myTriangles(nullptr),
        myIndex(-1)
  {
    myUV[0]     = Precision::Infinite();
    myUV[1]     = Precision::Infinite();
    myNormal[0] = 0.f;
    myNormal[1] = 0.f;
    myNormal[2] = 0.f;
  }

  inline void SetUV(const double theU, const double theV)
  {
    myUV[0] = theU;
    myUV[1] = theV;
  }

  inline double GetU() const { return myUV[0]; }

  inline double GetV() const { return myUV[1]; }

  Standard_EXPORT void SetNormal(const gp_XYZ& theVector);

  inline bool HasNormal() const
  {
    return ((myNormal[0] * myNormal[0] + myNormal[1] * myNormal[1] + myNormal[2] * myNormal[2])
            > Precision::Confusion());
  }

  inline gp_XYZ GetNormal() const { return gp_XYZ(myNormal[0], myNormal[1], myNormal[2]); }

  inline void SetIndex(const int theIndex) { myIndex = theIndex; }

  inline int GetIndex() const { return myIndex; }

  inline bool IsFreeNode() const noexcept { return myTriangles == nullptr; }

  Standard_EXPORT void Clear(const occ::handle<NCollection_BaseAllocator>&);

  Standard_EXPORT void AddTriangle(const Poly_CoherentTriangle&                  theTri,
                                   const occ::handle<NCollection_BaseAllocator>& theA);

  Standard_EXPORT bool RemoveTriangle(const Poly_CoherentTriangle&                  theTri,
                                      const occ::handle<NCollection_BaseAllocator>& theA);

  inline Poly_CoherentTriPtr::Iterator TriangleIterator() const { return *myTriangles; }

  Standard_EXPORT void Dump(Standard_OStream& theStream) const;

private:
  double               myUV[2];
  Poly_CoherentTriPtr* myTriangles;
  int                  myIndex;
  float                myNormal[3];
};
