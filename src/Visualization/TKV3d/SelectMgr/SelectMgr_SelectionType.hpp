#pragma once


//! Possible selection types
enum SelectMgr_SelectionType
{
  SelectMgr_SelectionType_Unknown = -1, //!< undefined selection type
  SelectMgr_SelectionType_Point,   //!< selection by point (frustum with some tolerance or axis)
  SelectMgr_SelectionType_Box,     //!< rectangle selection
  SelectMgr_SelectionType_Polyline //!< polygonal selection
};

