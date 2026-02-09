#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <gp_XY.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
class gp_Pnt;

class IGESDimen_Section : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_Section();

  Standard_EXPORT void Init(const int                                      dataType,
                            const double                                   aDisp,
                            const occ::handle<NCollection_HArray1<gp_XY>>& dataPoints);

  Standard_EXPORT void SetFormNumber(const int form);

  Standard_EXPORT int Datatype() const;

  Standard_EXPORT int NbPoints() const;

  Standard_EXPORT double ZDisplacement() const;

  Standard_EXPORT gp_Pnt Point(const int Index) const;

  Standard_EXPORT gp_Pnt TransformedPoint(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_Section, IGESData_IGESEntity)

private:
  int                                     theDatatype;
  double                                  theZDisplacement;
  occ::handle<NCollection_HArray1<gp_XY>> theDataPoints;
};
