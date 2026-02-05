#include <BRepClass_FacePassiveClassifier.hpp>

#include <Standard_DomainError.hpp>
#include <BRepClass_Edge.hpp>
#include <BRepClass_Intersector.hpp>
#include <gp_Lin2d.hpp>

#define TheEdge BRepClass_Edge
#define TheEdge_hxx <BRepClass_Edge.hpp>
#define TheIntersector BRepClass_Intersector
#define TheIntersector_hxx <BRepClass_Intersector.hpp>
#define TopClass_Classifier2d BRepClass_FacePassiveClassifier
#define TopClass_Classifier2d_hxx <BRepClass_FacePassiveClassifier.hpp>
#include <TopClass_Classifier2d.hpp>
