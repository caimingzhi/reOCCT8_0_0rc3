#pragma once

#include <Standard.hpp>

#include <BRepFill_Edge3DLaw.hpp>
#include <Standard_Real.hpp>
class TopoDS_Wire;
class GeomFill_LocationDraft;

class BRepFill_DraftLaw : public BRepFill_Edge3DLaw
{

public:
  Standard_EXPORT BRepFill_DraftLaw(const TopoDS_Wire&                         Path,
                                    const occ::handle<GeomFill_LocationDraft>& Law);

  Standard_EXPORT void CleanLaw(const double TolAngular);

  DEFINE_STANDARD_RTTIEXT(BRepFill_DraftLaw, BRepFill_Edge3DLaw)
};
