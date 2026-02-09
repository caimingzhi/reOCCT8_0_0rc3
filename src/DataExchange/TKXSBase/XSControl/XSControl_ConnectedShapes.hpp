#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExplore.hpp>
#include <Standard_Integer.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <TopAbs_ShapeEnum.hpp>
class XSControl_TransferReader;
class Standard_Transient;
class Interface_Graph;
class Interface_EntityIterator;
class TCollection_AsciiString;
class TopoDS_Shape;
class Transfer_TransientProcess;

class XSControl_ConnectedShapes : public IFSelect_SelectExplore
{

public:
  Standard_EXPORT XSControl_ConnectedShapes();

  Standard_EXPORT XSControl_ConnectedShapes(const occ::handle<XSControl_TransferReader>& TR);

  Standard_EXPORT void SetReader(const occ::handle<XSControl_TransferReader>& TR);

  Standard_EXPORT bool Explore(const int                              level,
                               const occ::handle<Standard_Transient>& ent,
                               const Interface_Graph&                 G,
                               Interface_EntityIterator&              explored) const override;

  Standard_EXPORT TCollection_AsciiString ExploreLabel() const override;

  Standard_EXPORT static occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
    AdjacentEntities(const TopoDS_Shape&                           ashape,
                     const occ::handle<Transfer_TransientProcess>& TP,
                     const TopAbs_ShapeEnum                        type);

  DEFINE_STANDARD_RTTIEXT(XSControl_ConnectedShapes, IFSelect_SelectExplore)

private:
  occ::handle<XSControl_TransferReader> theTR;
};
