#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XY.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_LeaderArrow;
class gp_Pnt2d;
class gp_Pnt;

class IGESDimen_RadiusDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_RadiusDimension();

  Standard_EXPORT void Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                            const occ::handle<IGESDimen_LeaderArrow>& anArrow,
                            const gp_XY&                              arcCenter,
                            const occ::handle<IGESDimen_LeaderArrow>& anotherArrow);

  Standard_EXPORT void InitForm(const int form);

  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> Leader() const;

  Standard_EXPORT gp_Pnt2d Center() const;

  Standard_EXPORT gp_Pnt TransformedCenter() const;

  Standard_EXPORT bool HasLeader2() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> Leader2() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_RadiusDimension, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote> theNote;
  occ::handle<IGESDimen_LeaderArrow> theLeaderArrow;
  gp_XY                              theCenter;
  occ::handle<IGESDimen_LeaderArrow> theLeader2;
};
