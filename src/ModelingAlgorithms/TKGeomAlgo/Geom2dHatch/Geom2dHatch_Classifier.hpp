#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>

#include <Geom2dHatch_FClass2dOfClassifier.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <IntRes2d_Position.hpp>
#include <TopAbs_State.hpp>
class Standard_DomainError;
class Geom2dHatch_Elements;
class Geom2dAdaptor_Curve;
class Geom2dHatch_Intersector;
class Geom2dHatch_FClass2dOfClassifier;
class gp_Pnt2d;

class Geom2dHatch_Classifier
{
public:
  DEFINE_STANDARD_ALLOC

  //! Empty constructor, undefined algorithm.
  Standard_EXPORT Geom2dHatch_Classifier();

  //! Creates an algorithm to classify the Point P with
  //! Tolerance <T> on the face described by <F>.
  Standard_EXPORT Geom2dHatch_Classifier(Geom2dHatch_Elements& F,
                                         const gp_Pnt2d&       P,
                                         const double          Tol);

  //! Classify the Point P with Tolerance <T> on the
  //! face described by <F>.
  Standard_EXPORT void Perform(Geom2dHatch_Elements& F, const gp_Pnt2d& P, const double Tol);

  //! Returns the result of the classification.
  Standard_EXPORT TopAbs_State State() const;

  //! Returns True when the state was computed by a
  //! rejection. The state is OUT.
  bool Rejected() const;

  //! Returns True if the face contains no wire.
  //! The state is IN.
  bool NoWires() const;

  //! Returns the Edge used to determine the
  //! classification. When the State is ON this is the
  //! Edge containing the point.
  Standard_EXPORT const Geom2dAdaptor_Curve& Edge() const;

  //! Returns the parameter on Edge() used to determine the
  //! classification.
  Standard_EXPORT double EdgeParameter() const;

  //! Returns the position of the point on the edge
  //! returned by Edge.
  IntRes2d_Position Position() const;

protected:
  Geom2dHatch_FClass2dOfClassifier myClassifier;
  Geom2dAdaptor_Curve              myEdge;
  double                           myEdgeParameter;
  IntRes2d_Position                myPosition;
  bool                             rejected;
  bool                             nowires;
};

#define TheFaceExplorer Geom2dHatch_Elements
#define TheFaceExplorer_hxx <Geom2dHatch_Elements.hpp>
#define TheEdge Geom2dAdaptor_Curve
#define TheEdge_hxx <Geom2dAdaptor_Curve.hpp>
#define TheIntersection2d Geom2dHatch_Intersector
#define TheIntersection2d_hxx <Geom2dHatch_Intersector.hpp>
#define TopClass_FClass2d Geom2dHatch_FClass2dOfClassifier
#define TopClass_FClass2d_hxx <Geom2dHatch_FClass2dOfClassifier.hpp>
#define TopClass_FaceClassifier Geom2dHatch_Classifier
#define TopClass_FaceClassifier_hxx <Geom2dHatch_Classifier.hpp>

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
