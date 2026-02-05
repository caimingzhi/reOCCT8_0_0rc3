#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_IGESEntity.hpp>
#include <Standard_Integer.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_LeaderArrow;
class IGESDimen_WitnessLine;

//! defines LinearDimension, Type <216> Form <0>
//! in package IGESDimen
//! Used for linear dimensioning
class IGESDimen_LinearDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_LinearDimension();

  //! This method is used to set the fields of the class
  //! LinearDimension
  //! - aNote          : General Note Entity
  //! - aLeader        : First Leader Entity
  //! - anotherLeader  : Second Leader Entity
  //! - aWitness       : First Witness Line Entity or a Null
  //! Handle
  //! - anotherWitness : Second Witness Line Entity or a Null
  //! Handle
  Standard_EXPORT void Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                            const occ::handle<IGESDimen_LeaderArrow>& aLeader,
                            const occ::handle<IGESDimen_LeaderArrow>& anotherLeader,
                            const occ::handle<IGESDimen_WitnessLine>& aWitness,
                            const occ::handle<IGESDimen_WitnessLine>& anotherWitness);

  //! Changes FormNumber (indicates the Nature of the Dimension
  //! Unspecified, Diameter or Radius)
  //! Error if not in range [0-2]
  Standard_EXPORT void SetFormNumber(const int form);

  //! returns General Note Entity
  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  //! returns first Leader Entity
  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> FirstLeader() const;

  //! returns second Leader Entity
  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> SecondLeader() const;

  //! returns False if no first witness line
  Standard_EXPORT bool HasFirstWitness() const;

  //! returns first Witness Line Entity or a Null Handle
  Standard_EXPORT occ::handle<IGESDimen_WitnessLine> FirstWitness() const;

  //! returns False if no second witness line
  Standard_EXPORT bool HasSecondWitness() const;

  //! returns second Witness Line Entity or a Null Handle
  Standard_EXPORT occ::handle<IGESDimen_WitnessLine> SecondWitness() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_LinearDimension, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote> theNote;
  occ::handle<IGESDimen_LeaderArrow> theFirstLeader;
  occ::handle<IGESDimen_LeaderArrow> theSecondLeader;
  occ::handle<IGESDimen_WitnessLine> theFirstWitness;
  occ::handle<IGESDimen_WitnessLine> theSecondWitness;
};
