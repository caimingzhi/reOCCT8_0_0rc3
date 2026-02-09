#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <BRepFill_LocationLaw.hpp>
class TopoDS_Wire;
class GeomFill_LocationGuide;

class BRepFill_ACRLaw : public BRepFill_LocationLaw
{

public:
  Standard_EXPORT BRepFill_ACRLaw(const TopoDS_Wire&                         Path,
                                  const occ::handle<GeomFill_LocationGuide>& Law);

  DEFINE_STANDARD_RTTIEXT(BRepFill_ACRLaw, BRepFill_LocationLaw)

private:
  occ::handle<NCollection_HArray1<double>> OrigParam;
};
