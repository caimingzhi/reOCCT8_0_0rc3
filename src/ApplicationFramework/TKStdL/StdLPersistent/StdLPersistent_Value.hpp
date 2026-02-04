#pragma once


#include <StdObjMgt_Attribute.hpp>
#include <StdLPersistent_HString.hpp>

#include <TDataStd_Integer.hpp>
#include <TDF_TagSource.hpp>
#include <TDF_Reference.hpp>
#include <TDataStd_UAttribute.hpp>
#include <TDataStd_Name.hpp>
#include <TDataStd_Comment.hpp>
#include <TDataStd_AsciiString.hpp>

class StdLPersistent_Value
{
  template <class AttribClass>
  class integer : public StdObjMgt_Attribute<AttribClass>::SingleInt
  {
  public:
    //! Import transient attribute from the persistent data.
    Standard_EXPORT void ImportAttribute() override;
  };

  template <class AttribClass, class HStringClass = StdLPersistent_HString::Extended>
  class string : public StdObjMgt_Attribute<AttribClass>::SingleRef
  {
  public:
    //! Import transient attribute from the persistent data.
    Standard_EXPORT void ImportAttribute() override;
  };

public:
  class TagSource : public integer<TDF_TagSource>
  {
  public:
    const char* PName() const override { return "PDF_TagSource"; }
  };

  class Reference : public string<TDF_Reference>
  {
  public:
    const char* PName() const override { return "PDF_Reference"; }
  };

  class Comment : public string<TDataStd_Comment>
  {
  public:
    const char* PName() const override { return "PDF_Comment"; }
  };

  class UAttribute : public string<TDataStd_UAttribute>
  {
  public:
    //! Create an empty transient attribute
    Standard_EXPORT occ::handle<TDF_Attribute> CreateAttribute() override;

    const char* PName() const override { return "PDataStd_UAttribute"; }
  };

  class Integer : public integer<TDataStd_Integer>
  {
  public:
    //! Create an empty transient attribute
    Standard_EXPORT occ::handle<TDF_Attribute> CreateAttribute() override;

    const char* PName() const override { return "PDataStd_Integer"; }
  };

  class Name : public string<TDataStd_Name>
  {
  public:
    //! Create an empty transient attribute
    Standard_EXPORT occ::handle<TDF_Attribute> CreateAttribute() override;

    const char* PName() const override { return "PDataStd_Name"; }
  };

  class AsciiString : public string<TDataStd_AsciiString, StdLPersistent_HString::Ascii>
  {
  public:
    //! Create an empty transient attribute
    Standard_EXPORT occ::handle<TDF_Attribute> CreateAttribute() override;

    const char* PName() const override { return "PDataStd_AsciiString"; }
  };
};

template <>
template <>
inline const char* StdObjMgt_Attribute<TDF_TagSource>::Simple<int>::PName() const
{
  return "PDF_TagSource";
}

template <>
template <>
inline const char* StdObjMgt_Attribute<TDF_Reference>::Simple<
  occ::handle<StdObjMgt_Persistent>>::PName() const
{
  return "PDF_Reference";
}

template <>
template <>
inline const char* StdObjMgt_Attribute<TDataStd_Comment>::Simple<
  occ::handle<StdObjMgt_Persistent>>::PName() const
{
  return "PDataStd_Comment";
}

