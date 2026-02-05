#pragma once

#include <Standard_Type.hpp>

class Graphic3d_Structure;
class Graphic3d_TransformPers;
class SelectMgr_Selection;
class gp_Trsf;

//! Auxiliary tools for SelectMgr package.
class SelectMgr
{
public:
  //! Compute debug presentation for sensitive objects.
  Standard_EXPORT static void ComputeSensitivePrs(
    const occ::handle<Graphic3d_Structure>&     theStructure,
    const occ::handle<SelectMgr_Selection>&     theSel,
    const gp_Trsf&                              theLoc,
    const occ::handle<Graphic3d_TransformPers>& theTrsfPers);
};
