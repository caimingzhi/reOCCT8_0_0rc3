#pragma once

#include <Graphic3d_DisplayPriority.hpp>
#include <Graphic3d_PresentationAttributes.hpp>
#include <Graphic3d_Group.hpp>
#include <NCollection_Sequence.hpp>
#include <Graphic3d_SequenceOfHClipPlane.hpp>
#include <Graphic3d_ViewAffinity.hpp>
#include <Graphic3d_TransformPers.hpp>
#include <Graphic3d_ZLayerId.hpp>
#include <TopLoc_Datum3D.hpp>
#include <NCollection_IndexedMap.hpp>

class Graphic3d_GraphicDriver;
class Graphic3d_StructureManager;

class Graphic3d_CStructure : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Graphic3d_CStructure, Standard_Transient)
protected:
  template <class Struct_t>
  class SubclassStructIterator
  {
  public:
    SubclassStructIterator(const NCollection_IndexedMap<const Graphic3d_CStructure*>& theStructs)
        : myIter(theStructs)
    {
    }

    bool More() const { return myIter.More(); }

    void Next() { myIter.Next(); }

    const Struct_t* Value() const { return (const Struct_t*)(myIter.Value()); }

    Struct_t* ChangeValue() { return (Struct_t*)(myIter.Value()); }

  private:
    NCollection_IndexedMap<const Graphic3d_CStructure*>::Iterator myIter;
  };

  template <class Group_t>
  class SubclassGroupIterator
  {
  public:
    SubclassGroupIterator(const NCollection_Sequence<occ::handle<Graphic3d_Group>>& theGroups)
        : myIter(theGroups)
    {
    }

    bool More() const { return myIter.More(); }

    void Next() { myIter.Next(); }

    const Group_t* Value() const { return (const Group_t*)(myIter.Value().get()); }

    Group_t* ChangeValue() { return (Group_t*)(myIter.ChangeValue().get()); }

  private:
    NCollection_Sequence<occ::handle<Graphic3d_Group>>::Iterator myIter;
  };

public:
  const occ::handle<Graphic3d_GraphicDriver>& GraphicDriver() const { return myGraphicDriver; }

  const NCollection_Sequence<occ::handle<Graphic3d_Group>>& Groups() const { return myGroups; }

  const occ::handle<TopLoc_Datum3D>& Transformation() const { return myTrsf; }

  virtual void SetTransformation(const occ::handle<TopLoc_Datum3D>& theTrsf) { myTrsf = theTrsf; }

  const occ::handle<Graphic3d_TransformPers>& TransformPersistence() const { return myTrsfPers; }

  virtual void SetTransformPersistence(const occ::handle<Graphic3d_TransformPers>& theTrsfPers)
  {
    myTrsfPers = theTrsfPers;
  }

  bool HasGroupTransformPersistence() const { return myHasGroupTrsf; }

  void SetGroupTransformPersistence(bool theValue) { myHasGroupTrsf = theValue; }

  const occ::handle<Graphic3d_SequenceOfHClipPlane>& ClipPlanes() const { return myClipPlanes; }

  void SetClipPlanes(const occ::handle<Graphic3d_SequenceOfHClipPlane>& thePlanes)
  {
    myClipPlanes = thePlanes;
  }

  const Graphic3d_BndBox3d& BoundingBox() const { return myBndBox; }

  Graphic3d_BndBox3d& ChangeBoundingBox() { return myBndBox; }

  bool IsVisible() const { return visible != 0; }

  bool IsVisible(const int theViewId) const
  {
    return visible != 0 && (ViewAffinity.IsNull() || ViewAffinity->IsVisible(theViewId));
  }

  virtual void SetZLayer(const Graphic3d_ZLayerId theLayerIndex) { myZLayer = theLayerIndex; }

  Graphic3d_ZLayerId ZLayer() const { return myZLayer; }

  const occ::handle<Graphic3d_PresentationAttributes>& HighlightStyle() const
  {
    return myHighlightStyle;
  }

  int Identification() const { return myId; }

  Graphic3d_DisplayPriority Priority() const { return myPriority; }

  void SetPriority(Graphic3d_DisplayPriority thePriority) { myPriority = thePriority; }

  Graphic3d_DisplayPriority PreviousPriority() const { return myPreviousPriority; }

  void SetPreviousPriority(Graphic3d_DisplayPriority thePriority)
  {
    myPreviousPriority = thePriority;
  }

public:
  bool IsCulled() const { return myIsCulled; }

  void SetCulled(bool theIsCulled) const { myIsCulled = theIsCulled; }

  void MarkAsNotCulled() const { myIsCulled = false; }

  bool BndBoxClipCheck() const { return myBndBoxClipCheck; }

  void SetBndBoxClipCheck(bool theBndBoxClipCheck) { myBndBoxClipCheck = theBndBoxClipCheck; }

  bool IsAlwaysRendered() const
  {
    return IsInfinite || IsForHighlight || IsMutable || Is2dText
           || (!myTrsfPers.IsNull() && myTrsfPers->IsTrihedronOr2d());
  }

public:
  virtual void OnVisibilityChanged() = 0;

  virtual void Clear() = 0;

  virtual void Connect(Graphic3d_CStructure& theStructure) = 0;

  virtual void Disconnect(Graphic3d_CStructure& theStructure) = 0;

  virtual void GraphicHighlight(const occ::handle<Graphic3d_PresentationAttributes>& theStyle) = 0;

  virtual void GraphicUnhighlight() = 0;

  virtual occ::handle<Graphic3d_CStructure> ShadowLink(
    const occ::handle<Graphic3d_StructureManager>& theManager) const = 0;

  virtual occ::handle<Graphic3d_Group> NewGroup(
    const occ::handle<Graphic3d_Structure>& theStruct) = 0;

  virtual void RemoveGroup(const occ::handle<Graphic3d_Group>& theGroup) = 0;

  virtual void updateLayerTransformation() {}

  Standard_EXPORT virtual void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

public:
  occ::handle<Graphic3d_ViewAffinity> ViewAffinity;

protected:
  Standard_EXPORT Graphic3d_CStructure(const occ::handle<Graphic3d_StructureManager>& theManager);

protected:
  occ::handle<Graphic3d_GraphicDriver>               myGraphicDriver;
  NCollection_Sequence<occ::handle<Graphic3d_Group>> myGroups;
  Graphic3d_BndBox3d                                 myBndBox;
  occ::handle<TopLoc_Datum3D>                        myTrsf;
  occ::handle<Graphic3d_TransformPers>               myTrsfPers;
  occ::handle<Graphic3d_SequenceOfHClipPlane>        myClipPlanes;

  occ::handle<Graphic3d_PresentationAttributes> myHighlightStyle;

  int                       myId;
  Graphic3d_ZLayerId        myZLayer;
  Graphic3d_DisplayPriority myPriority;
  Graphic3d_DisplayPriority myPreviousPriority;

  mutable bool myIsCulled;
  bool         myBndBoxClipCheck;

  bool myHasGroupTrsf;

public:
  unsigned IsInfinite : 1;
  unsigned stick : 1;
  unsigned highlight : 1;
  unsigned visible : 1;

  unsigned HLRValidation : 1;
  unsigned IsForHighlight : 1;
  unsigned IsMutable : 1;
  unsigned Is2dText : 1;
};
