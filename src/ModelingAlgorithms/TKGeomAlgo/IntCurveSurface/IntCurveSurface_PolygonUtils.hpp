#pragma once

#include <Bnd_Box.hpp>
#include <gp_Dir.hpp>
#include <gp_Lin.hpp>
#include <gp_Pnt.hpp>
#include <gp_Vec.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>

namespace IntCurveSurface_PolygonUtils
{

  template <typename CurveType, typename CurveTool>
  void InitUniform(const CurveType&            theCurve,
                   const double                theBinf,
                   const double                theBsup,
                   const int                   theNbPntIn,
                   NCollection_Array1<gp_Pnt>& thePnts,
                   Bnd_Box&                    theBnd,
                   double&                     theDeflection)
  {
    const double du = (theBsup - theBinf) / static_cast<double>(theNbPntIn - 1);
    double       u  = theBinf;
    gp_Pnt       P;

    for (int i = 1; i <= theNbPntIn; ++i)
    {
      CurveTool::D0(theCurve, u, P);
      theBnd.Add(P);
      thePnts.SetValue(i, P);
      u += du;
    }

    theDeflection = 0.0;
    if (theNbPntIn > 3)
    {
      u = theBinf + du * 0.5;
      for (int i = 1; i < theNbPntIn; ++i)
      {
        const gp_Pnt  Pm = CurveTool::Value(theCurve, u);
        const gp_Pnt& P1 = thePnts.Value(i);
        const gp_Pnt& P2 = thePnts.Value(i + 1);
        const gp_Lin  L(P1, gp_Dir(gp_Vec(P1, P2)));
        const double  t = L.Distance(Pm);
        if (t > theDeflection)
        {
          theDeflection = t;
        }
        u += du;
      }
      theBnd.Enlarge(1.5 * theDeflection);
    }
    else
    {
      theBnd.Enlarge(1e-10);
    }
  }

  template <typename CurveType, typename CurveTool>
  void InitWithParams(const CurveType&                          theCurve,
                      const NCollection_Array1<double>&         theUpars,
                      const int                                 theNbPntIn,
                      NCollection_Array1<gp_Pnt>&               thePnts,
                      Bnd_Box&                                  theBnd,
                      double&                                   theDeflection,
                      occ::handle<NCollection_HArray1<double>>& theParams)
  {
    theParams    = new NCollection_HArray1<double>(1, theUpars.Length());
    const int i0 = theUpars.Lower() - 1;
    gp_Pnt    P;

    for (int i = 1; i <= theNbPntIn; ++i)
    {
      theParams->SetValue(i, theUpars(i + i0));
      CurveTool::D0(theCurve, theUpars(i + i0), P);
      theBnd.Add(P);
      thePnts.SetValue(i, P);
    }

    theDeflection = 0.0;
    if (theNbPntIn > 3)
    {
      for (int i = 1; i < theNbPntIn; ++i)
      {
        const double  u  = 0.5 * (theUpars(i0 + i) + theUpars(i0 + i + 1));
        const gp_Pnt  Pm = CurveTool::Value(theCurve, u);
        const gp_Pnt& P1 = thePnts.Value(i);
        const gp_Pnt& P2 = thePnts.Value(i + 1);
        const gp_Lin  L(P1, gp_Dir(gp_Vec(P1, P2)));
        const double  t = L.Distance(Pm);
        if (t > theDeflection)
        {
          theDeflection = t;
        }
      }
      theBnd.Enlarge(1.5 * theDeflection);
    }
    else
    {
      theBnd.Enlarge(1e-10);
    }
  }

  inline double ApproxParamOnCurve(int                                             theIndex,
                                   double                                          theParamOnLine,
                                   const double                                    theBinf,
                                   const double                                    theBsup,
                                   const int                                       theNbPntIn,
                                   const occ::handle<NCollection_HArray1<double>>& theParams)
  {
    if (theParamOnLine < 0.0 || theParamOnLine > 1.0)
    {
#ifdef OCCT_DEBUG
      std::cout << " ParamOnLine  =  " << theParamOnLine << "  avec Index = " << theIndex
                << "  dans IntCurveSurface_Polygon::ApproxParamOnCurve" << std::endl;
#endif
      return theBinf + (theParamOnLine * (theBsup - theBinf)) / static_cast<double>(theNbPntIn - 1);
    }

    int    Index       = theIndex;
    double ParamOnLine = theParamOnLine;

#ifdef OCCT_DEBUG
    if (Index > theNbPntIn)
    {
      std::cout << "OutOfRange Polygon::ApproxParamOnCurve " << std::endl;
    }
#endif

    if ((Index == theNbPntIn) && (ParamOnLine == 0.0))
    {
      Index--;
      ParamOnLine = 1.0;
    }

    double du, u;
    if (theParams.IsNull())
    {
      du = (theBsup - theBinf) / static_cast<double>(theNbPntIn - 1);
      u  = theBinf + du * static_cast<double>(Index - 1);
    }
    else
    {
      du = theParams->Value(Index + 1) - theParams->Value(Index);
      u  = theParams->Value(Index);
    }

    u += du * ParamOnLine;
    return u;
  }

} // namespace IntCurveSurface_PolygonUtils
