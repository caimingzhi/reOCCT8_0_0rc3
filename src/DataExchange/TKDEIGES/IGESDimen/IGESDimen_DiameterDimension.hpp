#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XY.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_LeaderArrow;
class gp_Pnt2d;

class IGESDimen_DiameterDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_DiameterDimension();

  Standard_EXPORT void Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                            const occ::handle<IGESDimen_LeaderArrow>& aLeader,
                            const occ::handle<IGESDimen_LeaderArrow>& anotherLeader,
                            const gp_XY&                              aCenter);

  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> FirstLeader() const;

  Standard_EXPORT bool HasSecondLeader() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> SecondLeader() const;

  Standard_EXPORT gp_Pnt2d Center() const;

  Standard_EXPORT gp_Pnt2d TransformedCenter() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_DiameterDimension, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote> theNote;
  occ::handle<IGESDimen_LeaderArrow> theFirstLeader;
  occ::handle<IGESDimen_LeaderArrow> theSecondLeader;
  gp_XY                              theCenter;
};
