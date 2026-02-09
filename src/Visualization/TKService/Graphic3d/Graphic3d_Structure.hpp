#pragma once

#include <Graphic3d_CStructure.hpp>
#include <NCollection_Map.hpp>
#include <Graphic3d_Group.hpp>
#include <NCollection_Sequence.hpp>
#include <Graphic3d_SequenceOfHClipPlane.hpp>

enum Graphic3d_TypeOfConnection
{
  Graphic3d_TOC_ANCESTOR,
  Graphic3d_TOC_DESCENDANT
};

enum Graphic3d_TypeOfStructure
{
  Graphic3d_TOS_WIREFRAME,
  Graphic3d_TOS_SHADING,
  Graphic3d_TOS_COMPUTED,
  Graphic3d_TOS_ALL
};

#include <Graphic3d_TransformPers.hpp>
#include <Graphic3d_ZLayerId.hpp>
#include <NCollection_IndexedMap.hpp>
class Graphic3d_Structure;

class Graphic3d_StructureManager;
class Graphic3d_DataStructureManager;
class Bnd_Box;

class Graphic3d_Structure : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_Structure, Standard_Transient)
  friend class Graphic3d_Group;

public:
  Standard_EXPORT Graphic3d_Structure(
    const occ::handle<Graphic3d_StructureManager>& theManager,
    const occ::handle<Graphic3d_Structure>&        theLinkPrs = occ::handle<Graphic3d_Structure>());

  virtual void Clear(const bool WithDestruction = true) { clear(WithDestruction); }

  Standard_EXPORT ~Graphic3d_Structure() override;

  Standard_EXPORT virtual void Display();

  Graphic3d_DisplayPriority DisplayPriority() const { return myCStructure->Priority(); }

  Standard_EXPORT void SetDisplayPriority(const Graphic3d_DisplayPriority thePriority);

  Standard_DEPRECATED("Deprecated since OCCT7.7, Graphic3d_DisplayPriority should be passed "
                      "instead of integer number to SetDisplayPriority()")

  void SetDisplayPriority(const int thePriority)
  {
    SetDisplayPriority((Graphic3d_DisplayPriority)thePriority);
  }

  Standard_EXPORT void ResetDisplayPriority();

  virtual void Erase() { erase(); }

  Standard_EXPORT void Highlight(const occ::handle<Graphic3d_PresentationAttributes>& theStyle,
                                 const bool theToUpdateMgr = true);

  Standard_EXPORT void Remove();

  Standard_EXPORT virtual void CalculateBoundBox();

  void SetInfiniteState(const bool theToSet)
  {
    if (!myCStructure.IsNull())
    {
      myCStructure->IsInfinite = theToSet ? 1 : 0;
    }
  }

  Standard_EXPORT void SetZLayer(const Graphic3d_ZLayerId theLayerId);

  Graphic3d_ZLayerId GetZLayer() const { return myCStructure->ZLayer(); }

  void SetClipPlanes(const occ::handle<Graphic3d_SequenceOfHClipPlane>& thePlanes)
  {
    if (!myCStructure.IsNull())
    {
      myCStructure->SetClipPlanes(thePlanes);
    }
  }

  const occ::handle<Graphic3d_SequenceOfHClipPlane>& ClipPlanes() const
  {
    return myCStructure->ClipPlanes();
  }

  Standard_EXPORT void SetVisible(const bool AValue);

  Standard_EXPORT virtual void SetVisual(const Graphic3d_TypeOfStructure AVisual);

  Standard_EXPORT void SetZoomLimit(const double LimitInf, const double LimitSup);

  void SetIsForHighlight(const bool isForHighlight)
  {
    if (!myCStructure.IsNull())
    {
      myCStructure->IsForHighlight = isForHighlight;
    }
  }

  Standard_EXPORT void UnHighlight();

  virtual void Compute() {}

  virtual void computeHLR(const occ::handle<Graphic3d_Camera>& theProjector,
                          occ::handle<Graphic3d_Structure>&    theStructure)
  {
    (void)theProjector;
    (void)theStructure;
  }

  virtual void RecomputeTransformation(const occ::handle<Graphic3d_Camera>& theProjector)
  {
    (void)theProjector;
  }

  Standard_EXPORT void ReCompute();

  Standard_EXPORT void ReCompute(const occ::handle<Graphic3d_DataStructureManager>& aProjector);

  const NCollection_Sequence<occ::handle<Graphic3d_Group>>& Groups() const
  {
    return myCStructure->Groups();
  }

  int NumberOfGroups() const { return myCStructure->Groups().Length(); }

  Standard_EXPORT occ::handle<Graphic3d_Group> NewGroup();

  occ::handle<Graphic3d_Group> CurrentGroup()
  {
    if (Groups().IsEmpty())
    {
      return NewGroup();
    }
    return Groups().Last();
  }

  const occ::handle<Graphic3d_PresentationAttributes>& HighlightStyle() const
  {
    return myCStructure->HighlightStyle();
  }

  bool IsDeleted() const { return myCStructure.IsNull(); }

  virtual bool IsDisplayed() const { return !myCStructure.IsNull() && myCStructure->stick != 0; }

  Standard_EXPORT bool IsEmpty() const;

  bool IsInfinite() const { return IsDeleted() || myCStructure->IsInfinite; }

  virtual bool IsHighlighted() const
  {
    return !myCStructure.IsNull() && myCStructure->highlight != 0;
  }

  bool IsTransformed() const
  {
    return !myCStructure.IsNull() && !myCStructure->Transformation().IsNull()
           && myCStructure->Transformation()->Form() != gp_Identity;
  }

  bool IsVisible() const { return !myCStructure.IsNull() && myCStructure->visible != 0; }

  Standard_EXPORT Bnd_Box MinMaxValues(const bool theToIgnoreInfiniteFlag = false) const;

  Graphic3d_TypeOfStructure Visual() const { return myVisual; }

  Standard_EXPORT static bool AcceptConnection(Graphic3d_Structure*       theStructure1,
                                               Graphic3d_Structure*       theStructure2,
                                               Graphic3d_TypeOfConnection theType);

  Standard_EXPORT void Ancestors(NCollection_Map<occ::handle<Graphic3d_Structure>>& SG) const;

  Standard_EXPORT void Connect(Graphic3d_Structure*       theStructure,
                               Graphic3d_TypeOfConnection theType,
                               bool                       theWithCheck = false);

  Standard_DEPRECATED("Deprecated short-cut")

  void Connect(const occ::handle<Graphic3d_Structure>& thePrs)
  {
    Connect(thePrs.get(), Graphic3d_TOC_DESCENDANT);
  }

  Standard_EXPORT void Descendants(NCollection_Map<occ::handle<Graphic3d_Structure>>& SG) const;

  Standard_EXPORT void Disconnect(Graphic3d_Structure* theStructure);

  Standard_DEPRECATED("Deprecated alias for Disconnect()")

  void Remove(const occ::handle<Graphic3d_Structure>& thePrs) { Disconnect(thePrs.get()); }

  Standard_EXPORT void DisconnectAll(const Graphic3d_TypeOfConnection AType);

  Standard_DEPRECATED("Deprecated alias for DisconnectAll()")

  void RemoveAll() { DisconnectAll(Graphic3d_TOC_DESCENDANT); }

  Standard_EXPORT static void Network(Graphic3d_Structure*                   theStructure,
                                      const Graphic3d_TypeOfConnection       theType,
                                      NCollection_Map<Graphic3d_Structure*>& theSet);

  void SetOwner(void* const theOwner) { myOwner = theOwner; }

  void* Owner() const { return myOwner; }

  void SetHLRValidation(const bool theFlag)
  {
    if (!myCStructure.IsNull())
    {
      myCStructure->HLRValidation = theFlag ? 1 : 0;
    }
  }

  bool HLRValidation() const { return myOwner != nullptr && myCStructure->HLRValidation != 0; }

  const occ::handle<TopLoc_Datum3D>& Transformation() const
  {
    return myCStructure->Transformation();
  }

  Standard_EXPORT void SetTransformation(const occ::handle<TopLoc_Datum3D>& theTrsf);

  Standard_EXPORT void SetTransformPersistence(
    const occ::handle<Graphic3d_TransformPers>& theTrsfPers);

  const occ::handle<Graphic3d_TransformPers>& TransformPersistence() const
  {
    return myCStructure->TransformPersistence();
  }

  void SetMutable(const bool theIsMutable)
  {
    if (!myCStructure.IsNull())
    {
      myCStructure->IsMutable = theIsMutable;
    }
  }

  bool IsMutable() const { return !myCStructure.IsNull() && myCStructure->IsMutable; }

  Graphic3d_TypeOfStructure ComputeVisual() const { return myComputeVisual; }

  Standard_EXPORT void GraphicClear(const bool WithDestruction);

  void GraphicConnect(const occ::handle<Graphic3d_Structure>& theDaughter)
  {
    if (!myCStructure.IsNull())
    {
      myCStructure->Connect(*theDaughter->myCStructure);
    }
  }

  void GraphicDisconnect(const occ::handle<Graphic3d_Structure>& theDaughter)
  {
    if (!myCStructure.IsNull())
    {
      myCStructure->Disconnect(*theDaughter->myCStructure);
    }
  }

  void GraphicTransform(const occ::handle<TopLoc_Datum3D>& theTrsf)
  {
    if (!myCStructure.IsNull())
    {
      myCStructure->SetTransformation(theTrsf);
    }
  }

  int Identification() const { return myCStructure->Identification(); }

  Standard_EXPORT static void PrintNetwork(const occ::handle<Graphic3d_Structure>& AStructure,
                                           const Graphic3d_TypeOfConnection        AType);

  Standard_EXPORT void Remove(Graphic3d_Structure*             thePtr,
                              const Graphic3d_TypeOfConnection theType);

  void SetComputeVisual(const Graphic3d_TypeOfStructure theVisual)
  {

    if (theVisual != Graphic3d_TOS_COMPUTED)
    {
      myComputeVisual = theVisual;
    }
  }

  const occ::handle<Graphic3d_CStructure>& CStructure() const { return myCStructure; }

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  Standard_EXPORT bool AppendDescendant(Graphic3d_Structure* theDescendant);

  Standard_EXPORT bool RemoveDescendant(Graphic3d_Structure* theDescendant);

  Standard_EXPORT bool AppendAncestor(Graphic3d_Structure* theAncestor);

  Standard_EXPORT bool RemoveAncestor(Graphic3d_Structure* theAncestor);

  Standard_EXPORT void clear(const bool WithDestruction);

  Standard_EXPORT void erase();

private:
  Standard_EXPORT void Remove(const occ::handle<Graphic3d_Group>& theGroup);

  Standard_EXPORT Graphic3d_BndBox4f minMaxCoord() const;

  Standard_EXPORT void getBox(Graphic3d_BndBox3d& theBox,
                              const bool          theToIgnoreInfiniteFlag = false) const;

  Standard_EXPORT void addTransformed(Graphic3d_BndBox3d& theBox,
                                      const bool          theToIgnoreInfiniteFlag = false) const;

  Standard_EXPORT occ::handle<Graphic3d_StructureManager> StructureManager() const;

  Standard_EXPORT void Update(const bool theUpdateLayer = false) const;

protected:
  Graphic3d_StructureManager*                  myStructureManager;
  occ::handle<Graphic3d_CStructure>            myCStructure;
  NCollection_IndexedMap<Graphic3d_Structure*> myAncestors;
  NCollection_IndexedMap<Graphic3d_Structure*> myDescendants;
  void*                                        myOwner;
  Graphic3d_TypeOfStructure                    myVisual;
  Graphic3d_TypeOfStructure                    myComputeVisual;
};
