#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TopoDS_Shape.hpp>
#include <Standard_Integer.hpp>
#include <ShapeAnalysis_CheckSmallFace.hpp>
#include <ShapeFix_Root.hpp>
class TopoDS_Face;
class TopoDS_Edge;
class TopoDS_Compound;

//! Fixing face with small size
class ShapeFix_FixSmallFace : public ShapeFix_Root
{

public:
  Standard_EXPORT ShapeFix_FixSmallFace();

  Standard_EXPORT void Init(const TopoDS_Shape& S);

  //! Fixing case of spot face
  Standard_EXPORT void Perform();

  //! Fixing case of spot face, if tol = -1 used local tolerance.
  Standard_EXPORT TopoDS_Shape FixSpotFace();

  //! Compute average vertex and replacing vertices by new one.
  Standard_EXPORT bool ReplaceVerticesInCaseOfSpot(TopoDS_Face& F, const double tol) const;

  //! Remove spot face from compound
  Standard_EXPORT bool RemoveFacesInCaseOfSpot(const TopoDS_Face& F) const;

  //! Fixing case of strip face, if tol = -1 used local tolerance
  Standard_EXPORT TopoDS_Shape FixStripFace(const bool wasdone = false);

  //! Replace veretces and edges.
  Standard_EXPORT bool ReplaceInCaseOfStrip(TopoDS_Face& F,
                                            TopoDS_Edge& E1,
                                            TopoDS_Edge& E2,
                                            const double tol) const;

  //! Remove strip face from compound.
  Standard_EXPORT bool RemoveFacesInCaseOfStrip(const TopoDS_Face& F) const;

  //! Compute average edge for strip face
  Standard_EXPORT TopoDS_Edge ComputeSharedEdgeForStripFace(const TopoDS_Face& F,
                                                            const TopoDS_Edge& E1,
                                                            const TopoDS_Edge& E2,
                                                            const TopoDS_Face& F1,
                                                            const double       tol) const;

  Standard_EXPORT TopoDS_Shape FixSplitFace(const TopoDS_Shape& S);

  //! Compute data for face splitting.
  Standard_EXPORT bool SplitOneFace(TopoDS_Face& F, TopoDS_Compound& theSplittedFaces);

  Standard_EXPORT TopoDS_Face FixFace(const TopoDS_Face& F);

  Standard_EXPORT TopoDS_Shape FixShape();

  Standard_EXPORT TopoDS_Shape Shape();

  Standard_EXPORT bool FixPinFace(TopoDS_Face& F);

  DEFINE_STANDARD_RTTIEXT(ShapeFix_FixSmallFace, ShapeFix_Root)

private:
  TopoDS_Shape                 myShape;
  TopoDS_Shape                 myResult;
  int                          myStatus;
  ShapeAnalysis_CheckSmallFace myAnalyzer;
};
