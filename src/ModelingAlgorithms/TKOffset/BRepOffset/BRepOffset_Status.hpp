#pragma once


//! status of an offset face
//! Good :
//! Reversed : e.g. Offset > Radius of a cylinder
//! Degenerated : e.g. Offset = Radius of a cylinder
//! Unknown : e.g. for a Beziersurf
enum BRepOffset_Status
{
  BRepOffset_Good,
  BRepOffset_Reversed,
  BRepOffset_Degenerated,
  BRepOffset_Unknown
};

