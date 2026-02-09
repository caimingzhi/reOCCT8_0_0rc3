#pragma once

#include <Bnd_Box.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <GeomGridEval_Surface.hpp>
#include <gp.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <gp_XYZ.hpp>
#include <NCollection_Array2.hpp>
#include <Standard_Real.hpp>

namespace IntCurveSurface_PolyhedronUtils
{

  constexpr double THE_MIN_EDGE_LENGTH_SQUARED = 1e-15;

  inline void InitUniform(GeomGridEval_Surface& theEval,
                          const double          theU0,
                          const double          theV0,
                          const double          theU1,
                          const double          theV1,
                          const int             theNbDeltaU,
                          const int             theNbDeltaV,
                          gp_Pnt*               thePnts,
                          double*               theU,
                          double*               theV,
                          bool*                 theIsOnBounds,
                          Bnd_Box&              theBnd)
  {
    const double dU = (theU1 - theU0) / static_cast<double>(theNbDeltaU);
    const double dV = (theV1 - theV0) / static_cast<double>(theNbDeltaV);

    const int aNbU = theNbDeltaU + 1;
    const int aNbV = theNbDeltaV + 1;

    NCollection_Array1<double> aUParams(1, aNbU);
    NCollection_Array1<double> aVParams(1, aNbV);

    for (int i = 0; i < aNbU; ++i)
    {
      aUParams(i + 1) = theU0 + i * dU;
    }
    for (int j = 0; j < aNbV; ++j)
    {
      aVParams(j + 1) = theV0 + j * dV;
    }

    const NCollection_Array2<gp_Pnt> aGrid = theEval.EvaluateGrid(aUParams, aVParams);

    int Index = 1;
    for (int i1 = 0; i1 < aNbU; ++i1)
    {
      for (int i2 = 0; i2 < aNbV; ++i2)
      {
        const gp_Pnt& TP     = aGrid(i1 + 1, i2 + 1);
        thePnts[Index]       = TP;
        theU[Index]          = aUParams(i1 + 1);
        theV[Index]          = aVParams(i2 + 1);
        theIsOnBounds[Index] = (i1 == 0 || i1 == theNbDeltaU || i2 == 0 || i2 == theNbDeltaV);
        theBnd.Add(TP);
        ++Index;
      }
    }
  }

  inline void InitWithParams(GeomGridEval_Surface&             theEval,
                             const NCollection_Array1<double>& theUpars,
                             const NCollection_Array1<double>& theVpars,
                             const int                         theNbDeltaU,
                             const int                         theNbDeltaV,
                             gp_Pnt*                           thePnts,
                             double*                           theU,
                             double*                           theV,
                             bool*                             theIsOnBounds,
                             Bnd_Box&                          theBnd)
  {

    const NCollection_Array2<gp_Pnt> aGrid = theEval.EvaluateGrid(theUpars, theVpars);

    const int i0    = theUpars.Lower();
    const int j0    = theVpars.Lower();
    int       Index = 1;

    for (int i1 = 0; i1 <= theNbDeltaU; ++i1)
    {
      for (int i2 = 0; i2 <= theNbDeltaV; ++i2)
      {
        const gp_Pnt& TP     = aGrid(i1 + 1, i2 + 1);
        thePnts[Index]       = TP;
        theU[Index]          = theUpars(i1 + i0);
        theV[Index]          = theVpars(i2 + j0);
        theIsOnBounds[Index] = (i1 == 0 || i1 == theNbDeltaU || i2 == 0 || i2 == theNbDeltaV);
        theBnd.Add(TP);
        ++Index;
      }
    }
  }

  inline double ComputeBorderDeflection(GeomGridEval_Surface& theEval,
                                        const double          theParameter,
                                        const double          thePMin,
                                        const double          thePMax,
                                        const bool            theIsUIso,
                                        const int             theNbSamples)
  {

    const double aDelta  = (thePMax - thePMin) / theNbSamples;
    const int    aNbPnts = 2 * theNbSamples + 1;

    NCollection_Array1<double> aVaryingParams(1, aNbPnts);
    NCollection_Array1<double> aFixedParams(1, 1);
    aFixedParams(1) = theParameter;

    for (int i = 0; i <= theNbSamples; ++i)
    {
      aVaryingParams(2 * i + 1) = thePMin + i * aDelta;
      if (i < theNbSamples)
      {
        aVaryingParams(2 * i + 2) = thePMin + (i + 0.5) * aDelta;
      }
    }

    const NCollection_Array2<gp_Pnt> aGrid = theIsUIso
                                               ? theEval.EvaluateGrid(aFixedParams, aVaryingParams)
                                               : theEval.EvaluateGrid(aVaryingParams, aFixedParams);

    double aDeflection = RealFirst();

    for (int i = 0; i < theNbSamples; ++i)
    {

      gp_XYZ aP1, aP2, aPParMid;

      if (theIsUIso)
      {
        aP1      = aGrid(1, 2 * i + 1).XYZ();
        aP2      = aGrid(1, 2 * i + 3).XYZ();
        aPParMid = aGrid(1, 2 * i + 2).XYZ();
      }
      else
      {
        aP1      = aGrid(2 * i + 1, 1).XYZ();
        aP2      = aGrid(2 * i + 3, 1).XYZ();
        aPParMid = aGrid(2 * i + 2, 1).XYZ();
      }

      const gp_XYZ aPMid = (aP2 + aP1) / 2.0;
      const double aDist = (aPMid - aPParMid).Modulus();

      if (aDist > aDeflection)
        aDeflection = aDist;
    }

    return aDeflection;
  }

  inline int NbTriangles(const int theNbDeltaU, const int theNbDeltaV)
  {
    return theNbDeltaU * theNbDeltaV * 2;
  }

  inline int NbPoints(const int theNbDeltaU, const int theNbDeltaV)
  {
    return (theNbDeltaU + 1) * (theNbDeltaV + 1);
  }

  inline void Triangle(const int theIndex,
                       int&      theP1,
                       int&      theP2,
                       int&      theP3,
                       const int theNbDeltaV)
  {
    const int line   = 1 + ((theIndex - 1) / (theNbDeltaV * 2));
    const int colon  = 1 + ((theIndex - 1) % (theNbDeltaV * 2));
    const int colpnt = (colon + 1) / 2;

    theP1 = (line - 1) * (theNbDeltaV + 1) + colpnt;
    theP2 = line * (theNbDeltaV + 1) + colpnt + ((colon - 1) % 2);
    theP3 = (line - 1 + (colon % 2)) * (theNbDeltaV + 1) + colpnt + 1;
  }

  inline int TriConnex(const int theTriang,
                       const int thePivot,
                       const int thePedge,
                       int&      theTriCon,
                       int&      theOtherP,
                       const int theNbDeltaU,
                       const int theNbDeltaV)
  {
    const int Pivotm1    = thePivot - 1;
    const int nbdeltaVp1 = theNbDeltaV + 1;
    const int nbdeltaVm2 = theNbDeltaV + theNbDeltaV;

    const int ligP = Pivotm1 / nbdeltaVp1;
    const int colP = Pivotm1 - ligP * nbdeltaVp1;

    int ligE = 0, colE = 0, typE = 0;
    if (thePedge != 0)
    {
      ligE = (thePedge - 1) / nbdeltaVp1;
      colE = (thePedge - 1) - (ligE * nbdeltaVp1);
      if (ligP == ligE)
        typE = 1;
      else if (colP == colE)
        typE = 2;
      else
        typE = 3;
    }

    int linT = 0, colT = 0;
    int linO = 0, colO = 0;
    int t = 0, tt = 0;

    if (theTriang != 0)
    {
      t    = (theTriang - 1) / nbdeltaVm2;
      tt   = (theTriang - 1) - t * nbdeltaVm2;
      linT = 1 + t;
      colT = 1 + tt;
      if (typE == 0)
      {
        if (ligP == linT)
        {
          ligE = ligP - 1;
          colE = colP - 1;
          typE = 3;
        }
        else
        {
          if (colT == ligP + ligP)
          {
            ligE = ligP;
            colE = colP - 1;
            typE = 1;
          }
          else
          {
            ligE = ligP + 1;
            colE = colP + 1;
            typE = 3;
          }
        }
      }
      switch (typE)
      {
        case 1:
          if (linT == ligP)
          {
            linT++;
            linO = ligP + 1;
            colO = (colP > colE) ? colP : colE;
          }
          else
          {
            linT--;
            linO = ligP - 1;
            colO = (colP < colE) ? colP : colE;
          }
          break;
        case 2:
          if (colT == (colP + colP))
          {
            colT++;
            linO = (ligP > ligE) ? ligP : ligE;
            colO = colP + 1;
          }
          else
          {
            colT--;
            linO = (ligP < ligE) ? ligP : ligE;
            colO = colP - 1;
          }
          break;
        case 3:
          if ((colT & 1) == 0)
          {
            colT--;
            linO = (ligP > ligE) ? ligP : ligE;
            colO = (colP < colE) ? colP : colE;
          }
          else
          {
            colT++;
            linO = (ligP < ligE) ? ligP : ligE;
            colO = (colP > colE) ? colP : colE;
          }
          break;
      }
    }
    else
    {
      if (thePedge == 0)
      {
        linT = (1 > ligP) ? 1 : ligP;
        colT = (1 > (colP + colP)) ? 1 : (colP + colP);
        if (ligP == 0)
          linO = ligP + 1;
        else
          linO = ligP - 1;
        colO = colP;
      }
      else
      {
        switch (typE)
        {
          case 1:
            linT = ligP + 1;
            colT = (colP > colE) ? colP : colE;
            colT += colT;
            linO = ligP + 1;
            colO = (colP > colE) ? colP : colE;
            break;
          case 2:
            linT = (ligP > ligE) ? ligP : ligE;
            colT = colP + colP;
            linO = (ligP < ligE) ? ligP : ligE;
            colO = colP - 1;
            break;
          case 3:
            linT = (ligP > ligE) ? ligP : ligE;
            colT = colP + colE;
            linO = (ligP > ligE) ? ligP : ligE;
            colO = (colP < colE) ? colP : colE;
            break;
        }
      }
    }

    theTriCon = (linT - 1) * nbdeltaVm2 + colT;

    if (linT < 1)
    {
      linO = 0;
      colO = colP + colP - colE;
      if (colO < 0)
      {
        colO = 0;
        linO = 1;
      }
      else if (colO > theNbDeltaV)
      {
        colO = theNbDeltaV;
        linO = 1;
      }
      theTriCon = 0;
    }
    else if (linT > theNbDeltaU)
    {
      linO = theNbDeltaU;
      colO = colP + colP - colE;
      if (colO < 0)
      {
        colO = 0;
        linO = theNbDeltaU - 1;
      }
      else if (colO > theNbDeltaV)
      {
        colO = theNbDeltaV;
        linO = theNbDeltaU - 1;
      }
      theTriCon = 0;
    }

    if (colT < 1)
    {
      colO = 0;
      linO = ligP + ligP - ligE;
      if (linO < 0)
      {
        linO = 0;
        colO = 1;
      }
      else if (linO > theNbDeltaU)
      {
        linO = theNbDeltaU;
        colO = 1;
      }
      theTriCon = 0;
    }
    else if (colT > theNbDeltaV)
    {
      colO = theNbDeltaV;
      linO = ligP + ligP - ligE;
      if (linO < 0)
      {
        linO = 0;
        colO = theNbDeltaV - 1;
      }
      else if (linO > theNbDeltaU)
      {
        linO = theNbDeltaU;
        colO = theNbDeltaV - 1;
      }
      theTriCon = 0;
    }

    theOtherP = linO * nbdeltaVp1 + colO + 1;

    return theTriCon;
  }

  inline void PlaneEquation(const gp_Pnt& theP1,
                            const gp_Pnt& theP2,
                            const gp_Pnt& theP3,
                            gp_XYZ&       theNormalVector,
                            double&       thePolarDistance)
  {
    const gp_XYZ v1 = theP2.XYZ() - theP1.XYZ();
    const gp_XYZ v2 = theP3.XYZ() - theP2.XYZ();
    const gp_XYZ v3 = theP1.XYZ() - theP3.XYZ();

    if (v1.SquareModulus() <= THE_MIN_EDGE_LENGTH_SQUARED)
    {
      theNormalVector.SetCoord(1.0, 0.0, 0.0);
      return;
    }
    if (v2.SquareModulus() <= THE_MIN_EDGE_LENGTH_SQUARED)
    {
      theNormalVector.SetCoord(1.0, 0.0, 0.0);
      return;
    }
    if (v3.SquareModulus() <= THE_MIN_EDGE_LENGTH_SQUARED)
    {
      theNormalVector.SetCoord(1.0, 0.0, 0.0);
      return;
    }

    theNormalVector       = (v1 ^ v2) + (v2 ^ v3) + (v3 ^ v1);
    const double aNormLen = theNormalVector.Modulus();
    if (aNormLen < gp::Resolution())
    {
      thePolarDistance = 0.0;
    }
    else
    {
      theNormalVector.Divide(aNormLen);
      thePolarDistance = theNormalVector * theP1.XYZ();
    }
  }

  inline bool Contain(const gp_Pnt& theP1,
                      const gp_Pnt& theP2,
                      const gp_Pnt& theP3,
                      const gp_Pnt& theTestPnt)
  {
    const gp_XYZ v1 = (theP2.XYZ() - theP1.XYZ()) ^ (theTestPnt.XYZ() - theP1.XYZ());
    const gp_XYZ v2 = (theP3.XYZ() - theP2.XYZ()) ^ (theTestPnt.XYZ() - theP2.XYZ());
    const gp_XYZ v3 = (theP1.XYZ() - theP3.XYZ()) ^ (theTestPnt.XYZ() - theP3.XYZ());

    return (v1 * v2 >= 0.0 && v2 * v3 >= 0.0 && v3 * v1 >= 0.0);
  }

  inline void FillBounding(const gp_Pnt*                                    thePnts,
                           const int                                        theNbDeltaU,
                           const int                                        theNbDeltaV,
                           const double                                     theDeflection,
                           const occ::handle<NCollection_HArray1<Bnd_Box>>& theComponentsBnd)
  {
    Bnd_Box   Boite;
    int       np1, np2, np3;
    const int nbtriangles = NbTriangles(theNbDeltaU, theNbDeltaV);

    for (int iTri = 1; iTri <= nbtriangles; ++iTri)
    {
      Triangle(iTri, np1, np2, np3, theNbDeltaV);
      const gp_Pnt& p1 = thePnts[np1];
      const gp_Pnt& p2 = thePnts[np2];
      const gp_Pnt& p3 = thePnts[np3];
      Boite.SetVoid();
      if (p1.SquareDistance(p2) > THE_MIN_EDGE_LENGTH_SQUARED)
      {
        if (p1.SquareDistance(p3) > THE_MIN_EDGE_LENGTH_SQUARED)
        {
          if (p2.SquareDistance(p3) > THE_MIN_EDGE_LENGTH_SQUARED)
          {
            Boite.Add(p1);
            Boite.Add(p2);
            Boite.Add(p3);
            Boite.Enlarge(theDeflection);
          }
        }
      }
      Boite.Enlarge(theDeflection);
      theComponentsBnd->SetValue(iTri, Boite);
    }
  }

  inline double ComputeDeflectionWithCenter(const gp_Pnt& theP1,
                                            const gp_Pnt& theP2,
                                            const gp_Pnt& theP3,
                                            const gp_Pnt& theCenter)
  {

    if (theP1.SquareDistance(theP2) <= THE_MIN_EDGE_LENGTH_SQUARED)
      return 0.0;
    if (theP1.SquareDistance(theP3) <= THE_MIN_EDGE_LENGTH_SQUARED)
      return 0.0;
    if (theP2.SquareDistance(theP3) <= THE_MIN_EDGE_LENGTH_SQUARED)
      return 0.0;

    const gp_XYZ XYZ1 = theP2.XYZ() - theP1.XYZ();
    const gp_XYZ XYZ2 = theP3.XYZ() - theP2.XYZ();
    const gp_XYZ XYZ3 = theP1.XYZ() - theP3.XYZ();
    gp_Vec       NormalVector((XYZ1 ^ XYZ2) + (XYZ2 ^ XYZ3) + (XYZ3 ^ XYZ1));

    const double aNormLen = NormalVector.Magnitude();
    if (aNormLen < gp::Resolution())
      return 0.0;

    NormalVector.Divide(aNormLen);

    const gp_Vec P1P(theP1, theCenter);
    return std::abs(P1P.Dot(NormalVector));
  }

  template <typename PolyhedronType>
  double ComputeMaxDeflection(GeomGridEval_Surface& theEval,
                              const PolyhedronType& thePolyhedron,
                              const int             theNbTriangles)
  {
    if (theNbTriangles <= 0)
      return 0.0;

    NCollection_Array1<gp_Pnt2d> aCentroidUVs(1, theNbTriangles);

    for (int i = 1; i <= theNbTriangles; ++i)
    {
      int i1, i2, i3;
      thePolyhedron.Triangle(i, i1, i2, i3);

      double u1, v1, u2, v2, u3, v3;
      thePolyhedron.Point(i1, u1, v1);
      thePolyhedron.Point(i2, u2, v2);
      thePolyhedron.Point(i3, u3, v3);

      const double uCenter = (u1 + u2 + u3) / 3.0;
      const double vCenter = (v1 + v2 + v3) / 3.0;
      aCentroidUVs.SetValue(i, gp_Pnt2d(uCenter, vCenter));
    }

    NCollection_Array1<gp_Pnt> aCenterPoints = theEval.EvaluatePoints(aCentroidUVs);
    if (aCenterPoints.IsEmpty())
      return 0.0;

    double tol = 0.0;
    for (int i = 1; i <= theNbTriangles; ++i)
    {
      int i1, i2, i3;
      thePolyhedron.Triangle(i, i1, i2, i3);

      double       u1, v1, u2, v2, u3, v3;
      const gp_Pnt P1 = thePolyhedron.Point(i1, u1, v1);
      const gp_Pnt P2 = thePolyhedron.Point(i2, u2, v2);
      const gp_Pnt P3 = thePolyhedron.Point(i3, u3, v3);

      const double tol1 = ComputeDeflectionWithCenter(P1, P2, P3, aCenterPoints.Value(i));
      if (tol1 > tol)
        tol = tol1;
    }
    return tol;
  }

  inline double ComputeMaxBorderDeflection(GeomGridEval_Surface& theEval,
                                           const double          theU0,
                                           const double          theV0,
                                           const double          theU1,
                                           const double          theV1,
                                           const int             theNbDeltaU,
                                           const int             theNbDeltaV)
  {
    double maxDeflection = RealFirst();

    double aDeflection = ComputeBorderDeflection(theEval, theU0, theV0, theV1, true, theNbDeltaV);
    if (aDeflection > maxDeflection)
      maxDeflection = aDeflection;

    aDeflection = ComputeBorderDeflection(theEval, theU1, theV0, theV1, true, theNbDeltaV);
    if (aDeflection > maxDeflection)
      maxDeflection = aDeflection;

    aDeflection = ComputeBorderDeflection(theEval, theV0, theU0, theU1, false, theNbDeltaU);
    if (aDeflection > maxDeflection)
      maxDeflection = aDeflection;

    aDeflection = ComputeBorderDeflection(theEval, theV1, theU0, theU1, false, theNbDeltaU);
    if (aDeflection > maxDeflection)
      maxDeflection = aDeflection;

    return maxDeflection;
  }

  inline bool IsOnBound(const int   theIndex1,
                        const int   theIndex2,
                        const bool* theIsOnBounds,
                        const int   theNbDeltaU,
                        const int   theNbDeltaV)
  {
    const int aDiff = std::abs(theIndex1 - theIndex2);

    if (aDiff != 1 && aDiff != theNbDeltaV + 1)
      return false;

    for (int i = 0; i <= theNbDeltaU; ++i)
    {
      if ((theIndex1 == 1 + i * (theNbDeltaV + 1)) && (theIndex2 == theIndex1 - 1))
        return false;

      if ((theIndex1 == (1 + i) * (theNbDeltaV + 1)) && (theIndex2 == theIndex1 + 1))
        return false;
    }

    return (theIsOnBounds[theIndex1] && theIsOnBounds[theIndex2]);
  }

  inline void Destroy(void*& thePnts, void*& theU, void*& theV, void*& theIsOnBounds)
  {
    if (thePnts)
      delete[] static_cast<gp_Pnt*>(thePnts);
    if (theU)
      delete[] static_cast<double*>(theU);
    if (theV)
      delete[] static_cast<double*>(theV);
    if (theIsOnBounds)
      delete[] static_cast<bool*>(theIsOnBounds);
    thePnts = theU = theV = theIsOnBounds = NULL;
  }

  inline void AllocateArrays(const int theNbDeltaU,
                             const int theNbDeltaV,
                             void*&    thePnts,
                             void*&    theU,
                             void*&    theV,
                             void*&    theIsOnBounds)
  {
    const int t   = (theNbDeltaU + 1) * (theNbDeltaV + 1) + 1;
    thePnts       = new gp_Pnt[t];
    theU          = new double[t];
    theV          = new double[t];
    theIsOnBounds = new bool[t];
  }

  inline void SetDeflectionOverEstimation(const double theFlec,
                                          double&      theDeflection,
                                          Bnd_Box&     theBnd)
  {
    constexpr double THE_MIN_DEFLECTION = 0.0001;
    if (theFlec < THE_MIN_DEFLECTION)
    {
      theDeflection = THE_MIN_DEFLECTION;
      theBnd.Enlarge(THE_MIN_DEFLECTION);
    }
    else
    {
      theDeflection = theFlec;
      theBnd.Enlarge(theFlec);
    }
  }

  inline void Parameters(const int   theIndex,
                         void* const theU,
                         void* const theV,
                         double&     theOutU,
                         double&     theOutV)
  {
    const double* aU = static_cast<const double*>(theU);
    const double* aV = static_cast<const double*>(theV);
    theOutU          = aU[theIndex];
    theOutV          = aV[theIndex];
  }

  inline const gp_Pnt& Point(const int   theIndex,
                             void* const thePnts,
                             void* const theU,
                             void* const theV,
                             double&     theOutU,
                             double&     theOutV)
  {
    const gp_Pnt* aPnts = static_cast<const gp_Pnt*>(thePnts);
    const double* aU    = static_cast<const double*>(theU);
    const double* aV    = static_cast<const double*>(theV);
    theOutU             = aU[theIndex];
    theOutV             = aV[theIndex];
    return aPnts[theIndex];
  }

  inline const gp_Pnt& Point(const int theIndex, void* const thePnts)
  {
    const gp_Pnt* aPnts = static_cast<const gp_Pnt*>(thePnts);
    return aPnts[theIndex];
  }

  inline void Point(const int theIndex, void* const thePnts, gp_Pnt& thePoint)
  {
    const gp_Pnt* aPnts = static_cast<const gp_Pnt*>(thePnts);
    thePoint            = aPnts[theIndex];
  }

} // namespace IntCurveSurface_PolyhedronUtils
