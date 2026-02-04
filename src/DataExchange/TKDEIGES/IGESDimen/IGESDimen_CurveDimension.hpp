#pragma once


#include <Standard.hpp>

#include <IGESData_IGESEntity.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_LeaderArrow;
class IGESDimen_WitnessLine;

//! defines CurveDimension, Type <204> Form <0>
//! in package IGESDimen
//! Used to dimension curves
//! Consists of one tail segment of nonzero length
//! beginning with an arrowhead and which serves to define
//! the orientation
class IGESDimen_CurveDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_CurveDimension();

  //! This method is used to set the fields of the class
  //! CurveDimension
  //! - aNote         : General Note Entity
  //! - aCurve        : First Curve Entity
  //! - anotherCurve  : Second Curve Entity or a Null Handle
  //! - aLeader       : First Leader Entity
  //! - anotherLeader : Second Leader Entity
  //! - aLine         : First Witness Line Entity or a Null
  //! Handle
  //! - anotherLine   : Second Witness Line Entity or a Null
  //! Handle
  Standard_EXPORT void Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                            const occ::handle<IGESData_IGESEntity>&   aCurve,
                            const occ::handle<IGESData_IGESEntity>&   anotherCurve,
                            const occ::handle<IGESDimen_LeaderArrow>& aLeader,
                            const occ::handle<IGESDimen_LeaderArrow>& anotherLeader,
                            const occ::handle<IGESDimen_WitnessLine>& aLine,
                            const occ::handle<IGESDimen_WitnessLine>& anotherLine);

  //! returns the General Note Entity
  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  //! returns the First curve Entity
  Standard_EXPORT occ::handle<IGESData_IGESEntity> FirstCurve() const;

  //! returns False if theSecondCurve is a Null Handle.
  Standard_EXPORT bool HasSecondCurve() const;

  //! returns the Second curve Entity or a Null Handle.
  Standard_EXPORT occ::handle<IGESData_IGESEntity> SecondCurve() const;

  //! returns the First Leader Entity
  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> FirstLeader() const;

  //! returns the Second Leader Entity
  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> SecondLeader() const;

  //! returns False if theFirstWitnessLine is a Null Handle.
  Standard_EXPORT bool HasFirstWitnessLine() const;

  //! returns the First Witness Line Entity or a Null Handle.
  Standard_EXPORT occ::handle<IGESDimen_WitnessLine> FirstWitnessLine() const;

  //! returns False if theSecondWitnessLine is a Null Handle.
  Standard_EXPORT bool HasSecondWitnessLine() const;

  //! returns the Second Witness Line Entity or a Null Handle.
  Standard_EXPORT occ::handle<IGESDimen_WitnessLine> SecondWitnessLine() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_CurveDimension, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote> theNote;
  occ::handle<IGESData_IGESEntity>   theFirstCurve;
  occ::handle<IGESData_IGESEntity>   theSecondCurve;
  occ::handle<IGESDimen_LeaderArrow> theFirstLeader;
  occ::handle<IGESDimen_LeaderArrow> theSecondLeader;
  occ::handle<IGESDimen_WitnessLine> theFirstWitnessLine;
  occ::handle<IGESDimen_WitnessLine> theSecondWitnessLine;
};

