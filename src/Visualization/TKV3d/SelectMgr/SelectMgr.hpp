#pragma once

#include <Standard_Type.hpp>

class Graphic3d_Structure;
class Graphic3d_TransformPers;
class SelectMgr_Selection;
class gp_Trsf;

class SelectMgr
{
public:
  Standard_EXPORT static void ComputeSensitivePrs(
    const occ::handle<Graphic3d_Structure>&     theStructure,
    const occ::handle<SelectMgr_Selection>&     theSel,
    const gp_Trsf&                              theLoc,
    const occ::handle<Graphic3d_TransformPers>& theTrsfPers);
};
