#pragma once

#include <gp_XYZ.hpp>
#include <TopLoc_Datum3D.hpp>
#include <Graphic3d_LightSet.hpp>
#include <Graphic3d_PolygonOffset.hpp>
#include <Precision.hpp>
#include <Standard_Dump.hpp>
#include <TCollection_AsciiString.hpp>

struct Graphic3d_ZLayerSettings
{

  Graphic3d_ZLayerSettings()
      : myCullingDistance(Precision::Infinite()),
        myCullingSize(Precision::Infinite()),
        myIsImmediate(false),
        myToRaytrace(true),
        myUseEnvironmentTexture(true),
        myToEnableDepthTest(true),
        myToEnableDepthWrite(true),
        myToClearDepth(true),
        myToRenderInDepthPrepass(true)
  {
  }

  const TCollection_AsciiString& Name() const { return myName; }

  void SetName(const TCollection_AsciiString& theName) { myName = theName; }

  const occ::handle<Graphic3d_LightSet>& Lights() const { return myLights; }

  void SetLights(const occ::handle<Graphic3d_LightSet>& theLights) { myLights = theLights; }

  const gp_XYZ& Origin() const { return myOrigin; }

  const occ::handle<TopLoc_Datum3D>& OriginTransformation() const { return myOriginTrsf; }

  void SetOrigin(const gp_XYZ& theOrigin)
  {
    myOrigin = theOrigin;
    myOriginTrsf.Nullify();
    if (!theOrigin.IsEqual(gp_XYZ(0.0, 0.0, 0.0), gp::Resolution()))
    {
      gp_Trsf aTrsf;
      aTrsf.SetTranslation(theOrigin);
      myOriginTrsf = new TopLoc_Datum3D(aTrsf);
    }
  }

  bool HasCullingDistance() const
  {
    return !Precision::IsInfinite(myCullingDistance) && myCullingDistance > 0.0;
  }

  double CullingDistance() const { return myCullingDistance; }

  void SetCullingDistance(double theDistance) { myCullingDistance = theDistance; }

  bool HasCullingSize() const
  {
    return !Precision::IsInfinite(myCullingSize) && myCullingSize > 0.0;
  }

  double CullingSize() const { return myCullingSize; }

  void SetCullingSize(double theSize) { myCullingSize = theSize; }

  bool IsImmediate() const { return myIsImmediate; }

  void SetImmediate(const bool theValue) { myIsImmediate = theValue; }

  bool IsRaytracable() const { return myToRaytrace; }

  void SetRaytracable(bool theToRaytrace) { myToRaytrace = theToRaytrace; }

  bool UseEnvironmentTexture() const { return myUseEnvironmentTexture; }

  void SetEnvironmentTexture(const bool theValue) { myUseEnvironmentTexture = theValue; }

  bool ToEnableDepthTest() const { return myToEnableDepthTest; }

  void SetEnableDepthTest(const bool theValue) { myToEnableDepthTest = theValue; }

  bool ToEnableDepthWrite() const { return myToEnableDepthWrite; }

  void SetEnableDepthWrite(const bool theValue) { myToEnableDepthWrite = theValue; }

  bool ToClearDepth() const { return myToClearDepth; }

  void SetClearDepth(const bool theValue) { myToClearDepth = theValue; }

  bool ToRenderInDepthPrepass() const { return myToRenderInDepthPrepass; }

  void SetRenderInDepthPrepass(bool theToRender) { myToRenderInDepthPrepass = theToRender; }

  const Graphic3d_PolygonOffset& PolygonOffset() const { return myPolygonOffset; }

  void SetPolygonOffset(const Graphic3d_PolygonOffset& theParams) { myPolygonOffset = theParams; }

  Graphic3d_PolygonOffset& ChangePolygonOffset() { return myPolygonOffset; }

  void SetDepthOffsetPositive()
  {
    myPolygonOffset.Mode   = Aspect_POM_Fill;
    myPolygonOffset.Factor = 1.0f;
    myPolygonOffset.Units  = 1.0f;
  }

  void SetDepthOffsetNegative()
  {
    myPolygonOffset.Mode   = Aspect_POM_Fill;
    myPolygonOffset.Factor = 1.0f;
    myPolygonOffset.Units  = -1.0f;
  }

  void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const
  {
    OCCT_DUMP_CLASS_BEGIN(theOStream, Graphic3d_ZLayerSettings)

    OCCT_DUMP_FIELD_VALUE_STRING(theOStream, myName)
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, myOriginTrsf.get())
    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myOrigin)

    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myCullingDistance)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myCullingSize)

    OCCT_DUMP_FIELD_VALUES_DUMPED(theOStream, theDepth, &myPolygonOffset)

    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myIsImmediate)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myToRaytrace)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myUseEnvironmentTexture)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myToEnableDepthTest)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myToEnableDepthWrite)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myToClearDepth)
    OCCT_DUMP_FIELD_VALUE_NUMERICAL(theOStream, myToRenderInDepthPrepass)
  }

protected:
  TCollection_AsciiString         myName;
  occ::handle<Graphic3d_LightSet> myLights;
  occ::handle<TopLoc_Datum3D>     myOriginTrsf;

  gp_XYZ                  myOrigin;
  double                  myCullingDistance;
  double                  myCullingSize;
  Graphic3d_PolygonOffset myPolygonOffset;
  bool                    myIsImmediate;
  bool                    myToRaytrace;
  bool                    myUseEnvironmentTexture;
  bool                    myToEnableDepthTest;
  bool                    myToEnableDepthWrite;
  bool                    myToClearDepth;
  bool                    myToRenderInDepthPrepass;
};
