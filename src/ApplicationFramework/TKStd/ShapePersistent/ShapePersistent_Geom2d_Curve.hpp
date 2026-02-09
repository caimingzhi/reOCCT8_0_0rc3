#pragma once

#include <ShapePersistent_Geom2d.hpp>
#include <ShapePersistent_HArray1.hpp>
#include <StdLPersistent_HArray1.hpp>

#include <Geom2d_Line.hpp>
#include <Geom2d_Circle.hpp>
#include <Geom2d_Ellipse.hpp>
#include <Geom2d_Hyperbola.hpp>
#include <Geom2d_Parabola.hpp>
#include <Geom2d_BezierCurve.hpp>
#include <Geom2d_BSplineCurve.hpp>
#include <Geom2d_TrimmedCurve.hpp>
#include <Geom2d_OffsetCurve.hpp>

#include <gp_Circ2d.hpp>
#include <gp_Elips2d.hpp>
#include <gp_Hypr2d.hpp>
#include <gp_Parab2d.hpp>

class ShapePersistent_Geom2d_Curve : public ShapePersistent_Geom2d
{
  typedef Curve::PersistentBase pBase;

  typedef pBase pBounded;

  class pBezier : public pBounded
  {
    friend class ShapePersistent_Geom2d_Curve;

  public:
    pBezier()
        : myRational(false)
    {
    }

    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      theReadData >> myRational >> myPoles >> myWeights;
    }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myRational << myPoles << myWeights;
    }

    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      theChildren.Append(myPoles);
      theChildren.Append(myWeights);
    }

    inline const char* PName() const { return "PGeom2d_BezierCurve"; }

    occ::handle<Geom2d_Curve> Import() const override;

  private:
    bool                                   myRational;
    Handle(ShapePersistent_HArray1::Pnt2d) myPoles;
    Handle(StdLPersistent_HArray1::Real)   myWeights;
  };

  class pBSpline : public pBounded
  {
    friend class ShapePersistent_Geom2d_Curve;

  public:
    pBSpline()
        : myRational(false),
          myPeriodic(false),
          mySpineDegree(0)
    {
    }

    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      theReadData >> myRational >> myPeriodic >> mySpineDegree;
      theReadData >> myPoles >> myWeights >> myKnots >> myMultiplicities;
    }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myRational << myPeriodic << mySpineDegree;
      theWriteData << myPoles << myWeights << myKnots << myMultiplicities;
    }

    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      theChildren.Append(myPoles);
      theChildren.Append(myWeights);
      theChildren.Append(myKnots);
      theChildren.Append(myMultiplicities);
    }

    inline const char* PName() const { return "PGeom2d_BSplineCurve"; }

    occ::handle<Geom2d_Curve> Import() const override;

  private:
    bool                                    myRational;
    bool                                    myPeriodic;
    int                                     mySpineDegree;
    Handle(ShapePersistent_HArray1::Pnt2d)  myPoles;
    Handle(StdLPersistent_HArray1::Real)    myWeights;
    Handle(StdLPersistent_HArray1::Real)    myKnots;
    Handle(StdLPersistent_HArray1::Integer) myMultiplicities;
  };

  class pTrimmed : public pBounded
  {
    friend class ShapePersistent_Geom2d_Curve;

  public:
    pTrimmed()
        : myFirstU(0.0),
          myLastU(0.0)
    {
    }

    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      theReadData >> myBasisCurve >> myFirstU >> myLastU;
    }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myBasisCurve << myFirstU << myLastU;
    }

    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      theChildren.Append(myBasisCurve);
    }

    inline const char* PName() const { return "PGeom2d_TrimmedCurve"; }

    occ::handle<Geom2d_Curve> Import() const override;

  private:
    occ::handle<Curve> myBasisCurve;
    double             myFirstU;
    double             myLastU;
  };

  class pOffset : public pBase
  {
    friend class ShapePersistent_Geom2d_Curve;

  public:
    pOffset()
        : myOffsetValue(0.0)
    {
    }

    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      theReadData >> myBasisCurve >> myOffsetValue;
    }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myBasisCurve << myOffsetValue;
    }

    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      theChildren.Append(myBasisCurve);
    }

    inline const char* PName() const { return "PGeom2d_OffsetCurve"; }

    occ::handle<Geom2d_Curve> Import() const override;

  private:
    occ::handle<Curve> myBasisCurve;
    double             myOffsetValue;
  };

public:
  typedef instance<Curve, Geom2d_Line, gp_Ax2d> Line;

  typedef subBase_gp<Curve, gp_Ax22d>                  Conic;
  typedef instance<Conic, Geom2d_Circle, gp_Circ2d>    Circle;
  typedef instance<Conic, Geom2d_Ellipse, gp_Elips2d>  Ellipse;
  typedef instance<Conic, Geom2d_Hyperbola, gp_Hypr2d> Hyperbola;
  typedef instance<Conic, Geom2d_Parabola, gp_Parab2d> Parabola;

  typedef subBase_empty<Curve>       Bounded;
  typedef Delayed<Bounded, pBezier>  Bezier;
  typedef Delayed<Bounded, pBSpline> BSpline;
  typedef Delayed<Bounded, pTrimmed> Trimmed;

  typedef Delayed<Curve, pOffset> Offset;

public:
  Standard_EXPORT static occ::handle<Curve> Translate(
    const occ::handle<Geom2d_Line>& theCurve,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Curve> Translate(
    const occ::handle<Geom2d_Circle>& theCurve,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Curve> Translate(
    const occ::handle<Geom2d_Ellipse>& theCurve,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Curve> Translate(
    const occ::handle<Geom2d_Hyperbola>& theCurve,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Curve> Translate(
    const occ::handle<Geom2d_Parabola>& theCurve,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Curve> Translate(
    const occ::handle<Geom2d_BezierCurve>& theCurve,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Curve> Translate(
    const occ::handle<Geom2d_BSplineCurve>& theCurve,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Curve> Translate(
    const occ::handle<Geom2d_TrimmedCurve>& theCurve,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Curve> Translate(
    const occ::handle<Geom2d_OffsetCurve>& theCurve,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);
};

template <>
const char* ShapePersistent_Geom2d_Curve::
  instance<ShapePersistent_Geom2d::Curve, Geom2d_Line, gp_Ax2d>::PName() const;

template <>
void ShapePersistent_Geom2d_Curve::instance<ShapePersistent_Geom2d::Curve, Geom2d_Line, gp_Ax2d>::
  Write(StdObjMgt_WriteData& theWriteData) const;

template <>
const char* ShapePersistent_Geom2d_Curve::subBase_gp<ShapePersistent_Geom2d::Curve,
                                                     gp_Ax22d>::PName() const;

template <>
const char* ShapePersistent_Geom2d_Curve::
  instance<ShapePersistent_Geom2d_Curve::Conic, Geom2d_Circle, gp_Circ2d>::PName() const;

template <>
void ShapePersistent_Geom2d_Curve::
  instance<ShapePersistent_Geom2d_Curve::Conic, Geom2d_Circle, gp_Circ2d>::Write(
    StdObjMgt_WriteData& theWriteData) const;

template <>
const char* ShapePersistent_Geom2d_Curve::
  instance<ShapePersistent_Geom2d_Curve::Conic, Geom2d_Ellipse, gp_Elips2d>::PName() const;

template <>
void ShapePersistent_Geom2d_Curve::
  instance<ShapePersistent_Geom2d_Curve::Conic, Geom2d_Ellipse, gp_Elips2d>::Write(
    StdObjMgt_WriteData& theWriteData) const;

template <>
const char* ShapePersistent_Geom2d_Curve::
  instance<ShapePersistent_Geom2d_Curve::Conic, Geom2d_Hyperbola, gp_Hypr2d>::PName() const;

template <>
void ShapePersistent_Geom2d_Curve::
  instance<ShapePersistent_Geom2d_Curve::Conic, Geom2d_Hyperbola, gp_Hypr2d>::Write(
    StdObjMgt_WriteData& theWriteData) const;

template <>
const char* ShapePersistent_Geom2d_Curve::
  instance<ShapePersistent_Geom2d_Curve::Conic, Geom2d_Parabola, gp_Parab2d>::PName() const;

template <>
void ShapePersistent_Geom2d_Curve::
  instance<ShapePersistent_Geom2d_Curve::Conic, Geom2d_Parabola, gp_Parab2d>::Write(
    StdObjMgt_WriteData& theWriteData) const;
