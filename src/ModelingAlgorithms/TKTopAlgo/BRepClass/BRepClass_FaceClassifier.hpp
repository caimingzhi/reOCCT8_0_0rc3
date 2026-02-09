#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepClass_FClassifier.hpp>
class BRepClass_FaceExplorer;
class gp_Pnt2d;
class TopoDS_Face;
class gp_Pnt;

class BRepClass_FaceClassifier : public BRepClass_FClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepClass_FaceClassifier();

  Standard_EXPORT BRepClass_FaceClassifier(BRepClass_FaceExplorer& F,
                                           const gp_Pnt2d&         P,
                                           const double            Tol);

  Standard_EXPORT BRepClass_FaceClassifier(const TopoDS_Face& theF,
                                           const gp_Pnt2d&    theP,
                                           const double       theTol,
                                           const bool         theUseBndBox   = false,
                                           const double       theGapCheckTol = 0.1);

  Standard_EXPORT void Perform(const TopoDS_Face& theF,
                               const gp_Pnt2d&    theP,
                               const double       theTol,
                               const bool         theUseBndBox   = false,
                               const double       theGapCheckTol = 0.1);

  Standard_EXPORT BRepClass_FaceClassifier(const TopoDS_Face& theF,
                                           const gp_Pnt&      theP,
                                           const double       theTol,
                                           const bool         theUseBndBox   = false,
                                           const double       theGapCheckTol = 0.1);

  Standard_EXPORT void Perform(const TopoDS_Face& theF,
                               const gp_Pnt&      theP,
                               const double       theTol,
                               const bool         theUseBndBox   = false,
                               const double       theGapCheckTol = 0.1);
};
