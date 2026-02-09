#include <Message_Messenger.hpp>
#include <Message_ProgressScope.hpp>
#include <Storage_Schema.hpp>
#include <Standard_Transient.hpp>
#include <NCollection_Map.hpp>
#include <TDF_AttributeIterator.hpp>
#include <TDF_ChildIterator.hpp>
#include <TDF_Data.hpp>
#include <TDF_Label.hpp>
#include <TDF_Tool.hpp>
#include <XmlMDF.hpp>
#include <XmlMDF_ADriver.hpp>
#include <XmlMDF_ADriverTable.hpp>
#include <XmlMDF_ReferenceDriver.hpp>
#include <XmlMDF_TagSourceDriver.hpp>
#include <XmlObjMgt_Document.hpp>
#include <XmlObjMgt_Persistent.hpp>
#include <TDocStd_Owner.hpp>
#include <TDocStd_Document.hpp>
#include <Standard_GUID.hpp>

IMPLEMENT_DOMSTRING(TagString, "tag")
IMPLEMENT_DOMSTRING(LabelString, "label")
#define DATATYPE_MIGRATION

static NCollection_Map<occ::handle<Standard_Transient>>& UnsuppTypesMap()
{
  static NCollection_Map<occ::handle<Standard_Transient>> anUnsuppTypes;
  return anUnsuppTypes;
}

void XmlMDF::FromTo(const occ::handle<TDF_Data>&            theData,
                    XmlObjMgt_Element&                      theElement,
                    XmlObjMgt_SRelocationTable&             theRelocTable,
                    const occ::handle<XmlMDF_ADriverTable>& theDrivers,
                    const Message_ProgressRange&            theRange)
{
  UnsuppTypesMap().Clear();

  WriteSubTree(theData->Root(), theElement, theRelocTable, theDrivers, theRange);
  UnsuppTypesMap().Clear();
}

int XmlMDF::WriteSubTree(const TDF_Label&                        theLabel,
                         XmlObjMgt_Element&                      theElement,
                         XmlObjMgt_SRelocationTable&             theRelocTable,
                         const occ::handle<XmlMDF_ADriverTable>& theDrivers,
                         const Message_ProgressRange&            theRange)
{
  XmlObjMgt_Document aDoc = theElement.getOwnerDocument();

  XmlObjMgt_Element aLabElem = aDoc.createElement(::LabelString());

  int                   count = 0;
  TDF_AttributeIterator itr1(theLabel);
  for (; itr1.More(); itr1.Next())
  {
    const occ::handle<TDF_Attribute>& tAtt  = itr1.Value();
    const occ::handle<Standard_Type>& aType = tAtt->DynamicType();
    occ::handle<XmlMDF_ADriver>       aDriver;
    if (theDrivers->GetDriver(aType, aDriver))
    {
      count++;

      int anId = theRelocTable.Add(tAtt);

      XmlObjMgt_Persistent pAtt;

      const char* typeName = aDriver->TypeName().ToCString();
      if (theRelocTable.GetHeaderData()->StorageVersion().IntegerValue()
            < TDocStd_FormatVersion_VERSION_8
          && strcmp(typeName, "TDataXtd_Presentation") == 0)
      {
        typeName = "TPrsStd_AISPresentation";
      }
      pAtt.CreateElement(aLabElem, typeName, anId);

      aDriver->Paste(tAtt, pAtt, theRelocTable);
    }
#ifdef OCCT_DEBUG
    else if (!UnsuppTypesMap().Contains(aType))
    {
      std::cout << "attribute driver for type " << aType->Name() << " not found" << std::endl;
      UnsuppTypesMap().Add(aType);
    }
#endif
  }

  TDF_ChildIterator itr2(theLabel);
  double            child_count = 0;
  for (; itr2.More(); ++child_count, itr2.Next())
  {
  }
  itr2.Initialize(theLabel);
  Message_ProgressScope aPS(theRange, "Writing sub-tree", child_count, true);
  for (; itr2.More() && aPS.More(); itr2.Next())
  {
    const TDF_Label& aChildLab = itr2.Value();
    count += WriteSubTree(aChildLab, aLabElem, theRelocTable, theDrivers, aPS.Next());
  }

  if (count > 0 || TDocStd_Owner::GetDocument(theLabel.Data())->EmptyLabelsSavingMode())
  {
    theElement.appendChild(aLabElem);

    aLabElem.setAttribute(::TagString(), theLabel.Tag());
  }
  return count;
}

bool XmlMDF::FromTo(const XmlObjMgt_Element&                theElement,
                    occ::handle<TDF_Data>&                  theData,
                    XmlObjMgt_RRelocationTable&             theRelocTable,
                    const occ::handle<XmlMDF_ADriverTable>& theDrivers,
                    const Message_ProgressRange&            theRange)
{
  TDF_Label aRootLab = theData->Root();
  NCollection_DataMap<TCollection_AsciiString, occ::handle<XmlMDF_ADriver>> aDriverMap;
  theDrivers->CreateDrvMap(aDriverMap);

  int count = 0;

  LDOM_Node         theNode = theElement.getFirstChild();
  XmlObjMgt_Element anElem  = (const XmlObjMgt_Element&)theNode;
  while (!anElem.isNull())
  {
    if (anElem.getNodeName().equals(::LabelString()))
    {
      int subcount = ReadSubTree(anElem, aRootLab, theRelocTable, aDriverMap, theRange);

      if (subcount < 0)
        return false;

      (void)count;
      count += subcount;
    }

    LDOM_Node theNode1 = anElem.getNextSibling();
    anElem             = (const XmlObjMgt_Element&)theNode1;
  }

  return true;
}

int XmlMDF::ReadSubTree(
  const XmlObjMgt_Element&                                                         theElement,
  const TDF_Label&                                                                 theLabel,
  XmlObjMgt_RRelocationTable&                                                      theRelocTable,
  const NCollection_DataMap<TCollection_AsciiString, occ::handle<XmlMDF_ADriver>>& theDriverMap,
  const Message_ProgressRange&                                                     theRange)
{

  int count = 0;

  LDOM_Node             theNode = theElement.getFirstChild();
  XmlObjMgt_Element     anElem  = (const XmlObjMgt_Element&)theNode;
  Message_ProgressScope aPS(theRange, "Reading sub-tree", 2, true);
  while (!anElem.isNull())
  {
    if (anElem.getNodeType() == LDOM_Node::ELEMENT_NODE)
    {
      if (anElem.getNodeName().equals(::LabelString()))
      {

        int                 tag;
        XmlObjMgt_DOMString aTag(anElem.getAttribute(::TagString()));
        if (!aTag.GetInteger(tag))
        {
          TCollection_ExtendedString anErrorMessage =
            TCollection_ExtendedString("Wrong Tag value for OCAF Label: ") + aTag;
          theDriverMap.Find("TDF_TagSource")->myMessageDriver->Send(anErrorMessage, Message_Fail);
          return -1;
        }

        TDF_Label aLab = theLabel.FindChild(tag, true);

        int subcount = ReadSubTree(anElem, aLab, theRelocTable, theDriverMap, aPS.Next());

        if (subcount == -1)
          return -1;
        count += subcount;
      }
      else
      {

        XmlObjMgt_DOMString aName = anElem.getNodeName();

#ifdef DATATYPE_MIGRATION
        TCollection_AsciiString newName;
        if (Storage_Schema::CheckTypeMigration(aName, newName))
        {
  #ifdef OCCT_DEBUG
          std::cout << "CheckTypeMigration:OldType = " << aName.GetString()
                    << " Len = " << strlen(aName.GetString()) << std::endl;
          std::cout << "CheckTypeMigration:NewType = " << newName << " Len = " << newName.Length()
                    << std::endl;
  #endif
          aName = newName.ToCString();
        }
#endif

        if (theDriverMap.IsBound(aName))
        {
          count++;
          const occ::handle<XmlMDF_ADriver>& driver = theDriverMap.Find(aName);
          XmlObjMgt_Persistent               pAtt(anElem);
          int                                anID = pAtt.Id();
          if (anID <= 0)
          {
            TCollection_ExtendedString anErrorMessage =
              TCollection_ExtendedString("Wrong ID of OCAF attribute with type ") + aName;
            driver->myMessageDriver->Send(anErrorMessage, Message_Fail);
            return -1;
          }
          occ::handle<TDF_Attribute> tAtt;
          bool                       isBound = theRelocTable.IsBound(anID);
          if (isBound)
            tAtt = occ::down_cast<TDF_Attribute>(theRelocTable.Find(anID));
          else
            tAtt = driver->NewEmpty();

          if (tAtt->Label().IsNull())
          {
            try
            {
              theLabel.AddAttribute(tAtt);
            }
            catch (const Standard_DomainError&)
            {

              static const Standard_GUID fbidGuid;
              tAtt->SetID(fbidGuid);
              theLabel.AddAttribute(tAtt);
            }
          }
          else
            driver->myMessageDriver->Send(TCollection_ExtendedString("XmlDriver warning: ")
                                            + "attempt to attach attribute " + aName
                                            + " to a second label",
                                          Message_Warning);

          if (!driver->Paste(pAtt, tAtt, theRelocTable))
          {

            driver->myMessageDriver->Send(TCollection_ExtendedString("XmlDriver warning: ")
                                            + "failure reading attribute " + aName,
                                          Message_Warning);
          }
          else if (!isBound)
            theRelocTable.Bind(anID, tAtt);
        }
#ifdef OCCT_DEBUG
        else
        {
          const TCollection_AsciiString anAsciiName = aName;
          std::cerr << "XmlDriver warning: "
                    << "label contains object of unknown type " << anAsciiName << std::endl;
        }
#endif
      }
    }

    LDOM_Node theNode1 = anElem.getNextSibling();
    anElem             = (const XmlObjMgt_Element&)theNode1;

    if (!aPS.More())
      return -1;
  }

  if (count > 0)
  {
  }

  return count;
}

void XmlMDF::AddDrivers(const occ::handle<XmlMDF_ADriverTable>& aDriverTable,
                        const occ::handle<Message_Messenger>&   aMessageDriver)
{
  aDriverTable->AddDriver(new XmlMDF_TagSourceDriver(aMessageDriver));
  aDriverTable->AddDriver(new XmlMDF_ReferenceDriver(aMessageDriver));
}
