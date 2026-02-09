

#include <Image_VideoRecorder.hpp>
#include <Image_PixMap.hpp>

#include <gtest/gtest.h>

class Image_VideoRecorderTest : public ::testing::Test
{
protected:
  void SetUp() override { myRecorder = new Image_VideoRecorder(); }

  void TearDown() override
  {
    if (!myRecorder.IsNull())
    {
      myRecorder->Close();
    }
  }

  occ::handle<Image_VideoRecorder> myRecorder;
};

TEST_F(Image_VideoRecorderTest, DefaultConstructor)
{
  EXPECT_FALSE(myRecorder.IsNull());
  EXPECT_EQ(0, myRecorder->FrameCount());
}

TEST_F(Image_VideoRecorderTest, VideoParamsStructure)
{
  Image_VideoParams params;

  EXPECT_EQ(0, params.Width);
  EXPECT_EQ(0, params.Height);
  EXPECT_EQ(0, params.FpsNum);
  EXPECT_EQ(1, params.FpsDen);
  EXPECT_TRUE(params.Format.IsEmpty());
  EXPECT_TRUE(params.VideoCodec.IsEmpty());
  EXPECT_TRUE(params.PixelFormat.IsEmpty());

  params.SetFramerate(30);
  EXPECT_EQ(30, params.FpsNum);
  EXPECT_EQ(1, params.FpsDen);

  params.SetFramerate(25, 2);
  EXPECT_EQ(25, params.FpsNum);
  EXPECT_EQ(2, params.FpsDen);
}

TEST_F(Image_VideoRecorderTest, OpenVideoFile)
{
#ifdef HAVE_FFMPEG
  Image_VideoParams params;
  params.Width  = 320;
  params.Height = 240;
  params.SetFramerate(15);
  params.Format      = "avi";
  params.VideoCodec  = "mpeg4";
  params.PixelFormat = "yuv420p";

  bool isOpened = myRecorder->Open("test_video.avi", params);
  EXPECT_TRUE(isOpened);

  if (isOpened)
  {

    Image_PixMap& frame = myRecorder->ChangeFrame();
    EXPECT_EQ(params.Width, frame.Width());
    EXPECT_EQ(params.Height, frame.Height());
    EXPECT_EQ(Image_Format_RGBA, frame.Format());

    myRecorder->Close();
  }
#endif
}

TEST_F(Image_VideoRecorderTest, InvalidParameters)
{
#ifdef HAVE_FFMPEG
  Image_VideoParams params;

  bool isOpened = myRecorder->Open("invalid_test.avi", params);
  EXPECT_FALSE(isOpened);
#endif
}

TEST_F(Image_VideoRecorderTest, WriteFrames)
{
#ifdef HAVE_FFMPEG
  Image_VideoParams params;
  params.Width  = 160;
  params.Height = 120;
  params.SetFramerate(10);
  params.Format      = "avi";
  params.VideoCodec  = "mpeg4";
  params.PixelFormat = "yuv420p";

  bool isOpened = myRecorder->Open("test_frames.avi", params);

  if (isOpened)
  {

    Image_PixMap& frame = myRecorder->ChangeFrame();

    for (int y = 0; y < params.Height; ++y)
    {
      for (int x = 0; x < params.Width; ++x)
      {
        uint8_t* pixel = frame.ChangeData() + (y * frame.SizeRowBytes()) + (x * 4);
        pixel[0]       = (uint8_t)(255 * x / params.Width);
        pixel[1]       = 0;
        pixel[2]       = (uint8_t)(255 * y / params.Height);
        pixel[3]       = 255;
      }
    }

    EXPECT_EQ(0, myRecorder->FrameCount());

    EXPECT_TRUE(myRecorder->PushFrame());
    EXPECT_EQ(1, myRecorder->FrameCount());

    EXPECT_TRUE(myRecorder->PushFrame());
    EXPECT_EQ(2, myRecorder->FrameCount());

    EXPECT_TRUE(myRecorder->PushFrame());
    EXPECT_EQ(3, myRecorder->FrameCount());

    myRecorder->Close();
  }
#endif
}

TEST_F(Image_VideoRecorderTest, CloseWithoutOpen)
{

  myRecorder->Close();
  EXPECT_EQ(0, myRecorder->FrameCount());
}
