#pragma once

#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Adaptor3d_TopolTool.hpp>
#include <Bnd_BoundSortBox.hpp>
#include <Bnd_Box.hpp>
#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_Shape.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <gp_Circ.hpp>
#include <gp_Elips.hpp>
#include <gp_Hypr.hpp>
#include <gp_Lin.hpp>
#include <gp_Parab.hpp>
#include <IntAna_IntConicQuad.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <Intf_Tool.hpp>
#include <math_FunctionSetRoot.hpp>
#include <NCollection_Vector.hpp>
#include <Precision.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
// Copyright (c) 1993-1999 Matra Datavision
// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <Adaptor3d_Curve.hpp>
#include <Adaptor3d_Surface.hpp>
#include <Bnd_Box.hpp>
#include <ElCLib.hpp>
#include <ElSLib.hpp>
#include <Extrema_ExtElC.hpp>
#include <Extrema_POnCurv.hpp>
#include <GeomAbs_CurveType.hpp>
#include <GeomAbs_SurfaceType.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Lin.hpp>
#include <gp_Lin2d.hpp>
#include <gp_Parab2d.hpp>
#include <gp_Pln.hpp>
#include <gp_Vec.hpp>
#include <IntAna_IntConicQuad.hpp>
#include <IntAna_IntLinTorus.hpp>
#include <IntAna_Quadric.hpp>
#include <IntAna2d_AnaIntersection.hpp>
#include <IntAna2d_Conic.hpp>
#include <IntAna2d_IntPoint.hpp>
#include <IntCurveSurface_IntersectionPoint.hpp>
#include <IntCurveSurface_TransitionOnCurve.hpp>
#include <Intf_PIType.hpp>
#include <Intf_SectionPoint.hpp>
#include <Intf_TangentZone.hpp>
#include <math_FunctionSetRoot.hpp>
#include <NCollection_Vector.hpp>
#include <Precision.hpp>
#include <ProjLib_Plane.hpp>
#include <gp_Pnt.hpp>
#include <NCollection_Array2.hpp>
#include <NCollection_Array1.hpp>

namespace IntCurveSurface_InterUtils
{

  constexpr double THE_TOLERANCE_ANGULAIRE = 1.e-12;
  constexpr double THE_TOLTANGENCY         = 0.00000001;

  //! Project theLine and its X-axis symmetric line to thePln and
  //! intersect resulting curve with theBasCurvProj.
  //! Then estimate max and min parameters of intersection on theBasCurvProj.
  inline void ProjectIntersectAndEstLim(const gp_Lin&        theLine,
                                        const gp_Pln&        thePln,
                                        const ProjLib_Plane& theBasCurvProj,
                                        double&              theVmin,
                                        double&              theVmax,
                                        bool&                theNoIntersection)
  {
    ProjLib_Plane aLineProj(thePln, theLine);
    if (!aLineProj.IsDone())
    {
      return;
    }
    gp_Lin2d aLin2d = aLineProj.Line();

    // make a second line X-axe symmetric to the first one
    gp_Pnt2d aP1 = aLin2d.Location();
    gp_Pnt2d aP2(aP1.XY() + aLin2d.Direction().XY());
    gp_Pnt2d aP1sym(aP1.X(), -aP1.Y());
    gp_Pnt2d aP2sym(aP2.X(), -aP2.Y());
    gp_Lin2d aLin2dsym(aP1sym, gp_Vec2d(aP1sym, aP2sym));

    // intersect projections
    IntAna2d_Conic           aCon(aLin2d);
    IntAna2d_Conic           aConSym(aLin2dsym);
    IntAna2d_AnaIntersection anIntersect;
    IntAna2d_AnaIntersection anIntersectSym;

    switch (theBasCurvProj.GetType())
    {
      case GeomAbs_Line:
        anIntersectSym.Perform(theBasCurvProj.Line(), aConSym);
        anIntersect.Perform(theBasCurvProj.Line(), aCon);
        break;
      case GeomAbs_Hyperbola:
        anIntersectSym.Perform(theBasCurvProj.Hyperbola(), aConSym);
        anIntersect.Perform(theBasCurvProj.Hyperbola(), aCon);
        break;
      case GeomAbs_Parabola:
        anIntersectSym.Perform(theBasCurvProj.Parabola(), aConSym);
        anIntersect.Perform(theBasCurvProj.Parabola(), aCon);
        break;
      default:
        return; // not infinite curve
    }

    // retrieve params of intersections
    int aNbIntPnt    = anIntersect.IsDone() ? anIntersect.NbPoints() : 0;
    int aNbIntPntSym = anIntersectSym.IsDone() ? anIntersectSym.NbPoints() : 0;
    int iPnt, aNbPnt = std::max(aNbIntPnt, aNbIntPntSym);

    if (aNbPnt == 0)
    {
      theNoIntersection = true;
      return;
    }
    double aParam;
    for (iPnt = 1; iPnt <= aNbPnt; iPnt++)
    {
      if (iPnt <= aNbIntPnt)
      {
        const IntAna2d_IntPoint& aIntPnt = anIntersect.Point(iPnt);
        aParam                           = aIntPnt.ParamOnFirst();
        theVmin                          = std::min(theVmin, aParam);
        theVmax                          = std::max(theVmax, aParam);
      }
      if (iPnt <= aNbIntPntSym)
      {
        const IntAna2d_IntPoint& aIntPnt = anIntersectSym.Point(iPnt);
        aParam                           = aIntPnt.ParamOnFirst();
        theVmin                          = std::min(theVmin, aParam);
        theVmax                          = std::max(theVmax, aParam);
      }
    }
  }

  //! Estimate limits for infinite surfaces (generic fallback).
  inline void EstLimForInfSurf(double& U1new, double& U2new, double& V1new, double& V2new)
  {
    U1new = std::max(U1new, -1.e10);
    U2new = std::min(U2new, 1.e10);
    V1new = std::max(V1new, -1.e10);
    V2new = std::min(V2new, 1.e10);
  }

  //! Estimate limits for infinite extrusion surfaces.
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  template <typename SurfaceType, typename SurfaceTool>
  void EstLimForInfExtr(const gp_Lin&      Line,
                        const SurfaceType& surface,
                        const bool         IsOffSurf,
                        const int          nbsu,
                        const bool         U1inf,
                        const bool         U2inf,
                        const bool         V1inf,
                        const bool         V2inf,
                        double&            U1new,
                        double&            U2new,
                        double&            V1new,
                        double&            V2new,
                        bool&              NoIntersection)
  {
    NoIntersection = false;

    occ::handle<Adaptor3d_Surface> aBasSurf;

    if (IsOffSurf)
      aBasSurf = SurfaceTool::BasisSurface(surface);

    gp_Dir aDirOfExt;

    if (IsOffSurf)
      aDirOfExt = aBasSurf->Direction();
    else
      aDirOfExt = SurfaceTool::Direction(surface);

    double tolang = THE_TOLERANCE_ANGULAIRE;

    if (aDirOfExt.IsParallel(Line.Direction(), tolang))
    {
      NoIntersection = true;
      return;
    }

    if ((V1inf || V2inf) && !(U1inf || U2inf))
    {
      double          vmin = RealLast(), vmax = -vmin;
      gp_Lin          aL;
      double          step = (U2new - U1new) / nbsu;
      double          u    = U1new, v;
      gp_Pnt          aP;
      Extrema_POnCurv aP1, aP2;
      int             i;

      for (i = 0; i <= nbsu; i++)
      {
        SurfaceTool::D0(surface, u, 0., aP);
        aL.SetLocation(aP);
        aL.SetDirection(aDirOfExt);

        Extrema_ExtElC aExtr(aL, Line, tolang);

        if (!aExtr.IsDone())
          return;

        if (aExtr.IsParallel())
        {
          NoIntersection = true;
          return;
        }

        aExtr.Points(1, aP1, aP2);
        v    = aP1.Parameter();
        vmin = std::min(vmin, v);
        vmax = std::max(vmax, v);

        u += step;
      }

      vmin = vmin - std::abs(vmin) - 10.;
      vmax = vmax + std::abs(vmax) + 10.;

      V1new = std::max(V1new, vmin);
      V2new = std::min(V2new, vmax);
    }
    else if (U1inf || U2inf)
    {
      double umin = RealLast(), umax = -umin;
      double u0 = std::min(std::max(0., U1new), U2new);
      double v0 = std::min(std::max(0., V1new), V2new);
      gp_Pnt aP;
      SurfaceTool::D0(surface, u0, v0, aP);
      gp_Pln aRefPln(aP, aDirOfExt);

      occ::handle<Adaptor3d_Curve> aBasCurv;

      if (IsOffSurf)
        aBasCurv = aBasSurf->BasisCurve();
      else
        aBasCurv = SurfaceTool::BasisCurve(surface);

      ProjLib_Plane Projector(aRefPln);

      Projector.Project(Line);

      if (!Projector.IsDone())
        return;

      gp_Lin2d Line2d = Projector.Line();

      GeomAbs_CurveType aCurvTyp = aBasCurv->GetType();

      if (aCurvTyp == GeomAbs_Line)
      {
        Projector.Project(aBasCurv->Line());

        if (!Projector.IsDone())
          return;

        gp_Lin2d aL2d = Projector.Line();

        IntAna2d_AnaIntersection anInter(Line2d, aL2d);

        if (!anInter.IsDone())
          return;

        if (anInter.IsEmpty() || anInter.IdenticalElements() || anInter.ParallelElements())
        {
          NoIntersection = true;
          return;
        }

        const IntAna2d_IntPoint& anIntPnt = anInter.Point(1);
        umin = umax = anIntPnt.ParamOnSecond();
      }
      else if (aCurvTyp == GeomAbs_Parabola || aCurvTyp == GeomAbs_Hyperbola)
      {
        IntAna2d_Conic           aCon(Line2d);
        IntAna2d_AnaIntersection anInter;

        if (aCurvTyp == GeomAbs_Parabola)
        {
          Projector.Project(aBasCurv->Parabola());
          if (!Projector.IsDone())
            return;

          const gp_Parab2d& aP2d = Projector.Parabola();

          anInter.Perform(aP2d, aCon);
        }
        else
        {
          Projector.Project(aBasCurv->Hyperbola());
          if (!Projector.IsDone())
            return;

          const gp_Hypr2d& aH2d = Projector.Hyperbola();
          anInter.Perform(aH2d, aCon);
        }

        if (!anInter.IsDone())
          return;

        if (anInter.IsEmpty())
        {
          NoIntersection = true;
          return;
        }

        int i, nbint = anInter.NbPoints();
        for (i = 1; i <= nbint; i++)
        {
          const IntAna2d_IntPoint& anIntPnt = anInter.Point(i);

          umin = std::min(anIntPnt.ParamOnFirst(), umin);
          umax = std::max(anIntPnt.ParamOnFirst(), umax);
        }
      }
      else
      {
        return;
      }

      umin = umin - std::abs(umin) - 10;
      umax = umax + std::abs(umax) + 10;

      U1new = std::max(U1new, umin);
      U2new = std::min(U2new, umax);

      if (V1inf || V2inf)
      {
        EstLimForInfExtr<SurfaceType, SurfaceTool>(Line,
                                                   surface,
                                                   IsOffSurf,
                                                   nbsu,
                                                   false,
                                                   false,
                                                   V1inf,
                                                   V2inf,
                                                   U1new,
                                                   U2new,
                                                   V1new,
                                                   V2new,
                                                   NoIntersection);
      }
    }
  }

  //! Estimate V1 and V2 for infinite surfaces of revolution.
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  template <typename SurfaceType, typename SurfaceTool>
  void EstLimForInfRevl(const gp_Lin&      Line,
                        const SurfaceType& surface,
                        const bool         U1inf,
                        const bool         U2inf,
                        const bool         V1inf,
                        const bool         V2inf,
                        double&            U1new,
                        double&            U2new,
                        double&            V1new,
                        double&            V2new,
                        bool&              NoIntersection)
  {
    NoIntersection = false;

    if (U1inf || U2inf)
    {
      if (U1inf)
        U1new = std::max(0., U1new);
      else
        U2new = std::min(2 * M_PI, U2new);
      if (!V1inf && !V2inf)
        return;
    }

    occ::handle<Adaptor3d_Curve> aBasisCurve = SurfaceTool::BasisCurve(surface);
    gp_Ax1                       aRevAx      = SurfaceTool::AxeOfRevolution(surface);
    gp_Vec                       aXVec       = aRevAx.Direction();
    constexpr double             aTolAng     = Precision::Angular();

    // make plane to project a basis curve
    gp_Pnt O  = aRevAx.Location();
    double aU = 0.;
    gp_Pnt P  = aBasisCurve->Value(aU);
    while (O.SquareDistance(P) <= Precision::PConfusion()
           || aXVec.IsParallel(gp_Vec(O, P), aTolAng))
    {
      aU += 1.;
      P = aBasisCurve->Value(aU);
      if (aU > 3)
        // basis curve is a line coinciding with aXVec, P is any not on aXVec
        P = gp_Pnt(aU, aU + 1, aU + 2);
    }
    gp_Vec aNVec = aXVec ^ gp_Vec(O, P);
    gp_Pln aPln(gp_Ax3(O, aNVec, aXVec));

    // project basic curve
    ProjLib_Plane aBasCurvProj(aPln);
    switch (aBasisCurve->GetType())
    {
      case GeomAbs_Line:
        aBasCurvProj.Project(aBasisCurve->Line());
        break;
      case GeomAbs_Hyperbola:
        aBasCurvProj.Project(aBasisCurve->Hyperbola());
        break;
      case GeomAbs_Parabola:
        aBasCurvProj.Project(aBasisCurve->Parabola());
        break;
      default:
        return; // not infinite curve
    }
    if (!aBasCurvProj.IsDone())
    {
      return;
    }
    // make plane to project Line
    if (aXVec.IsParallel(Line.Direction(), aTolAng))
    {
      P = Line.Location();
      while (O.SquareDistance(P) <= Precision::PConfusion())
      {
        aU += 1.;
        P = gp_Pnt(aU, aU + 1, aU + 2); // any not on aXVec
      }
      aNVec = aXVec ^ gp_Vec(O, P);
    }
    else
      aNVec = aXVec.Crossed(Line.Direction());

    aPln = gp_Pln(gp_Ax3(O, aNVec, aXVec));

    // make a second plane perpendicular to the first one, rotated around aXVec
    gp_Pln aPlnPrp = aPln.Rotated(gp_Ax1(O, aXVec), M_PI / 2.);

    // project Line and its X-axe symmetric one to plane and intersect
    // resulting curve with projection of Basic Curve
    double aVmin = RealLast(), aVmax = -aVmin;
    bool   aNoInt1 = false, aNoInt2 = false;
    ProjectIntersectAndEstLim(Line, aPln, aBasCurvProj, aVmin, aVmax, aNoInt1);
    ProjectIntersectAndEstLim(Line, aPlnPrp, aBasCurvProj, aVmin, aVmax, aNoInt2);

    if (aNoInt1 && aNoInt2)
    {
      NoIntersection = true;
      return;
    }

    aVmin = aVmin - std::abs(aVmin) - 10;
    aVmax = aVmax + std::abs(aVmax) + 10;

    if (V1inf)
      V1new = aVmin;
    if (V2inf)
      V2new = aVmax;
  }

  //! Estimate limits for infinite offset surfaces.
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  template <typename SurfaceType, typename SurfaceTool>
  void EstLimForInfOffs(const gp_Lin&      Line,
                        const SurfaceType& surface,
                        const int          nbsu,
                        const bool         U1inf,
                        const bool         U2inf,
                        const bool         V1inf,
                        const bool         V2inf,
                        double&            U1new,
                        double&            U2new,
                        double&            V1new,
                        double&            V2new,
                        bool&              NoIntersection)
  {
    NoIntersection = false;

    const occ::handle<Adaptor3d_Surface>& aBasSurf = SurfaceTool::BasisSurface(surface);
    double                                anOffVal = SurfaceTool::OffsetValue(surface);

    GeomAbs_SurfaceType aTypeOfBasSurf = aBasSurf->GetType();

    //  case for plane, cylinder and cone - make equivalent surface;
    if (aTypeOfBasSurf == GeomAbs_Plane)
    {
      gp_Pln aPln = aBasSurf->Plane();
      gp_Vec aT   = aPln.Position().XDirection() ^ aPln.Position().YDirection();
      aT *= anOffVal;
      aPln.Translate(aT);
      IntAna_IntConicQuad LinPlane(Line, aPln, THE_TOLERANCE_ANGULAIRE);

      if (!LinPlane.IsDone())
        return;

      if (LinPlane.IsParallel() || LinPlane.IsInQuadric())
      {
        NoIntersection = true;
        return;
      }

      double u, v;
      ElSLib::Parameters(aPln, LinPlane.Point(1), u, v);
      U1new = std::max(U1new, u - 10.);
      U2new = std::min(U2new, u + 10.);
      V1new = std::max(V1new, v - 10.);
      V2new = std::min(V2new, v + 10.);
    }
    else if (aTypeOfBasSurf == GeomAbs_Cylinder)
    {
      gp_Cylinder aCyl = aBasSurf->Cylinder();

      double aR  = aCyl.Radius();
      gp_Ax3 anA = aCyl.Position();

      if (anA.Direct())
        aR += anOffVal;
      else
        aR -= anOffVal;

      if (aR >= THE_TOLTANGENCY)
      {
        aCyl.SetRadius(aR);
      }
      else if (aR <= -THE_TOLTANGENCY)
      {
        anA.Rotate(gp_Ax1(anA.Location(), anA.Direction()), M_PI);
        aCyl.SetPosition(anA);
        aCyl.SetRadius(-aR);
      }
      else
      {
        NoIntersection = true;
        return;
      }

      IntAna_IntConicQuad LinCylinder(Line, aCyl);

      if (!LinCylinder.IsDone())
        return;

      if (LinCylinder.IsParallel() || LinCylinder.IsInQuadric())
      {
        NoIntersection = true;
        return;
      }

      int    i, nbp = LinCylinder.NbPoints();
      double vmin = RealLast(), vmax = -vmin, u, v;

      for (i = 1; i <= nbp; i++)
      {
        ElSLib::Parameters(aCyl, LinCylinder.Point(i), u, v);
        vmin = std::min(vmin, v);
        vmax = std::max(vmax, v);
      }

      V1new = std::max(V1new, vmin - std::abs(vmin) - 10.);
      V2new = std::min(V2new, vmax + std::abs(vmax) + 10.);
    }
    else if (aTypeOfBasSurf == GeomAbs_Cone)
    {
      gp_Cone aCon  = aBasSurf->Cone();
      double  anAng = aCon.SemiAngle();
      double  aR    = aCon.RefRadius() + anOffVal * std::cos(anAng);
      gp_Ax3  anA   = aCon.Position();
      if (aR >= 0.)
      {
        gp_Vec aZ(anA.Direction());
        aZ *= -anOffVal * std::sin(anAng);
        anA.Translate(aZ);
        aCon.SetPosition(anA);
        aCon.SetRadius(aR);
        aCon.SetSemiAngle(anAng);
      }
      else
      {
        return;
      }

      IntAna_IntConicQuad LinCone(Line, aCon);

      if (!LinCone.IsDone())
        return;

      if (LinCone.IsParallel() || LinCone.IsInQuadric())
      {
        NoIntersection = true;
        return;
      }

      int    i, nbp = LinCone.NbPoints();
      double vmin = RealLast(), vmax = -vmin, u, v;

      for (i = 1; i <= nbp; i++)
      {
        ElSLib::Parameters(aCon, LinCone.Point(i), u, v);
        vmin = std::min(vmin, v);
        vmax = std::max(vmax, v);
      }

      V1new = std::max(V1new, vmin - std::abs(vmin) - 10.);
      V2new = std::min(V2new, vmax + std::abs(vmax) + 10.);
    }
    else if (aTypeOfBasSurf == GeomAbs_SurfaceOfExtrusion)
    {
      double anU1 = U1new, anU2 = U2new;

      EstLimForInfExtr<SurfaceType, SurfaceTool>(Line,
                                                 surface,
                                                 true,
                                                 nbsu,
                                                 U1inf,
                                                 U2inf,
                                                 V1inf,
                                                 V2inf,
                                                 U1new,
                                                 U2new,
                                                 V1new,
                                                 V2new,
                                                 NoIntersection);

      if (NoIntersection)
        return;

      if (U1inf || U2inf)
      {
        GeomAbs_CurveType aBasCurvType = aBasSurf->BasisCurve()->GetType();
        if (aBasCurvType == GeomAbs_Line)
        {
          U1new = std::max(anU1, -1.e10);
          U2new = std::min(anU2, 1.e10);
        }
        else if (aBasCurvType == GeomAbs_Parabola)
        {
          gp_Parab aPrb = aBasSurf->BasisCurve()->Parabola();
          double   aF   = aPrb.Focal();
          double   dU   = 2.e5 * std::sqrt(aF);
          U1new         = std::max(anU1, -dU);
          U2new         = std::min(anU2, dU);
        }
        else if (aBasCurvType == GeomAbs_Hyperbola)
        {
          U1new = std::max(anU1, -30.);
          U2new = std::min(anU2, 30.);
        }
        else
        {
          U1new = std::max(anU1, -1.e10);
          U2new = std::min(anU2, 1.e10);
        }
      }
    }
    else if (aTypeOfBasSurf == GeomAbs_SurfaceOfRevolution)
    {
      GeomAbs_CurveType aBasCurvType = aBasSurf->BasisCurve()->GetType();
      if (aBasCurvType == GeomAbs_Line)
      {
        V1new = std::max(V1new, -1.e10);
        V2new = std::min(V2new, 1.e10);
      }
      else if (aBasCurvType == GeomAbs_Parabola)
      {
        gp_Parab aPrb = aBasSurf->BasisCurve()->Parabola();
        double   aF   = aPrb.Focal();
        double   dV   = 2.e5 * std::sqrt(aF);
        V1new         = std::max(V1new, -dV);
        V2new         = std::min(V2new, dV);
      }
      else if (aBasCurvType == GeomAbs_Hyperbola)
      {
        V1new = std::max(V1new, -30.);
        V2new = std::min(V2new, 30.);
      }
      else
      {
        V1new = std::max(V1new, -1.e10);
        V2new = std::min(V2new, 1.e10);
      }
    }
    else
    {
      V1new = std::max(V1new, -1.e10);
      V2new = std::min(V2new, 1.e10);
    }
  }

  //! Convert section point to surface and curve parameters.
  //! @tparam PolyhedronType The polyhedron type
  //! @tparam PolygonType The polygon type
  template <typename PolyhedronType, typename PolygonType>
  void SectionPointToParameters(const Intf_SectionPoint& Sp,
                                const PolyhedronType&    Polyhedron,
                                const PolygonType&       Polygon,
                                double&                  U,
                                double&                  V,
                                double&                  W)
  {
    Intf_PIType typ;
    int         Adr1, Adr2;
    double      Param, u, v;
    gp_Pnt      P(Sp.Pnt());

    int    Pt1, Pt2, Pt3;
    double u1 = 0., v1 = 0., param;
    //----------------------------------------------------------------------
    //--          Approximate parameter calculation on surface            --
    //----------------------------------------------------------------------

    Sp.InfoSecond(typ, Adr1, Adr2, Param);
    switch (typ)
    {
      case Intf_VERTEX: //-- Adr1 is the vertex number
      {
        Polyhedron.Parameters(Adr1, u1, v1);
        break;
      }
      case Intf_EDGE:
      {
        Polyhedron.Parameters(Adr1, u1, v1);
        Polyhedron.Parameters(Adr2, u, v);
        u1 += Param * (u - u1);
        v1 += Param * (v - v1);
        break;
      }
      case Intf_FACE:
      {
        double ua, va, ub, vb, uc, vc, ca, cb, cc, cabc;
        Polyhedron.Triangle(Adr1, Pt1, Pt2, Pt3);
        gp_Pnt PA(Polyhedron.Point(Pt1));
        gp_Pnt PB(Polyhedron.Point(Pt2));
        gp_Pnt PC(Polyhedron.Point(Pt3));
        Polyhedron.Parameters(Pt1, ua, va);
        Polyhedron.Parameters(Pt2, ub, vb);
        Polyhedron.Parameters(Pt3, uc, vc);
        gp_Vec Normale(gp_Vec(PA, PB).Crossed(gp_Vec(PA, PC)));
        cc   = (gp_Vec(PA, PB).Crossed(gp_Vec(PA, P))).Dot(Normale);
        ca   = (gp_Vec(PB, PC).Crossed(gp_Vec(PB, P))).Dot(Normale);
        cb   = (gp_Vec(PC, PA).Crossed(gp_Vec(PC, P))).Dot(Normale);
        cabc = ca + cb + cc;

        ca /= cabc;
        cb /= cabc;
        cc /= cabc;

        u1 = ca * ua + cb * ub + cc * uc;
        v1 = ca * va + cb * vb + cc * vc;
        break;
      }
      default:
      {
        break;
      }
    }
    //----------------------------------------------------------------------
    //--              Approximate point calculation on Curve              --
    //----------------------------------------------------------------------
    int SegIndex;

    Sp.InfoFirst(typ, SegIndex, param);
    W = Polygon.ApproxParamOnCurve(SegIndex, param);
    U = u1;
    V = v1;
  }

  //! Compute transitions at intersection point.
  //! @tparam CurveType The curve type
  //! @tparam CurveTool The curve tool class
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  template <typename CurveType, typename CurveTool, typename SurfaceType, typename SurfaceTool>
  void ComputeTransitions(const CurveType&                   curve,
                          const double                       w,
                          IntCurveSurface_TransitionOnCurve& TransOnCurve,
                          const SurfaceType&                 surface,
                          const double                       u,
                          const double                       v)
  {
    gp_Vec NSurf, D1U, D1V;
    gp_Pnt Psurf;
    double CosDir;

    SurfaceTool::D1(surface, u, v, Psurf, D1U, D1V);
    NSurf = D1U.Crossed(D1V);
    CurveTool::D1(curve, w, Psurf, D1U);
    double Norm = NSurf.Magnitude();
    if (Norm > THE_TOLERANCE_ANGULAIRE && D1U.SquareMagnitude() > THE_TOLERANCE_ANGULAIRE)
    {
      D1U.Normalize();
      CosDir = NSurf.Dot(D1U);
      CosDir /= Norm;
      if (-CosDir > THE_TOLERANCE_ANGULAIRE)
      {
        //--  --Curve--->    <----Surface----
        TransOnCurve = IntCurveSurface_In;
      }
      else if (CosDir > THE_TOLERANCE_ANGULAIRE)
      {
        //--  --Curve--->  ----Surface-->
        TransOnCurve = IntCurveSurface_Out;
      }
      else
      {
        TransOnCurve = IntCurveSurface_Tangent;
      }
    }
    else
    {
      TransOnCurve = IntCurveSurface_Tangent;
    }
  }

  //! Compute parameters on quadric surface from a point.
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  template <typename SurfaceType, typename SurfaceTool>
  void ComputeParamsOnQuadric(const SurfaceType& surface, const gp_Pnt& P, double& u, double& v)
  {
    GeomAbs_SurfaceType SurfaceType_ = SurfaceTool::GetType(surface);
    switch (SurfaceType_)
    {
      case GeomAbs_Plane:
      {
        ElSLib::Parameters(SurfaceTool::Plane(surface), P, u, v);
        break;
      }
      case GeomAbs_Cylinder:
      {
        ElSLib::Parameters(SurfaceTool::Cylinder(surface), P, u, v);
        break;
      }
      case GeomAbs_Cone:
      {
        ElSLib::Parameters(SurfaceTool::Cone(surface), P, u, v);
        break;
      }
      case GeomAbs_Sphere:
      {
        ElSLib::Parameters(SurfaceTool::Sphere(surface), P, u, v);
        break;
      }
      default:
        break;
    }
  }

  //! Sample surface points into array and compute bounding box.
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  template <typename SurfaceType, typename SurfaceTool>
  void DoSurface(const SurfaceType&          theSurface,
                 const double                theU0,
                 const double                theU1,
                 const double                theV0,
                 const double                theV1,
                 NCollection_Array2<gp_Pnt>& thePntsOnSurface,
                 Bnd_Box&                    theBoxSurface,
                 double&                     theGap)
  {
    int    iU = 0, iV = 0;
    double U = 0., V = 0.;
    double dU = (theU1 - theU0) / 50., dV = (theV1 - theV0) / 50.;
    gp_Pnt aPnt;

    for (iU = 0; iU < 50; iU++)
    {
      if (iU == 0)
        U = theU0;
      else if (iU == 49)
        U = theU1;
      else
        U = theU0 + dU * ((double)iU);

      for (iV = 0; iV < 50; iV++)
      {
        if (iV == 0)
          V = theV0;
        else if (iV == 49)
          V = theV1;
        else
          V = theV0 + dV * ((double)iV);

        SurfaceTool::D0(theSurface, U, V, aPnt);
        theBoxSurface.Add(aPnt);
        thePntsOnSurface.SetValue(iU + 1, iV + 1, aPnt);
      }
    }
    double Ures = SurfaceTool::UResolution(theSurface, dU);
    double Vres = SurfaceTool::VResolution(theSurface, dV);
    theGap      = std::max(Ures, Vres);
  }

  //! Compute new bounds for surface based on intersection with bounding box corners.
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  template <typename SurfaceType, typename SurfaceTool>
  void DoNewBounds(const SurfaceType&                theSurface,
                   const double                      theU0,
                   const double                      theU1,
                   const double                      theV0,
                   const double                      theV1,
                   const NCollection_Array2<gp_Pnt>& thePntsOnSurface,
                   const NCollection_Array1<double>& theX,
                   const NCollection_Array1<double>& theY,
                   const NCollection_Array1<double>& theZ,
                   NCollection_Array1<double>&       theBounds)
  {
    theBounds.SetValue(1, theU0);
    theBounds.SetValue(2, theU1);
    theBounds.SetValue(3, theV0);
    theBounds.SetValue(4, theV1);

    bool isUClosed = (SurfaceTool::IsUClosed(theSurface) || SurfaceTool::IsUPeriodic(theSurface));
    bool isVClosed = (SurfaceTool::IsVClosed(theSurface) || SurfaceTool::IsVPeriodic(theSurface));
    bool checkU    = (isUClosed) ? false : true;
    bool checkV    = (isVClosed) ? false : true;

    int i = 0, j = 0, k = 0, iU = 0, iV = 0;
    int iUmin = 50, iVmin = 50, iUmax = 1, iVmax = 1;

    for (i = 1; i <= 2; i++)
    {
      for (j = 1; j <= 2; j++)
      {
        for (k = 1; k <= 2; k++)
        {
          gp_Pnt aPoint(theX(i), theY(j), theZ(k));
          double DistMin = 1.e+100;
          int    diU = 0, diV = 0;
          for (iU = 1; iU <= 50; iU++)
          {
            for (iV = 1; iV <= 50; iV++)
            {
              const gp_Pnt aP   = thePntsOnSurface.Value(iU, iV);
              double       dist = aP.SquareDistance(aPoint);
              if (dist < DistMin)
              {
                DistMin = dist;
                diU     = iU;
                diV     = iV;
              }
            }
          }
          if (diU > 0 && diU < iUmin)
            iUmin = diU;
          if (diU > 0 && diU > iUmax)
            iUmax = diU;
          if (diV > 0 && diV < iVmin)
            iVmin = diV;
          if (diV > 0 && diV > iVmax)
            iVmax = diV;
        }
      }
    }

    double dU = (theU1 - theU0) / 50., dV = (theV1 - theV0) / 50.;

    double USmin = theU0 + dU * ((double)(iUmin - 1));
    double USmax = theU0 + dU * ((double)(iUmax - 1));
    double VSmin = theV0 + dV * ((double)(iVmin - 1));
    double VSmax = theV0 + dV * ((double)(iVmax - 1));

    if (USmin > USmax)
    {
      double tmp = USmax;
      USmax      = USmin;
      USmin      = tmp;
    }
    if (VSmin > VSmax)
    {
      double tmp = VSmax;
      VSmax      = VSmin;
      VSmin      = tmp;
    }

    USmin -= 1.5 * dU;
    if (USmin < theU0)
      USmin = theU0;
    USmax += 1.5 * dU;
    if (USmax > theU1)
      USmax = theU1;
    VSmin -= 1.5 * dV;
    if (VSmin < theV0)
      VSmin = theV0;
    VSmax += 1.5 * dV;
    if (VSmax > theV1)
      VSmax = theV1;

    if (checkU)
    {
      theBounds.SetValue(1, USmin);
      theBounds.SetValue(2, USmax);
    }
    if (checkV)
    {
      theBounds.SetValue(3, VSmin);
      theBounds.SetValue(4, VSmax);
    }
  }

  //! Compute intersection point with parameter validation and transition computation.
  //! Returns true if the point is valid and should be appended.
  //! @tparam CurveType The curve type
  //! @tparam CurveTool The curve tool class
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  //! @param[out] thePoint The computed intersection point (valid only if returns true)
  template <typename CurveType, typename CurveTool, typename SurfaceType, typename SurfaceTool>
  bool ComputeAppendPoint(const CurveType&                   theCurve,
                          const double                       theLw,
                          const SurfaceType&                 theSurface,
                          const double                       theSu,
                          const double                       theSv,
                          IntCurveSurface_IntersectionPoint& thePoint)
  {
    double W0 = CurveTool::FirstParameter(theCurve);
    double W1 = CurveTool::LastParameter(theCurve);
    double U0 = SurfaceTool::FirstUParameter(theSurface);
    double U1 = SurfaceTool::LastUParameter(theSurface);
    double V0 = SurfaceTool::FirstVParameter(theSurface);
    double V1 = SurfaceTool::LastVParameter(theSurface);

    double w = theLw, u = theSu, v = theSv;

    GeomAbs_CurveType aCType = CurveTool::GetType(theCurve);

    if (CurveTool::IsPeriodic(theCurve) || aCType == GeomAbs_Circle || aCType == GeomAbs_Ellipse)
    {
      w = ElCLib::InPeriod(w, W0, W0 + CurveTool::Period(theCurve));
    }

    if ((W0 - w) >= THE_TOLTANGENCY || (w - W1) >= THE_TOLTANGENCY)
      return false;

    GeomAbs_SurfaceType aSType = SurfaceTool::GetType(theSurface);
    if (SurfaceTool::IsUPeriodic(theSurface) || aSType == GeomAbs_Cylinder || aSType == GeomAbs_Cone
        || aSType == GeomAbs_Sphere)
    {
      u = ElCLib::InPeriod(u, U0, U0 + SurfaceTool::UPeriod(theSurface));
    }

    if (SurfaceTool::IsVPeriodic(theSurface))
    {
      v = ElCLib::InPeriod(v, V0, V0 + SurfaceTool::VPeriod(theSurface));
    }

    if ((U0 - u) >= THE_TOLTANGENCY || (u - U1) >= THE_TOLTANGENCY)
      return false;
    if ((V0 - v) >= THE_TOLTANGENCY || (v - V1) >= THE_TOLTANGENCY)
      return false;

    IntCurveSurface_TransitionOnCurve TransOnCurve;
    ComputeTransitions<CurveType, CurveTool, SurfaceType, SurfaceTool>(theCurve,
                                                                       w,
                                                                       TransOnCurve,
                                                                       theSurface,
                                                                       u,
                                                                       v);
    gp_Pnt P(CurveTool::Value(theCurve, w));
    thePoint = IntCurveSurface_IntersectionPoint(P, u, v, w, TransOnCurve);
    return true;
  }

  //! Process analytical intersection of conic with quadric.
  //! Returns status and computes intersection points.
  //! @tparam CurveType The curve type
  //! @tparam CurveTool The curve tool class
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  //! @param[out] theIsParallel Set to true if curve is parallel or in quadric
  //! @param[out] thePoints Vector of computed intersection points
  //! @return true if the operation was done successfully
  template <typename CurveType, typename CurveTool, typename SurfaceType, typename SurfaceTool>
  bool ProcessIntAna(const CurveType&                                       theCurve,
                     const SurfaceType&                                     theSurface,
                     const IntAna_IntConicQuad&                             theIntAna,
                     bool&                                                  theIsParallel,
                     NCollection_Vector<IntCurveSurface_IntersectionPoint>& thePoints)
  {
    theIsParallel = false;
    thePoints.Clear();

    if (!theIntAna.IsDone())
    {
      return false;
    }

    if (theIntAna.IsInQuadric() || theIntAna.IsParallel())
    {
      theIsParallel = true;
      return true;
    }

    int    nbp = theIntAna.NbPoints();
    double u, v, w;
    for (int i = 1; i <= nbp; i++)
    {
      gp_Pnt P(theIntAna.Point(i));
      w = theIntAna.ParamOnConic(i);
      ComputeParamsOnQuadric<SurfaceType, SurfaceTool>(theSurface, P, u, v);

      IntCurveSurface_IntersectionPoint aPoint;
      if (ComputeAppendPoint<CurveType, CurveTool, SurfaceType, SurfaceTool>(theCurve,
                                                                             w,
                                                                             theSurface,
                                                                             u,
                                                                             v,
                                                                             aPoint))
      {
        thePoints.Append(aPoint);
      }
    }
    return true;
  }

  //! Perform intersection between curve and quadric surface.
  //! Uses exact quadric-curve intersection algorithm.
  //! @tparam QuadCurvExactType The exact quadric-curve intersection type
  //! @tparam CurveType The curve type
  //! @tparam CurveTool The curve tool class
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  //! @param[out] thePoints Vector of computed intersection points
  template <typename QuadCurvExactType,
            typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool>
  void PerformCurveQuadric(const CurveType&                                       theCurve,
                           const SurfaceType&                                     theSurface,
                           NCollection_Vector<IntCurveSurface_IntersectionPoint>& thePoints)
  {
    thePoints.Clear();

    QuadCurvExactType QuadCurv(theSurface, theCurve);
    if (QuadCurv.IsDone())
    {
      int    NbRoots = QuadCurv.NbRoots();
      double u, v, w;
      for (int i = 1; i <= NbRoots; i++)
      {
        w = QuadCurv.Root(i);
        ComputeParamsOnQuadric<SurfaceType, SurfaceTool>(theSurface,
                                                         CurveTool::Value(theCurve, w),
                                                         u,
                                                         v);

        IntCurveSurface_IntersectionPoint aPoint;
        if (ComputeAppendPoint<CurveType, CurveTool, SurfaceType, SurfaceTool>(theCurve,
                                                                               w,
                                                                               theSurface,
                                                                               u,
                                                                               v,
                                                                               aPoint))
        {
          thePoints.Append(aPoint);
        }
      }
    }
  }

  //! Process line-torus intersection.
  //! @tparam CurveType The curve type
  //! @tparam CurveTool The curve tool class
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  //! @return true if intersection was processed successfully, false if fallback is needed
  template <typename CurveType, typename CurveTool, typename SurfaceType, typename SurfaceTool>
  bool ProcessLinTorus(const gp_Lin&                                          theLine,
                       const CurveType&                                       theCurve,
                       const SurfaceType&                                     theSurface,
                       NCollection_Vector<IntCurveSurface_IntersectionPoint>& thePoints)
  {
    thePoints.Clear();

    IntAna_IntLinTorus intlintorus(theLine, SurfaceTool::Torus(theSurface));
    if (!intlintorus.IsDone())
    {
      return false;
    }

    int    nbp = intlintorus.NbPoints();
    double fi, theta, w;
    for (int i = 1; i <= nbp; i++)
    {
      w = intlintorus.ParamOnLine(i);
      intlintorus.ParamOnTorus(i, fi, theta);

      IntCurveSurface_IntersectionPoint aPoint;
      if (ComputeAppendPoint<CurveType, CurveTool, SurfaceType, SurfaceTool>(theCurve,
                                                                             w,
                                                                             theSurface,
                                                                             fi,
                                                                             theta,
                                                                             aPoint))
      {
        thePoints.Append(aPoint);
      }
    }
    return true;
  }

  //! Structure to hold sorted intersection start points.
  struct SortedStartPoints
  {
    NCollection_Vector<double> TabU;
    NCollection_Vector<double> TabV;
    NCollection_Vector<double> TabW;

    void Clear()
    {
      TabU.Clear();
      TabV.Clear();
      TabW.Clear();
    }

    int Size() const { return TabU.Size(); }

    void Append(double theU, double theV, double theW)
    {
      TabU.Append(theU);
      TabV.Append(theV);
      TabW.Append(theW);
    }
  };

  //! Collect section points from interference and convert to parameters.
  //! @tparam InterferenceType The interference type
  //! @tparam PolyhedronType The polyhedron type
  //! @tparam PolygonType The polygon type
  template <typename InterferenceType, typename PolyhedronType, typename PolygonType>
  void CollectInterferencePoints(const InterferenceType& theInterference,
                                 const PolyhedronType&   thePolyhedron,
                                 const PolygonType&      thePolygon,
                                 SortedStartPoints&      thePoints)
  {
    thePoints.Clear();

    int NbSectionPoints = theInterference.NbSectionPoints();
    int NbTangentZones  = theInterference.NbTangentZones();

    double u, v, w;

    for (int i = 1; i <= NbSectionPoints; i++)
    {
      const Intf_SectionPoint& SP = theInterference.PntValue(i);
      SectionPointToParameters<PolyhedronType, PolygonType>(SP, thePolyhedron, thePolygon, u, v, w);
      thePoints.Append(u, v, w);
    }

    for (int i = 1; i <= NbTangentZones; i++)
    {
      const Intf_TangentZone& TZ     = theInterference.ZoneValue(i);
      int                     nbpnts = TZ.NumberOfPoints();
      for (int j = 1; j <= nbpnts; j++)
      {
        const Intf_SectionPoint& SP = TZ.GetPoint(j);
        SectionPointToParameters<PolyhedronType, PolygonType>(SP,
                                                              thePolyhedron,
                                                              thePolygon,
                                                              u,
                                                              v,
                                                              w);
        thePoints.Append(u, v, w);
      }
    }
  }

  //! Sort start points by W, then U, then V parameters.
  //! Uses bubble sort to eliminate duplicates.
  inline void SortStartPoints(SortedStartPoints& thePoints)
  {
    int NbStartPoints = thePoints.Size();
    if (NbStartPoints == 0)
      return;

    double ptol = 10 * Precision::PConfusion();

    // Sort by W
    bool Triok;
    do
    {
      Triok = true;
      for (int i = 1; i < NbStartPoints; i++)
      {
        int im1 = i - 1;
        if (thePoints.TabW(i) < thePoints.TabW(im1))
        {
          std::swap(thePoints.TabW.ChangeValue(i), thePoints.TabW.ChangeValue(im1));
          std::swap(thePoints.TabU.ChangeValue(i), thePoints.TabU.ChangeValue(im1));
          std::swap(thePoints.TabV.ChangeValue(i), thePoints.TabV.ChangeValue(im1));
          Triok = false;
        }
      }
    } while (!Triok);

    // Sort by U for same W
    do
    {
      Triok = true;
      for (int i = 1; i < NbStartPoints; i++)
      {
        int im1 = i - 1;
        if ((thePoints.TabW(i) - thePoints.TabW(im1)) < ptol)
        {
          thePoints.TabW.ChangeValue(i) = thePoints.TabW(im1);
          if (thePoints.TabU(i) < thePoints.TabU(im1))
          {
            std::swap(thePoints.TabU.ChangeValue(i), thePoints.TabU.ChangeValue(im1));
            std::swap(thePoints.TabV.ChangeValue(i), thePoints.TabV.ChangeValue(im1));
            Triok = false;
          }
        }
      }
    } while (!Triok);

    // Sort by V for same W and U
    do
    {
      Triok = true;
      for (int i = 1; i < NbStartPoints; i++)
      {
        int im1 = i - 1;
        if (((thePoints.TabW(i) - thePoints.TabW(im1)) < ptol)
            && ((thePoints.TabU(i) - thePoints.TabU(im1)) < ptol))
        {
          thePoints.TabU.ChangeValue(i) = thePoints.TabU(im1);
          if (thePoints.TabV(i) < thePoints.TabV(im1))
          {
            std::swap(thePoints.TabV.ChangeValue(i), thePoints.TabV.ChangeValue(im1));
            Triok = false;
          }
        }
      }
    } while (!Triok);
  }

  //! Process sorted start points through exact intersection.
  //! @tparam ExactInterType The exact intersection type
  //! @tparam CurveType The curve type
  //! @tparam CurveTool The curve tool class
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  template <typename ExactInterType,
            typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool>
  void ProcessSortedPoints(ExactInterType&                                        theExactInter,
                           math_FunctionSetRoot&                                  theRsnld,
                           const SortedStartPoints&                               thePoints,
                           const double                                           theU0,
                           const double                                           theU1,
                           const double                                           theV0,
                           const double                                           theV1,
                           const double                                           theWinf,
                           const double                                           theWsup,
                           const CurveType&                                       theCurve,
                           const SurfaceType&                                     theSurface,
                           NCollection_Vector<IntCurveSurface_IntersectionPoint>& theResult)
  {
    theResult.Clear();

    int NbStartPoints = thePoints.Size();
    if (NbStartPoints == 0)
      return;

    double ptol = 10 * Precision::PConfusion();
    double su = 0, sv = 0, sw = 0;

    for (int i = 0; i < NbStartPoints; i++)
    {
      double u = thePoints.TabU(i);
      double v = thePoints.TabV(i);
      double w = thePoints.TabW(i);

      if (i == 0)
      {
        su = u - 1;
      }

      if (std::abs(u - su) > ptol || std::abs(v - sv) > ptol || std::abs(w - sw) > ptol)
      {
        theExactInter.Perform(u, v, w, theRsnld, theU0, theU1, theV0, theV1, theWinf, theWsup);
        if (theExactInter.IsDone() && !theExactInter.IsEmpty())
        {
          w = theExactInter.ParameterOnCurve();
          theExactInter.ParameterOnSurface(u, v);

          IntCurveSurface_IntersectionPoint aPoint;
          if (ComputeAppendPoint<CurveType, CurveTool, SurfaceType, SurfaceTool>(theCurve,
                                                                                 w,
                                                                                 theSurface,
                                                                                 u,
                                                                                 v,
                                                                                 aPoint))
          {
            theResult.Append(aPoint);
          }
        }
      }
      su = thePoints.TabU(i);
      sv = thePoints.TabV(i);
      sw = thePoints.TabW(i);
    }
  }

  //! Structure to hold UV parameter bounds.
  struct UVBounds
  {
    double U0;
    double U1;
    double V0;
    double V1;

    UVBounds()
        : U0(0.),
          U1(0.),
          V0(0.),
          V1(0.)
    {
    }

    UVBounds(double theU0, double theU1, double theV0, double theV1)
        : U0(theU0),
          U1(theU1),
          V0(theV0),
          V1(theV1)
    {
    }
  };

  //! Decompose surface into UV intervals based on C2 continuity.
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  template <typename SurfaceType, typename SurfaceTool>
  void DecomposeSurfaceIntervals(const SurfaceType&            theSurface,
                                 NCollection_Vector<UVBounds>& theIntervals)
  {
    theIntervals.Clear();

    int NbUOnS = SurfaceTool::NbUIntervals(theSurface, GeomAbs_C2);
    int NbVOnS = SurfaceTool::NbVIntervals(theSurface, GeomAbs_C2);

    if (NbUOnS > 1)
    {
      NCollection_Array1<double> TabU(1, NbUOnS + 1);
      SurfaceTool::UIntervals(theSurface, TabU, GeomAbs_C2);

      for (int iu = 1; iu <= NbUOnS; iu++)
      {
        double U0 = TabU.Value(iu);
        double U1 = TabU.Value(iu + 1);

        if (NbVOnS > 1)
        {
          NCollection_Array1<double> TabV(1, NbVOnS + 1);
          SurfaceTool::VIntervals(theSurface, TabV, GeomAbs_C2);
          for (int iv = 1; iv <= NbVOnS; iv++)
          {
            double V0 = TabV.Value(iv);
            double V1 = TabV.Value(iv + 1);
            theIntervals.Append(UVBounds(U0, U1, V0, V1));
          }
        }
        else
        {
          double V0 = SurfaceTool::FirstVParameter(theSurface);
          double V1 = SurfaceTool::LastVParameter(theSurface);
          theIntervals.Append(UVBounds(U0, U1, V0, V1));
        }
      }
    }
    else if (NbVOnS > 1)
    {
      double U0 = SurfaceTool::FirstUParameter(theSurface);
      double U1 = SurfaceTool::LastUParameter(theSurface);

      NCollection_Array1<double> TabV(1, NbVOnS + 1);
      SurfaceTool::VIntervals(theSurface, TabV, GeomAbs_C2);

      for (int iv = 1; iv <= NbVOnS; iv++)
      {
        double V0 = TabV.Value(iv);
        double V1 = TabV.Value(iv + 1);
        theIntervals.Append(UVBounds(U0, U1, V0, V1));
      }
    }
    else
    {
      double U0 = SurfaceTool::FirstUParameter(theSurface);
      double U1 = SurfaceTool::LastUParameter(theSurface);
      double V0 = SurfaceTool::FirstVParameter(theSurface);
      double V1 = SurfaceTool::LastVParameter(theSurface);
      theIntervals.Append(UVBounds(U0, U1, V0, V1));
    }
  }

  //! Clamp UV parameters to prevent double overflow.
  //! Protection from double type overflow in square magnitude computation.
  inline void ClampUVParameters(double& theU1, double& theU2, double& theV1, double& theV2)
  {
    constexpr double THE_PARAM_LIMIT = 1.0e50;
    if (theU1 < -THE_PARAM_LIMIT)
      theU1 = -THE_PARAM_LIMIT;
    if (theU2 > THE_PARAM_LIMIT)
      theU2 = THE_PARAM_LIMIT;
    if (theV1 < -THE_PARAM_LIMIT)
      theV1 = -THE_PARAM_LIMIT;
    if (theV2 > THE_PARAM_LIMIT)
      theV2 = THE_PARAM_LIMIT;
  }

} // namespace IntCurveSurface_InterUtils

namespace IntCurveSurface_InterImpl
{

  constexpr double THE_TOLTANGENCY         = 0.00000001;
  constexpr double THE_TOLERANCE_ANGULAIRE = 1.e-12;
  constexpr double THE_TOLERANCE           = 0.00000001;
  constexpr int    THE_NBSAMPLESONCIRCLE   = 32;
  constexpr int    THE_NBSAMPLESONELLIPSE  = 32;
  constexpr int    THE_NBSAMPLESONPARAB    = 16;
  constexpr int    THE_NBSAMPLESONHYPR     = 32;

  //! Perform intersection decomposing surface by C2 intervals.
  //! @tparam CurveType The curve type
  //! @tparam CurveTool The curve tool class
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  //! @tparam PerformBoundsFunc Callback type for Perform with bounds
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename ResetFunc,
            typename PerformBoundsFunc>
  void Perform(const CurveType&   theCurve,
               const SurfaceType& theSurface,
               bool&              theDone,
               ResetFunc          theReset,
               PerformBoundsFunc  thePerformBounds)
  {
    theReset();
    theDone = true;

    NCollection_Vector<IntCurveSurface_InterUtils::UVBounds> aIntervals;
    IntCurveSurface_InterUtils::DecomposeSurfaceIntervals<SurfaceType, SurfaceTool>(theSurface,
                                                                                    aIntervals);

    for (const IntCurveSurface_InterUtils::UVBounds& aBounds : aIntervals)
    {
      thePerformBounds(theCurve, theSurface, aBounds.U0, aBounds.V0, aBounds.U1, aBounds.V1);
    }
  }

  //! Perform intersection with given UV bounds.
  //! @tparam CurveType The curve type
  //! @tparam CurveTool The curve tool class
  //! @tparam SurfaceType The surface type
  //! @tparam SurfaceTool The surface tool class
  //! @tparam PolygonType The polygon type
  //! @tparam PerformConicFunc Callback for conic surface intersection
  //! @tparam InternalPerformFunc Callback for internal perform
  //! @tparam InternalPerformQuadricFunc Callback for quadric perform
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename PolygonType,
            typename PerformConicFunc,
            typename InternalPerformFunc,
            typename InternalPerformQuadricFunc>
  void PerformBounds(const CurveType&           theCurve,
                     const SurfaceType&         theSurface,
                     const double               theU1,
                     const double               theV1,
                     const double               theU2,
                     const double               theV2,
                     PerformConicFunc           thePerformConic,
                     InternalPerformFunc        theInternalPerform,
                     InternalPerformQuadricFunc theInternalPerformQuadric)
  {
    // Protection from double type overflow (bug26525).
    double UU1 = theU1, UU2 = theU2, VV1 = theV1, VV2 = theV2;
    IntCurveSurface_InterUtils::ClampUVParameters(UU1, UU2, VV1, VV2);

    GeomAbs_CurveType aCurveType = CurveTool::GetType(theCurve);

    switch (aCurveType)
    {
      case GeomAbs_Line:
        thePerformConic(CurveTool::Line(theCurve), theCurve, theSurface, UU1, VV1, UU2, VV2);
        break;
      case GeomAbs_Circle:
        thePerformConic(CurveTool::Circle(theCurve), theCurve, theSurface, UU1, VV1, UU2, VV2);
        break;
      case GeomAbs_Ellipse:
        thePerformConic(CurveTool::Ellipse(theCurve), theCurve, theSurface, UU1, VV1, UU2, VV2);
        break;
      case GeomAbs_Parabola:
        thePerformConic(CurveTool::Parabola(theCurve), theCurve, theSurface, UU1, VV1, UU2, VV2);
        break;
      case GeomAbs_Hyperbola:
        thePerformConic(CurveTool::Hyperbola(theCurve), theCurve, theSurface, UU1, VV1, UU2, VV2);
        break;
      default:
      {
        int                 nbIntervalsOnCurve = CurveTool::NbIntervals(theCurve, GeomAbs_C2);
        GeomAbs_SurfaceType aSurfaceType       = SurfaceTool::GetType(theSurface);
        if ((aSurfaceType != GeomAbs_Plane) && (aSurfaceType != GeomAbs_Cylinder)
            && (aSurfaceType != GeomAbs_Cone) && (aSurfaceType != GeomAbs_Sphere))
        {
          if (nbIntervalsOnCurve > 1)
          {
            NCollection_Array1<double> TabW(1, nbIntervalsOnCurve + 1);
            CurveTool::Intervals(theCurve, TabW, GeomAbs_C2);
            for (int i = 1; i <= nbIntervalsOnCurve; i++)
            {
              double u1 = TabW.Value(i);
              double u2 = TabW.Value(i + 1);

              occ::handle<NCollection_HArray1<double>> aPars;
              double                                   defl  = 0.1;
              int                                      NbMin = 10;
              CurveTool::SamplePars(theCurve, u1, u2, defl, NbMin, aPars);

              PolygonType polygon(theCurve, aPars->Array1());
              theInternalPerform(theCurve, polygon, theSurface, UU1, VV1, UU2, VV2);
            }
          }
          else
          {
            double u1 = CurveTool::FirstParameter(theCurve);
            double u2 = CurveTool::LastParameter(theCurve);

            occ::handle<NCollection_HArray1<double>> aPars;
            double                                   defl  = 0.1;
            int                                      NbMin = 10;
            CurveTool::SamplePars(theCurve, u1, u2, defl, NbMin, aPars);

            PolygonType polygon(theCurve, aPars->Array1());
            theInternalPerform(theCurve, polygon, theSurface, UU1, VV1, UU2, VV2);
          }
        }
        else
        {
          theInternalPerformQuadric(theCurve, theSurface);
        }
      }
    }
  }

  //! Perform with polygon, creating polyhedron internally.
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename PolygonType,
            typename PolyhedronType,
            typename ResetFunc,
            typename PerformPolyFunc>
  void PerformPolygon(const CurveType&   theCurve,
                      const PolygonType& thePolygon,
                      const SurfaceType& theSurface,
                      bool&              theDone,
                      ResetFunc          theReset,
                      PerformPolyFunc    thePerformPoly)
  {
    theReset();
    theDone     = true;
    double u1   = SurfaceTool::FirstUParameter(theSurface);
    double v1   = SurfaceTool::FirstVParameter(theSurface);
    double u2   = SurfaceTool::LastUParameter(theSurface);
    double v2   = SurfaceTool::LastVParameter(theSurface);
    int    nbsu = SurfaceTool::NbSamplesU(theSurface, u1, u2);
    int    nbsv = SurfaceTool::NbSamplesV(theSurface, v1, v2);
    if (nbsu > 40)
      nbsu = 40;
    if (nbsv > 40)
      nbsv = 40;
    PolyhedronType polyhedron(theSurface, nbsu, nbsv, u1, v1, u2, v2);
    thePerformPoly(theCurve, thePolygon, theSurface, polyhedron);
  }

  //! Perform with polyhedron, creating polygon internally.
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename PolygonType,
            typename PolyhedronType,
            typename ResetFunc,
            typename PerformPolyFunc>
  void PerformPolyhedron(const CurveType&      theCurve,
                         const SurfaceType&    theSurface,
                         const PolyhedronType& thePolyhedron,
                         bool&                 theDone,
                         ResetFunc             theReset,
                         PerformPolyFunc       thePerformPoly)
  {
    theReset();
    theDone        = true;
    double      u1 = CurveTool::FirstParameter(theCurve);
    double      u2 = CurveTool::LastParameter(theCurve);
    PolygonType polygon(theCurve, CurveTool::NbSamples(theCurve, u1, u2));
    thePerformPoly(theCurve, polygon, theSurface, thePolyhedron);
  }

  //! Perform with both polygon and polyhedron provided.
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename PolygonType,
            typename PolyhedronType,
            typename ResetFunc,
            typename InternalPerformFunc>
  void PerformPolygonPolyhedron(const CurveType&      theCurve,
                                const PolygonType&    thePolygon,
                                const SurfaceType&    theSurface,
                                const PolyhedronType& thePolyhedron,
                                bool&                 theDone,
                                ResetFunc             theReset,
                                InternalPerformFunc   theInternalPerform)
  {
    theReset();
    theDone   = true;
    double u1 = SurfaceTool::FirstUParameter(theSurface);
    double v1 = SurfaceTool::FirstVParameter(theSurface);
    double u2 = SurfaceTool::LastUParameter(theSurface);
    double v2 = SurfaceTool::LastVParameter(theSurface);
    theInternalPerform(theCurve, thePolygon, theSurface, thePolyhedron, u1, v1, u2, v2);
  }

  //! Perform with polygon, polyhedron and bounding sort box.
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename PolygonType,
            typename PolyhedronType,
            typename ResetFunc,
            typename InternalPerformBSBFunc>
  void PerformPolygonPolyhedronBSB(const CurveType&       theCurve,
                                   const PolygonType&     thePolygon,
                                   const SurfaceType&     theSurface,
                                   const PolyhedronType&  thePolyhedron,
                                   Bnd_BoundSortBox&      theBSB,
                                   bool&                  theDone,
                                   ResetFunc              theReset,
                                   InternalPerformBSBFunc theInternalPerform)
  {
    theReset();
    theDone   = true;
    double u1 = SurfaceTool::FirstUParameter(theSurface);
    double v1 = SurfaceTool::FirstVParameter(theSurface);
    double u2 = SurfaceTool::LastUParameter(theSurface);
    double v2 = SurfaceTool::LastVParameter(theSurface);
    theInternalPerform(theCurve, thePolygon, theSurface, thePolyhedron, u1, v1, u2, v2, theBSB);
  }

  //! Internal perform with interference from BSB.
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename PolygonType,
            typename PolyhedronType,
            typename InterferenceType,
            typename CSFunctionType,
            typename ExactInterType,
            typename AppendFunc>
  void InternalPerformBSB(const CurveType&      theCurve,
                          const PolygonType&    thePolygon,
                          const SurfaceType&    theSurface,
                          const PolyhedronType& thePolyhedron,
                          const double          theU0,
                          const double          theV0,
                          const double          theU1,
                          const double          theV1,
                          Bnd_BoundSortBox&     theBSB,
                          AppendFunc            theAppend)
  {
    InterferenceType     interference(thePolygon, thePolyhedron, theBSB);
    CSFunctionType       theicsfunction(theSurface, theCurve);
    ExactInterType       intersectionExacte(theicsfunction, THE_TOLTANGENCY);
    math_FunctionSetRoot rsnld(intersectionExacte.Function());

    double winf = thePolygon.InfParameter();
    double wsup = thePolygon.SupParameter();

    IntCurveSurface_InterUtils::SortedStartPoints aStartPoints;
    IntCurveSurface_InterUtils::
      CollectInterferencePoints<InterferenceType, PolyhedronType, PolygonType>(interference,
                                                                               thePolyhedron,
                                                                               thePolygon,
                                                                               aStartPoints);
    IntCurveSurface_InterUtils::SortStartPoints(aStartPoints);

    NCollection_Vector<IntCurveSurface_IntersectionPoint> aResultPoints;
    IntCurveSurface_InterUtils::
      ProcessSortedPoints<ExactInterType, CurveType, CurveTool, SurfaceType, SurfaceTool>(
        intersectionExacte,
        rsnld,
        aStartPoints,
        theU0,
        theU1,
        theV0,
        theV1,
        winf,
        wsup,
        theCurve,
        theSurface,
        aResultPoints);

    for (const IntCurveSurface_IntersectionPoint& aPoint : aResultPoints)
    {
      theAppend(aPoint);
    }
  }

  //! Internal perform without BSB.
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename PolygonType,
            typename PolyhedronType,
            typename InterferenceType,
            typename CSFunctionType,
            typename ExactInterType,
            typename AppendFunc>
  void InternalPerform(const CurveType&      theCurve,
                       const PolygonType&    thePolygon,
                       const SurfaceType&    theSurface,
                       const PolyhedronType& thePolyhedron,
                       const double          theU0,
                       const double          theV0,
                       const double          theU1,
                       const double          theV1,
                       AppendFunc            theAppend)
  {
    InterferenceType     interference(thePolygon, thePolyhedron);
    CSFunctionType       theicsfunction(theSurface, theCurve);
    ExactInterType       intersectionExacte(theicsfunction, THE_TOLTANGENCY);
    math_FunctionSetRoot rsnld(intersectionExacte.Function());

    double winf = thePolygon.InfParameter();
    double wsup = thePolygon.SupParameter();

    IntCurveSurface_InterUtils::SortedStartPoints aStartPoints;
    IntCurveSurface_InterUtils::
      CollectInterferencePoints<InterferenceType, PolyhedronType, PolygonType>(interference,
                                                                               thePolyhedron,
                                                                               thePolygon,
                                                                               aStartPoints);
    IntCurveSurface_InterUtils::SortStartPoints(aStartPoints);

    NCollection_Vector<IntCurveSurface_IntersectionPoint> aResultPoints;
    IntCurveSurface_InterUtils::
      ProcessSortedPoints<ExactInterType, CurveType, CurveTool, SurfaceType, SurfaceTool>(
        intersectionExacte,
        rsnld,
        aStartPoints,
        theU0,
        theU1,
        theV0,
        theV1,
        winf,
        wsup,
        theCurve,
        theSurface,
        aResultPoints);

    for (const IntCurveSurface_IntersectionPoint& aPoint : aResultPoints)
    {
      theAppend(aPoint);
    }
  }

  //! Internal perform for curve-quadric intersection.
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename QuadCurvExactInterType,
            typename AppendFunc>
  void InternalPerformCurveQuadric(const CurveType&   theCurve,
                                   const SurfaceType& theSurface,
                                   AppendFunc         theAppend)
  {
    NCollection_Vector<IntCurveSurface_IntersectionPoint> aPoints;

    IntCurveSurface_InterUtils::
      PerformCurveQuadric<QuadCurvExactInterType, CurveType, CurveTool, SurfaceType, SurfaceTool>(
        theCurve,
        theSurface,
        aPoints);

    for (const IntCurveSurface_IntersectionPoint& aPoint : aPoints)
    {
      theAppend(aPoint);
    }
  }

  //! Internal perform with polygon and UV bounds, creating polyhedron as needed.
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename PolygonType,
            typename PolyhedronType,
            typename QuadCurvExactInterType,
            typename InternalPerformPolyFunc,
            typename AppendFunc>
  void InternalPerformPolygonBounds(const CurveType&        theCurve,
                                    const PolygonType&      thePolygon,
                                    const SurfaceType&      theSurface,
                                    const double            theU1,
                                    const double            theV1,
                                    const double            theU2,
                                    const double            theV2,
                                    InternalPerformPolyFunc theInternalPerformPoly,
                                    AppendFunc              theAppend)
  {
    GeomAbs_SurfaceType aSurfaceType = SurfaceTool::GetType(theSurface);
    if ((aSurfaceType != GeomAbs_Plane) && (aSurfaceType != GeomAbs_Cylinder)
        && (aSurfaceType != GeomAbs_Cone) && (aSurfaceType != GeomAbs_Sphere))
    {
      if (aSurfaceType != GeomAbs_BSplineSurface)
      {
        int nbsu = SurfaceTool::NbSamplesU(theSurface, theU1, theU2);
        int nbsv = SurfaceTool::NbSamplesV(theSurface, theV1, theV2);
        if (nbsu > 40)
          nbsu = 40;
        if (nbsv > 40)
          nbsv = 40;
        PolyhedronType polyhedron(theSurface, nbsu, nbsv, theU1, theV1, theU2, theV2);
        theInternalPerformPoly(theCurve,
                               thePolygon,
                               theSurface,
                               polyhedron,
                               theU1,
                               theV1,
                               theU2,
                               theV2);
      }
      else
      {
        occ::handle<Adaptor3d_Surface> aS = SurfaceTool::UTrim(theSurface, theU1, theU2, 1.e-9);
        aS                                = aS->VTrim(theV1, theV2, 1.e-9);
        occ::handle<Adaptor3d_TopolTool> aTopTool = new Adaptor3d_TopolTool(aS);
        double                           defl     = 0.1;
        aTopTool->SamplePnts(defl, 10, 10);

        int                        nbpu = aTopTool->NbSamplesU();
        int                        nbpv = aTopTool->NbSamplesV();
        NCollection_Array1<double> Upars(1, nbpu), Vpars(1, nbpv);
        aTopTool->UParameters(Upars);
        aTopTool->VParameters(Vpars);

        PolyhedronType polyhedron(theSurface, Upars, Vpars);
        theInternalPerformPoly(theCurve,
                               thePolygon,
                               theSurface,
                               polyhedron,
                               theU1,
                               theV1,
                               theU2,
                               theV2);
      }
    }
    else
    {
      InternalPerformCurveQuadric<CurveType,
                                  CurveTool,
                                  SurfaceType,
                                  SurfaceTool,
                                  QuadCurvExactInterType>(theCurve, theSurface, theAppend);
    }
  }

  //! Perform conic (line) surface intersection.
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename PolygonType,
            typename PolyhedronType,
            typename AppendIntAnaFunc,
            typename InternalPerformPolyFunc,
            typename AppendFunc>
  void PerformConicSurfLine(const gp_Lin&           theLine,
                            const CurveType&        theCurve,
                            const SurfaceType&      theSurface,
                            const double            theU1,
                            const double            theV1,
                            const double            theU2,
                            const double            theV2,
                            AppendIntAnaFunc        theAppendIntAna,
                            InternalPerformPolyFunc theInternalPerformPoly,
                            AppendFunc              theAppend)
  {
    GeomAbs_SurfaceType aSurfaceType   = SurfaceTool::GetType(theSurface);
    bool                isAnaProcessed = true;

    switch (aSurfaceType)
    {
      case GeomAbs_Plane:
      {
        IntAna_IntConicQuad LinPlane(theLine,
                                     SurfaceTool::Plane(theSurface),
                                     THE_TOLERANCE_ANGULAIRE);
        theAppendIntAna(theCurve, theSurface, LinPlane);
        break;
      }
      case GeomAbs_Cylinder:
      {
        IntAna_IntConicQuad LinCylinder(theLine, SurfaceTool::Cylinder(theSurface));
        theAppendIntAna(theCurve, theSurface, LinCylinder);
        break;
      }
      case GeomAbs_Sphere:
      {
        IntAna_IntConicQuad LinSphere(theLine, SurfaceTool::Sphere(theSurface));
        theAppendIntAna(theCurve, theSurface, LinSphere);
        break;
      }
      case GeomAbs_Torus:
      {
        NCollection_Vector<IntCurveSurface_IntersectionPoint> aPoints;
        if (IntCurveSurface_InterUtils::
              ProcessLinTorus<CurveType, CurveTool, SurfaceType, SurfaceTool>(theLine,
                                                                              theCurve,
                                                                              theSurface,
                                                                              aPoints))
        {
          for (const IntCurveSurface_IntersectionPoint& aPoint : aPoints)
          {
            theAppend(aPoint);
          }
        }
        else
          isAnaProcessed = false;
        break;
      }
      case GeomAbs_Cone:
      {
        constexpr double correction = 1.E+5 * Precision::Angular();
        gp_Cone          cn         = SurfaceTool::Cone(theSurface);
        if (std::abs(cn.SemiAngle()) < M_PI / 2.0 - correction)
        {
          IntAna_IntConicQuad LinCone(theLine, cn);
          theAppendIntAna(theCurve, theSurface, LinCone);
        }
        else
          isAnaProcessed = false;
        break;
      }
      default:
        isAnaProcessed = false;
    }

    if (!isAnaProcessed)
    {
      int nbsu = SurfaceTool::NbSamplesU(theSurface, theU1, theU2);
      int nbsv = SurfaceTool::NbSamplesV(theSurface, theV1, theV2);

      bool U1inf = Precision::IsInfinite(theU1);
      bool U2inf = Precision::IsInfinite(theU2);
      bool V1inf = Precision::IsInfinite(theV1);
      bool V2inf = Precision::IsInfinite(theV2);

      double U1new = theU1, U2new = theU2, V1new = theV1, V2new = theV2;
      bool   NoIntersection = false;

      if (U1inf || U2inf || V1inf || V2inf)
      {
        if (aSurfaceType == GeomAbs_SurfaceOfExtrusion)
        {
          IntCurveSurface_InterUtils::EstLimForInfExtr<SurfaceType, SurfaceTool>(theLine,
                                                                                 theSurface,
                                                                                 false,
                                                                                 nbsu,
                                                                                 U1inf,
                                                                                 U2inf,
                                                                                 V1inf,
                                                                                 V2inf,
                                                                                 U1new,
                                                                                 U2new,
                                                                                 V1new,
                                                                                 V2new,
                                                                                 NoIntersection);
        }
        else if (aSurfaceType == GeomAbs_SurfaceOfRevolution)
        {
          IntCurveSurface_InterUtils::EstLimForInfRevl<SurfaceType, SurfaceTool>(theLine,
                                                                                 theSurface,
                                                                                 U1inf,
                                                                                 U2inf,
                                                                                 V1inf,
                                                                                 V2inf,
                                                                                 U1new,
                                                                                 U2new,
                                                                                 V1new,
                                                                                 V2new,
                                                                                 NoIntersection);
        }
        else if (aSurfaceType == GeomAbs_OffsetSurface)
        {
          IntCurveSurface_InterUtils::EstLimForInfOffs<SurfaceType, SurfaceTool>(theLine,
                                                                                 theSurface,
                                                                                 nbsu,
                                                                                 U1inf,
                                                                                 U2inf,
                                                                                 V1inf,
                                                                                 V2inf,
                                                                                 U1new,
                                                                                 U2new,
                                                                                 V1new,
                                                                                 V2new,
                                                                                 NoIntersection);
        }
        else
        {
          IntCurveSurface_InterUtils::EstLimForInfSurf(U1new, U2new, V1new, V2new);
        }
      }

      if (NoIntersection)
        return;

      if (nbsu < 20)
        nbsu = 20;
      if (nbsv < 20)
        nbsv = 20;

      PolyhedronType polyhedron(theSurface, nbsu, nbsv, U1new, V1new, U2new, V2new);
      Intf_Tool      bndTool;
      Bnd_Box        boxLine;
      bndTool.LinBox(theLine, polyhedron.Bounding(), boxLine);

      for (int nbseg = 1; nbseg <= bndTool.NbSegments(); nbseg++)
      {
        double pinf = bndTool.BeginParam(nbseg);
        double psup = bndTool.EndParam(nbseg);
        if ((psup - pinf) < 1e-10)
        {
          pinf -= 1e-10;
          psup += 1e-10;
        }
        PolygonType polygon(theCurve, pinf, psup, 2);
        theInternalPerformPoly(theCurve,
                               polygon,
                               theSurface,
                               polyhedron,
                               U1new,
                               V1new,
                               U2new,
                               V2new);
      }
    }
  }

  //! Perform conic (circle) surface intersection.
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename PolygonType,
            typename AppendIntAnaFunc,
            typename InternalPerformFunc>
  void PerformConicSurfCircle(const gp_Circ&      theCircle,
                              const CurveType&    theCurve,
                              const SurfaceType&  theSurface,
                              const double        theU1,
                              const double        theV1,
                              const double        theU2,
                              const double        theV2,
                              AppendIntAnaFunc    theAppendIntAna,
                              InternalPerformFunc theInternalPerform)
  {
    GeomAbs_SurfaceType aSurfaceType = SurfaceTool::GetType(theSurface);
    switch (aSurfaceType)
    {
      case GeomAbs_Plane:
      {
        IntAna_IntConicQuad CircPlane(theCircle,
                                      SurfaceTool::Plane(theSurface),
                                      THE_TOLERANCE_ANGULAIRE,
                                      THE_TOLERANCE);
        theAppendIntAna(theCurve, theSurface, CircPlane);
        break;
      }
      case GeomAbs_Cylinder:
      {
        IntAna_IntConicQuad CircCylinder(theCircle, SurfaceTool::Cylinder(theSurface));
        theAppendIntAna(theCurve, theSurface, CircCylinder);
        break;
      }
      case GeomAbs_Cone:
      {
        IntAna_IntConicQuad CircCone(theCircle, SurfaceTool::Cone(theSurface));
        theAppendIntAna(theCurve, theSurface, CircCone);
        break;
      }
      case GeomAbs_Sphere:
      {
        IntAna_IntConicQuad CircSphere(theCircle, SurfaceTool::Sphere(theSurface));
        theAppendIntAna(theCurve, theSurface, CircSphere);
        break;
      }
      default:
      {
        PolygonType polygon(theCurve, THE_NBSAMPLESONCIRCLE);
        theInternalPerform(theCurve, polygon, theSurface, theU1, theV1, theU2, theV2);
      }
    }
  }

  //! Perform conic (ellipse) surface intersection.
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename PolygonType,
            typename AppendIntAnaFunc,
            typename InternalPerformFunc>
  void PerformConicSurfEllipse(const gp_Elips&     theEllipse,
                               const CurveType&    theCurve,
                               const SurfaceType&  theSurface,
                               const double        theU1,
                               const double        theV1,
                               const double        theU2,
                               const double        theV2,
                               AppendIntAnaFunc    theAppendIntAna,
                               InternalPerformFunc theInternalPerform)
  {
    GeomAbs_SurfaceType aSurfaceType = SurfaceTool::GetType(theSurface);
    switch (aSurfaceType)
    {
      case GeomAbs_Plane:
      {
        IntAna_IntConicQuad EllipsePlane(theEllipse,
                                         SurfaceTool::Plane(theSurface),
                                         THE_TOLERANCE_ANGULAIRE,
                                         THE_TOLERANCE);
        theAppendIntAna(theCurve, theSurface, EllipsePlane);
        break;
      }
      case GeomAbs_Cylinder:
      {
        IntAna_IntConicQuad EllipseCylinder(theEllipse, SurfaceTool::Cylinder(theSurface));
        theAppendIntAna(theCurve, theSurface, EllipseCylinder);
        break;
      }
      case GeomAbs_Cone:
      {
        IntAna_IntConicQuad EllipseCone(theEllipse, SurfaceTool::Cone(theSurface));
        theAppendIntAna(theCurve, theSurface, EllipseCone);
        break;
      }
      case GeomAbs_Sphere:
      {
        IntAna_IntConicQuad EllipseSphere(theEllipse, SurfaceTool::Sphere(theSurface));
        theAppendIntAna(theCurve, theSurface, EllipseSphere);
        break;
      }
      default:
      {
        PolygonType polygon(theCurve, THE_NBSAMPLESONELLIPSE);
        theInternalPerform(theCurve, polygon, theSurface, theU1, theV1, theU2, theV2);
      }
    }
  }

  //! Perform conic (parabola) surface intersection.
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename PolygonType,
            typename PolyhedronType,
            typename AppendIntAnaFunc,
            typename InternalPerformPolyFunc>
  void PerformConicSurfParabola(const gp_Parab&         theParab,
                                const CurveType&        theCurve,
                                const SurfaceType&      theSurface,
                                const double            theU1,
                                const double            theV1,
                                const double            theU2,
                                const double            theV2,
                                AppendIntAnaFunc        theAppendIntAna,
                                InternalPerformPolyFunc theInternalPerformPoly)
  {
    GeomAbs_SurfaceType aSurfaceType = SurfaceTool::GetType(theSurface);
    switch (aSurfaceType)
    {
      case GeomAbs_Plane:
      {
        IntAna_IntConicQuad ParabPlane(theParab,
                                       SurfaceTool::Plane(theSurface),
                                       THE_TOLERANCE_ANGULAIRE);
        theAppendIntAna(theCurve, theSurface, ParabPlane);
        break;
      }
      case GeomAbs_Cylinder:
      {
        IntAna_IntConicQuad ParabCylinder(theParab, SurfaceTool::Cylinder(theSurface));
        theAppendIntAna(theCurve, theSurface, ParabCylinder);
        break;
      }
      case GeomAbs_Cone:
      {
        IntAna_IntConicQuad ParabCone(theParab, SurfaceTool::Cone(theSurface));
        theAppendIntAna(theCurve, theSurface, ParabCone);
        break;
      }
      case GeomAbs_Sphere:
      {
        IntAna_IntConicQuad ParabSphere(theParab, SurfaceTool::Sphere(theSurface));
        theAppendIntAna(theCurve, theSurface, ParabSphere);
        break;
      }
      default:
      {
        int nbsu = SurfaceTool::NbSamplesU(theSurface, theU1, theU2);
        int nbsv = SurfaceTool::NbSamplesV(theSurface, theV1, theV2);
        if (nbsu > 40)
          nbsu = 40;
        if (nbsv > 40)
          nbsv = 40;
        PolyhedronType polyhedron(theSurface, nbsu, nbsv, theU1, theV1, theU2, theV2);
        Intf_Tool      bndTool;
        Bnd_Box        boxParab;
        bndTool.ParabBox(theParab, polyhedron.Bounding(), boxParab);
        for (int nbseg = 1; nbseg <= bndTool.NbSegments(); nbseg++)
        {
          PolygonType polygon(theCurve,
                              bndTool.BeginParam(nbseg),
                              bndTool.EndParam(nbseg),
                              THE_NBSAMPLESONPARAB);
          theInternalPerformPoly(theCurve,
                                 polygon,
                                 theSurface,
                                 polyhedron,
                                 theU1,
                                 theV1,
                                 theU2,
                                 theV2);
        }
      }
    }
  }

  //! Perform conic (hyperbola) surface intersection.
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename PolygonType,
            typename PolyhedronType,
            typename AppendIntAnaFunc,
            typename InternalPerformPolyFunc>
  void PerformConicSurfHyperbola(const gp_Hypr&          theHypr,
                                 const CurveType&        theCurve,
                                 const SurfaceType&      theSurface,
                                 const double            theU1,
                                 const double            theV1,
                                 const double            theU2,
                                 const double            theV2,
                                 AppendIntAnaFunc        theAppendIntAna,
                                 InternalPerformPolyFunc theInternalPerformPoly)
  {
    GeomAbs_SurfaceType aSurfaceType = SurfaceTool::GetType(theSurface);
    switch (aSurfaceType)
    {
      case GeomAbs_Plane:
      {
        IntAna_IntConicQuad HyprPlane(theHypr,
                                      SurfaceTool::Plane(theSurface),
                                      THE_TOLERANCE_ANGULAIRE);
        theAppendIntAna(theCurve, theSurface, HyprPlane);
        break;
      }
      case GeomAbs_Cylinder:
      {
        IntAna_IntConicQuad HyprCylinder(theHypr, SurfaceTool::Cylinder(theSurface));
        theAppendIntAna(theCurve, theSurface, HyprCylinder);
        break;
      }
      case GeomAbs_Cone:
      {
        IntAna_IntConicQuad HyprCone(theHypr, SurfaceTool::Cone(theSurface));
        theAppendIntAna(theCurve, theSurface, HyprCone);
        break;
      }
      case GeomAbs_Sphere:
      {
        IntAna_IntConicQuad HyprSphere(theHypr, SurfaceTool::Sphere(theSurface));
        theAppendIntAna(theCurve, theSurface, HyprSphere);
        break;
      }
      default:
      {
        int nbsu = SurfaceTool::NbSamplesU(theSurface, theU1, theU2);
        int nbsv = SurfaceTool::NbSamplesV(theSurface, theV1, theV2);
        if (nbsu > 40)
          nbsu = 40;
        if (nbsv > 40)
          nbsv = 40;
        PolyhedronType polyhedron(theSurface, nbsu, nbsv, theU1, theV1, theU2, theV2);
        Intf_Tool      bndTool;
        Bnd_Box        boxHypr;
        bndTool.HyprBox(theHypr, polyhedron.Bounding(), boxHypr);
        for (int nbseg = 1; nbseg <= bndTool.NbSegments(); nbseg++)
        {
          PolygonType polygon(theCurve,
                              bndTool.BeginParam(nbseg),
                              bndTool.EndParam(nbseg),
                              THE_NBSAMPLESONHYPR);
          theInternalPerformPoly(theCurve,
                                 polygon,
                                 theSurface,
                                 polyhedron,
                                 theU1,
                                 theV1,
                                 theU2,
                                 theV2);
        }
      }
    }
  }

  //! Append analytical intersection results.
  template <typename CurveType,
            typename CurveTool,
            typename SurfaceType,
            typename SurfaceTool,
            typename AppendFunc>
  void AppendIntAna(const CurveType&           theCurve,
                    const SurfaceType&         theSurface,
                    const IntAna_IntConicQuad& theIntAna,
                    bool&                      theIsParallel,
                    AppendFunc                 theAppend)
  {
    bool                                                  aIsParallel = false;
    NCollection_Vector<IntCurveSurface_IntersectionPoint> aPoints;

    if (IntCurveSurface_InterUtils::ProcessIntAna<CurveType, CurveTool, SurfaceType, SurfaceTool>(
          theCurve,
          theSurface,
          theIntAna,
          aIsParallel,
          aPoints))
    {
      if (aIsParallel)
      {
        theIsParallel = true;
      }
      else
      {
        for (const IntCurveSurface_IntersectionPoint& aPoint : aPoints)
        {
          theAppend(aPoint);
        }
      }
    }
  }

} // namespace IntCurveSurface_InterImpl
