#pragma once

#include <RWMesh_CoordinateSystem.hpp>

#include <gp_Ax3.hpp>
#include <gp_XYZ.hpp>
#include <gp_Trsf.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <NCollection_Vec3.hpp>
#include <NCollection_Vec4.hpp>
#include <NCollection_Mat4.hpp>

class RWMesh_CoordinateSystemConverter
{
public:
  static gp_Ax3 StandardCoordinateSystem(RWMesh_CoordinateSystem theSys)
  {
    switch (theSys)
    {
      case RWMesh_CoordinateSystem_posYfwd_posZup:
        return gp_Ax3(gp::Origin(), gp::DZ(), gp::DX());
      case RWMesh_CoordinateSystem_negZfwd_posYup:
        return gp_Ax3(gp::Origin(), gp::DY(), gp::DX());
      case RWMesh_CoordinateSystem_Undefined:
        break;
    }
    return gp_Ax3();
  }

public:
  Standard_EXPORT RWMesh_CoordinateSystemConverter();

  bool IsEmpty() const { return myIsEmpty; }

  double InputLengthUnit() const { return myInputLengthUnit; }

  void SetInputLengthUnit(double theInputScale)
  {
    Init(myInputAx3, theInputScale, myOutputAx3, myOutputLengthUnit);
  }

  double OutputLengthUnit() const { return myOutputLengthUnit; }

  void SetOutputLengthUnit(double theOutputScale)
  {
    Init(myInputAx3, myInputLengthUnit, myOutputAx3, theOutputScale);
  }

  bool HasInputCoordinateSystem() const { return myHasInputAx3; }

  const gp_Ax3& InputCoordinateSystem() const { return myInputAx3; }

  void SetInputCoordinateSystem(const gp_Ax3& theSysFrom)
  {
    myHasInputAx3 = true;
    Init(theSysFrom, myInputLengthUnit, myOutputAx3, myOutputLengthUnit);
  }

  void SetInputCoordinateSystem(RWMesh_CoordinateSystem theSysFrom)
  {
    myHasInputAx3 = theSysFrom != RWMesh_CoordinateSystem_Undefined;
    Init(StandardCoordinateSystem(theSysFrom), myInputLengthUnit, myOutputAx3, myOutputLengthUnit);
  }

  bool HasOutputCoordinateSystem() const { return myHasOutputAx3; }

  const gp_Ax3& OutputCoordinateSystem() const { return myOutputAx3; }

  void SetOutputCoordinateSystem(const gp_Ax3& theSysTo)
  {
    myHasOutputAx3 = true;
    Init(myInputAx3, myInputLengthUnit, theSysTo, myOutputLengthUnit);
  }

  void SetOutputCoordinateSystem(RWMesh_CoordinateSystem theSysTo)
  {
    myHasOutputAx3 = theSysTo != RWMesh_CoordinateSystem_Undefined;
    Init(myInputAx3, myInputLengthUnit, StandardCoordinateSystem(theSysTo), myOutputLengthUnit);
  }

  Standard_EXPORT void Init(const gp_Ax3& theInputSystem,
                            double        theInputLengthUnit,
                            const gp_Ax3& theOutputSystem,
                            double        theOutputLengthUnit);

public:
  void TransformTransformation(gp_Trsf& theTrsf) const
  {
    if (myHasScale)
    {
      gp_XYZ aTransPart = theTrsf.TranslationPart();
      aTransPart *= myUnitFactor;
      theTrsf.SetTranslationPart(aTransPart);
    }
    if (myTrsf.Form() != gp_Identity)
    {
      theTrsf = myTrsf * theTrsf * myTrsfInv;
    }
  }

  void TransformPosition(gp_XYZ& thePos) const
  {
    if (myHasScale)
    {
      thePos *= myUnitFactor;
    }
    if (myTrsf.Form() != gp_Identity)
    {
      myTrsf.Transforms(thePos);
    }
  }

  void TransformNormal(NCollection_Vec3<float>& theNorm) const
  {
    if (myTrsf.Form() != gp_Identity)
    {
      const NCollection_Vec4<float> aNorm = myNormTrsf * NCollection_Vec4<float>(theNorm, 0.0f);
      theNorm                             = aNorm.xyz();
    }
  }

private:
  gp_Ax3 myInputAx3;
  gp_Ax3 myOutputAx3;

  double myInputLengthUnit;
  double myOutputLengthUnit;
  bool   myHasInputAx3;
  bool   myHasOutputAx3;

  gp_Trsf                 myTrsf;
  gp_Trsf                 myTrsfInv;
  NCollection_Mat4<float> myNormTrsf;
  double                  myUnitFactor;
  bool                    myHasScale;

  bool myIsEmpty;
};
