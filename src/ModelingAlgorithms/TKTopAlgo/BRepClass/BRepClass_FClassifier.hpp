#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <BRepClass_FClass2dOfFClassifier.hpp>
#include <BRepClass_Edge.hpp>
#include <IntRes2d_Position.hpp>
#include <TopAbs_State.hpp>
class Standard_DomainError;
class BRepClass_FaceExplorer;
class BRepClass_Edge;
class BRepClass_Intersector;
class BRepClass_FClass2dOfFClassifier;
class gp_Pnt2d;

class BRepClass_FClassifier
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT BRepClass_FClassifier();

  Standard_EXPORT BRepClass_FClassifier(BRepClass_FaceExplorer& F,
                                        const gp_Pnt2d&         P,
                                        const double            Tol);

  Standard_EXPORT void Perform(BRepClass_FaceExplorer& F, const gp_Pnt2d& P, const double Tol);

  Standard_EXPORT TopAbs_State State() const;

  bool Rejected() const;

  bool NoWires() const;

  Standard_EXPORT const BRepClass_Edge& Edge() const;

  Standard_EXPORT double EdgeParameter() const;

  IntRes2d_Position Position() const;

protected:
  BRepClass_FClass2dOfFClassifier myClassifier;
  BRepClass_Edge                  myEdge;
  double                          myEdgeParameter;
  IntRes2d_Position               myPosition;
  bool                            rejected;
  bool                            nowires;
};

#define TheFaceExplorer BRepClass_FaceExplorer
#define TheFaceExplorer_hxx <BRepClass_FaceExplorer.hpp>
#define TheEdge BRepClass_Edge
#define TheEdge_hxx <BRepClass_Edge.hpp>
#define TheIntersection2d BRepClass_Intersector
#define TheIntersection2d_hxx <BRepClass_Intersector.hpp>
#define TopClass_FClass2d BRepClass_FClass2dOfFClassifier
#define TopClass_FClass2d_hxx <BRepClass_FClass2dOfFClassifier.hpp>
#define TopClass_FaceClassifier BRepClass_FClassifier
#define TopClass_FaceClassifier_hxx <BRepClass_FClassifier.hpp>

#include <TopClass_FaceClassifier_1.hpp>

#undef TheFaceExplorer
#undef TheFaceExplorer_hxx
#undef TheEdge
#undef TheEdge_hxx
#undef TheIntersection2d
#undef TheIntersection2d_hxx
#undef TopClass_FClass2d
#undef TopClass_FClass2d_hxx
#undef TopClass_FaceClassifier
#undef TopClass_FaceClassifier_hxx
