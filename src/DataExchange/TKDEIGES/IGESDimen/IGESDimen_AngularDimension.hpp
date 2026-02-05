#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XY.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_WitnessLine;
class IGESDimen_LeaderArrow;
class gp_Pnt2d;

//! defines AngularDimension, Type <202> Form <0>
//! in package IGESDimen
//! Used to dimension angles
class IGESDimen_AngularDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_AngularDimension();

  //! This method is used to set the fields of the class
  //! AngularDimension
  //! - aNote         : General Note Entity
  //! - aLine         : First Witness Line Entity or Null
  //! Handle
  //! - anotherLine   : Second Witness Line Entity or Null
  //! Handle
  //! - aVertex       : Coordinates of vertex point
  //! - aRadius       : Radius of leader arcs
  //! - aLeader       : First Leader Entity
  //! - anotherLeader : Second Leader Entity
  Standard_EXPORT void Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                            const occ::handle<IGESDimen_WitnessLine>& aLine,
                            const occ::handle<IGESDimen_WitnessLine>& anotherLine,
                            const gp_XY&                              aVertex,
                            const double                              aRadius,
                            const occ::handle<IGESDimen_LeaderArrow>& aLeader,
                            const occ::handle<IGESDimen_LeaderArrow>& anotherLeader);

  //! returns the General Note Entity of the Dimension.
  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  //! returns False if theFirstWitnessLine is Null Handle.
  Standard_EXPORT bool HasFirstWitnessLine() const;

  //! returns the First Witness Line Entity or Null Handle.
  Standard_EXPORT occ::handle<IGESDimen_WitnessLine> FirstWitnessLine() const;

  //! returns False if theSecondWitnessLine is Null Handle.
  Standard_EXPORT bool HasSecondWitnessLine() const;

  //! returns the Second Witness Line Entity or Null Handle.
  Standard_EXPORT occ::handle<IGESDimen_WitnessLine> SecondWitnessLine() const;

  //! returns the coordinates of the Vertex point as Pnt2d from gp.
  Standard_EXPORT gp_Pnt2d Vertex() const;

  //! returns the coordinates of the Vertex point as Pnt2d from gp
  //! after Transformation. (Z = 0.0 for Transformation)
  Standard_EXPORT gp_Pnt2d TransformedVertex() const;

  //! returns the Radius of the Leader arcs.
  Standard_EXPORT double Radius() const;

  //! returns the First Leader Entity.
  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> FirstLeader() const;

  //! returns the Second Leader Entity.
  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> SecondLeader() const;

  DEFINE_STANDARD_RTTIEXT(IGESDimen_AngularDimension, IGESData_IGESEntity)

private:
  occ::handle<IGESDimen_GeneralNote> theNote;
  occ::handle<IGESDimen_WitnessLine> theFirstWitnessLine;
  occ::handle<IGESDimen_WitnessLine> theSecondWitnessLine;
  gp_XY                              theVertex;
  double                             theRadius;
  occ::handle<IGESDimen_LeaderArrow> theFirstLeader;
  occ::handle<IGESDimen_LeaderArrow> theSecondLeader;
};
