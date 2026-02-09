#pragma once

#include <NCollection_Vec2.hpp>
#include <Standard_TypeDef.hpp>
#include <Image_PixMap.hpp>
#include <Standard_Transient.hpp>
#include <Standard_Type.hpp>

struct AVFrame;

class Media_Frame : public Standard_Transient
{
  DEFINE_STANDARD_RTTIEXT(Media_Frame, Standard_Transient)
public:
  Standard_EXPORT static Image_Format FormatFFmpeg2Occt(int theFormat);

  Standard_EXPORT static int FormatOcct2FFmpeg(Image_Format theFormat);

  Standard_EXPORT static void Swap(const occ::handle<Media_Frame>& theFrame1,
                                   const occ::handle<Media_Frame>& theFrame2);

public:
  Standard_EXPORT Media_Frame();

  Standard_EXPORT ~Media_Frame() override;

  Standard_EXPORT bool IsEmpty() const;

  Standard_EXPORT void Unref();

  NCollection_Vec2<int> Size() const { return NCollection_Vec2<int>(SizeX(), SizeY()); }

  Standard_EXPORT int SizeX() const;

  Standard_EXPORT int SizeY() const;

  Standard_EXPORT int Format() const;

  Standard_EXPORT bool IsFullRangeYUV() const;

  Standard_EXPORT uint8_t* Plane(int thePlaneId) const;

  Standard_EXPORT int LineSize(int thePlaneId) const;

  Standard_EXPORT int64_t BestEffortTimestamp() const;

  const AVFrame* Frame() const { return myFrame; }

  AVFrame* ChangeFrame() { return myFrame; }

  double Pts() const { return myFramePts; }

  void SetPts(double thePts) { myFramePts = thePts; }

  float PixelAspectRatio() const { return myPixelRatio; }

  void SetPixelAspectRatio(float theRatio) { myPixelRatio = theRatio; }

  bool IsLocked() const { return myIsLocked; }

  void SetLocked(bool theToLock) { myIsLocked = theToLock; }

public:
  Standard_EXPORT bool InitWrapper(const occ::handle<Image_PixMap>& thePixMap);

protected:
  AVFrame* myFrame;
  double   myFramePts;
  float    myPixelRatio;
  bool     myIsLocked;
};
