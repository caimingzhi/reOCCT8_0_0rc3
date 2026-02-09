#pragma once

#include <ShapePersistent_Geom.hpp>
#include <ShapePersistent_HArray2.hpp>
#include <StdLPersistent_HArray1.hpp>
#include <StdLPersistent_HArray2.hpp>

#include <Geom_Plane.hpp>
#include <Geom_ConicalSurface.hpp>
#include <Geom_CylindricalSurface.hpp>
#include <Geom_SphericalSurface.hpp>
#include <Geom_ToroidalSurface.hpp>
#include <Geom_SurfaceOfLinearExtrusion.hpp>
#include <Geom_SurfaceOfRevolution.hpp>
#include <Geom_BezierSurface.hpp>
#include <Geom_RectangularTrimmedSurface.hpp>
#include <Geom_OffsetSurface.hpp>

#include <gp_Ax3.hpp>
#include <gp_Cone.hpp>
#include <gp_Cylinder.hpp>
#include <gp_Sphere.hpp>
#include <gp_Torus.hpp>

class ShapePersistent_Geom_Surface : private ShapePersistent_Geom
{
  typedef Surface::PersistentBase pBase;

  class pSweptData
  {
    friend class ShapePersistent_Geom_Surface;

  public:
    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      theReadData >> myBasisCurve >> myDirection;
    }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myBasisCurve << myDirection;
    }

    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      theChildren.Append(myBasisCurve);
    }

  protected:
    occ::handle<Curve> myBasisCurve;
    gp_Dir             myDirection;
  };

  struct pSwept : pBase, pSweptData
  {
    inline const char* PName() const { return "PGeom_SweptSurface"; }
  };

  class pLinearExtrusion : public pSwept
  {
    friend class ShapePersistent_Geom_Surface;

  public:
    occ::handle<Geom_Surface> Import() const override;

    inline const char* PName() const { return "PGeom_SurfaceOfLinearExtrusion"; }
  };

  class pRevolution : public pSwept
  {
    friend class ShapePersistent_Geom_Surface;

  public:
    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      pSwept::Read(theReadData);
      theReadData >> myLocation;
    }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      pSwept::Write(theWriteData);
      theWriteData << myLocation;
    }

    inline const char* PName() const { return "PGeom_SurfaceOfRevolution"; }

    occ::handle<Geom_Surface> Import() const override;

  private:
    gp_Pnt myLocation;
  };

  typedef pBase pBounded;

  class pBezier : public pBounded
  {
    friend class ShapePersistent_Geom_Surface;

  public:
    pBezier()
        : myURational(false),
          myVRational(false)
    {
    }

    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      theReadData >> myURational >> myVRational >> myPoles >> myWeights;
    }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myURational << myVRational << myPoles << myWeights;
    }

    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      theChildren.Append(myPoles);
      theChildren.Append(myWeights);
    }

    inline const char* PName() const { return "PGeom_BezierSurface"; }

    occ::handle<Geom_Surface> Import() const override;

  private:
    bool                                 myURational;
    bool                                 myVRational;
    Handle(ShapePersistent_HArray2::Pnt) myPoles;
    Handle(StdLPersistent_HArray2::Real) myWeights;
  };

  class pBSpline : public pBounded
  {
    friend class ShapePersistent_Geom_Surface;

  public:
    pBSpline()
        : myURational(false),
          myVRational(false),
          myUPeriodic(false),
          myVPeriodic(false),
          myUSpineDegree(0),
          myVSpineDegree(0)
    {
    }

    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      theReadData >> myURational >> myVRational;
      theReadData >> myUPeriodic >> myVPeriodic;
      theReadData >> myUSpineDegree >> myVSpineDegree;
      theReadData >> myPoles;
      theReadData >> myWeights;
      theReadData >> myUKnots >> myVKnots;
      theReadData >> myUMultiplicities >> myVMultiplicities;
    }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myURational << myVRational;
      theWriteData << myUPeriodic << myVPeriodic;
      theWriteData << myUSpineDegree << myVSpineDegree;
      theWriteData << myPoles;
      theWriteData << myWeights;
      theWriteData << myUKnots << myVKnots;
      theWriteData << myUMultiplicities << myVMultiplicities;
    }

    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      theChildren.Append(myPoles);
      theChildren.Append(myWeights);
      theChildren.Append(myUKnots);
      theChildren.Append(myVKnots);
      theChildren.Append(myUMultiplicities);
      theChildren.Append(myVMultiplicities);
    }

    inline const char* PName() const { return "PGeom_BSplineSurface"; }

    occ::handle<Geom_Surface> Import() const override;

  private:
    bool                                    myURational;
    bool                                    myVRational;
    bool                                    myUPeriodic;
    bool                                    myVPeriodic;
    int                                     myUSpineDegree;
    int                                     myVSpineDegree;
    Handle(ShapePersistent_HArray2::Pnt)    myPoles;
    Handle(StdLPersistent_HArray2::Real)    myWeights;
    Handle(StdLPersistent_HArray1::Real)    myUKnots;
    Handle(StdLPersistent_HArray1::Real)    myVKnots;
    Handle(StdLPersistent_HArray1::Integer) myUMultiplicities;
    Handle(StdLPersistent_HArray1::Integer) myVMultiplicities;
  };

  class pRectangularTrimmed : public pBounded
  {
    friend class ShapePersistent_Geom_Surface;

  public:
    pRectangularTrimmed()
        : myFirstU(0.0),
          myLastU(0.0),
          myFirstV(0.0),
          myLastV(0.0)
    {
    }

    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      theReadData >> myBasisSurface;
      theReadData >> myFirstU >> myLastU >> myFirstV >> myLastV;
    }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myBasisSurface;
      theWriteData << myFirstU << myLastU << myFirstV << myLastV;
    }

    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      theChildren.Append(myBasisSurface);
    }

    inline const char* PName() const { return "PGeom_RectangularTrimmedSurface"; }

    occ::handle<Geom_Surface> Import() const override;

  private:
    occ::handle<Surface> myBasisSurface;
    double               myFirstU;
    double               myLastU;
    double               myFirstV;
    double               myLastV;
  };

  class pOffset : public pBase
  {
    friend class ShapePersistent_Geom_Surface;

  public:
    pOffset()
        : myOffsetValue(0.0)
    {
    }

    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      theReadData >> myBasisSurface >> myOffsetValue;
    }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myBasisSurface << myOffsetValue;
    }

    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      theChildren.Append(myBasisSurface);
    }

    inline const char* PName() const { return "PGeom_OffsetSurface"; }

    occ::handle<Geom_Surface> Import() const override;

  private:
    occ::handle<Surface> myBasisSurface;
    double               myOffsetValue;
  };

public:
  typedef subBase_gp<Surface, gp_Ax3>                                Elementary;
  typedef instance<Elementary, Geom_Plane, gp_Ax3>                   Plane;
  typedef instance<Elementary, Geom_ConicalSurface, gp_Cone>         Conical;
  typedef instance<Elementary, Geom_CylindricalSurface, gp_Cylinder> Cylindrical;
  typedef instance<Elementary, Geom_SphericalSurface, gp_Sphere>     Spherical;
  typedef instance<Elementary, Geom_ToroidalSurface, gp_Torus>       Toroidal;

  typedef subBase<Surface, pSweptData>     Swept;
  typedef Delayed<Swept, pLinearExtrusion> LinearExtrusion;
  typedef Delayed<Swept, pRevolution>      Revolution;

  typedef subBase_empty<Surface>                Bounded;
  typedef Delayed<Bounded, pBezier>             Bezier;
  typedef Delayed<Bounded, pBSpline>            BSpline;
  typedef Delayed<Bounded, pRectangularTrimmed> RectangularTrimmed;

  typedef Delayed<Surface, pOffset> Offset;

public:
  Standard_EXPORT static occ::handle<Surface> Translate(
    const occ::handle<Geom_Plane>& theSurf,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Surface> Translate(
    const occ::handle<Geom_CylindricalSurface>& theSurf,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Surface> Translate(
    const occ::handle<Geom_ConicalSurface>& theSurf,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Surface> Translate(
    const occ::handle<Geom_SphericalSurface>& theSurf,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Surface> Translate(
    const occ::handle<Geom_ToroidalSurface>& theSurf,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Surface> Translate(
    const occ::handle<Geom_SurfaceOfLinearExtrusion>& theSurf,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Surface> Translate(
    const occ::handle<Geom_SurfaceOfRevolution>& theSurf,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Surface> Translate(
    const occ::handle<Geom_BezierSurface>& theSurf,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Surface> Translate(
    const occ::handle<Geom_BSplineSurface>& theSurf,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Surface> Translate(
    const occ::handle<Geom_RectangularTrimmedSurface>& theSurf,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Surface> Translate(
    const occ::handle<Geom_OffsetSurface>& theSurf,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);
};

template <>
const char* ShapePersistent_Geom::subBase_gp<ShapePersistent_Geom::Surface, gp_Ax3>::PName() const;

template <>
const char* ShapePersistent_Geom::instance<
  ShapePersistent_Geom::subBase_gp<ShapePersistent_Geom::Surface, gp_Ax3>,
  Geom_Plane,
  gp_Ax3>::PName() const;

template <>
void ShapePersistent_Geom::instance<
  ShapePersistent_Geom::subBase_gp<ShapePersistent_Geom::Surface, gp_Ax3>,
  Geom_Plane,
  gp_Ax3>::Write(StdObjMgt_WriteData& theWriteData) const;

template <>
const char* ShapePersistent_Geom::instance<
  ShapePersistent_Geom::subBase_gp<ShapePersistent_Geom::Surface, gp_Ax3>,
  Geom_ConicalSurface,
  gp_Cone>::PName() const;

template <>
void ShapePersistent_Geom::instance<
  ShapePersistent_Geom::subBase_gp<ShapePersistent_Geom::Surface, gp_Ax3>,
  Geom_ConicalSurface,
  gp_Cone>::Write(StdObjMgt_WriteData& theWriteData) const;

template <>
const char* ShapePersistent_Geom::instance<
  ShapePersistent_Geom::subBase_gp<ShapePersistent_Geom::Surface, gp_Ax3>,
  Geom_CylindricalSurface,
  gp_Cylinder>::PName() const;

template <>
void ShapePersistent_Geom::instance<
  ShapePersistent_Geom::subBase_gp<ShapePersistent_Geom::Surface, gp_Ax3>,
  Geom_CylindricalSurface,
  gp_Cylinder>::Write(StdObjMgt_WriteData& theWriteData) const;

template <>
const char* ShapePersistent_Geom::instance<
  ShapePersistent_Geom::subBase_gp<ShapePersistent_Geom::Surface, gp_Ax3>,
  Geom_SphericalSurface,
  gp_Sphere>::PName() const;

template <>
void ShapePersistent_Geom::instance<
  ShapePersistent_Geom::subBase_gp<ShapePersistent_Geom::Surface, gp_Ax3>,
  Geom_SphericalSurface,
  gp_Sphere>::Write(StdObjMgt_WriteData& theWriteData) const;

template <>
const char* ShapePersistent_Geom::instance<
  ShapePersistent_Geom::subBase_gp<ShapePersistent_Geom::Surface, gp_Ax3>,
  Geom_ToroidalSurface,
  gp_Torus>::PName() const;

template <>
void ShapePersistent_Geom::instance<
  ShapePersistent_Geom::subBase_gp<ShapePersistent_Geom::Surface, gp_Ax3>,
  Geom_ToroidalSurface,
  gp_Torus>::Write(StdObjMgt_WriteData& theWriteData) const;
