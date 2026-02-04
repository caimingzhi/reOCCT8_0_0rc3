#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESSelect_ModelModifier.hpp>
class IFSelect_ContextModif;
class IGESData_IGESModel;
class Interface_CopyTool;
class TCollection_AsciiString;

//! Removes Curves UV or 3D (not both !) from Faces, those
//! designated by the Selection. No Selection means all the file
class IGESSelect_RemoveCurves : public IGESSelect_ModelModifier
{

public:
  //! Creates a RemoveCurves from Faces (141/142/143/144)
  //! UV True  : Removes UV Curves (pcurves)
  //! UV False : Removes 3D Curves
  Standard_EXPORT IGESSelect_RemoveCurves(const bool UV);

  //! Specific action : Removes the Curves
  Standard_EXPORT void Performing(IFSelect_ContextModif&                 ctx,
                                  const occ::handle<IGESData_IGESModel>& target,
                                  Interface_CopyTool&                    TC) const override;

  //! Returns a text which is
  //! "Remove Curves UV on Face" or "Remove Curves 3D on Face"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_RemoveCurves, IGESSelect_ModelModifier)

private:
  bool theUV;
};

