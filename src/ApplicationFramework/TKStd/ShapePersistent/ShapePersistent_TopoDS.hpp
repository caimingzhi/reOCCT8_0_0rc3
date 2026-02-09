#pragma once

enum ShapePersistent_TriangleMode
{
  ShapePersistent_WithTriangle,
  ShapePersistent_WithoutTriangle
};

#include <StdPersistent_HArray1.hpp>
#include <StdLPersistent_HArray1.hpp>
#include <StdObject_Shape.hpp>
#include <NCollection_DataMap.hpp>

#include <TopoDS_TWire.hpp>
#include <TopoDS_TShell.hpp>
#include <TopoDS_TSolid.hpp>
#include <TopoDS_TCompSolid.hpp>
#include <TopoDS_TCompound.hpp>
class Standard_Transient;
class StdObjMgt_Persistent;

class ShapePersistent_TopoDS : public StdPersistent_TopoDS
{
public:
  class HShape : public StdObjMgt_Persistent, public StdObject_Shape
  {
  public:
    Standard_EXPORT void Read(StdObjMgt_ReadData& theReadData) override;

    Standard_EXPORT void Write(StdObjMgt_WriteData& theWriteData) const override;

    Standard_EXPORT void PChildren(SequenceOfPersistent& theChildren) const override;

    const char* PName() const override { return "PTopoDS_HShape"; }

  private:
    occ::handle<StdObjMgt_Persistent> myEntry;
  };

protected:
  class pTBase : public pTShape
  {
  public:
    inline occ::handle<TopoDS_TShape> Import() const
    {
      occ::handle<TopoDS_TShape> aTShape = createTShape();

      TopoDS_Shape aWrapperShape;
      aWrapperShape.TShape(aTShape);
      addShapes(aWrapperShape);

      setFlags(aTShape);

      return aTShape;
    }

  private:
    virtual occ::handle<TopoDS_TShape> createTShape() const = 0;

    virtual void addShapes(TopoDS_Shape& theParent) const = 0;

    void setFlags(const occ::handle<TopoDS_TShape>& theTShape) const;

  protected:
    template <class ShapesArray>
    void addShapesT(TopoDS_Shape& theParent) const;
  };

private:
  template <class Target>
  class pTSimple : public pTBase
  {
    occ::handle<TopoDS_TShape> createTShape() const override;

  public:
    inline const char* PName() const;
  };

  template <class Persistent, class ShapesArray>
  class pTObject : public Persistent
  {
    void addShapes(TopoDS_Shape& theParent) const override
    {
      pTBase::addShapesT<ShapesArray>(theParent);
    }
  };

  template <class Persistent, class ShapesArray>
  struct tObjectT : public Delayed<DelayedBase<TShape, TopoDS_TShape, pTBase>,
                                   pTObject<Persistent, ShapesArray>>
  {
    typedef pTObject<Persistent, ShapesArray> pTObjectT;
  };

protected:
  template <class Persistent>
  struct tObject : public tObjectT<Persistent, StdLPersistent_HArray1::Persistent>
  {
  };

  template <class Persistent>
  struct tObject1 : public tObjectT<Persistent, StdPersistent_HArray1::Shape1>
  {
  };

public:
  typedef tObject<pTSimple<TopoDS_TWire>>      TWire;
  typedef tObject<pTSimple<TopoDS_TShell>>     TShell;
  typedef tObject<pTSimple<TopoDS_TSolid>>     TSolid;
  typedef tObject<pTSimple<TopoDS_TCompSolid>> TCompSolid;
  typedef tObject<pTSimple<TopoDS_TCompound>>  TCompound;

  typedef tObject1<pTSimple<TopoDS_TWire>>      TWire1;
  typedef tObject1<pTSimple<TopoDS_TShell>>     TShell1;
  typedef tObject1<pTSimple<TopoDS_TSolid>>     TSolid1;
  typedef tObject1<pTSimple<TopoDS_TCompSolid>> TCompSolid1;
  typedef tObject1<pTSimple<TopoDS_TCompound>>  TCompound1;

public:
  Standard_EXPORT static occ::handle<HShape> Translate(
    const TopoDS_Shape& theShape,
    NCollection_DataMap<occ::handle<Standard_Transient>, occ::handle<StdObjMgt_Persistent>>& theMap,
    ShapePersistent_TriangleMode theTriangleMode);
};

template <>
inline const char* ShapePersistent_TopoDS::pTSimple<TopoDS_TWire>::PName() const
{
  return "PTopoDS_TWire";
}

template <>
inline const char* ShapePersistent_TopoDS::pTSimple<TopoDS_TShell>::PName() const
{
  return "PTopoDS_TShell";
}

template <>
inline const char* ShapePersistent_TopoDS::pTSimple<TopoDS_TSolid>::PName() const
{
  return "PTopoDS_TSolid";
}

template <>
inline const char* ShapePersistent_TopoDS::pTSimple<TopoDS_TCompSolid>::PName() const
{
  return "PTopoDS_TCompSolid";
}

template <>
inline const char* ShapePersistent_TopoDS::pTSimple<TopoDS_TCompound>::PName() const
{
  return "PTopoDS_TCompound";
}
