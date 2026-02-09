#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XY.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class gp_Pnt2d;
class gp_Pnt;

class IGESDimen_LeaderArrow : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_LeaderArrow();

  Standard_EXPORT void Init(const double                                   height,
                            const double                                   width,
                            const double                                   depth,
                            const gp_XY&                                   position,
                            const occ::handle<NCollection_HArray1<gp_XY>>& segments);

  Standard_EXPORT void SetFormNumber(const int form);

  Standard_EXPORT int NbSegments() const;

  Standard_EXPORT double ArrowHeadHeight() const;

  Standard_EXPORT double ArrowHeadWidth() const;

  Standard_EXPORT double ZDepth() const;

  Standard_EXPORT gp_Pnt2d ArrowHead() const;

  Standard_EXPORT gp_Pnt TransformedArrowHead() const;

  Standard_EXPORT gp_Pnt2d SegmentTail(const int Index) const;

  Standard_EXPORT gp_Pnt TransformedSegmentTail(const int Index) const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_LeaderArrow, IGESData_IGESEntity)

private:
  double                                  theArrowHeadHeight;
  double                                  theArrowHeadWidth;
  double                                  theZDepth;
  gp_XY                                   theArrowHead;
  occ::handle<NCollection_HArray1<gp_XY>> theSegmentTails;
};
