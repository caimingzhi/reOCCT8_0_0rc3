// Copyright (c) 1999-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

#include <XCAFDimTolObjects_Tool.hpp>
#include <TDF_ChildIterator.hpp>
#include <XCAFDoc_DimTolTool.hpp>
#include <XCAFDoc_Dimension.hpp>
#include <XCAFDoc_GeomTolerance.hpp>
#include <XCAFDoc_ShapeTool.hpp>
#include <XCAFDoc_Datum.hpp>
#include <TDF_Label.hpp>
#include <NCollection_Sequence.hpp>
#include <XCAFDoc_DocumentTool.hpp>
#include <TDocStd_Document.hpp>
#include <NCollection_DataMap.hpp>
#include <XCAFDimTolObjects_GeomToleranceObject.hpp>
#include <XCAFDimTolObjects_DatumObject.hpp>
class XCAFDimTolObjects_GeomToleranceObject;

class XCAFDimTolObjects_DimensionObject;
class XCAFDimTolObjects_DatumObject;

//=================================================================================================

XCAFDimTolObjects_Tool::XCAFDimTolObjects_Tool(const occ::handle<TDocStd_Document>& theDoc)
{
  myDimTolTool = XCAFDoc_DocumentTool::DimTolTool(theDoc->Main());
}

//=================================================================================================

void XCAFDimTolObjects_Tool::GetDimensions(
  NCollection_Sequence<occ::handle<XCAFDimTolObjects_DimensionObject>>& theDimensionObjectSequence)
  const
{
  theDimensionObjectSequence.Clear();
  TDF_ChildIterator aChildIterator(myDimTolTool->Label());
  for (; aChildIterator.More(); aChildIterator.Next())
  {
    TDF_Label                      aL = aChildIterator.Value();
    occ::handle<XCAFDoc_Dimension> aDimension;
    if (aL.FindAttribute(XCAFDoc_Dimension::GetID(), aDimension))
    {
      theDimensionObjectSequence.Append(aDimension->GetObject());
    }
  }
}

//=================================================================================================

void XCAFDimTolObjects_Tool::GetGeomTolerances(
  NCollection_Sequence<occ::handle<XCAFDimTolObjects_GeomToleranceObject>>&
                                                                    theGeomToleranceObjectSequence,
  NCollection_Sequence<occ::handle<XCAFDimTolObjects_DatumObject>>& theDatumSequence,
  NCollection_DataMap<occ::handle<XCAFDimTolObjects_GeomToleranceObject>,
                      occ::handle<XCAFDimTolObjects_DatumObject>>&  theMap) const
{
  theGeomToleranceObjectSequence.Clear();
  TDF_ChildIterator aChildIterator(myDimTolTool->Label());
  for (; aChildIterator.More(); aChildIterator.Next())
  {
    TDF_Label                          aL = aChildIterator.Value();
    occ::handle<XCAFDoc_GeomTolerance> aGeomTolerance;
    if (aL.FindAttribute(XCAFDoc_GeomTolerance::GetID(), aGeomTolerance))
    {
      theGeomToleranceObjectSequence.Append(aGeomTolerance->GetObject());
      NCollection_Sequence<TDF_Label> aSeq;
      if (myDimTolTool->GetDatumOfTolerLabels(aGeomTolerance->Label(), aSeq))
      {
        for (int i = 1; i <= aSeq.Length(); i++)
        {
          occ::handle<XCAFDoc_Datum> aDatum;
          if (aSeq.Value(i).FindAttribute(XCAFDoc_Datum::GetID(), aDatum))
          {
            theDatumSequence.Append(aDatum->GetObject());
            theMap.Bind(theGeomToleranceObjectSequence.Last(), theDatumSequence.Last());
          }
        }
      }
    }
  }
}

//=================================================================================================

bool XCAFDimTolObjects_Tool::GetRefDimensions(
  const TopoDS_Shape&                                                   theShape,
  NCollection_Sequence<occ::handle<XCAFDimTolObjects_DimensionObject>>& theDimensionObjectSequence)
  const
{
  theDimensionObjectSequence.Clear();
  TDF_Label aShapeL;
  myDimTolTool->ShapeTool()->Search(theShape, aShapeL);
  if (!aShapeL.IsNull())
  {
    NCollection_Sequence<TDF_Label> aSeq;
    if (myDimTolTool->GetRefDimensionLabels(aShapeL, aSeq))
    {
      for (int i = 1; i <= aSeq.Length(); i++)
      {
        occ::handle<XCAFDoc_Dimension> aDimension;
        if (aSeq.Value(i).FindAttribute(XCAFDoc_Dimension::GetID(), aDimension))
          theDimensionObjectSequence.Append(aDimension->GetObject());
      }
      return true;
    }
  }
  return false;
}

//=================================================================================================

bool XCAFDimTolObjects_Tool::GetRefGeomTolerances(
  const TopoDS_Shape& theShape,
  NCollection_Sequence<occ::handle<XCAFDimTolObjects_GeomToleranceObject>>&
                                                                    theGeomToleranceObjectSequence,
  NCollection_Sequence<occ::handle<XCAFDimTolObjects_DatumObject>>& theDatumSequence,
  NCollection_DataMap<occ::handle<XCAFDimTolObjects_GeomToleranceObject>,
                      occ::handle<XCAFDimTolObjects_DatumObject>>&  theMap) const
{
  theGeomToleranceObjectSequence.Clear();
  TDF_Label aShapeL;
  myDimTolTool->ShapeTool()->Search(theShape, aShapeL);
  if (!aShapeL.IsNull())
  {
    NCollection_Sequence<TDF_Label> aSeq;
    if (myDimTolTool->GetRefGeomToleranceLabels(aShapeL, aSeq))
    {
      for (int i = 1; i <= aSeq.Length(); i++)
      {
        occ::handle<XCAFDoc_GeomTolerance> aGeomTolerance;
        if (aSeq.Value(i).FindAttribute(XCAFDoc_GeomTolerance::GetID(), aGeomTolerance))
        {
          theGeomToleranceObjectSequence.Append(aGeomTolerance->GetObject());
          NCollection_Sequence<TDF_Label> aLocalSeq;
          if (myDimTolTool->GetDatumOfTolerLabels(aGeomTolerance->Label(), aLocalSeq))
          {
            for (int j = 1; j <= aLocalSeq.Length(); j++)
            {
              occ::handle<XCAFDoc_Datum> aDatum;
              if (aLocalSeq.Value(j).FindAttribute(XCAFDoc_Datum::GetID(), aDatum))
              {
                theDatumSequence.Append(aDatum->GetObject());
                theMap.Bind(theGeomToleranceObjectSequence.Last(), theDatumSequence.Last());
              }
            }
          }
        }
      }
      return true;
    }
  }
  return false;
}

//=================================================================================================

bool XCAFDimTolObjects_Tool::GetRefDatum(
  const TopoDS_Shape&                         theShape,
  occ::handle<XCAFDimTolObjects_DatumObject>& theDatumObject) const
{
  TDF_Label aShapeL;
  myDimTolTool->ShapeTool()->Search(theShape, aShapeL);
  if (!aShapeL.IsNull())
  {
    NCollection_Sequence<TDF_Label> aDatumL;
    if (myDimTolTool->GetRefDatumLabel(aShapeL, aDatumL))
    {
      occ::handle<XCAFDoc_Datum> aDatum;
      if (aDatumL.First().FindAttribute(XCAFDoc_Datum::GetID(), aDatum))
      {
        theDatumObject = aDatum->GetObject();
        return true;
      }
    }
  }
  return false;
}
