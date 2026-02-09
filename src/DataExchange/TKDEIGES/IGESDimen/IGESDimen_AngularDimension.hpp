#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <gp_XY.hpp>
#include <IGESData_IGESEntity.hpp>
class IGESDimen_GeneralNote;
class IGESDimen_WitnessLine;
class IGESDimen_LeaderArrow;
class gp_Pnt2d;

class IGESDimen_AngularDimension : public IGESData_IGESEntity
{

public:
  Standard_EXPORT IGESDimen_AngularDimension();

  Standard_EXPORT void Init(const occ::handle<IGESDimen_GeneralNote>& aNote,
                            const occ::handle<IGESDimen_WitnessLine>& aLine,
                            const occ::handle<IGESDimen_WitnessLine>& anotherLine,
                            const gp_XY&                              aVertex,
                            const double                              aRadius,
                            const occ::handle<IGESDimen_LeaderArrow>& aLeader,
                            const occ::handle<IGESDimen_LeaderArrow>& anotherLeader);

  Standard_EXPORT occ::handle<IGESDimen_GeneralNote> Note() const;

  Standard_EXPORT bool HasFirstWitnessLine() const;

  Standard_EXPORT occ::handle<IGESDimen_WitnessLine> FirstWitnessLine() const;

  Standard_EXPORT bool HasSecondWitnessLine() const;

  Standard_EXPORT occ::handle<IGESDimen_WitnessLine> SecondWitnessLine() const;

  Standard_EXPORT gp_Pnt2d Vertex() const;

  Standard_EXPORT gp_Pnt2d TransformedVertex() const;

  Standard_EXPORT double Radius() const;

  Standard_EXPORT occ::handle<IGESDimen_LeaderArrow> FirstLeader() const;

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
