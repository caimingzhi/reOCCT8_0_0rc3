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
    void Read(StdObjMgt_ReadData&) override {}

    void Write(StdObjMgt_WriteData&) const override {}

    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent&) const override {}

    const char* PName() const override;

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
