#pragma once

#include <BVH_Box.hpp>
#include <BVH_Ray.hpp>
#include <BVH_Types.hpp>

template <class T, int N>
class BVH_Tools
{
public:
  typedef typename BVH::VectorType<T, N>::Type BVH_VecNt;

public:
  enum BVH_PrjStateInTriangle
  {
    BVH_PrjStateInTriangle_VERTEX,
    BVH_PrjStateInTriangle_EDGE,
    BVH_PrjStateInTriangle_INNER
  };

public:
  static T BoxBoxSquareDistance(const BVH_Box<T, N>& theBox1, const BVH_Box<T, N>& theBox2)
  {
    if (!theBox1.IsValid() || !theBox2.IsValid())
    {
      return static_cast<T>(0);
    }
    return BoxBoxSquareDistance(theBox1.CornerMin(),
                                theBox1.CornerMax(),
                                theBox2.CornerMin(),
                                theBox2.CornerMax());
  }

  static T BoxBoxSquareDistance(const BVH_VecNt& theCMin1,
                                const BVH_VecNt& theCMax1,
                                const BVH_VecNt& theCMin2,
                                const BVH_VecNt& theCMax2)
  {
    T aDist = T(0);
    for (int i = 0; i < N; ++i)
    {
      if (theCMin1[i] > theCMax2[i])
      {
        T d = theCMin1[i] - theCMax2[i];
        aDist += d * d;
      }
      else if (theCMax1[i] < theCMin2[i])
      {
        T d = theCMin2[i] - theCMax1[i];
        aDist += d * d;
      }
    }
    return aDist;
  }

public:
  static T PointBoxSquareDistance(const BVH_VecNt& thePoint, const BVH_Box<T, N>& theBox)
  {
    if (!theBox.IsValid())
    {
      return static_cast<T>(0);
    }
    return PointBoxSquareDistance(thePoint, theBox.CornerMin(), theBox.CornerMax());
  }

  static T PointBoxSquareDistance(const BVH_VecNt& thePoint,
                                  const BVH_VecNt& theCMin,
                                  const BVH_VecNt& theCMax)
  {
    T aDist = T(0);
    for (int i = 0; i < N; ++i)
    {
      if (thePoint[i] < theCMin[i])
      {
        T d = theCMin[i] - thePoint[i];
        aDist += d * d;
      }
      else if (thePoint[i] > theCMax[i])
      {
        T d = thePoint[i] - theCMax[i];
        aDist += d * d;
      }
    }
    return aDist;
  }

public:
  static BVH_VecNt PointBoxProjection(const BVH_VecNt& thePoint, const BVH_Box<T, N>& theBox)
  {
    if (!theBox.IsValid())
    {
      return thePoint;
    }
    return PointBoxProjection(thePoint, theBox.CornerMin(), theBox.CornerMax());
  }

  static BVH_VecNt PointBoxProjection(const BVH_VecNt& thePoint,
                                      const BVH_VecNt& theCMin,
                                      const BVH_VecNt& theCMax)
  {
    return thePoint.cwiseMax(theCMin).cwiseMin(theCMax);
  }

private:
  static void SetVertexState(BVH_PrjStateInTriangle* thePrjState,
                             int*                    theFirstNode,
                             int*                    theLastNode,
                             int                     theVertexIndex)
  {
    if (thePrjState != nullptr)
    {
      *thePrjState  = BVH_PrjStateInTriangle_VERTEX;
      *theFirstNode = theVertexIndex;
      *theLastNode  = theVertexIndex;
    }
  }

  static void SetEdgeState(BVH_PrjStateInTriangle* thePrjState,
                           int*                    theFirstNode,
                           int*                    theLastNode,
                           int                     theStartVertex,
                           int                     theEndVertex)
  {
    if (thePrjState != nullptr)
    {
      *thePrjState  = BVH_PrjStateInTriangle_EDGE;
      *theFirstNode = theStartVertex;
      *theLastNode  = theEndVertex;
    }
  }

  static BVH_VecNt ProjectToEdge(const BVH_VecNt& theEdgeStart,
                                 const BVH_VecNt& theEdge,
                                 T                theDot1,
                                 T                theDot2)
  {
    T aT = theDot1 / (theDot1 + theDot2);
    return theEdgeStart + theEdge * aT;
  }

public:
  static BVH_VecNt PointTriangleProjection(const BVH_VecNt&        thePoint,
                                           const BVH_VecNt&        theNode0,
                                           const BVH_VecNt&        theNode1,
                                           const BVH_VecNt&        theNode2,
                                           BVH_PrjStateInTriangle* thePrjState          = nullptr,
                                           int*                    theNumberOfFirstNode = nullptr,
                                           int*                    theNumberOfLastNode  = nullptr)
  {

    const BVH_VecNt aAB = theNode1 - theNode0;
    const BVH_VecNt aAC = theNode2 - theNode0;
    const BVH_VecNt aBC = theNode2 - theNode1;

    const BVH_VecNt aAP = thePoint - theNode0;
    const BVH_VecNt aBP = thePoint - theNode1;
    const BVH_VecNt aCP = thePoint - theNode2;

    const T aABdotAP = aAB.Dot(aAP);
    const T aACdotAP = aAC.Dot(aAP);

    if (aABdotAP <= T(0) && aACdotAP <= T(0))
    {
      SetVertexState(thePrjState, theNumberOfFirstNode, theNumberOfLastNode, 0);
      return theNode0;
    }

    const T aBAdotBP = -aAB.Dot(aBP);
    const T aBCdotBP = aBC.Dot(aBP);

    if (aBAdotBP <= T(0) && aBCdotBP <= T(0))
    {
      SetVertexState(thePrjState, theNumberOfFirstNode, theNumberOfLastNode, 1);
      return theNode1;
    }

    const T aCBdotCP = -aBC.Dot(aCP);
    const T aCAdotCP = -aAC.Dot(aCP);

    if (aCAdotCP <= T(0) && aCBdotCP <= T(0))
    {
      SetVertexState(thePrjState, theNumberOfFirstNode, theNumberOfLastNode, 2);
      return theNode2;
    }

    const T aACdotBP = aAC.Dot(aBP);
    const T aVC      = aABdotAP * aACdotBP + aBAdotBP * aACdotAP;

    if (aVC <= T(0) && aABdotAP > T(0) && aBAdotBP > T(0))
    {
      SetEdgeState(thePrjState, theNumberOfFirstNode, theNumberOfLastNode, 0, 1);
      return ProjectToEdge(theNode0, aAB, aABdotAP, aBAdotBP);
    }

    const T aABdotCP = aAB.Dot(aCP);
    const T aVA      = aBAdotBP * aCAdotCP - aABdotCP * aACdotBP;

    if (aVA <= T(0) && aBCdotBP > T(0) && aCBdotCP > T(0))
    {
      SetEdgeState(thePrjState, theNumberOfFirstNode, theNumberOfLastNode, 1, 2);
      return ProjectToEdge(theNode1, aBC, aBCdotBP, aCBdotCP);
    }

    const T aVB = aABdotCP * aACdotAP + aABdotAP * aCAdotCP;

    if (aVB <= T(0) && aACdotAP > T(0) && aCAdotCP > T(0))
    {
      SetEdgeState(thePrjState, theNumberOfFirstNode, theNumberOfLastNode, 2, 0);
      return ProjectToEdge(theNode0, aAC, aACdotAP, aCAdotCP);
    }

    const T aNorm = aVA + aVB + aVC;

    if (aNorm
        <= std::numeric_limits<T>::epsilon() * (std::abs(aVA) + std::abs(aVB) + std::abs(aVC)))
    {
      SetVertexState(thePrjState, theNumberOfFirstNode, theNumberOfLastNode, 0);
      return (theNode0 + theNode1 + theNode2) / T(3);
    }

    if (thePrjState != nullptr)
    {
      *thePrjState = BVH_PrjStateInTriangle_INNER;
    }

    return (theNode0 * aVA + theNode1 * aVB + theNode2 * aVC) / aNorm;
  }

  static T PointTriangleSquareDistance(const BVH_VecNt& thePoint,
                                       const BVH_VecNt& theNode0,
                                       const BVH_VecNt& theNode1,
                                       const BVH_VecNt& theNode2)
  {
    const BVH_VecNt aProj = PointTriangleProjection(thePoint, theNode0, theNode1, theNode2);
    const BVH_VecNt aPP   = aProj - thePoint;
    return aPP.Dot(aPP);
  }

public:
  static bool RayBoxIntersection(const BVH_Ray<T, N>& theRay,
                                 const BVH_Box<T, N>& theBox,
                                 T&                   theTimeEnter,
                                 T&                   theTimeLeave)
  {
    if (!theBox.IsValid())
    {
      return false;
    }
    return RayBoxIntersection(theRay,
                              theBox.CornerMin(),
                              theBox.CornerMax(),
                              theTimeEnter,
                              theTimeLeave);
  }

  static bool RayBoxIntersection(const BVH_Ray<T, N>& theRay,
                                 const BVH_VecNt&     theBoxCMin,
                                 const BVH_VecNt&     theBoxCMax,
                                 T&                   theTimeEnter,
                                 T&                   theTimeLeave)
  {
    T aTimeEnter = (std::numeric_limits<T>::lowest)();
    T aTimeLeave = (std::numeric_limits<T>::max)();

    for (int i = 0; i < N; ++i)
    {

      if (std::isinf(theRay.InvDirect[i]))
      {
        if (theRay.Origin[i] < theBoxCMin[i] || theRay.Origin[i] > theBoxCMax[i])
        {
          return false;
        }
        continue;
      }
      T aT1      = (theBoxCMin[i] - theRay.Origin[i]) * theRay.InvDirect[i];
      T aT2      = (theBoxCMax[i] - theRay.Origin[i]) * theRay.InvDirect[i];
      aTimeEnter = (std::max)(aTimeEnter, (std::min)(aT1, aT2));
      aTimeLeave = (std::min)(aTimeLeave, (std::max)(aT1, aT2));
      if (aTimeEnter > aTimeLeave)
      {
        return false;
      }
    }

    if (aTimeLeave < T(0))
    {
      return false;
    }

    theTimeEnter = aTimeEnter;
    theTimeLeave = aTimeLeave;
    return true;
  }

  static bool RayBoxIntersection(const BVH_VecNt&     theRayOrigin,
                                 const BVH_VecNt&     theRayDirection,
                                 const BVH_Box<T, N>& theBox,
                                 T&                   theTimeEnter,
                                 T&                   theTimeLeave)
  {
    if (!theBox.IsValid())
    {
      return false;
    }
    return RayBoxIntersection(theRayOrigin,
                              theRayDirection,
                              theBox.CornerMin(),
                              theBox.CornerMax(),
                              theTimeEnter,
                              theTimeLeave);
  }

  static bool RayBoxIntersection(const BVH_VecNt& theRayOrigin,
                                 const BVH_VecNt& theRayDirection,
                                 const BVH_VecNt& theBoxCMin,
                                 const BVH_VecNt& theBoxCMax,
                                 T&               theTimeEnter,
                                 T&               theTimeLeave)
  {
    T aTimeEnter = (std::numeric_limits<T>::lowest)();
    T aTimeLeave = (std::numeric_limits<T>::max)();

    for (int i = 0; i < N; ++i)
    {
      if (theRayDirection[i] == T(0))
      {

        if (theRayOrigin[i] < theBoxCMin[i] || theRayOrigin[i] > theBoxCMax[i])
        {
          return false;
        }

        continue;
      }

      T aT1 = (theBoxCMin[i] - theRayOrigin[i]) / theRayDirection[i];
      T aT2 = (theBoxCMax[i] - theRayOrigin[i]) / theRayDirection[i];

      T aTMin = (std::min)(aT1, aT2);
      T aTMax = (std::max)(aT1, aT2);

      aTimeEnter = (std::max)(aTimeEnter, aTMin);
      aTimeLeave = (std::min)(aTimeLeave, aTMax);

      if (aTimeEnter > aTimeLeave)
      {
        return false;
      }
    }

    if (aTimeLeave < T(0))
    {
      return false;
    }

    theTimeEnter = aTimeEnter;
    theTimeLeave = aTimeLeave;
    return true;
  }
};
