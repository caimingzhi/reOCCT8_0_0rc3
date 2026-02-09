#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Integer.hpp>
class TCollection_HAsciiString;
class Interface_UndefinedContent;
class StepData_StepReaderData;
class Interface_Check;
class StepData_StepWriter;
class Interface_CopyTool;
class Interface_EntityIterator;

class StepData_UndefinedEntity : public Standard_Transient
{

public:
  Standard_EXPORT StepData_UndefinedEntity();

  Standard_EXPORT StepData_UndefinedEntity(const bool issub);

  Standard_EXPORT occ::handle<Interface_UndefinedContent> UndefinedContent() const;

  Standard_EXPORT bool IsSub() const;

  Standard_EXPORT occ::handle<StepData_UndefinedEntity> Super() const;

  Standard_EXPORT bool IsComplex() const;

  Standard_EXPORT occ::handle<StepData_UndefinedEntity> Next() const;

  Standard_EXPORT const char* StepType() const;

  Standard_EXPORT void ReadRecord(const occ::handle<StepData_StepReaderData>& SR,
                                  const int                                   num,
                                  occ::handle<Interface_Check>&               ach);

  Standard_EXPORT void WriteParams(StepData_StepWriter& SW) const;

  Standard_EXPORT void GetFromAnother(const occ::handle<StepData_UndefinedEntity>& other,
                                      Interface_CopyTool&                          TC);

  Standard_EXPORT void FillShared(Interface_EntityIterator& list) const;

  DEFINE_STANDARD_RTTIEXT(StepData_UndefinedEntity, Standard_Transient)

private:
  occ::handle<TCollection_HAsciiString>   thetype;
  occ::handle<Interface_UndefinedContent> thecont;
  bool                                    thesub;
  occ::handle<StepData_UndefinedEntity>   thenext;
};
