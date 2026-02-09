#pragma once

#include <Aspect_GenId.hpp>
#include <Graphic3d_CView.hpp>
#include <Graphic3d_ViewAffinity.hpp>
#include <NCollection_DataMap.hpp>
#include <NCollection_Map.hpp>
#include <Graphic3d_ZLayerId.hpp>
#include <Graphic3d_ZLayerSettings.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_IndexedMap.hpp>
#include <Standard.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Array2.hpp>

class Graphic3d_GraphicDriver;
class Graphic3d_Structure;
class Graphic3d_DataStructureManager;

class Graphic3d_StructureManager : public Standard_Transient
{
  friend class Graphic3d_Structure;
  DEFINE_STANDARD_RTTIEXT(Graphic3d_StructureManager, Standard_Transient)
public:
  Standard_EXPORT Graphic3d_StructureManager(const occ::handle<Graphic3d_GraphicDriver>& theDriver);

  Standard_EXPORT ~Graphic3d_StructureManager() override;

  Standard_EXPORT virtual void Update(
    const Graphic3d_ZLayerId theLayerId = Graphic3d_ZLayerId_UNKNOWN) const;

  Standard_EXPORT virtual void Remove();

  Standard_EXPORT virtual void Erase();

  Standard_EXPORT void DisplayedStructures(
    NCollection_Map<occ::handle<Graphic3d_Structure>>& SG) const;

  Standard_EXPORT void HighlightedStructures(
    NCollection_Map<occ::handle<Graphic3d_Structure>>& SG) const;

  Standard_EXPORT virtual void ReCompute(const occ::handle<Graphic3d_Structure>& theStructure);

  Standard_EXPORT virtual void ReCompute(
    const occ::handle<Graphic3d_Structure>&            theStructure,
    const occ::handle<Graphic3d_DataStructureManager>& theProjector);

  Standard_EXPORT virtual void Clear(Graphic3d_Structure* theStructure,
                                     const bool           theWithDestruction);

  Standard_EXPORT virtual void Connect(const Graphic3d_Structure* theMother,
                                       const Graphic3d_Structure* theDaughter);

  Standard_EXPORT virtual void Disconnect(const Graphic3d_Structure* theMother,
                                          const Graphic3d_Structure* theDaughter);

  Standard_EXPORT virtual void Display(const occ::handle<Graphic3d_Structure>& theStructure);

  Standard_EXPORT virtual void Erase(const occ::handle<Graphic3d_Structure>& theStructure);

  Standard_EXPORT virtual void Highlight(const occ::handle<Graphic3d_Structure>& theStructure);

  Standard_EXPORT virtual void SetTransform(const occ::handle<Graphic3d_Structure>& theStructure,
                                            const occ::handle<TopLoc_Datum3D>&      theTrsf);

  Standard_EXPORT virtual void ChangeDisplayPriority(
    const occ::handle<Graphic3d_Structure>& theStructure,
    const Graphic3d_DisplayPriority         theOldPriority,
    const Graphic3d_DisplayPriority         theNewPriority);

  Standard_EXPORT virtual void ChangeZLayer(const occ::handle<Graphic3d_Structure>& theStructure,
                                            const Graphic3d_ZLayerId                theLayerId);

  Standard_EXPORT const occ::handle<Graphic3d_GraphicDriver>& GraphicDriver() const;

  Standard_EXPORT int Identification(Graphic3d_CView* theView);

  Standard_EXPORT void UnIdentification(Graphic3d_CView* theView);

  Standard_EXPORT const NCollection_IndexedMap<Graphic3d_CView*>& DefinedViews() const;

  Standard_EXPORT int MaxNumOfViews() const;

  Standard_EXPORT virtual occ::handle<Graphic3d_Structure> Identification(const int AId) const;

  Standard_EXPORT virtual void UnHighlight(const occ::handle<Graphic3d_Structure>& AStructure);

  Standard_EXPORT virtual void UnHighlight();

  Standard_EXPORT void RecomputeStructures();

  Standard_EXPORT void RecomputeStructures(
    const NCollection_Map<Graphic3d_Structure*>& theStructures);

  Standard_EXPORT void RegisterObject(const occ::handle<Standard_Transient>&     theObject,
                                      const occ::handle<Graphic3d_ViewAffinity>& theAffinity);

  Standard_EXPORT void UnregisterObject(const occ::handle<Standard_Transient>& theObject);

  Standard_EXPORT const occ::handle<Graphic3d_ViewAffinity>& ObjectAffinity(
    const occ::handle<Standard_Transient>& theObject) const;

  bool IsDeviceLost() const { return myDeviceLostFlag; }

  void SetDeviceLost() { myDeviceLostFlag = true; }

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  Standard_EXPORT int NumberOfDisplayedStructures() const;

protected:
  Aspect_GenId                                      myViewGenId;
  NCollection_Map<occ::handle<Graphic3d_Structure>> myDisplayedStructure;
  NCollection_Map<occ::handle<Graphic3d_Structure>> myHighlightedStructure;
  NCollection_DataMap<const Standard_Transient*, occ::handle<Graphic3d_ViewAffinity>>
                                           myRegisteredObjects;
  occ::handle<Graphic3d_GraphicDriver>     myGraphicDriver;
  NCollection_IndexedMap<Graphic3d_CView*> myDefinedViews;
  bool                                     myDeviceLostFlag;
};
