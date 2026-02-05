#include <BRepClass_FClassifier.hpp>

#include <Standard_DomainError.hpp>
#include <BRepClass_FaceExplorer.hpp>
#include <BRepClass_Edge.hpp>
#include <BRepClass_Intersector.hpp>
#include <BRepClass_FClass2dOfFClassifier.hpp>
#include <gp_Pnt2d.hpp>

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
#include <TopClass_FaceClassifier.hpp>
