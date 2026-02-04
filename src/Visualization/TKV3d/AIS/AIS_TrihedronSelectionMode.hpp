#pragma once


//! Enumeration defining selection modes supported by AIS_Trihedron.
enum AIS_TrihedronSelectionMode
{
  AIS_TrihedronSelectionMode_EntireObject = 0, //!< select trihedron as whole
  AIS_TrihedronSelectionMode_Origin       = 1, //!< origin
  AIS_TrihedronSelectionMode_Axes         = 2, //!< axes
  AIS_TrihedronSelectionMode_MainPlanes   = 3  //!< main planes
};

