#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <gp_Pnt.hpp>
#include <TopOpeBRepTool_SolidClassifier.hpp>
#include <TopoDS_Shape.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <TopOpeBRepBuild_CompositeClassifier.hpp>
#include <TopAbs_State.hpp>
class TopOpeBRepBuild_BlockBuilder;

//! Classify faces and shells.
//! shapes are Shells, Elements are Faces.
class TopOpeBRepBuild_ShellFaceClassifier : public TopOpeBRepBuild_CompositeClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  //! Creates a classifier in 3D space, to compare :
  //! a face with a set of faces
  //! a shell with a set of faces
  //! a shell with a shell
  Standard_EXPORT TopOpeBRepBuild_ShellFaceClassifier(const TopOpeBRepBuild_BlockBuilder& BB);

  Standard_EXPORT void Clear();

  //! classify shell <B1> with shell <B2>
  Standard_EXPORT TopAbs_State CompareShapes(const TopoDS_Shape& B1,
                                             const TopoDS_Shape& B2) override;

  //! classify face <F> with shell <S>
  Standard_EXPORT TopAbs_State CompareElementToShape(const TopoDS_Shape& F,
                                                     const TopoDS_Shape& S) override;

  //! prepare classification involving shell <S>
  //! calls ResetElement on first face of <S>
  Standard_EXPORT void ResetShape(const TopoDS_Shape& S) override;

  //! prepare classification involving face <F>
  //! define 3D point (later used in Compare()) on first vertex of face <F>.
  Standard_EXPORT void ResetElement(const TopoDS_Shape& F) override;

  //! Add the face <F> in the set of faces used in 3D point
  //! classification. Returns FALSE if the face <F> has been already
  //! added to the set of faces, otherwise returns TRUE.
  Standard_EXPORT bool CompareElement(const TopoDS_Shape& F) override;

  //! Returns state of classification of 3D point, defined by
  //! ResetElement, with the current set of faces, defined by Compare.
  Standard_EXPORT TopAbs_State State() override;

private:
  bool                                                                     myFirstCompare;
  gp_Pnt                                                                   myPoint3d;
  TopoDS_Shell                                                             myShell;
  BRep_Builder                                                             myBuilder;
  TopOpeBRepTool_SolidClassifier                                           mySolidClassifier;
  NCollection_DataMap<TopoDS_Shape, TopoDS_Shape, TopTools_ShapeMapHasher> myFaceShellMap;
  TopoDS_Shape                                                             myShape;
};
