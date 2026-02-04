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

//! defines FlagNote, Type <208> Form <0>
//! in package IGESDimen
//! Is label information formatted in different ways
class IGESDimen_FlagNote : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_FlagNote();

  //! This method is used to set the fields of the class
  //! FlagNote
  //! - leftCorner  : Lower left corner of the Flag
  //! - anAngle     : Rotation angle in radians
  //! - aNote       : General Note Entity
  //! - someLeaders : Leader Entities
  Standard_EXPORT void Init(
    const gp_XYZ&                                                               leftCorner,
    const double                                                                anAngle,
    const occ::handle<IGESDimen_GeneralNote>&                                   aNote,
    const occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>>& someLeaders);

  //! returns Lower Left coordinate of Flag as Pnt from package gp
  Standard_EXPORT gp_Pnt LowerLeftCorner() const;

  //! returns Lower Left coordinate of Flag as Pnt from package gp
  //! after Transformation.
  Standard_EXPORT gp_Pnt TransformedLowerLeftCorner() const;

  //! returns Rotation angle in radians
  Standard_EXPORT double Angle() const;

  //! returns General Note Entity
  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  //! returns number of Arrows (Leaders) or zero
  Standard_EXPORT int NbLeaders() const;

  //! returns Leader Entity
  //! raises exception if Index <= 0 or Index > NbLeaders()
  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> Leader(const int Index) const;

  //! returns Height computed by the formula :
  //! Height = 2 * CH   where CH is from theNote
  Standard_EXPORT double Height() const;

  //! returns the Character Height (from General Note)
  Standard_EXPORT double CharacterHeight() const;

  //! returns Length computed by the formula :
  //! Length = TW + 0.4*CH  where CH is from theNote
  //! and TW is from theNote
  Standard_EXPORT double Length() const;

  //! returns the Text Width (from General Note)
  Standard_EXPORT double TextWidth() const;

  //! returns TipLength computed by the formula :
  //! TipLength = 0.5 * H / tan 35(deg)  where H is Height()
  Standard_EXPORT double TipLength() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_FlagNote, IGESData_IGESEntity)

private:
  gp_XYZ                                                               theLowerLeftcorner;
  double                                                               theAngle;
  occ::handle<IGESDimen_GeneralNote>                                   theNote;
  occ::handle<NCollection_HArray1<occ::handle<IGESDimen_LeaderArrow>>> theLeaders;
};

