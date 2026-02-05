#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Draw_Drawable3D.hpp>
#include <Standard_OStream.hpp>
#include <Draw_Interpretor.hpp>
class HLRTopoBRep_OutLiner;
class TopoDS_Shape;
class Draw_Display;

class HLRTest_OutLiner : public Draw_Drawable3D
{

public:
  Standard_EXPORT HLRTest_OutLiner(const TopoDS_Shape& S);

  occ::handle<HLRTopoBRep_OutLiner> OutLiner() const;

  //! Does nothhing,
  Standard_EXPORT void DrawOn(Draw_Display& dis) const override;

  //! For variable copy.
  Standard_EXPORT occ::handle<Draw_Drawable3D> Copy() const override;

  //! For variable dump.
  Standard_EXPORT void Dump(Standard_OStream& S) const override;

  //! For variable whatis command. Set as a result the
  //! type of the variable.
  Standard_EXPORT void Whatis(Draw_Interpretor& I) const override;

  DEFINE_STANDARD_RTTIEXT(HLRTest_OutLiner, Draw_Drawable3D)

private:
  occ::handle<HLRTopoBRep_OutLiner> myOutLiner;
};

inline occ::handle<HLRTopoBRep_OutLiner> HLRTest_OutLiner::OutLiner() const
{
  return myOutLiner;
}
