#include <BRepTools.hpp>
#include <Message_Messenger.hpp>
#include <Message_ProgressScope.hpp>
#include <LDOM_OSStream.hpp>
#include <LDOM_Text.hpp>
#include <Standard_SStream.hpp>
#include <Standard_Type.hpp>
#include <TDF_Label.hpp>
#include <TNaming_Builder.hpp>
#include <TNaming_Iterator.hpp>
#include <TNaming_NamedShape.hpp>
#include <TopoDS_Shape.hpp>
#include <XmlMNaming_NamedShapeDriver.hpp>
#include <XmlMNaming_Shape1.hpp>
#include <XmlObjMgt.hpp>
#include <XmlObjMgt_Array1.hpp>
#include <XmlObjMgt_Persistent.hpp>

IMPLEMENT_STANDARD_RTTIEXT(XmlMNaming_NamedShapeDriver, XmlMDF_ADriver)

static TNaming_Evolution          EvolutionEnum(const XmlObjMgt_DOMString&);
static const XmlObjMgt_DOMString& EvolutionString(const TNaming_Evolution);
static void doTranslate(const TopoDS_Shape&, XmlMNaming_Shape1&, BRepTools_ShapeSet&);
static int  doTranslate(const XmlMNaming_Shape1&, TopoDS_Shape&, BRepTools_ShapeSet&);

IMPLEMENT_DOMSTRING(OldsString, "olds")
IMPLEMENT_DOMSTRING(NewsString, "news")
IMPLEMENT_DOMSTRING(StatusString, "evolution")
IMPLEMENT_DOMSTRING(VersionString, "version")
IMPLEMENT_DOMSTRING(ShapesString, "shapes")

IMPLEMENT_DOMSTRING(EvolPrimitiveString, "primitive")
IMPLEMENT_DOMSTRING(EvolGeneratedString, "generated")
IMPLEMENT_DOMSTRING(EvolModifyString, "modify")
IMPLEMENT_DOMSTRING(EvolDeleteString, "delete")
IMPLEMENT_DOMSTRING(EvolSelectedString, "selected")
IMPLEMENT_DOMSTRING(EvolReplaceString, "replace")

XmlMNaming_NamedShapeDriver::XmlMNaming_NamedShapeDriver(
  const occ::handle<Message_Messenger>& theMessageDriver)
    : XmlMDF_ADriver(theMessageDriver, nullptr),
      myShapeSet(false)
{
}

occ::handle<TDF_Attribute> XmlMNaming_NamedShapeDriver::NewEmpty() const
{
  return (new TNaming_NamedShape());
}

bool XmlMNaming_NamedShapeDriver::Paste(const XmlObjMgt_Persistent&       theSource,
                                        const occ::handle<TDF_Attribute>& theTarget,
                                        XmlObjMgt_RRelocationTable&) const
{
  occ::handle<TNaming_NamedShape> aTarget = occ::down_cast<TNaming_NamedShape>(theTarget);
  TDF_Label                       Label   = aTarget->Label();
  TNaming_Builder                 aBld(Label);

  int                      aVersion   = 0;
  const XmlObjMgt_Element& anElement  = theSource;
  XmlObjMgt_DOMString      aVerString = anElement.getAttribute(::VersionString());
  if (aVerString != nullptr)
    aVerString.GetInteger(aVersion);

  XmlObjMgt_DOMString aStatus = anElement.getAttribute(::StatusString());
  TNaming_Evolution   evol    = EvolutionEnum(aStatus);

  aTarget->SetVersion(aVersion);

  const XmlObjMgt_Array1 OldPShapes(anElement, ::OldsString());
  const XmlObjMgt_Array1 NewPShapes(anElement, ::NewsString());
  if (NewPShapes.Length() == 0 && OldPShapes.Length() == 0)
    return true;

  TopoDS_Shape        anOldShape;
  TopoDS_Shape        aNewShape;
  BRepTools_ShapeSet& aShapeSet = (BRepTools_ShapeSet&)myShapeSet;

  int lower = NewPShapes.Lower();
  if (OldPShapes.Lower() < lower)
    lower = OldPShapes.Lower();

  int upper = NewPShapes.Upper();
  if (OldPShapes.Upper() > upper)
    upper = OldPShapes.Upper();

  for (int i = upper; i >= lower; --i)
  {
    const XmlMNaming_Shape1 aNewPShape  = NewPShapes.Value(i);
    const XmlMNaming_Shape1 anOldPShape = OldPShapes.Value(i);

    if (evol != TNaming_PRIMITIVE && anOldPShape.Element() != nullptr)
    {
      if (::doTranslate(anOldPShape, anOldShape, aShapeSet))
      {
        myMessageDriver->Send("NamedShapeDriver: Error reading a shape from array", Message_Fail);
        return false;
      }
    }

    if (evol != TNaming_DELETE && aNewPShape.Element() != nullptr)
    {
      if (::doTranslate(aNewPShape, aNewShape, aShapeSet))
      {
        myMessageDriver->Send("NamedShapeDriver: Error reading a shape from array", Message_Fail);
        return false;
      }
    }

    switch (evol)
    {
      case TNaming_PRIMITIVE:
        aBld.Generated(aNewShape);
        break;
      case TNaming_GENERATED:
        aBld.Generated(anOldShape, aNewShape);
        break;
      case TNaming_MODIFY:
        aBld.Modify(anOldShape, aNewShape);
        break;
      case TNaming_DELETE:
        aBld.Delete(anOldShape);
        break;
      case TNaming_SELECTED:
        aBld.Select(aNewShape, anOldShape);
        break;
      case TNaming_REPLACE:
        aBld.Modify(anOldShape, aNewShape);
        break;

      default:
        throw Standard_DomainError("TNaming_Evolution; enum term unknown");
    }
    anOldShape.Nullify();
    aNewShape.Nullify();
  }
  return true;
}

void XmlMNaming_NamedShapeDriver::Paste(const occ::handle<TDF_Attribute>& theSource,
                                        XmlObjMgt_Persistent&             theTarget,
                                        XmlObjMgt_SRelocationTable&) const
{

  XmlObjMgt_Document aDoc = XmlObjMgt_Document(theTarget.Element().getOwnerDocument());

  occ::handle<TNaming_NamedShape> aNamedShape = occ::down_cast<TNaming_NamedShape>(theSource);
  TNaming_Evolution               evol        = aNamedShape->Evolution();

  int              NbShapes = 0;
  TNaming_Iterator SItr(aNamedShape);
  while (SItr.More())
  {
    NbShapes++;
    SItr.Next();
  }

  BRepTools_ShapeSet& aShapeSet = (BRepTools_ShapeSet&)myShapeSet;
  XmlObjMgt_Array1    OldPShapes(1, NbShapes), NewPShapes(1, NbShapes);

  OldPShapes.CreateArrayElement(theTarget, ::OldsString());
  NewPShapes.CreateArrayElement(theTarget, ::NewsString());

  int              i = 1;
  TNaming_Iterator SIterator(aNamedShape);
  while (SIterator.More())
  {
    const TopoDS_Shape& OldShape = SIterator.OldShape();
    const TopoDS_Shape& NewShape = SIterator.NewShape();

    if (evol != TNaming_PRIMITIVE)
    {
      XmlMNaming_Shape1 anOldPShape(aDoc);
      ::doTranslate(OldShape, anOldPShape, aShapeSet);
      OldPShapes.SetValue(i, anOldPShape.Element());
    }

    if (evol != TNaming_DELETE)
    {
      XmlMNaming_Shape1 aNewPShape(aDoc);
      ::doTranslate(NewShape, aNewPShape, aShapeSet);
      NewPShapes.SetValue(i, aNewPShape.Element());
    }
    i++;
    SIterator.Next();
  }

  theTarget.Element().setAttribute(::StatusString(), EvolutionString(evol));
  int aVersion = aNamedShape->Version();
  if (aVersion != 0)
    theTarget.Element().setAttribute(::VersionString(), aVersion);
}

static const XmlObjMgt_DOMString& EvolutionString(const TNaming_Evolution i)
{
  switch (i)
  {
    case TNaming_PRIMITIVE:
      return ::EvolPrimitiveString();
    case TNaming_GENERATED:
      return ::EvolGeneratedString();
    case TNaming_MODIFY:
      return ::EvolModifyString();
    case TNaming_DELETE:
      return ::EvolDeleteString();
    case TNaming_SELECTED:
      return ::EvolSelectedString();

    case TNaming_REPLACE:
      return ::EvolModifyString();

    default:
      throw Standard_DomainError("TNaming_Evolution; enum term unknown");
  }
}

static TNaming_Evolution EvolutionEnum(const XmlObjMgt_DOMString& theString)
{
  TNaming_Evolution aResult = TNaming_PRIMITIVE;
  if (!theString.equals(::EvolPrimitiveString()))
  {
    if (theString.equals(::EvolGeneratedString()))
      aResult = TNaming_GENERATED;
    else if (theString.equals(::EvolModifyString()))
      aResult = TNaming_MODIFY;
    else if (theString.equals(::EvolDeleteString()))
      aResult = TNaming_DELETE;
    else if (theString.equals(::EvolSelectedString()))
      aResult = TNaming_SELECTED;
    else if (theString.equals(::EvolReplaceString()))
      aResult = TNaming_MODIFY;
    else
      throw Standard_DomainError("TNaming_Evolution; string value without enum term equivalence");
  }
  return aResult;
}

static void doTranslate(const TopoDS_Shape& theShape,
                        XmlMNaming_Shape1&  theResult,
                        BRepTools_ShapeSet& theShapeSet)
{

  if (theShape.IsNull())
    return;

  const int aTShapeId = theShapeSet.Add(theShape);
  const int aLocId    = theShapeSet.Locations().Index(theShape.Location());

  theResult.SetShape(aTShapeId, aLocId, theShape.Orientation());

  if (theShape.ShapeType() == TopAbs_VERTEX)
  {
    theResult.SetVertex(theShape);
  }
}

static int doTranslate(const XmlMNaming_Shape1& thePShape,
                       TopoDS_Shape&            theResult,
                       BRepTools_ShapeSet&      theShapeSet)
{
  const int aShapeId = thePShape.TShapeId();

  if (aShapeId <= 0 || aShapeId > theShapeSet.NbShapes())
    return 1;
  theResult.TShape(theShapeSet.Shape(aShapeId).TShape());
  theResult.Orientation(thePShape.Orientation());
  theResult.Location(theShapeSet.Locations().Location(thePShape.LocId()), false);

  return 0;
}

void XmlMNaming_NamedShapeDriver::ReadShapeSection(const XmlObjMgt_Element&     theElement,
                                                   const Message_ProgressRange& theRange)
{
  XmlObjMgt_Element anElement = XmlObjMgt::FindChildByName(theElement, ::ShapesString());
  if (anElement != nullptr)
  {
    for (LDOM_Node aNode = anElement.getFirstChild(); aNode != nullptr;
         aNode           = anElement.getNextSibling())
    {
      if (aNode.getNodeType() == LDOM_Node::TEXT_NODE)
      {
        LDOMString        aData = aNode.getNodeValue();
        std::stringstream aStream(std::string(aData.GetString()));
        myShapeSet.Clear();
        myShapeSet.Read(aStream, theRange);
        break;
      }
    }
  }
}

void XmlMNaming_NamedShapeDriver::WriteShapeSection(XmlObjMgt_Element&    theElement,
                                                    TDocStd_FormatVersion theStorageFormatVersion,
                                                    const Message_ProgressRange& theRange)
{

  XmlObjMgt_Document aDoc      = theElement.getOwnerDocument();
  XmlObjMgt_Element  anElement = aDoc.createElement(::ShapesString());
  theElement.appendChild(anElement);

  if (myShapeSet.NbShapes() > 0)
  {
    if (theStorageFormatVersion >= TDocStd_FormatVersion_VERSION_11)
    {
      myShapeSet.SetFormatNb(TopTools_FormatVersion_VERSION_3);
    }
    else
    {
      myShapeSet.SetFormatNb(TopTools_FormatVersion_VERSION_1);
    }

    LDOM_OSStream aStream(16 * 1024);

    Message_ProgressScope aPS(theRange, "Writing shape section", 2);
    myShapeSet.Write(aStream, aPS.Next());
    if (!aPS.More())
      return;

    aStream << std::ends;
    char*     aStr  = (char*)aStream.str();
    LDOM_Text aText = aDoc.createTextNode(aStr);
    delete[] aStr;
    aText.SetValueClear();

    anElement.appendChild(aText);

    BRepTools_ShapeSet& aShapeSet = (BRepTools_ShapeSet&)myShapeSet;
    aShapeSet.Clear();
    if (!aPS.More())
      return;
    aPS.Next();
  }
}

void XmlMNaming_NamedShapeDriver::Clear()
{
  myShapeSet.Clear();
}
