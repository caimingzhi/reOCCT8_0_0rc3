#pragma once


//! Errors that can occur at thrusection algorithm.
enum BRepFill_ThruSectionErrorStatus
{
  BRepFill_ThruSectionErrorStatus_Done,            //!< Thrusection algorithm is done
  BRepFill_ThruSectionErrorStatus_NotDone,         //!< Thrusection algorithm is not done
  BRepFill_ThruSectionErrorStatus_NotSameTopology, //!< All profiles have not same topology (they
                                                   //!< should be all closed or all opened)
  BRepFill_ThruSectionErrorStatus_ProfilesInconsistent, //!< Profiles are inconsistent
  BRepFill_ThruSectionErrorStatus_WrongUsage,           //!< Wrong usage of punctual sections
  BRepFill_ThruSectionErrorStatus_Null3DCurve,          //!< Null 3D curve in edge
  BRepFill_ThruSectionErrorStatus_Failed                //!< Thrusection algorithm has failed
};

