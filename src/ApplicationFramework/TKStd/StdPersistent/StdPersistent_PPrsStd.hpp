#pragma once

#include <StdObjMgt_Attribute.hpp>
#include <StdLPersistent_HString.hpp>

#include <TDataXtd_Presentation.hpp>

class StdPersistent_PPrsStd
{
public:
  class AISPresentation : public StdObjMgt_Attribute<TDataXtd_Presentation>
  {
  public:
    //! Read persistent data from a file.
    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      theReadData >> myIsDisplayed >> myDriverGUID >> myTransparency >> myColor >> myMaterial
        >> myWidth;
    }

    //! Write persistent data to a file.
    inline void Write(StdObjMgt_WriteData& theWriteData) const
    {
      theWriteData << myIsDisplayed << myDriverGUID << myTransparency << myColor << myMaterial
                   << myWidth;
    }

    //! Gets persistent child objects
    inline void PChildren(StdObjMgt_Persistent::SequenceOfPersistent& theChildren) const
    {
      theChildren.Append(myDriverGUID);
    }

    //! Returns persistent type name
    inline const char* PName() const { return "PPrsStd_AISPresentation"; }

    //! Import transient attribute from the persistent data.
    void Import(const occ::handle<TDataXtd_Presentation>& theAttribute) const;

  private:
    bool                              myIsDisplayed;
    occ::handle<StdObjMgt_Persistent> myDriverGUID;
    double                            myTransparency;
    int                               myColor;
    int                               myMaterial;
    double                            myWidth;
  };

  class AISPresentation_1 : public AISPresentation
  {
  public:
    //! Read persistent data from a file.
    inline void Read(StdObjMgt_ReadData& theReadData)
    {
      AISPresentation::Read(theReadData);
      theReadData >> myMode;
    }

    //! Write persistent data to a file.
    inline void Write(StdObjMgt_WriteData& theWriteData)
    {
      AISPresentation::Write(theWriteData);
      theWriteData << myMode;
    }

    //! Returns persistent type name
    inline const char* PName() const { return "PPrsStd_AISPresentation_1"; }

    //! Import transient attribute from the persistent data.
    void Import(const occ::handle<TDataXtd_Presentation>& theAttribute) const;

  private:
    int myMode;
  };
};
