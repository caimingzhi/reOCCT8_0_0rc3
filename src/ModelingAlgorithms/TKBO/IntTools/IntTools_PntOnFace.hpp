#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <Standard_Boolean.hpp>
#include <gp_Pnt.hpp>
#include <TopoDS_Face.hpp>

//! Contains a Face, a 3d point, corresponded UV parameters and a flag
class IntTools_PntOnFace
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor
  Standard_EXPORT IntTools_PntOnFace();

  //! Initializes me by aFace, a 3d point
  //! and it's UV parameters on face
  Standard_EXPORT void Init(const TopoDS_Face& aF,
                            const gp_Pnt&      aP,
                            const double       U,
                            const double       V);

  //! Modifier
  Standard_EXPORT void SetFace(const TopoDS_Face& aF);

  //! Modifier
  Standard_EXPORT void SetPnt(const gp_Pnt& aP);

  //! Modifier
  Standard_EXPORT void SetParameters(const double U, const double V);

  //! Modifier
  Standard_EXPORT void SetValid(const bool bF);

  //! Selector
  Standard_EXPORT bool Valid() const;

  //! Selector
  Standard_EXPORT const TopoDS_Face& Face() const;

  //! Selector
  Standard_EXPORT const gp_Pnt& Pnt() const;

  //! Selector
  Standard_EXPORT void Parameters(double& U, double& V) const;

  //! Selector
  Standard_EXPORT bool IsValid() const;

private:
  bool        myIsValid;
  gp_Pnt      myPnt;
  double      myU;
  double      myV;
  TopoDS_Face myFace;
};
