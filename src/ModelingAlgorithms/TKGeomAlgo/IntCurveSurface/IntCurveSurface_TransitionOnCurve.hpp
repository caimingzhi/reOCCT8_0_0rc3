#pragma once


//! \ Uo     ^        \ U1     ^
//! \       | n       \       | n
//! Surf  ====\======|===   ====\======|===
//! \     .           \     .
//! \    .            \    .
//! U1  \   .          Uo \   .
//!
//! ( In )            ( Out )
//!
//! \           /
//! \         /
//! \       /
//! \     /
//! Surf =====-----=====
//!
//! ( Tangent )
//! Crb and Surf are C1
enum IntCurveSurface_TransitionOnCurve
{
  IntCurveSurface_Tangent,
  IntCurveSurface_In,
  IntCurveSurface_Out
};

