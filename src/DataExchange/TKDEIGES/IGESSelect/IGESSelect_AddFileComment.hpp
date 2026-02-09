#pragma once

#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <TCollection_HAsciiString.hpp>
#include <NCollection_Sequence.hpp>
#include <NCollection_HSequence.hpp>
#include <IGESSelect_FileModifier.hpp>
#include <Standard_Integer.hpp>
class IFSelect_ContextWrite;
class IGESData_IGESWriter;
class TCollection_AsciiString;

class IGESSelect_AddFileComment : public IGESSelect_FileModifier
{

public:
  Standard_EXPORT IGESSelect_AddFileComment();

  Standard_EXPORT void Clear();

  Standard_EXPORT void AddLine(const char* line);

  Standard_EXPORT void AddLines(
    const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& lines);

  Standard_EXPORT int NbLines() const;

  Standard_EXPORT const char* Line(const int num) const;

  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> Lines()
    const;

  Standard_EXPORT void Perform(IFSelect_ContextWrite& ctx,
                               IGESData_IGESWriter&   writer) const override;

  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_AddFileComment, IGESSelect_FileModifier)

private:
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> thelist;
};
