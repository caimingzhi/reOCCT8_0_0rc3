#pragma once

#include <Graphic3d_SequenceOfHClipPlane.hpp>
#include <NCollection_Vector.hpp>
#include <Standard_TypeDef.hpp>

class OpenGl_ClippingIterator;

class OpenGl_Clipping
{
  friend class OpenGl_ClippingIterator;

public:
  Standard_EXPORT OpenGl_Clipping();

  Standard_EXPORT void Init();

  Standard_EXPORT void Reset(const occ::handle<Graphic3d_SequenceOfHClipPlane>& thePlanes);

  Standard_EXPORT void SetLocalPlanes(const occ::handle<Graphic3d_SequenceOfHClipPlane>& thePlanes);

  bool IsCappingOn() const { return myNbCapping > 0; }

  bool IsClippingOrCappingOn() const { return NbClippingOrCappingOn() > 0; }

  int NbClippingOrCappingOn() const
  {
    if (IsCappingDisableAllExcept())
    {
      return 1;
    }
    return myNbClipping + myNbCapping + (IsCappingEnableAllExcept() ? -1 : 0);
  }

  bool HasClippingChains() const
  {
    if (IsCappingDisableAllExcept() || myNbChains == (myNbClipping + myNbCapping))
    {
      return false;
    }
    return !IsCappingEnableAllExcept() || myCappedChain->NbChainNextPlanes() == 1 || myNbChains > 1;
  }

public:
  bool HasDisabled() const { return myNbDisabled > 0; }

  Standard_EXPORT bool SetEnabled(const OpenGl_ClippingIterator& thePlane, const bool theIsEnabled);

  Standard_EXPORT void DisableGlobal();

  Standard_EXPORT void RestoreDisabled();

public:
  const occ::handle<Graphic3d_ClipPlane>& CappedChain() const { return myCappedChain; }

  int CappedSubPlane() const { return myCappedSubPlane; }

  bool IsCappingFilterOn() const { return !myCappedChain.IsNull(); }

  bool IsCappingDisableAllExcept() const { return myCappedSubPlane > 0; }

  bool IsCappingEnableAllExcept() const { return myCappedSubPlane < 0; }

  Standard_EXPORT void DisableAllExcept(const occ::handle<Graphic3d_ClipPlane>& theChain,
                                        const int                               theSubPlaneIndex);

  Standard_EXPORT void EnableAllExcept(const occ::handle<Graphic3d_ClipPlane>& theChain,
                                       const int                               theSubPlaneIndex);

  Standard_EXPORT void ResetCappingFilter();

protected:
  Standard_EXPORT void add(const occ::handle<Graphic3d_SequenceOfHClipPlane>& thePlanes,
                           const int                                          theStartIndex);

  Standard_EXPORT void remove(const occ::handle<Graphic3d_SequenceOfHClipPlane>& thePlanes,
                              const int                                          theStartIndex);

private:
  occ::handle<Graphic3d_SequenceOfHClipPlane> myPlanesGlobal;
  occ::handle<Graphic3d_SequenceOfHClipPlane> myPlanesLocal;
  NCollection_Vector<bool>                    myDisabledPlanes;

  occ::handle<Graphic3d_ClipPlane> myCappedChain;
  int                              myCappedSubPlane;

  int myNbClipping;
  int myNbCapping;
  int myNbChains;
  int myNbDisabled;

private:
  OpenGl_Clipping(const OpenGl_Clipping&)            = delete;
  OpenGl_Clipping& operator=(const OpenGl_Clipping&) = delete;
};
