#include <Geom2dHatch_Classifier.hpp>

#include <Standard_DomainError.hpp>
#include <Geom2dHatch_Elements.hpp>
#include <Geom2dAdaptor_Curve.hpp>
#include <Geom2dHatch_Intersector.hpp>
#include <Geom2dHatch_FClass2dOfClassifier.hpp>
#include <gp_Pnt2d.hpp>

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
#include <TopClass_FaceClassifier.hpp>
