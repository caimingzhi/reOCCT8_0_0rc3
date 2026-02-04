#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XY.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_LeaderArrow;
class gp_Pnt2d;

//! defines DiameterDimension, Type <206> Form <0>
//! in package IGESDimen
//! Used for dimensioning diameters
class IGESDimen_DiameterDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_DiameterDimension();

  //! This method is used to set the fields of the class
  //! DiameterDimension
  //! - aNote         : General Note Entity
  //! - aLeader       : First Leader Entity
  //! - anotherLeader : Second Leader Entity or a Null Handle.
  //! - aCenter       : Arc center coordinates
  Standard_EXPORT void Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                            const occ::handle<IGESDimen_LeaderArrow>& aLeader,
                            const occ::handle<IGESDimen_LeaderArrow>& anotherLeader,
                            const gp_XY&                              aCenter);

  //! returns the General Note Entity
  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  //! returns the First Leader Entity
  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> FirstLeader() const;

  //! returns False if theSecondleader is a Null Handle.
  Standard_EXPORT bool HasSecondLeader() const;

  //! returns the Second Leader Entity
  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> SecondLeader() const;

  //! returns the Arc Center coordinates as Pnt2d from package gp
  Standard_EXPORT gp_Pnt2d Center() const;

  //! returns the Arc Center coordinates as Pnt2d from package gp
  //! after Transformation. (Z = 0.0 for Transformation)
  Standard_EXPORT gp_Pnt2d TransformedCenter() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_DiameterDimension, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote> theNote;
  occ::handle<IGESDimen_LeaderArrow> theFirstLeader;
  occ::handle<IGESDimen_LeaderArrow> theSecondLeader;
  gp_XY                              theCenter;
};

