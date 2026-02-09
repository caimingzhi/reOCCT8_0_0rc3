

#include <StdPersistent.hpp>
#include <StdObjMgt_MapOfInstantiators.hpp>

#include <StdPersistent_TopLoc.hpp>
#include <StdPersistent_Naming.hpp>
#include <StdPersistent_HArray1.hpp>
#include <StdLPersistent_HArray1.hpp>
#include <StdPersistent_DataXtd.hpp>
#include <StdPersistent_DataXtd_Constraint.hpp>
#include <StdPersistent_DataXtd_PatternStd.hpp>
#include <StdPersistent_PPrsStd.hpp>

void StdPersistent::BindTypes(StdObjMgt_MapOfInstantiators& theMap)
{

  theMap.Bind<StdPersistent_TopLoc::Datum3D>("PTopLoc_Datum3D");
  theMap.Bind<StdPersistent_TopLoc::ItemLocation>("PTopLoc_ItemLocation");
  theMap.Bind<StdPersistent_TopoDS::TShape>("PTopoDS_TShape1");
  theMap.Bind<StdPersistent_HArray1::Shape1>("PTopoDS_HArray1OfShape1");
  theMap.Bind<StdPersistent_Naming::Name>("PNaming_Name");
  theMap.Bind<StdPersistent_Naming::Name_1>("PNaming_Name_1");
  theMap.Bind<StdPersistent_Naming::Name_2>("PNaming_Name_2");

  theMap.Bind<StdLPersistent_HArray1::Persistent>("PNaming_HArray1OfNamedShape");

  theMap.Bind<StdPersistent_Naming::NamedShape>("PNaming_NamedShape");
  theMap.Bind<StdPersistent_Naming::Naming>("PNaming_Naming");
  theMap.Bind<StdPersistent_Naming::Naming_1>("PNaming_Naming_1");
  theMap.Bind<StdPersistent_Naming::Naming_2>("PNaming_Naming_2");

  theMap.Bind<StdPersistent_DataXtd::Shape>("PDataXtd_Shape");
  theMap.Bind<StdPersistent_DataXtd::Point>("PDataXtd_Point");
  theMap.Bind<StdPersistent_DataXtd::Axis>("PDataXtd_Axis");
  theMap.Bind<StdPersistent_DataXtd::Plane>("PDataXtd_Plane");
  theMap.Bind<StdPersistent_DataXtd::Placement>("PDataXtd_Placement");
  theMap.Bind<StdPersistent_DataXtd::Geometry>("PDataXtd_Geometry");
  theMap.Bind<StdPersistent_DataXtd::Position>("PDataXtd_Position");
  theMap.Bind<StdPersistent_DataXtd_Constraint>("PDataXtd_Constraint");
  theMap.Bind<StdPersistent_DataXtd_PatternStd>("PDataXtd_PatternStd");

  theMap.Bind<StdPersistent_PPrsStd::AISPresentation>("PPrsStd_AISPresentation");

  theMap.Bind<StdPersistent_PPrsStd::AISPresentation_1>("PPrsStd_AISPresentation_1");
}
