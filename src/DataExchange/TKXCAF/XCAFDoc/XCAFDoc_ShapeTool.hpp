#pragma once

#include <Standard.hpp>

#include <TDF_Label.hpp>
#include <TopTools_ShapeMapHasher.hpp>
#include <NCollection_DataMap.hpp>
#include <Standard_Boolean.hpp>
#include <TDataStd_NamedData.hpp>
#include <TDataStd_GenericEmpty.hpp>
#include <NCollection_Map.hpp>
#include <NCollection_Sequence.hpp>
#include <Standard_Integer.hpp>
#include <Standard_OStream.hpp>
#include <TCollection_HAsciiString.hpp>
#include <TDF_Attribute.hpp>
#include <TopoDS_Shape.hpp>
class Standard_GUID;
class TDF_Label;
class TopoDS_Shape;
class TopLoc_Location;
class XCAFDoc_GraphNode;

class XCAFDoc_ShapeTool : public TDataStd_GenericEmpty
{

public:
  Standard_EXPORT static const Standard_GUID& GetID();

  Standard_EXPORT static occ::handle<XCAFDoc_ShapeTool> Set(const TDF_Label& L);

  Standard_EXPORT XCAFDoc_ShapeTool();

  Standard_EXPORT bool IsTopLevel(const TDF_Label& L) const;

  Standard_EXPORT static bool IsFree(const TDF_Label& L);

  Standard_EXPORT static bool IsShape(const TDF_Label& L);

  Standard_EXPORT static bool IsSimpleShape(const TDF_Label& L);

  Standard_EXPORT static bool IsReference(const TDF_Label& L);

  Standard_EXPORT static bool IsAssembly(const TDF_Label& L);

  Standard_EXPORT static bool IsComponent(const TDF_Label& L);

  Standard_EXPORT static bool IsCompound(const TDF_Label& L);

  Standard_EXPORT static bool IsSubShape(const TDF_Label& L);

  Standard_EXPORT bool IsSubShape(const TDF_Label& shapeL, const TopoDS_Shape& sub) const;

  Standard_EXPORT bool SearchUsingMap(const TopoDS_Shape& S,
                                      TDF_Label&          L,
                                      const bool          findWithoutLoc,
                                      const bool          findSubshape) const;

  Standard_EXPORT bool Search(const TopoDS_Shape& S,
                              TDF_Label&          L,
                              const bool          findInstance  = true,
                              const bool          findComponent = true,
                              const bool          findSubshape  = true) const;

  Standard_EXPORT bool FindShape(const TopoDS_Shape& S,
                                 TDF_Label&          L,
                                 const bool          findInstance = false) const;

  Standard_EXPORT TDF_Label FindShape(const TopoDS_Shape& S, const bool findInstance = false) const;

  Standard_EXPORT static bool GetShape(const TDF_Label& L, TopoDS_Shape& S);

  Standard_EXPORT static TopoDS_Shape GetShape(const TDF_Label& L);

  Standard_EXPORT static TopoDS_Shape GetOneShape(const NCollection_Sequence<TDF_Label>& theLabels);

  Standard_EXPORT TopoDS_Shape GetOneShape() const;

  Standard_EXPORT TDF_Label NewShape() const;

  Standard_EXPORT void SetShape(const TDF_Label& L, const TopoDS_Shape& S);

  Standard_EXPORT TDF_Label AddShape(const TopoDS_Shape& S,
                                     const bool          makeAssembly = true,
                                     const bool          makePrepare  = true);

  Standard_EXPORT bool RemoveShape(const TDF_Label& L, const bool removeCompletely = true) const;

  Standard_EXPORT void Init();

  Standard_EXPORT static void SetAutoNaming(const bool V);

  Standard_EXPORT static bool AutoNaming();

  Standard_EXPORT void ComputeShapes(const TDF_Label& L);

  Standard_EXPORT void ComputeSimpleShapes();

  Standard_EXPORT void GetShapes(NCollection_Sequence<TDF_Label>& Labels) const;

  Standard_EXPORT void GetFreeShapes(NCollection_Sequence<TDF_Label>& FreeLabels) const;

  Standard_EXPORT static int GetUsers(const TDF_Label&                 L,
                                      NCollection_Sequence<TDF_Label>& Labels,
                                      const bool                       getsubchilds = false);

  Standard_EXPORT static TopLoc_Location GetLocation(const TDF_Label& L);

  Standard_EXPORT static bool GetReferredShape(const TDF_Label& L, TDF_Label& Label);

  Standard_EXPORT static int NbComponents(const TDF_Label& L, const bool getsubchilds = false);

  Standard_EXPORT static bool GetComponents(const TDF_Label&                 L,
                                            NCollection_Sequence<TDF_Label>& Labels,
                                            const bool                       getsubchilds = false);

  Standard_EXPORT TDF_Label AddComponent(const TDF_Label&       assembly,
                                         const TDF_Label&       comp,
                                         const TopLoc_Location& Loc);

  Standard_EXPORT TDF_Label AddComponent(const TDF_Label&    assembly,
                                         const TopoDS_Shape& comp,
                                         const bool          expand = false);

  Standard_EXPORT void RemoveComponent(const TDF_Label& comp) const;

  Standard_EXPORT void UpdateAssemblies();

  Standard_EXPORT bool FindSubShape(const TDF_Label&    shapeL,
                                    const TopoDS_Shape& sub,
                                    TDF_Label&          L) const;

  Standard_EXPORT TDF_Label AddSubShape(const TDF_Label& shapeL, const TopoDS_Shape& sub) const;

  Standard_EXPORT bool AddSubShape(const TDF_Label&    shapeL,
                                   const TopoDS_Shape& sub,
                                   TDF_Label&          addedSubShapeL) const;

  Standard_EXPORT TDF_Label FindMainShapeUsingMap(const TopoDS_Shape& sub) const;

  Standard_EXPORT TDF_Label FindMainShape(const TopoDS_Shape& sub) const;

  Standard_EXPORT static bool GetSubShapes(const TDF_Label&                 L,
                                           NCollection_Sequence<TDF_Label>& Labels);

  Standard_EXPORT TDF_Label BaseLabel() const;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& theDumpLog, const bool deep) const;

  Standard_EXPORT Standard_OStream& Dump(Standard_OStream& theDumpLog) const override;

  Standard_EXPORT static void DumpShape(Standard_OStream& theDumpLog,
                                        const TDF_Label&  L,
                                        const int         level = 0,
                                        const bool        deep  = false);

  Standard_EXPORT const Standard_GUID& ID() const override;

  Standard_EXPORT static bool IsExternRef(const TDF_Label& L);

  Standard_EXPORT TDF_Label
    SetExternRefs(const NCollection_Sequence<occ::handle<TCollection_HAsciiString>>& SHAS) const;

  Standard_EXPORT void SetExternRefs(
    const TDF_Label&                                                   L,
    const NCollection_Sequence<occ::handle<TCollection_HAsciiString>>& SHAS) const;

  Standard_EXPORT static void GetExternRefs(
    const TDF_Label&                                             L,
    NCollection_Sequence<occ::handle<TCollection_HAsciiString>>& SHAS);

  Standard_EXPORT bool SetSHUO(const NCollection_Sequence<TDF_Label>& Labels,
                               occ::handle<XCAFDoc_GraphNode>&        MainSHUOAttr) const;

  Standard_EXPORT static bool GetSHUO(const TDF_Label&                SHUOLabel,
                                      occ::handle<XCAFDoc_GraphNode>& aSHUOAttr);

  Standard_EXPORT static bool GetAllComponentSHUO(
    const TDF_Label&                                  CompLabel,
    NCollection_Sequence<occ::handle<TDF_Attribute>>& SHUOAttrs);

  Standard_EXPORT static bool GetSHUOUpperUsage(const TDF_Label&                 NextUsageL,
                                                NCollection_Sequence<TDF_Label>& Labels);

  Standard_EXPORT static bool GetSHUONextUsage(const TDF_Label&                 UpperUsageL,
                                               NCollection_Sequence<TDF_Label>& Labels);

  Standard_EXPORT bool RemoveSHUO(const TDF_Label& SHUOLabel) const;

  Standard_EXPORT bool FindComponent(const TopoDS_Shape&              theShape,
                                     NCollection_Sequence<TDF_Label>& Labels) const;

  Standard_EXPORT TopoDS_Shape GetSHUOInstance(const occ::handle<XCAFDoc_GraphNode>& theSHUO) const;

  Standard_EXPORT occ::handle<XCAFDoc_GraphNode> SetInstanceSHUO(
    const TopoDS_Shape& theShape) const;

  Standard_EXPORT bool GetAllSHUOInstances(
    const occ::handle<XCAFDoc_GraphNode>& theSHUO,
    NCollection_Sequence<TopoDS_Shape>&   theSHUOShapeSeq) const;

  Standard_EXPORT static bool FindSHUO(const NCollection_Sequence<TDF_Label>& Labels,
                                       occ::handle<XCAFDoc_GraphNode>&        theSHUOAttr);

  Standard_EXPORT bool SetLocation(const TDF_Label&       theShapeLabel,
                                   const TopLoc_Location& theLoc,
                                   TDF_Label&             theRefLabel);

  Standard_EXPORT bool Expand(const TDF_Label& Shape);

  Standard_EXPORT occ::handle<TDataStd_NamedData> GetNamedProperties(
    const TDF_Label& theLabel,
    const bool       theToCreate = false) const;

  Standard_EXPORT occ::handle<TDataStd_NamedData> GetNamedProperties(
    const TopoDS_Shape& theShape,
    const bool          theToCreate = false) const;

  Standard_EXPORT void DumpJson(Standard_OStream& theOStream, int theDepth = -1) const override;

  DEFINE_DERIVED_ATTRIBUTE(XCAFDoc_ShapeTool, TDataStd_GenericEmpty)

private:
  Standard_EXPORT bool updateComponent(const TDF_Label&            theAssmLabel,
                                       TopoDS_Shape&               theUpdatedShape,
                                       NCollection_Map<TDF_Label>& theUpdated) const;

  Standard_EXPORT TDF_Label addShape(const TopoDS_Shape& S, const bool makeAssembly = true);

  Standard_EXPORT static void MakeReference(const TDF_Label&       L,
                                            const TDF_Label&       refL,
                                            const TopLoc_Location& loc);

  Standard_EXPORT void makeSubShape(const TDF_Label&       theMainShapeL,
                                    const TDF_Label&       thePart,
                                    const TopoDS_Shape&    theShape,
                                    const TopLoc_Location& theLoc);

  NCollection_DataMap<TopoDS_Shape, TDF_Label, TopTools_ShapeMapHasher> myShapeLabels;
  NCollection_DataMap<TopoDS_Shape, TDF_Label, TopTools_ShapeMapHasher> mySubShapes;
  NCollection_DataMap<TopoDS_Shape, TDF_Label, TopTools_ShapeMapHasher> mySimpleShapes;
  bool                                                                  hasSimpleShapes;
};
