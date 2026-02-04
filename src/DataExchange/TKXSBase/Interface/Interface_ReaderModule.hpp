#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class Interface_FileReaderData;
class Interface_Check;

//! Defines unitary operations required to read an Entity from a
//! File (see FileReaderData, FileReaderTool), under control of
//! a FileReaderTool. The initial creation is performed by a
//! GeneralModule (set in GeneralLib). Then, which remains is
//! Loading data from the FileReaderData to the Entity
//!
//! To work, a GeneralModule has formerly recognized the Type read
//! from FileReaderData as a positive Case Number, then the
//! ReaderModule reads it according to this Case Number
class Interface_ReaderModule : public Standard_Transient
{

public:
  //! Translates the type of record <num> in <data> to a positive
  //! Case Number. If Recognition fails, must return 0
  Standard_EXPORT virtual int CaseNum(const occ::handle<Interface_FileReaderData>& data,
                                      const int                                    num) const = 0;

  //! Performs the effective loading from <data>, record <num>,
  //! to the Entity <ent> formerly created
  //! In case of Error or Warning, fills <ach> with messages
  //! Remark that the Case Number comes from translating a record
  Standard_EXPORT virtual void Read(const int                                    casenum,
                                    const occ::handle<Interface_FileReaderData>& data,
                                    const int                                    num,
                                    occ::handle<Interface_Check>&                ach,
                                    const occ::handle<Standard_Transient>&       ent) const = 0;

  //! Specific operator (create+read) defaulted to do nothing.
  //! It can be redefined when it is not possible to work in two
  //! steps (NewVoid then Read). This occurs when no default
  //! constructor is defined : hence the result <ent> must be
  //! created with an effective definition from the reader.
  //! Remark : if NewRead is defined, Copy has nothing to do.
  //!
  //! Returns True if it has produced something, false else.
  //! If nothing was produced, <ach> should be filled : it will be
  //! treated as "Unrecognized case" by reader tool.
  Standard_EXPORT virtual bool NewRead(const int                                    casenum,
                                       const occ::handle<Interface_FileReaderData>& data,
                                       const int                                    num,
                                       occ::handle<Interface_Check>&                ach,
                                       occ::handle<Standard_Transient>&             ent) const;

  DEFINE_STANDARD_RTTIEXT(Interface_ReaderModule, Standard_Transient)
};

