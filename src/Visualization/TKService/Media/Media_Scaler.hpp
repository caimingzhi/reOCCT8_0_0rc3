#pragma once

#include <Media_Frame.hpp>

#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>
#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>

struct SwsContext;

//! SwsContext wrapper - tool performing image scaling and pixel format conversion.
class Media_Scaler : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_Scaler, Standard_Transient)
public:
  //! Empty constructor.
  Standard_EXPORT Media_Scaler();

  //! Destructor.
  Standard_EXPORT ~Media_Scaler() override;

  //! sws_freeContext() wrapper.
  Standard_EXPORT void Release();

  //! sws_getContext() wrapper - creates conversion context.
  //! @param theSrcDims   dimensions of input frame
  //! @param theSrcFormat pixel format (AVPixelFormat) of input frame
  //! @param theResDims   dimensions of destination frame
  //! @param theResFormat pixel format (AVPixelFormat) of destination frame
  Standard_EXPORT bool Init(const NCollection_Vec2<int>& theSrcDims,
                            int                          theSrcFormat,
                            const NCollection_Vec2<int>& theResDims,
                            int                          theResFormat);

  //! Convert one frame to another.
  Standard_EXPORT bool Convert(const occ::handle<Media_Frame>& theSrc,
                               const occ::handle<Media_Frame>& theRes);

  //! Return TRUE if context was initialized.
  bool IsValid() const { return mySwsContext != nullptr; }

protected:
  SwsContext*           mySwsContext; //!< conversion context
  NCollection_Vec2<int> mySrcDims;    //!< dimensions of input frame
  int                   mySrcFormat;  //!< pixel format (AVPixelFormat) of input frame
  NCollection_Vec2<int> myResDims;    //!< dimensions of destination frame
  int                   myResFormat;  //!< pixel format (AVPixelFormat) of destination frame
};
