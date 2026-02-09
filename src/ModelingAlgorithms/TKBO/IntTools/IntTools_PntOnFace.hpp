#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <gp_Pnt.hpp>
#include <TopoDS_Face.hpp>

class IntTools_PntOnFace
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT IntTools_PntOnFace();

  Standard_EXPORT void Init(const TopoDS_Face& aF,
                            const gp_Pnt&      aP,
                            const double       U,
                            const double       V);

  Standard_EXPORT void SetFace(const TopoDS_Face& aF);

  Standard_EXPORT void SetPnt(const gp_Pnt& aP);

  Standard_EXPORT void SetParameters(const double U, const double V);

  Standard_EXPORT void SetValid(const bool bF);

  Standard_EXPORT bool Valid() const;

  Standard_EXPORT const TopoDS_Face& Face() const;

  Standard_EXPORT const gp_Pnt& Pnt() const;

  Standard_EXPORT void Parameters(double& U, double& V) const;

  Standard_EXPORT bool IsValid() const;

private:
  bool        myIsValid;
  gp_Pnt      myPnt;
  double      myU;
  double      myV;
  TopoDS_Face myFace;
};
