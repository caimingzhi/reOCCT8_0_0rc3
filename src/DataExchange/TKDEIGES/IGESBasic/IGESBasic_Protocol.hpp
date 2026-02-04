#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_Protocol.hpp>
#include <Standard_Integer.hpp>
class Interface_Protocol;

//! Description of Protocol for IGESBasic
class IGESBasic_Protocol : public IGESData_Protocol
{

public:
  Standard_EXPORT IGESBasic_Protocol();

  //! Gives the count of Resource Protocol. Here, one
  //! (Protocol from IGESData)
  Standard_EXPORT int NbResources() const override;

  //! Returns a Resource, given a rank.
  Standard_EXPORT occ::handle<Interface_Protocol> Resource(const int num) const override;

  //! Returns a Case Number, specific of each recognized Type
  //! This Case Number is then used in Libraries : the various
  //! Modules attached to this class of Protocol must use them
  //! in accordance (for a given value of TypeNumber, they must
  //! consider the same Type as the Protocol defines)
  Standard_EXPORT int TypeNumber(const occ::handle<Standard_Type>& atype) const override;

  DEFINE_STANDARD_RTTIEXT(IGESBasic_Protocol, IGESData_Protocol)
};

