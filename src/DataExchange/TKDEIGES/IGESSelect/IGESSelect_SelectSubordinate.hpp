#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Integer.hpp>
#include <IFSelect_SelectExtract.hpp>
class Standard_Transient;
class Interface_InterfaceModel;
class TCollection_AsciiString;

// resolve name collisions with X11 headers
#ifdef Status
  #undef Status
#endif

//! This selections uses Subordinate Status as sort criterium
//! It is an integer number which can be :
//! 0 Independent
//! 1 Physically Dependent
//! 2 Logically Dependent
//! 3 Both (recorded)
//! + to sort :
//! 4 : 1 or 3  ->  at least Physically
//! 5 : 2 or 3  ->  at least Logically
//! 6 : 1 or 2 or 3 -> any kind of dependence
//! (corresponds to 0 reversed)
class IGESSelect_SelectSubordinate : public IFSelect_SelectExtract
{

public:
  //! Creates a SelectSubordinate with a status to be sorted
  Standard_EXPORT IGESSelect_SelectSubordinate(const int status);

  //! Returns the status used for sorting
  Standard_EXPORT int Status() const;

  //! Returns True if <ent> is an IGES Entity with Subordinate
  //! Status matching the criterium
  Standard_EXPORT bool Sort(const int                                    rank,
                            const occ::handle<Standard_Transient>&       ent,
                            const occ::handle<Interface_InterfaceModel>& model) const override;

  //! Returns the Selection criterium : "IGES Entity, Independent"
  //! etc...
  Standard_EXPORT TCollection_AsciiString ExtractLabel() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_SelectSubordinate, IFSelect_SelectExtract)

private:
  int thestatus;
};

