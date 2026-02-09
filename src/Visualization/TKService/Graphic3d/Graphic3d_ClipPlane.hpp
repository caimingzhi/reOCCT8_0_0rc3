#pragma once

#include <gp_Pln.hpp>
#include <Graphic3d_AspectFillArea3d.hpp>
#include <Graphic3d_BndBox3d.hpp>

enum Graphic3d_CappingFlags
{
  Graphic3d_CappingFlags_None           = 0x0000,
  Graphic3d_CappingFlags_ObjectMaterial = 0x0001,
  Graphic3d_CappingFlags_ObjectTexture  = 0x0002,
  Graphic3d_CappingFlags_ObjectShader   = 0x0008,
  Graphic3d_CappingFlags_ObjectAspect   = Graphic3d_CappingFlags_ObjectMaterial
                                        | Graphic3d_CappingFlags_ObjectTexture
                                        | Graphic3d_CappingFlags_ObjectShader
};

#include <Graphic3d_TextureMap.hpp>
#include <NCollection_Vec4.hpp>
#include <Standard_Macro.hpp>
#include <Standard_TypeDef.hpp>
#include <Standard_Transient.hpp>

enum Graphic3d_ClipState
{
  Graphic3d_ClipState_Out,
  Graphic3d_ClipState_In,
  Graphic3d_ClipState_On,
};

class Graphic3d_ClipPlane : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_ClipPlane, Standard_Transient)
public:
  typedef NCollection_Vec4<double> Equation;

public:
  Standard_EXPORT Graphic3d_ClipPlane();

  Standard_EXPORT Graphic3d_ClipPlane(const Graphic3d_ClipPlane& theOther);

  Standard_EXPORT Graphic3d_ClipPlane(const NCollection_Vec4<double>& theEquation);

  Standard_EXPORT Graphic3d_ClipPlane(const gp_Pln& thePlane);

  Standard_EXPORT void SetEquation(const gp_Pln& thePlane);

  Standard_EXPORT void SetEquation(const NCollection_Vec4<double>& theEquation);

  const NCollection_Vec4<double>& GetEquation() const { return myEquation; }

  const NCollection_Vec4<double>& ReversedEquation() const { return myEquationRev; }

  bool IsOn() const { return myIsOn; }

  Standard_EXPORT void SetOn(const bool theIsOn);

  Standard_EXPORT void SetCapping(const bool theIsOn);

  bool IsCapping() const { return myIsCapping; }

  const gp_Pln& ToPlane() const { return myPlane; }

  Standard_EXPORT virtual occ::handle<Graphic3d_ClipPlane> Clone() const;

public:
  bool IsChain() const { return !myNextInChain.IsNull(); }

  occ::handle<Graphic3d_ClipPlane> ChainPreviousPlane() const { return myPrevInChain; }

  const occ::handle<Graphic3d_ClipPlane>& ChainNextPlane() const { return myNextInChain; }

  int NbChainNextPlanes() const { return myChainLenFwd; }

  Standard_EXPORT void SetChainNextPlane(const occ::handle<Graphic3d_ClipPlane>& thePlane);

public:
  Quantity_Color CappingColor() const
  {
    return myAspect->FrontMaterial().MaterialType() == Graphic3d_MATERIAL_ASPECT
             ? myAspect->FrontMaterial().Color()
             : myAspect->InteriorColor();
  }

  Standard_EXPORT void SetCappingColor(const Quantity_Color& theColor);

  Standard_EXPORT void SetCappingMaterial(const Graphic3d_MaterialAspect& theMat);

  const Graphic3d_MaterialAspect& CappingMaterial() const { return myAspect->FrontMaterial(); }

  Standard_EXPORT void SetCappingTexture(const occ::handle<Graphic3d_TextureMap>& theTexture);

  occ::handle<Graphic3d_TextureMap> CappingTexture() const
  {
    return !myAspect->TextureSet().IsNull() && !myAspect->TextureSet()->IsEmpty()
             ? myAspect->TextureSet()->First()
             : occ::handle<Graphic3d_TextureMap>();
  }

  Standard_EXPORT void SetCappingHatch(const Aspect_HatchStyle theStyle);

  Aspect_HatchStyle CappingHatch() const
  {
    return (Aspect_HatchStyle)myAspect->HatchStyle()->HatchType();
  }

  Standard_EXPORT void SetCappingCustomHatch(const occ::handle<Graphic3d_HatchStyle>& theStyle);

  const occ::handle<Graphic3d_HatchStyle>& CappingCustomHatch() const
  {
    return myAspect->HatchStyle();
  }

  Standard_EXPORT void SetCappingHatchOn();

  Standard_EXPORT void SetCappingHatchOff();

  bool IsHatchOn() const { return myAspect->InteriorStyle() == Aspect_IS_HATCH; }

  const TCollection_AsciiString& GetId() const { return myId; }

public:
  const occ::handle<Graphic3d_AspectFillArea3d>& CappingAspect() const { return myAspect; }

  Standard_EXPORT void SetCappingAspect(const occ::handle<Graphic3d_AspectFillArea3d>& theAspect);

  bool ToUseObjectMaterial() const
  {
    return (myFlags & Graphic3d_CappingFlags_ObjectMaterial) != 0;
  }

  void SetUseObjectMaterial(bool theToUse)
  {
    setCappingFlag(theToUse, Graphic3d_CappingFlags_ObjectMaterial);
  }

  bool ToUseObjectTexture() const { return (myFlags & Graphic3d_CappingFlags_ObjectTexture) != 0; }

  void SetUseObjectTexture(bool theToUse)
  {
    setCappingFlag(theToUse, Graphic3d_CappingFlags_ObjectTexture);
  }

  bool ToUseObjectShader() const { return (myFlags & Graphic3d_CappingFlags_ObjectShader) != 0; }

  void SetUseObjectShader(bool theToUse)
  {
    setCappingFlag(theToUse, Graphic3d_CappingFlags_ObjectShader);
  }

  bool ToUseObjectProperties() const { return myFlags != Graphic3d_CappingFlags_None; }

public:
  Graphic3d_ClipState ProbePoint(const NCollection_Vec4<double>& thePoint) const
  {
    Graphic3d_ClipState aState = Graphic3d_ClipState_Out;
    for (const Graphic3d_ClipPlane* aPlaneIter = this; aPlaneIter != nullptr;
         aPlaneIter                            = aPlaneIter->myNextInChain.get())
    {
      Graphic3d_ClipState aPlnState = aPlaneIter->ProbePointHalfspace(thePoint);
      if (aPlnState == Graphic3d_ClipState_In)
      {
        return Graphic3d_ClipState_In;
      }
      else if (aPlnState != Graphic3d_ClipState_Out)
      {
        aState = Graphic3d_ClipState_On;
      }
    }
    return aState;
  }

  Graphic3d_ClipState ProbeBox(const Graphic3d_BndBox3d& theBox) const
  {
    Graphic3d_ClipState aState = Graphic3d_ClipState_Out;
    for (const Graphic3d_ClipPlane* aPlaneIter = this; aPlaneIter != nullptr;
         aPlaneIter                            = aPlaneIter->myNextInChain.get())
    {
      if (aPlaneIter->IsBoxFullInHalfspace(theBox))
      {

        return Graphic3d_ClipState_In;
      }
      else if (!aPlaneIter->IsBoxFullOutHalfspace(theBox))
      {

        aState = Graphic3d_ClipState_On;
      }
    }
    return aState;
  }

  bool ProbeBoxTouch(const Graphic3d_BndBox3d& theBox) const
  {
    for (const Graphic3d_ClipPlane* aPlaneIter = this; aPlaneIter != nullptr;
         aPlaneIter                            = aPlaneIter->myNextInChain.get())
    {
      if (aPlaneIter->IsBoxFullInHalfspace(theBox))
      {

        return false;
      }
      else if (!aPlaneIter->IsBoxFullOutHalfspace(theBox))
      {

        if (ProbeBoxMaxPointHalfspace(theBox) != Graphic3d_ClipState_Out)
        {
          return true;
        }
      }
    }
    return false;
  }

public:
  Graphic3d_ClipState ProbePointHalfspace(const NCollection_Vec4<double>& thePoint) const
  {
    const double aVal = myEquation.Dot(thePoint);
    return aVal < 0.0 ? Graphic3d_ClipState_Out
                      : (aVal == 0.0 ? Graphic3d_ClipState_On : Graphic3d_ClipState_In);
  }

  Graphic3d_ClipState ProbeBoxHalfspace(const Graphic3d_BndBox3d& theBox) const
  {
    if (IsBoxFullOutHalfspace(theBox))
    {
      return Graphic3d_ClipState_Out;
    }
    return IsBoxFullInHalfspace(theBox) ? Graphic3d_ClipState_In : Graphic3d_ClipState_On;
  }

  bool IsPointOutHalfspace(const NCollection_Vec4<double>& thePoint) const
  {
    return ProbePointHalfspace(thePoint) == Graphic3d_ClipState_Out;
  }

  bool IsBoxFullOutHalfspace(const Graphic3d_BndBox3d& theBox) const
  {
    const NCollection_Vec4<double> aMaxPnt(
      myEquation.x() > 0.0 ? theBox.CornerMax().x() : theBox.CornerMin().x(),
      myEquation.y() > 0.0 ? theBox.CornerMax().y() : theBox.CornerMin().y(),
      myEquation.z() > 0.0 ? theBox.CornerMax().z() : theBox.CornerMin().z(),
      1.0);
    return IsPointOutHalfspace(aMaxPnt);
  }

  Graphic3d_ClipState ProbeBoxMaxPointHalfspace(const Graphic3d_BndBox3d& theBox) const
  {
    const NCollection_Vec4<double> aMaxPnt(
      myEquation.x() > 0.0 ? theBox.CornerMax().x() : theBox.CornerMin().x(),
      myEquation.y() > 0.0 ? theBox.CornerMax().y() : theBox.CornerMin().y(),
      myEquation.z() > 0.0 ? theBox.CornerMax().z() : theBox.CornerMin().z(),
      1.0);
    return ProbePointHalfspace(aMaxPnt);
  }

  bool IsBoxFullInHalfspace(const Graphic3d_BndBox3d& theBox) const
  {
    const NCollection_Vec4<double> aMinPnt(
      myEquation.x() > 0.0 ? theBox.CornerMin().x() : theBox.CornerMax().x(),
      myEquation.y() > 0.0 ? theBox.CornerMin().y() : theBox.CornerMax().y(),
      myEquation.z() > 0.0 ? theBox.CornerMin().z() : theBox.CornerMax().z(),
      1.0);
    return !IsPointOutHalfspace(aMinPnt);
  }

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

public:
  unsigned int MCountEquation() const { return myEquationMod; }

  unsigned int MCountAspect() const { return myAspectMod; }

private:
  void makeId();

  Standard_EXPORT void setCappingFlag(bool theToUse, int theFlag);

  void updateChainLen();

  void updateInversedPlane()
  {
    gp_Pln aPlane = myPlane;
    aPlane.SetAxis(aPlane.Axis().Reversed());
    aPlane.Coefficients(myEquationRev[0], myEquationRev[1], myEquationRev[2], myEquationRev[3]);
  }

private:
  occ::handle<Graphic3d_AspectFillArea3d> myAspect;

  occ::handle<Graphic3d_ClipPlane> myNextInChain;
  Graphic3d_ClipPlane*             myPrevInChain;
  TCollection_AsciiString          myId;
  gp_Pln                           myPlane;
  NCollection_Vec4<double>         myEquation;
  NCollection_Vec4<double>         myEquationRev;
  int                              myChainLenFwd;

  unsigned int myFlags;
  unsigned int myEquationMod;
  unsigned int myAspectMod;
  bool         myIsOn;
  bool         myIsCapping;
};
