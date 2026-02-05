#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IFSelect_SelectExtract.hpp>
#include <Standard_Integer.hpp>
class IFSelect_IntParam;
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

//! This selection looks at Level Number of IGES Entities :
//! it considers items attached, either to a single level with a
//! given value, or to a level list which contains this value
//!
//! Level = 0  means entities not attached to any level
//!
//! Remark : the class CounterOfLevelNumber gives information
//! about present levels in a file.
class IGESSelect_SelectLevelNumber : public IFSelect_SelectExtract
{

public:
  //! Creates a SelectLevelNumber, with no Level criterium : see
  //! SetLevelNumber. Empty, this selection filters nothing.
  Standard_EXPORT IGESSelect_SelectLevelNumber();

  //! Sets a Parameter as Level criterium
  Standard_EXPORT void SetLevelNumber(const occ::handle<IFSelect_IntParam>& levnum);

  //! Returns the Level criterium. NullHandle if not yet set
  //! (interpreted as Level = 0 : no level number attached)
  Standard_EXPORT occ::handle<IFSelect_IntParam> LevelNumber() const;

  //! Returns True if <ent> is an IGES Entity with Level Number
  //! admits the criterium (= value if single level, or one of the
  //! attached level numbers = value if level list)
  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  //! Returns the Selection criterium :
  //! "IGES Entity, Level Number admits <nn>" (if nn > 0) or
  //! "IGES Entity attached to no Level" (if nn = 0)
  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectLevelNumber, IFSelect_SelectExtract)

private:
  occ::handle<IFSelect_IntParam> thelevnum;
};
