#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <IGESData_Protocol.hpp>
#include <Standard_Integer.hpp>
class Interface_Protocol;

//! This class allows to define complex protocols, in order to
//! treat various sub-sets (or the complete set) of the IGES Norm,
//! such as Solid + Draw (which are normally independent), etc...
//! While it inherits Protocol from IGESData, it admits UndefinedEntity too
class IGESData_FileProtocol : public IGESData_Protocol
{

public:
  //! Returns an empty FileProtocol
  Standard_EXPORT IGESData_FileProtocol();

  //! Adds a resource
  Standard_EXPORT void Add(const occ::handle<IGESData_Protocol>& protocol);

  //! Gives the count of Resources : the count of Added Protocols
  Standard_EXPORT int NbResources() const override;

  //! Returns a Resource, given a rank (rank of call to Add)
  Standard_EXPORT occ::handle<Interface_Protocol> Resource(const int num) const override;

  DEFINE_STANDARD_RTTIEXT(IGESData_FileProtocol, IGESData_Protocol)

private:
  occ::handle<IGESData_Protocol>     theresource;
  occ::handle<IGESData_FileProtocol> thenext;
};

