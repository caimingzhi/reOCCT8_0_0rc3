

#include <BRepClass3d_SolidPassiveClassifier.hpp>

#include <BRepClass3d_Intersector3d.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <IntCurveSurface_TransitionOnCurve.hpp>
#include <Standard_DomainError.hpp>
#include <TopoDS_Face.hpp>
#include <gp_Lin.hpp>

BRepClass3d_SolidPassiveClassifier::BRepClass3d_SolidPassiveClassifier()
    : isSet(false),
      myParam(0.0),
      myTolerance(0.0),
      myState(TopAbs_UNKNOWN),
      hasIntersect(false)
{
}

void BRepClass3d_SolidPassiveClassifier::Reset(const gp_Lin& L, const double, const double Tol)
{
  myLin       = L;
  myParam     = RealLast();
  myTolerance = Tol;
  myState     = TopAbs_UNKNOWN;
  isSet       = true;
}

void BRepClass3d_SolidPassiveClassifier::Compare(const TopoDS_Face& Face, const TopAbs_Orientation)
{
  if (!isSet)
  {
#ifdef OCCT_DEBUG
    std::cout << " Call to BRepClass3d_SolidPassiveClassifier::Compare  without a Reset ! ";
#endif
    return;
  }

  hasIntersect = false;
  myIntersector.Perform(myLin, myParam, myTolerance, Face);
  if (myIntersector.IsDone())
  {
    if (myIntersector.HasAPoint())
    {
      hasIntersect = true;
      if (myIntersector.WParameter() < myParam)
      {
        myParam = myIntersector.WParameter();
        myFace  = myIntersector.Face();
        if (std::abs(myParam) <= myTolerance)
        {

#ifdef OCCT_DEBUG
          std::cout << " myParam = " << myParam << " ds BRepClass3d_SolidPassiveClassifier.gxx  "
                    << std::endl;
#endif

          myState = TopAbs_ON;
        }
        else
        {

          if (myIntersector.Transition() == IntCurveSurface_Out)
          {

            myState = TopAbs_IN;
          }
          else if (myIntersector.Transition() == IntCurveSurface_In)
          {
            myState = TopAbs_OUT;
          }
#ifdef OCCT_DEBUG
          else
          {
            std::cout << " -------- Probleme ds BRepClass3d_SolidPassiveClassifier.gxx "
                      << std::endl;
          }
#endif
        }
      }
      else
      {
      }
    }
    else
    {
    }
  }
}
