

#include <StdPersistent_Naming.hpp>
#include <StdObjMgt_ReadData.hpp>

#include <TNaming_Name.hpp>
#include <TNaming_Builder.hpp>
#include <TNaming_Iterator.hpp>

void StdPersistent_Naming::NamedShape::Import(
  const occ::handle<TNaming_NamedShape>& theAttribute) const
{
  theAttribute->SetVersion(myVersion);

  if (myOldShapes.IsNull() || myNewShapes.IsNull())
    return;

  TNaming_Builder aBuilder(theAttribute->Label());

  NCollection_HArray1<StdObject_Shape>::Iterator aOldShapesIter(*myOldShapes->Array());
  NCollection_HArray1<StdObject_Shape>::Iterator aNewShapesIter(*myNewShapes->Array());
  for (; aNewShapesIter.More(); aOldShapesIter.Next(), aNewShapesIter.Next())
  {
    TopoDS_Shape aOldShape = aOldShapesIter.Value().Import();
    TopoDS_Shape aNewShape = aNewShapesIter.Value().Import();

    switch (myShapeStatus)
    {
      case 0:
        aBuilder.Generated(aNewShape);
        break;
      case 1:
        aBuilder.Generated(aOldShape, aNewShape);
        break;
      case 2:
        aBuilder.Modify(aOldShape, aNewShape);
        break;
      case 3:
        aBuilder.Delete(aOldShape);
        break;
      case 4:
        aBuilder.Select(aNewShape, aOldShape);
        break;
      case 5:
        aBuilder.Modify(aOldShape, aNewShape);
        break;
    }
  }
}

void StdPersistent_Naming::Name::Read(StdObjMgt_ReadData& theReadData)
{
  theReadData >> myType >> myShapeType >> myArgs >> myStop >> myIndex;
}

void StdPersistent_Naming::Name::Write(StdObjMgt_WriteData& theWriteData) const
{
  theWriteData << myType << myShapeType << myArgs << myStop << myIndex;
}

void StdPersistent_Naming::Name::Import(TNaming_Name& theName, const occ::handle<TDF_Data>&) const
{
  theName.Type(static_cast<TNaming_NameType>(myType));
  theName.ShapeType(static_cast<TopAbs_ShapeEnum>(myShapeType));

  if (myArgs)
  {
    NCollection_HArray1<occ::handle<StdObjMgt_Persistent>>::Iterator anIter(*myArgs->Array());
    for (; anIter.More(); anIter.Next())
    {
      const occ::handle<StdObjMgt_Persistent>& aPersistent = anIter.Value();
      if (aPersistent)
      {
        occ::handle<TDF_Attribute> anArg = aPersistent->GetAttribute();
        theName.Append(occ::down_cast<TNaming_NamedShape>(anArg));
      }
    }
  }

  if (myStop)
  {
    occ::handle<TDF_Attribute> aStop = myStop->GetAttribute();
    theName.StopNamedShape(occ::down_cast<TNaming_NamedShape>(aStop));
  }

  theName.Index(myIndex);
}

void StdPersistent_Naming::Name_1::Read(StdObjMgt_ReadData& theReadData)
{
  Name::Read(theReadData);
  theReadData >> myContextLabel;
}

void StdPersistent_Naming::Name_1::Write(StdObjMgt_WriteData& theWriteData) const
{
  Name::Write(theWriteData);
  theWriteData << myContextLabel;
}

void StdPersistent_Naming::Name_1::Import(TNaming_Name&                theName,
                                          const occ::handle<TDF_Data>& theDF) const
{
  Name::Import(theName, theDF);
  if (myContextLabel)
    theName.ContextLabel(myContextLabel->Label(theDF));
}

void StdPersistent_Naming::Name_2::Read(StdObjMgt_ReadData& theReadData)
{
  Name_1::Read(theReadData);
  theReadData >> myOrientation;
}

void StdPersistent_Naming::Name_2::Write(StdObjMgt_WriteData& theWriteData) const
{
  Name_1::Write(theWriteData);
  theWriteData << myOrientation;
}

void StdPersistent_Naming::Name_2::Import(TNaming_Name&                theName,
                                          const occ::handle<TDF_Data>& theDF) const
{
  Name_1::Import(theName, theDF);
  theName.Orientation(static_cast<TopAbs_Orientation>(myOrientation));
}

void StdPersistent_Naming::Naming::ImportAttribute()
{
  occ::handle<Name> aName = occ::down_cast<Name>(myData);
  if (aName)
  {
    aName->Import(myTransient->ChangeName(), myTransient->Label().Data());
    myData.Nullify();
  }
}

void StdPersistent_Naming::Naming_1::ImportAttribute()
{
  Naming::ImportAttribute();

  occ::handle<TNaming_NamedShape> aNamedShape;
  if (myTransient->Label().FindAttribute(TNaming_NamedShape::GetID(), aNamedShape)
      && aNamedShape->Evolution() == TNaming_SELECTED)
  {
    for (TNaming_Iterator anIter(aNamedShape); anIter.More(); anIter.Next())
    {
      const TopoDS_Shape& aOldShape = anIter.OldShape();
      const TopoDS_Shape& aNewShape = anIter.NewShape();

      if (!aOldShape.IsNull() && aOldShape.ShapeType() == TopAbs_VERTEX && !aNewShape.IsNull()
          && aNewShape.ShapeType() != TopAbs_VERTEX)
      {
        myTransient->ChangeName().Orientation(aOldShape.Orientation());
      }
    }
  }
}
