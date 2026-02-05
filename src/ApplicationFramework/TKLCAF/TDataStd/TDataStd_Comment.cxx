#include <TDataStd_Comment.hpp>

#include <Standard_Dump.hpp>
#include <TDF_Label.hpp>

IMPLEMENT_DERIVED_ATTRIBUTE(TDataStd_Comment, TDataStd_GenericExtString)

//=================================================================================================

const Standard_GUID& TDataStd_Comment::GetID()
{
  static Standard_GUID TDataStd_CommentID("2a96b616-ec8b-11d0-bee7-080009dc3333");
  return TDataStd_CommentID;
}

//=================================================================================================

occ::handle<TDataStd_Comment> TDataStd_Comment::Set(const TDF_Label&                  L,
                                                    const TCollection_ExtendedString& S)
{
  occ::handle<TDataStd_Comment> A;
  if (!L.FindAttribute(TDataStd_Comment::GetID(), A))
  {
    A = new TDataStd_Comment();
    L.AddAttribute(A);
  }
  A->Set(S);
  return A;
}

//=================================================================================================

occ::handle<TDataStd_Comment> TDataStd_Comment::Set(const TDF_Label& L)
{
  occ::handle<TDataStd_Comment> A;
  if (!L.FindAttribute(TDataStd_Comment::GetID(), A))
  {
    A = new TDataStd_Comment();
    L.AddAttribute(A);
  }
  return A;
}

//=================================================================================================

TDataStd_Comment::TDataStd_Comment()
{
  myID = GetID();
}

//=================================================================================================

void TDataStd_Comment::Set(const TCollection_ExtendedString& S)
{
  // OCC2932 correction
  if (myString == S)
    return;

  Backup();
  myString = S;
}

//=================================================================================================

void TDataStd_Comment::SetID(const Standard_GUID& theGuid)
{
  if (myID == theGuid)
    return;

  Backup();
  myID = theGuid;
}

//=================================================================================================

void TDataStd_Comment::SetID()
{
  Backup();
  myID = GetID();
}

//=================================================================================================

Standard_OStream& TDataStd_Comment::Dump(Standard_OStream& anOS) const
{
  TDF_Attribute::Dump(anOS);
  anOS << "Comment=|" << Get() << "|";
  return anOS;
}
