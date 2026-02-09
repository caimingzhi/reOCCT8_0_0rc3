

#include <RWMesh.hpp>

#include <TDataStd_Name.hpp>
#include <TDF_Tool.hpp>

TCollection_AsciiString RWMesh::ReadNameAttribute(const TDF_Label& theLabel)
{
  occ::handle<TDataStd_Name> aNodeName;
  return theLabel.FindAttribute(TDataStd_Name::GetID(), aNodeName)
           ? TCollection_AsciiString(aNodeName->Get())
           : TCollection_AsciiString();
}

TCollection_AsciiString RWMesh::FormatName(RWMesh_NameFormat theFormat,
                                           const TDF_Label&  theLabel,
                                           const TDF_Label&  theRefLabel)
{
  switch (theFormat)
  {
    case RWMesh_NameFormat_Empty:
    {
      return TCollection_AsciiString();
    }
    case RWMesh_NameFormat_Product:
    {
      occ::handle<TDataStd_Name> aRefNodeName;
      return theRefLabel.FindAttribute(TDataStd_Name::GetID(), aRefNodeName)
               ? TCollection_AsciiString(aRefNodeName->Get())
               : TCollection_AsciiString();
    }
    case RWMesh_NameFormat_Instance:
    {
      occ::handle<TDataStd_Name> aNodeName;
      return theLabel.FindAttribute(TDataStd_Name::GetID(), aNodeName)
               ? TCollection_AsciiString(aNodeName->Get())
               : TCollection_AsciiString();
    }
    case RWMesh_NameFormat_InstanceOrProduct:
    {
      occ::handle<TDataStd_Name> aNodeName;
      if (theLabel.FindAttribute(TDataStd_Name::GetID(), aNodeName) && !aNodeName->Get().IsEmpty())
      {
        return TCollection_AsciiString(aNodeName->Get());
      }

      occ::handle<TDataStd_Name> aRefNodeName;
      return theRefLabel.FindAttribute(TDataStd_Name::GetID(), aRefNodeName)
               ? TCollection_AsciiString(aRefNodeName->Get())
               : TCollection_AsciiString();
    }
    case RWMesh_NameFormat_ProductOrInstance:
    {
      occ::handle<TDataStd_Name> aRefNodeName;
      if (theRefLabel.FindAttribute(TDataStd_Name::GetID(), aRefNodeName)
          && !aRefNodeName->Get().IsEmpty())
      {
        return TCollection_AsciiString(aRefNodeName->Get());
      }

      occ::handle<TDataStd_Name> aNodeName;
      return theLabel.FindAttribute(TDataStd_Name::GetID(), aNodeName)
               ? TCollection_AsciiString(aNodeName->Get())
               : TCollection_AsciiString();
    }
    case RWMesh_NameFormat_ProductAndInstance:
    {
      const TCollection_AsciiString anInstName = ReadNameAttribute(theLabel);
      const TCollection_AsciiString aProdName  = ReadNameAttribute(theRefLabel);
      return !anInstName.IsEmpty() && aProdName != anInstName
               ? aProdName + " [" + anInstName + "]"
               : (!aProdName.IsEmpty() ? aProdName : TCollection_AsciiString(""));
    }
    case RWMesh_NameFormat_ProductAndInstanceAndOcaf:
    {
      const TCollection_AsciiString anInstName = ReadNameAttribute(theLabel);
      const TCollection_AsciiString aProdName  = ReadNameAttribute(theRefLabel);
      TCollection_AsciiString       anEntryId;
      TDF_Tool::Entry(theLabel, anEntryId);
      return !anInstName.IsEmpty() && aProdName != anInstName
               ? aProdName + " [" + anInstName + "]" + " [" + anEntryId + "]"
               : aProdName + " [" + anEntryId + "]";
    }
  }

  return TCollection_AsciiString();
}
