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

//! This class allows the definition of a manager to
//! which the graphic objects are associated.
//! It allows them to be globally manipulated.
//! It defines the global attributes.
//! Keywords: Structure, Structure Manager, Update Mode,
//! Destroy, Highlight, Visible
class Graphic3d_StructureManager : public Standard_Transient
{
  friend class Graphic3d_Structure;
  DEFINE_STANDARD_RTTIEXT(Graphic3d_StructureManager, Standard_Transient)
public:
  //! Initializes the ViewManager.
  //! Currently creating of more than 100 viewer instances
  //! is not supported and leads to InitializationError and
  //! initialization failure.
  //! This limitation might be addressed in some future OCCT releases.
  //! Warning: Raises InitialisationError if the initialization
  //! of the ViewManager failed.
  Standard_EXPORT Graphic3d_StructureManager(const occ::handle<Graphic3d_GraphicDriver>& theDriver);

  //! Deletes the manager <me>.
  Standard_EXPORT ~Graphic3d_StructureManager() override;

  //! Invalidates bounding box of specified ZLayerId.
  Standard_EXPORT virtual void Update(
    const Graphic3d_ZLayerId theLayerId = Graphic3d_ZLayerId_UNKNOWN) const;

  //! Deletes and erases the 3D structure manager.
  Standard_EXPORT virtual void Remove();

  //! Erases all the structures.
  Standard_EXPORT virtual void Erase();

  //! Returns the set of structures displayed in
  //! visualiser <me>.
  Standard_EXPORT void DisplayedStructures(
    NCollection_Map<occ::handle<Graphic3d_Structure>>& SG) const;

  //! Returns the set of highlighted structures
  //! in a visualiser <me>.
  Standard_EXPORT void HighlightedStructures(
    NCollection_Map<occ::handle<Graphic3d_Structure>>& SG) const;

  //! Forces a new construction of the structure.
  //! if <theStructure> is displayed and TOS_COMPUTED.
  Standard_EXPORT virtual void ReCompute(const occ::handle<Graphic3d_Structure>& theStructure);

  //! Forces a new construction of the structure.
  //! if <theStructure> is displayed in <theProjector> and TOS_COMPUTED.
  Standard_EXPORT virtual void ReCompute(
    const occ::handle<Graphic3d_Structure>&            theStructure,
    const occ::handle<Graphic3d_DataStructureManager>& theProjector);

  //! Clears the structure.
  Standard_EXPORT virtual void Clear(Graphic3d_Structure* theStructure,
                                     const bool           theWithDestruction);

  //! Connects the structures.
  Standard_EXPORT virtual void Connect(const Graphic3d_Structure* theMother,
                                       const Graphic3d_Structure* theDaughter);

  //! Disconnects the structures.
  Standard_EXPORT virtual void Disconnect(const Graphic3d_Structure* theMother,
                                          const Graphic3d_Structure* theDaughter);

  //! Display the structure.
  Standard_EXPORT virtual void Display(const occ::handle<Graphic3d_Structure>& theStructure);

  //! Erases the structure.
  Standard_EXPORT virtual void Erase(const occ::handle<Graphic3d_Structure>& theStructure);

  //! Highlights the structure.
  Standard_EXPORT virtual void Highlight(const occ::handle<Graphic3d_Structure>& theStructure);

  //! Transforms the structure.
  Standard_EXPORT virtual void SetTransform(const occ::handle<Graphic3d_Structure>& theStructure,
                                            const occ::handle<TopLoc_Datum3D>&      theTrsf);

  //! Changes the display priority of the structure <AStructure>.
  Standard_EXPORT virtual void ChangeDisplayPriority(
    const occ::handle<Graphic3d_Structure>& theStructure,
    const Graphic3d_DisplayPriority         theOldPriority,
    const Graphic3d_DisplayPriority         theNewPriority);

  //! Change Z layer for structure. The Z layer mechanism allows to display structures in higher
  //! layers in overlay of structures in lower layers.
  Standard_EXPORT virtual void ChangeZLayer(const occ::handle<Graphic3d_Structure>& theStructure,
                                            const Graphic3d_ZLayerId                theLayerId);

  //! Returns the graphic driver of <me>.
  Standard_EXPORT const occ::handle<Graphic3d_GraphicDriver>& GraphicDriver() const;

  //! Attaches the view to this structure manager and sets its identification number within the
  //! manager.
  Standard_EXPORT int Identification(Graphic3d_CView* theView);

  //! Detach the view from this structure manager and release its identification.
  Standard_EXPORT void UnIdentification(Graphic3d_CView* theView);

  //! Returns the group of views defined in the structure manager.
  Standard_EXPORT const NCollection_IndexedMap<Graphic3d_CView*>& DefinedViews() const;

  //! Returns the theoretical maximum number of definable views in the manager.
  //! Warning: It's not possible to accept an infinite number of definable views because each
  //! view must have an identification and we have different managers.
  Standard_EXPORT int MaxNumOfViews() const;

  //! Returns the structure with the identification number <AId>.
  Standard_EXPORT virtual occ::handle<Graphic3d_Structure> Identification(const int AId) const;

  //! Suppress the highlighting on the structure <AStructure>.
  Standard_EXPORT virtual void UnHighlight(const occ::handle<Graphic3d_Structure>& AStructure);

  //! Suppresses the highlighting on all the structures in <me>.
  Standard_EXPORT virtual void UnHighlight();

  //! Recomputes all structures in the manager.
  //! Resets Device Lost flag.
  Standard_EXPORT void RecomputeStructures();

  //! Recomputes all structures from theStructures.
  Standard_EXPORT void RecomputeStructures(
    const NCollection_Map<Graphic3d_Structure*>& theStructures);

  Standard_EXPORT void RegisterObject(const occ::handle<Standard_Transient>&     theObject,
                                      const occ::handle<Graphic3d_ViewAffinity>& theAffinity);

  Standard_EXPORT void UnregisterObject(const occ::handle<Standard_Transient>& theObject);

  Standard_EXPORT const occ::handle<Graphic3d_ViewAffinity>& ObjectAffinity(
    const occ::handle<Standard_Transient>& theObject) const;

  //! Returns TRUE if Device Lost flag has been set and presentation data should be reuploaded onto
  //! graphics driver.
  bool IsDeviceLost() const { return myDeviceLostFlag; }

  //! Sets Device Lost flag.
  void SetDeviceLost() { myDeviceLostFlag = true; }

  //! Dumps the content of me into the stream
  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const;

protected:
  //! Returns the number of structures displayed in
  //! visualizer <me>.
  //! Returns the structure displayed in visualizer <me>.
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

