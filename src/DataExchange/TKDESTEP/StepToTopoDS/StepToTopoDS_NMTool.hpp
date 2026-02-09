#pragma once

#include <Standard.hpp>
#include <Standard_DefineAlloc.hpp>
#include <Standard_Handle.hpp>

#include <StepRepr_RepresentationItem.hpp>
#include <TopoDS_Shape.hpp>
#include <NCollection_DataMap.hpp>
#include <TCollection_AsciiString.hpp>
#include <NCollection_List.hpp>
#include <Standard_Boolean.hpp>
class StepRepr_RepresentationItem;
class TCollection_AsciiString;
class TopoDS_Shape;

class StepToTopoDS_NMTool
{
public:
  DEFINE_STANDARD_ALLOC

  Standard_EXPORT StepToTopoDS_NMTool();

  Standard_EXPORT StepToTopoDS_NMTool(
    const NCollection_DataMap<occ::handle<StepRepr_RepresentationItem>, TopoDS_Shape>& MapOfRI,
    const NCollection_DataMap<TCollection_AsciiString, TopoDS_Shape>& MapOfRINames);

  Standard_EXPORT void Init(
    const NCollection_DataMap<occ::handle<StepRepr_RepresentationItem>, TopoDS_Shape>& MapOfRI,
    const NCollection_DataMap<TCollection_AsciiString, TopoDS_Shape>& MapOfRINames);

  Standard_EXPORT void SetActive(const bool isActive);

  Standard_EXPORT bool IsActive();

  Standard_EXPORT void CleanUp();

  Standard_EXPORT bool IsBound(const occ::handle<StepRepr_RepresentationItem>& RI);

  Standard_EXPORT bool IsBound(const TCollection_AsciiString& RIName);

  Standard_EXPORT void Bind(const occ::handle<StepRepr_RepresentationItem>& RI,
                            const TopoDS_Shape&                             S);

  Standard_EXPORT void Bind(const TCollection_AsciiString& RIName, const TopoDS_Shape& S);

  Standard_EXPORT const TopoDS_Shape& Find(const occ::handle<StepRepr_RepresentationItem>& RI);

  Standard_EXPORT const TopoDS_Shape& Find(const TCollection_AsciiString& RIName);

  Standard_EXPORT void RegisterNMEdge(const TopoDS_Shape& Edge);

  Standard_EXPORT bool IsSuspectedAsClosing(const TopoDS_Shape& BaseShell,
                                            const TopoDS_Shape& SuspectedShell);

  Standard_EXPORT bool IsPureNMShell(const TopoDS_Shape& Shell);

  Standard_EXPORT void SetIDEASCase(const bool IDEASCase);

  Standard_EXPORT bool IsIDEASCase();

private:
  Standard_EXPORT bool isEdgeRegisteredAsNM(const TopoDS_Shape& Edge);

  Standard_EXPORT bool isAdjacentShell(const TopoDS_Shape& ShellA, const TopoDS_Shape& ShellB);

  NCollection_DataMap<occ::handle<StepRepr_RepresentationItem>, TopoDS_Shape> myRIMap;
  NCollection_DataMap<TCollection_AsciiString, TopoDS_Shape>                  myRINamesMap;
  NCollection_List<TopoDS_Shape>                                              myNMEdges;
  bool                                                                        myIDEASCase;
  bool                                                                        myActiveFlag;
};
