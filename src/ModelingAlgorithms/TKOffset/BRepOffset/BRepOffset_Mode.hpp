#pragma once

//! Lists the offset modes. These are the following:
//! - BRepOffset_Skin which describes the offset along
//! the surface of a solid, used to obtain a manifold topological space,
//! - BRepOffset_Pipe which describes the offset of a
//! curve, used to obtain a pre-surface,
//! - BRepOffset_RectoVerso which describes the offset
//! of a given surface shell along both sides of the surface.
enum BRepOffset_Mode
{
  BRepOffset_Skin,
  BRepOffset_Pipe,
  BRepOffset_RectoVerso
};
