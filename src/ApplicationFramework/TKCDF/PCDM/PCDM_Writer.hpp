#pragma once


#include <Standard.hpp>
#include <Standard_Type.hpp>

#include <Standard_Transient.hpp>

#include <Message_ProgressIndicator.hpp>

class CDM_Document;
class TCollection_ExtendedString;

class PCDM_Writer : public Standard_Transient
{
public:
  Standard_EXPORT virtual void Write(
    const occ::handle<CDM_Document>&  aDocument,
    const TCollection_ExtendedString& aFileName,
    const Message_ProgressRange&      theRange = Message_ProgressRange()) = 0;

  //! Write <theDocument> to theOStream
  Standard_EXPORT virtual void Write(
    const occ::handle<CDM_Document>& theDocument,
    Standard_OStream&                theOStream,
    const Message_ProgressRange&     theRange = Message_ProgressRange()) = 0;

  DEFINE_STANDARD_RTTIEXT(PCDM_Writer, Standard_Transient)
};

