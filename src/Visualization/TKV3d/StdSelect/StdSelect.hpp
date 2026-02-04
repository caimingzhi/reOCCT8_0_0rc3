#pragma once


#include <SelectMgr_Selection.hpp>
#include <Prs3d_Drawer.hpp>

//! The StdSelect package provides the following services
//! -   the definition of selection modes for topological shapes
//! -   the definition of several concrete filtertandard
//! Selection2d.ap classes
//! -   2D and 3D viewer selectors.
//! Note that each new Interactive Object must have all
//! its selection modes defined.
//! Standard Classes is useful to build
//! 3D Selectable Objects, and to process
//! 3D Selections:
//!
//! - Implementation of View Selector for dynamic selection
//! in Views from V3d.
//!
//! - Implementation of Tool class to decompose 3D BRep Objects
//! into sensitive Primitives for every desired mode of selection
//! (selection of vertex,edges,wires,faces,...)
//!
//! -  Implementation of dedicated Sensitives Entities:
//! Text for 2D Views (linked to Specific 2D projectors.)
class StdSelect
{
public:
  DEFINE_STANDARD_ALLOC

  //! puts The same drawer in every BRepOwner Of SensitivePrimitive
  //! Used Only for hilight Of BRepOwner...
  Standard_EXPORT static void SetDrawerForBRepOwner(
    const occ::handle<SelectMgr_Selection>& aSelection,
    const occ::handle<Prs3d_Drawer>&        aDrawer);
};

