#include <XCAFDoc_View.hpp>

#include <TDataStd_AsciiString.hpp>
#include <TDataStd_Integer.hpp>
#include <TDataStd_Real.hpp>
#include <TDataXtd_Axis.hpp>
#include <TDataXtd_Geometry.hpp>
#include <TDataXtd_Point.hpp>
#include <TDF_ChildIterator.hpp>
#include <XCAFDoc.hpp>
#include <XCAFView_Object.hpp>

IMPLEMENT_DERIVED_ATTRIBUTE(XCAFDoc_View, TDataStd_GenericEmpty)

enum ChildLab
{
  ChildLab_Name = 1,
  ChildLab_Type,
  ChildLab_ProjectionPoint,
  ChildLab_ViewDirection,
  ChildLab_UpDirection,
  ChildLab_ZoomFactor,
  ChildLab_WindowHorizontalSize,
  ChildLab_WindowVerticalSize,
  ChildLab_FrontPlaneDistance,
  ChildLab_BackPlaneDistance,
  ChildLab_ViewVolumeSidesClipping,
  ChildLab_ClippingExpression,
  ChildLab_GDTPoints
};

XCAFDoc_View::XCAFDoc_View() = default;

const Standard_GUID& XCAFDoc_View::GetID()
{
  static Standard_GUID ViewID("efd213e8-6dfd-11d4-b9c8-0060b0ee281b");
  return ViewID;
}

occ::handle<XCAFDoc_View> XCAFDoc_View::Set(const TDF_Label& theLabel)
{
  occ::handle<XCAFDoc_View> A;
  if (!theLabel.FindAttribute(XCAFDoc_View::GetID(), A))
  {
    A = new XCAFDoc_View();
    theLabel.AddAttribute(A);
  }
  return A;
}

void XCAFDoc_View::SetObject(const occ::handle<XCAFView_Object>& theObject)
{
  Backup();

  TDF_ChildIterator anIter(Label());
  for (; anIter.More(); anIter.Next())
  {
    anIter.Value().ForgetAllAttributes();
  }

  TDataStd_AsciiString::Set(Label().FindChild(ChildLab_Name), theObject->Name()->String());

  TDataStd_Integer::Set(Label().FindChild(ChildLab_Type), theObject->Type());

  TDataXtd_Point::Set(Label().FindChild(ChildLab_ProjectionPoint), theObject->ProjectionPoint());

  gp_Ax1 aViewDir(gp_Pnt(), theObject->ViewDirection());
  TDataXtd_Axis::Set(Label().FindChild(ChildLab_ViewDirection), aViewDir);

  gp_Ax1 anUpDir(gp_Pnt(), theObject->UpDirection());
  TDataXtd_Axis::Set(Label().FindChild(ChildLab_UpDirection), anUpDir);

  TDataStd_Real::Set(Label().FindChild(ChildLab_ZoomFactor), theObject->ZoomFactor());

  TDataStd_Real::Set(Label().FindChild(ChildLab_WindowHorizontalSize),
                     theObject->WindowHorizontalSize());

  TDataStd_Real::Set(Label().FindChild(ChildLab_WindowVerticalSize),
                     theObject->WindowVerticalSize());

  if (theObject->HasFrontPlaneClipping())
  {
    TDataStd_Real::Set(Label().FindChild(ChildLab_FrontPlaneDistance),
                       theObject->FrontPlaneDistance());
  }

  if (theObject->HasBackPlaneClipping())
  {
    TDataStd_Real::Set(Label().FindChild(ChildLab_BackPlaneDistance),
                       theObject->BackPlaneDistance());
  }

  int aValue = theObject->HasViewVolumeSidesClipping() ? 1 : 0;
  TDataStd_Integer::Set(Label().FindChild(ChildLab_ViewVolumeSidesClipping), aValue);

  if (!theObject->ClippingExpression().IsNull())
    TDataStd_AsciiString::Set(Label().FindChild(ChildLab_ClippingExpression),
                              theObject->ClippingExpression()->String());

  if (theObject->HasGDTPoints())
  {
    TDF_Label aPointsLabel = Label().FindChild(ChildLab_GDTPoints);
    for (int i = 1; i <= theObject->NbGDTPoints(); i++)
    {
      TDataXtd_Point::Set(aPointsLabel.FindChild(i), theObject->GDTPoint(i));
    }
  }
}

occ::handle<XCAFView_Object> XCAFDoc_View::GetObject() const
{
  occ::handle<XCAFView_Object> anObj = new XCAFView_Object();

  occ::handle<TDataStd_AsciiString> aName;
  if (Label().FindChild(ChildLab_Name).FindAttribute(TDataStd_AsciiString::GetID(), aName))
  {
    anObj->SetName(new TCollection_HAsciiString(aName->Get()));
  }

  occ::handle<TDataStd_Integer> aType;
  if (Label().FindChild(ChildLab_Type).FindAttribute(TDataStd_Integer::GetID(), aType))
  {
    anObj->SetType((XCAFView_ProjectionType)aType->Get());
  }

  occ::handle<TDataXtd_Point> aPointAttr;
  if (Label()
        .FindChild(ChildLab_ProjectionPoint)
        .FindAttribute(TDataXtd_Point::GetID(), aPointAttr))
  {
    gp_Pnt aPoint;
    TDataXtd_Geometry::Point(aPointAttr->Label(), aPoint);
    anObj->SetProjectionPoint(aPoint);
  }

  occ::handle<TDataXtd_Axis> aViewDirAttr;
  if (Label().FindChild(ChildLab_ViewDirection).FindAttribute(TDataXtd_Axis::GetID(), aViewDirAttr))
  {
    gp_Ax1 aDir;
    TDataXtd_Geometry::Axis(aViewDirAttr->Label(), aDir);
    anObj->SetViewDirection(aDir.Direction());
  }

  occ::handle<TDataXtd_Axis> anUpDirAttr;
  if (Label().FindChild(ChildLab_UpDirection).FindAttribute(TDataXtd_Axis::GetID(), anUpDirAttr))
  {
    gp_Ax1 aDir;
    TDataXtd_Geometry::Axis(anUpDirAttr->Label(), aDir);
    anObj->SetUpDirection(aDir.Direction());
  }

  occ::handle<TDataStd_Real> aZoomFactor;
  if (Label().FindChild(ChildLab_ZoomFactor).FindAttribute(TDataStd_Real::GetID(), aZoomFactor))
  {
    anObj->SetZoomFactor(aZoomFactor->Get());
  }

  occ::handle<TDataStd_Real> aWindowHorizontalSize;
  if (Label()
        .FindChild(ChildLab_WindowHorizontalSize)
        .FindAttribute(TDataStd_Real::GetID(), aWindowHorizontalSize))
  {
    anObj->SetWindowHorizontalSize(aWindowHorizontalSize->Get());
  }

  occ::handle<TDataStd_Real> aWindowVerticalSize;
  if (Label()
        .FindChild(ChildLab_WindowVerticalSize)
        .FindAttribute(TDataStd_Real::GetID(), aWindowVerticalSize))
  {
    anObj->SetWindowVerticalSize(aWindowVerticalSize->Get());
  }

  occ::handle<TDataStd_Real> aFrontPlaneDistance;
  if (Label()
        .FindChild(ChildLab_FrontPlaneDistance)
        .FindAttribute(TDataStd_Real::GetID(), aFrontPlaneDistance))
  {
    anObj->SetFrontPlaneDistance(aFrontPlaneDistance->Get());
  }

  occ::handle<TDataStd_Real> aBackPlaneDistance;
  if (Label()
        .FindChild(ChildLab_BackPlaneDistance)
        .FindAttribute(TDataStd_Real::GetID(), aBackPlaneDistance))
  {
    anObj->SetBackPlaneDistance(aBackPlaneDistance->Get());
  }

  occ::handle<TDataStd_Integer> aViewVolumeSidesClipping;
  if (Label()
        .FindChild(ChildLab_ViewVolumeSidesClipping)
        .FindAttribute(TDataStd_Integer::GetID(), aViewVolumeSidesClipping))
  {
    bool aValue = (aViewVolumeSidesClipping->Get() == 1);
    anObj->SetViewVolumeSidesClipping(aValue);
  }

  occ::handle<TDataStd_AsciiString> aClippingExpression;
  if (Label()
        .FindChild(ChildLab_ClippingExpression)
        .FindAttribute(TDataStd_AsciiString::GetID(), aClippingExpression))
  {
    anObj->SetClippingExpression(new TCollection_HAsciiString(aClippingExpression->Get()));
  }

  if (!Label().FindChild(ChildLab_GDTPoints, false).IsNull())
  {
    TDF_Label aPointsLabel = Label().FindChild(ChildLab_GDTPoints);

    int                         aNbGDTPoints = 0;
    occ::handle<TDataXtd_Point> aGDTPointAttr;
    TDF_ChildIterator           anItrPnts(aPointsLabel, false);
    for (; anItrPnts.More(); anItrPnts.Next())
    {
      if (anItrPnts.Value().FindAttribute(TDataXtd_Point::GetID(), aGDTPointAttr))
        aNbGDTPoints++;
    }

    if (aNbGDTPoints)
    {
      anObj->CreateGDTPoints(aNbGDTPoints);
      const int aNbChildren = aPointsLabel.NbChildren();
      for (int aLabelIndex = 1, aPointIndex = 1; aLabelIndex <= aNbChildren; aLabelIndex++)
      {
        gp_Pnt aPoint;
        if (aPointsLabel.FindChild(aLabelIndex)
              .FindAttribute(TDataXtd_Point::GetID(), aGDTPointAttr))
        {
          TDataXtd_Geometry::Point(aGDTPointAttr->Label(), aPoint);
          anObj->SetGDTPoint(aPointIndex++, aPoint);
        }
      }
    }
  }

  return anObj;
}

const Standard_GUID& XCAFDoc_View::ID() const
{
  return GetID();
}
