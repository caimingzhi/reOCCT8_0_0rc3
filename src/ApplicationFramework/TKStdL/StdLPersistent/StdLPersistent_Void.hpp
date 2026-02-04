#pragma once


#include <StdObjMgt_Attribute.hpp>

#include <TDataStd_Directory.hpp>
#include <TDataStd_Tick.hpp>
#include <TDataStd_NoteBook.hpp>

class StdLPersistent_Void
{
protected:
  template <class AttribClass>
  class instance : public StdObjMgt_Attribute<AttribClass>::Static
  {
  public:
    //! Read persistent data from a file.
    void Read(StdObjMgt_ReadData&) override {}

    //! Write persistent data to a file.
    void Write(StdObjMgt_WriteData&) const override {}

    //! Gets persistent child objects
    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const override {}

    //! Returns persistent type name
    const char* PName() const override;

    //! Import transient attribute from the persistent data
    void ImportAttribute() override {}
  };

public:
  typedef instance<TDataStd_Directory> Directory;
  typedef instance<TDataStd_Tick>      Tick;
  typedef instance<TDataStd_NoteBook>  NoteBook;
};

template <>
inline const char* StdLPersistent_Void::instance<TDataStd_Directory>::PName() const
{
  return "PDataStd_Directory";
}

template <>
inline const char* StdLPersistent_Void::instance<TDataStd_Tick>::PName() const
{
  return "PDataStd_Tick";
}

template <>
inline const char* StdLPersistent_Void::instance<TDataStd_NoteBook>::PName() const
{
  return "PDataStd_Notebook";
}

