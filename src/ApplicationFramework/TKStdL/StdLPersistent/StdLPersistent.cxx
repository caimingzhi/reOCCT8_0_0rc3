

#include <StdLPersistent.hpp>
#include <StdObjMgt_MapOfInstantiators.hpp>

#include <StdLPersistent_Document.hpp>
#include <StdLPersistent_Data.hpp>
#include <StdLPersistent_HArray1.hpp>
#include <StdLPersistent_Void.hpp>
#include <StdLPersistent_Real.hpp>
#include <StdLPersistent_Value.hpp>
#include <StdLPersistent_Collection.hpp>
#include <StdLPersistent_Dependency.hpp>
#include <StdLPersistent_Variable.hpp>
#include <StdLPersistent_XLink.hpp>
#include <StdLPersistent_Function.hpp>
#include <StdLPersistent_TreeNode.hpp>
#include <StdLPersistent_NamedData.hpp>

void StdLPersistent::BindTypes(StdObjMgt_MapOfInstantiators& theMap)
{

  theMap.Bind<StdLPersistent_Document>("PDocStd_Document");
  theMap.Bind<StdLPersistent_Data>("PDF_Data");

  theMap.Bind<StdLPersistent_HString::Ascii>("PCollection_HAsciiString");
  theMap.Bind<StdLPersistent_HString::Extended>("PCollection_HExtendedString");

  theMap.Bind<StdLPersistent_HArray1::Integer>("PColStd_HArray1OfInteger");
  theMap.Bind<StdLPersistent_HArray1::Real>("PColStd_HArray1OfReal");
  theMap.Bind<StdLPersistent_HArray1::Persistent>("PColStd_HArray1OfExtendedString");
  theMap.Bind<StdLPersistent_HArray1::Persistent>("PDF_HAttributeArray1");
  theMap.Bind<StdLPersistent_HArray1::Persistent>("PDataStd_HArray1OfHAsciiString");
  theMap.Bind<StdLPersistent_HArray1::Persistent>("PDataStd_HArray1OfHArray1OfInteger");
  theMap.Bind<StdLPersistent_HArray1::Persistent>("PDataStd_HArray1OfHArray1OfReal");
  theMap.Bind<StdLPersistent_HArray1::Byte>("PDataStd_HArray1OfByte");

  theMap.Bind<StdLPersistent_HArray2::Integer>("PColStd_HArray2OfInteger");

  theMap.Bind<StdLPersistent_Void::Directory>("PDataStd_Directory");
  theMap.Bind<StdLPersistent_Void::Tick>("PDataStd_Tick");
  theMap.Bind<StdLPersistent_Void::NoteBook>("PDataStd_NoteBook");

  theMap.Bind<StdLPersistent_Value::Integer>("PDataStd_Integer");
  theMap.Bind<StdLPersistent_Value::TagSource>("PDF_TagSource");
  theMap.Bind<StdLPersistent_Value::Reference>("PDF_Reference");
  theMap.Bind<StdLPersistent_Value::UAttribute>("PDataStd_UAttribute");

  theMap.Bind<StdLPersistent_Value::Name>("PDataStd_Name");
  theMap.Bind<StdLPersistent_Value::Comment>("PDataStd_Comment");
  theMap.Bind<StdLPersistent_Value::AsciiString>("PDataStd_AsciiString");

  theMap.Bind<StdLPersistent_Collection::IntegerArray>("PDataStd_IntegerArray");
  theMap.Bind<StdLPersistent_Collection::RealArray>("PDataStd_RealArray");
  theMap.Bind<StdLPersistent_Collection::ByteArray>("PDataStd_ByteArray");
  theMap.Bind<StdLPersistent_Collection::ExtStringArray>("PDataStd_ExtStringArray");
  theMap.Bind<StdLPersistent_Collection::BooleanArray>("PDataStd_BooleanArray");
  theMap.Bind<StdLPersistent_Collection::ReferenceArray>("PDataStd_ReferenceArray");

  theMap.Bind<StdLPersistent_Collection::IntegerArray_1>("PDataStd_IntegerArray_1");
  theMap.Bind<StdLPersistent_Collection::RealArray_1>("PDataStd_RealArray_1");
  theMap.Bind<StdLPersistent_Collection::ByteArray_1>("PDataStd_ByteArray_1");
  theMap.Bind<StdLPersistent_Collection::ExtStringArray_1>("PDataStd_ExtStringArray_1");

  theMap.Bind<StdLPersistent_Collection::IntegerList>("PDataStd_IntegerList");
  theMap.Bind<StdLPersistent_Collection::RealList>("PDataStd_RealList");
  theMap.Bind<StdLPersistent_Collection::BooleanList>("PDataStd_BooleanList");
  theMap.Bind<StdLPersistent_Collection::ExtStringList>("PDataStd_ExtStringList");
  theMap.Bind<StdLPersistent_Collection::ReferenceList>("PDataStd_ReferenceList");

  theMap.Bind<StdLPersistent_Collection::IntPackedMap>("PDataStd_IntPackedMap");
  theMap.Bind<StdLPersistent_Collection::IntPackedMap_1>("PDataStd_IntPackedMap_1");

  theMap.Bind<StdLPersistent_Real>("PDataStd_Real");
  theMap.Bind<StdLPersistent_Dependency::Expression>("PDataStd_Expression");
  theMap.Bind<StdLPersistent_Dependency::Relation>("PDataStd_Relation");
  theMap.Bind<StdLPersistent_Variable>("PDataStd_Variable");
  theMap.Bind<StdLPersistent_XLink>("PDocStd_XLink");
  theMap.Bind<StdLPersistent_Function>("PFunction_Function");
  theMap.Bind<StdLPersistent_TreeNode>("PDataStd_TreeNode");
  theMap.Bind<StdLPersistent_NamedData>("PDataStd_NamedData");
}
