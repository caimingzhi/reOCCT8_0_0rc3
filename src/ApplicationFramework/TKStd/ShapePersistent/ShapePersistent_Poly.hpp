#pragma once

#include <StdObjMgt_SharedObject.hpp>
#include <NCollection_DataMap.hpp>
#include <ShapePersistent_HArray1.hpp>
class Standard_Transient;
class StdObjMgt_Persistent;

class Poly_Polygon2D;
class Poly_Polygon3D;
class Poly_PolygonOnTriangulation;
class Poly_Triangulation;

class ShapePersistent_Poly : private StdObjMgt_SharedObject
{
  class pPolygon2D : public Standard_Transient
  {
    friend class ShapePersistent_Poly;

  public:
    pPolygon2D()
        : myDeflection(0.0)
    {
    }

    inline void Read(StdObjMgt_ReadData& theReadData) { theReadData >> myDeflection >> myNodes; }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myDeflection << myNodes;
    }

    Standard_EXPORT void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const;

    inline const char* PName() const { return "PPoly_Polygon2D"; }

    occ::handle<Poly_Polygon2D> Import() const;

  private:
    double                                 myDeflection;
    Handle(ShapePersistent_HArray1::Pnt2d) myNodes;
  };

  class pPolygon3D : public Standard_Transient
  {
    friend class ShapePersistent_Poly;

  public:
    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      theReadData >> myDeflection >> myNodes >> myParameters;
    }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myDeflection << myNodes << myParameters;
    }

    Standard_EXPORT void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const;

    inline const char* PName() const { return "PPoly_Polygon3D"; }

    occ::handle<Poly_Polygon3D> Import() const;

  private:
    double                               myDeflection;
    Handle(ShapePersistent_HArray1::Pnt) myNodes;
    Handle(StdLPersistent_HArray1::Real) myParameters;
  };

  class pPolygonOnTriangulation : public Standard_Transient
  {
    friend class ShapePersistent_Poly;

  public:
    pPolygonOnTriangulation()
        : myDeflection(0.0)
    {
    }

    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      theReadData >> myDeflection >> myNodes >> myParameters;
    }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myDeflection << myNodes << myParameters;
    }

    Standard_EXPORT void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const;

    inline const char* PName() const { return "PPoly_PolygonOnTriangulation"; }

    occ::handle<Poly_PolygonOnTriangulation> Import() const;

  private:
    double                                  myDeflection;
    Handle(StdLPersistent_HArray1::Integer) myNodes;
    Handle(StdLPersistent_HArray1::Real)    myParameters;
  };

  class pTriangulation : public Standard_Transient
  {
    friend class ShapePersistent_Poly;

  public:
    pTriangulation()
        : myDeflection(0.0)
    {
    }

    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      theReadData >> myDeflection >> myNodes >> myUVNodes >> myTriangles;
    }

    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myDeflection << myNodes << myUVNodes << myTriangles;
    }

    Standard_EXPORT void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const;

    inline const char* PName() const { return "PPoly_Triangulation"; }

    occ::handle<Poly_Triangulation> Import() const;

  private:
    double                                    myDeflection;
    Handle(ShapePersistent_HArray1::Pnt)      myNodes;
    Handle(ShapePersistent_HArray1::Pnt2d)    myUVNodes;
    Handle(ShapePersistent_HArray1::Triangle) myTriangles;
  };

  template <class Persistent, class Transient>
  struct instance : public Delayed<DelayedBase<StdObjMgt_Persistent, Transient, Persistent>>
  {
  };

public:
  typedef instance<pPolygon2D, Poly_Polygon2D>                           Polygon2D;
  typedef instance<pPolygon3D, Poly_Polygon3D>                           Polygon3D;
  typedef instance<pPolygonOnTriangulation, Poly_PolygonOnTriangulation> PolygonOnTriangulation;
  typedef instance<pTriangulation, Poly_Triangulation>                   Triangulation;

public:
  Standard_EXPORT static occ::handle<Polygon2D> Translate(
    const occ::handle<Poly_Polygon2D>& thePoly,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Polygon3D> Translate(
    const occ::handle<Poly_Polygon3D>& thePoly,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<PolygonOnTriangulation> Translate(
    const occ::handle<Poly_PolygonOnTriangulation>& thePolyOnTriang,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);

  Standard_EXPORT static occ::handle<Triangulation> Translate(
    const occ::handle<Poly_Triangulation>& thePolyTriang,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>&
      theMap);
};
