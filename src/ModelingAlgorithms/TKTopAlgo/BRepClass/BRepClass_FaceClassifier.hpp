#pragma once


#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <BRepClass_FClassifier.hpp>
class BRepClass_FaceExplorer;
class gp_Pnt2d;
class TopoDS_Face;
class gp_Pnt;

//! Provides Constructors with a Face.
class BRepClass_FaceClassifier : public BRepClass_FClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor, undefined algorithm.
  Standard_EXPORT BRepClass_FaceClassifier();

  //! Creates an algorithm to classify the Point P with
  //! Tolerance <T> on the face described by <F>.
  Standard_EXPORT BRepClass_FaceClassifier(BRepClass_FaceExplorer& F,
                                           const gp_Pnt2d&         P,
                                           const double            Tol);

  //! Creates an algorithm to classify the Point P with
  //! Tolerance <T> on the face <F>.
  //! Recommended to use Bnd_Box if the number of edges > 10
  //! and the geometry is mostly spline
  Standard_EXPORT BRepClass_FaceClassifier(const TopoDS_Face& theF,
                                           const gp_Pnt2d&    theP,
                                           const double       theTol,
                                           const bool         theUseBndBox   = false,
                                           const double       theGapCheckTol = 0.1);

  //! Classify the Point P with Tolerance <T> on the
  //! face described by <F>.
  //! Recommended to use Bnd_Box if the number of edges > 10
  //! and the geometry is mostly spline
  Standard_EXPORT void Perform(const TopoDS_Face& theF,
                               const gp_Pnt2d&    theP,
                               const double       theTol,
                               const bool         theUseBndBox   = false,
                               const double       theGapCheckTol = 0.1);

  //! Creates an algorithm to classify the Point P with
  //! Tolerance <T> on the face <F>.
  //! Recommended to use Bnd_Box if the number of edges > 10
  //! and the geometry is mostly spline
  Standard_EXPORT BRepClass_FaceClassifier(const TopoDS_Face& theF,
                                           const gp_Pnt&      theP,
                                           const double       theTol,
                                           const bool         theUseBndBox   = false,
                                           const double       theGapCheckTol = 0.1);

  //! Classify the Point P with Tolerance <T> on the
  //! face described by <F>.
  //! Recommended to use Bnd_Box if the number of edges > 10
  //! and the geometry is mostly spline
  Standard_EXPORT void Perform(const TopoDS_Face& theF,
                               const gp_Pnt&      theP,
                               const double       theTol,
                               const bool         theUseBndBox   = false,
                               const double       theGapCheckTol = 0.1);
};

