#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class Interface_FileReaderData;
class Interface_Check;

class Interface_ReaderModule : public Standard_Transient
{

public:
  Standard_EXPORT virtual int CaseNum(const occ::handle<Interface_FileReaderData>& data,
                                      const int                                    num) const = 0;

  Standard_EXPORT virtual void Read(const int                                    casenum,
                                    const occ::handle<Interface_FileReaderData>& data,
                                    const int                                    num,
                                    occ::handle<Interface_Check>&                ach,
                                    const occ::handle<Standard_Transient>&       ent) const = 0;

  Standard_EXPORT virtual bool NewRead(const int                                    casenum,
                                       const occ::handle<Interface_FileReaderData>& data,
                                       const int                                    num,
                                       occ::handle<Interface_Check>&                ach,
                                       occ::handle<Standard_Transient>&             ent) const;

  DEFINE_STANDARD_RTTIEXT(Interface_ReaderModule, Standard_Transient)
};
