#include <TDocStd_ApplicationDelta.hpp>

#include <Standard_Type.hpp>
#include <TCollection_ExtendedString.hpp>
#include <TDocStd_Document.hpp>

IMPLEMENT_STANDARD_RTTIEXT(TDocStd_ApplicationDelta, Standard_Transient)

TDocStd_ApplicationDelta::TDocStd_ApplicationDelta() = default;

void TDocStd_ApplicationDelta::Dump(Standard_OStream& anOS) const
{
  anOS << "\t";
  myName.Print(anOS);
  anOS << " - " << myDocuments.Length() << " documents ";
  anOS << " ( ";
  int i;
  for (i = 1; i <= myDocuments.Length(); i++)
  {
    occ::handle<TDocStd_Document> aDocAddr = myDocuments.Value(i);
    anOS << "\"" << aDocAddr.get();
    anOS << "\" ";
  }
  anOS << ") ";
}
