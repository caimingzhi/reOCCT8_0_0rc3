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

//! From a TopoDS_Shape, or from the entity which has produced it,
//! searches for the shapes, and the entities which have produced
//! them in last transfer, which are adjacent to it by VERTICES
class XSControl_ConnectedShapes : public IFSelect_SelectExplore
{

public:
  //! Creates a Selection ConnectedShapes. It remains to be set a
  //! TransferReader
  Standard_EXPORT XSControl_ConnectedShapes();

  //! Creates a Selection ConnectedShapes, which will work with the
  //! current TransferProcess brought by the TransferReader
  Standard_EXPORT XSControl_ConnectedShapes(const occ::handle<XSControl_TransferReader>& TR);

  //! Sets a TransferReader to sort entities : it brings the
  //! TransferProcess which may change, while the TransferReader does not
  Standard_EXPORT void SetReader(const occ::handle<XSControl_TransferReader>& TR);

  //! Explores an entity : entities from which are connected to that
  //! produced by this entity, including itself
  Standard_EXPORT bool Explore(const int                              level,
                               const occ::handle<Standard_Transient>& ent,
                               const Interface_Graph&                 G,
                               Interface_EntityIterator&              explored) const override;

  //! Returns a text defining the criterium.
  //! "Connected Entities through produced Shapes"
  Standard_EXPORT TCollection_AsciiString ExploreLabel() const override;

  //! This functions considers a shape from a transfer and performs
  //! the search function explained above
  Standard_EXPORT static occ::handle<NCollection_HSequence<occ::handle<Standard_Transient>>>
    AdjacentEntities(const TopoDS_Shape&                           ashape,
                     const occ::handle<Transfer_TransientProcess>& TP,
                     const TopAbs_ShapeEnum                        type);

  DEFINE_STANDARD_RTTIEXT(XSControl_ConnectedShapes, IFSelect_SelectExplore)

private:
  occ::handle<XSControl_TransferReader> theTR;
};
