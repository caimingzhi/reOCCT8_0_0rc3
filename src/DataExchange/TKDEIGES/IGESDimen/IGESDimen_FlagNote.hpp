#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XYZ.hpp>
#include <IGESDimen_LeaderArrow.hpp>
#include <NCollection_Array1.hpp>
#include <NCollection_HArray1.hpp>
#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESDimen_GeneralNote;
class gp_Pnt;
class IGESDimen_LeaderArrow;

class IGESDimen_FlagNote : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_FlagNote();

  Standard_EXPORT void Init(
    const gp_XYZ&                                                               leftCorner,
    const double                                                                anAngle,
    const occ::handle<IGESDimen_GeneralNote>&                                   aNote,
    const occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>>& someLeaders);

  Standard_EXPORT gp_Pnt LowerLeftCorner() const;

  Standard_EXPORT gp_Pnt TransformedLowerLeftCorner() const;

  Standard_EXPORT double Angle() const;

  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  Standard_EXPORT int NbLeaders() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> Leader(const int Index) const;

  Standard_EXPORT double Height() const;

  Standard_EXPORT double CharacterHeight() const;

  Standard_EXPORT double Length() const;

  Standard_EXPORT double TextWidth() const;

  Standard_EXPORT double TipLength() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_FlagNote, IGESData_IGESEntity)

private:
  gp_XYZ                                                               theLowerLeftcorner;
  double                                                               theAngle;
  occ::handle<IGESDimen_GeneralNote>                                   theNote;
  occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>> theLeaders;
};
