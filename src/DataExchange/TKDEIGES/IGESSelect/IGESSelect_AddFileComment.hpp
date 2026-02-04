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

//! This class allows to add comment lines on writing an IGES File
//! These lines are added to Start Section, instead of the only
//! one blank line written by default.
class IGESSelect_AddFileComment : public IGESSelect_FileModifier
{

public:
  //! Creates a new empty AddFileComment. Use AddLine to complete it
  Standard_EXPORT IGESSelect_AddFileComment();

  //! Clears the list of file comment lines already stored
  Standard_EXPORT void Clear();

  //! Adds a line for file comment
  //! Remark: Lines are limited to 72 useful chars. A line of more than
  //! 72 chars will be split into several ones of 72 max each.
  Standard_EXPORT void AddLine(const char* line);

  //! Adds a list of lines for file comment
  //! Each of them must comply with demand of AddLine
  Standard_EXPORT void AddLines(
    const occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>>& lines);

  //! Returns the count of stored lines
  Standard_EXPORT int NbLines() const;

  //! Returns a stored line given its rank
  Standard_EXPORT const char* Line(const int num) const;

  //! Returns the complete list of lines in once
  Standard_EXPORT occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> Lines()
    const;

  //! Sends the comment lines to the file (Start Section)
  Standard_EXPORT void Perform(IFSelect_ContextWrite& ctx,
                               IGESData_IGESWriter&   writer) const override;

  //! Returns specific Label, which is
  //! "Add <nn> Comment Lines (Start Section)"
  Standard_EXPORT TCollection_AsciiString Label() const override;

  DEFINE_STANDARD_RTTIEXT(IGESSelect_AddFileComment, IGESSelect_FileModifier)

private:
  occ::handle<NCollection_HSequence<occ::handle<TCollection_HAsciiString>>> thelist;
};

