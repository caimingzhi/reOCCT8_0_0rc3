

#include <OSD_Path.hpp>
#include <OSD_Process.hpp>
#include <TCollection_AsciiString.hpp>

#include <gtest/gtest.h>

class OSD_PathTest : public testing::Test
{
protected:
  void SetUp() override {}

  void TearDown() override {}
};

TEST_F(OSD_PathTest, DosAbsolutePaths)
{

  EXPECT_TRUE(OSD_Path::IsAbsolutePath("c:\\folder\\file.png"));
  EXPECT_TRUE(OSD_Path::IsDosPath("c:\\folder\\file.png"));
  EXPECT_FALSE(OSD_Path::IsRelativePath("c:\\folder\\file.png"));
  EXPECT_FALSE(OSD_Path::IsUnixPath("c:\\folder\\file.png"));
  EXPECT_FALSE(OSD_Path::IsUncPath("c:\\folder\\file.png"));

  EXPECT_TRUE(OSD_Path::IsAbsolutePath("D:\\"));
  EXPECT_TRUE(OSD_Path::IsDosPath("D:\\"));

  EXPECT_TRUE(OSD_Path::IsAbsolutePath("c:\\file.png"));
  EXPECT_TRUE(OSD_Path::IsDosPath("c:\\file.png"));
}

TEST_F(OSD_PathTest, UncPaths)
{

  EXPECT_TRUE(OSD_Path::IsAbsolutePath("\\\\share\\file.pdf"));
  EXPECT_TRUE(OSD_Path::IsUncPath("\\\\share\\file.pdf"));
  EXPECT_FALSE(OSD_Path::IsDosPath("\\\\share\\file.pdf"));
  EXPECT_FALSE(OSD_Path::IsUnixPath("\\\\share\\file.pdf"));
}

TEST_F(OSD_PathTest, NtExtendedPaths)
{

  EXPECT_TRUE(OSD_Path::IsAbsolutePath("\\\\?\\C:\\documents\\file.docx"));
  EXPECT_TRUE(OSD_Path::IsNtExtendedPath("\\\\?\\C:\\documents\\file.docx"));
  EXPECT_FALSE(OSD_Path::IsUncPath("\\\\?\\C:\\documents\\file.docx"));
}

TEST_F(OSD_PathTest, UncExtendedPaths)
{

  EXPECT_TRUE(OSD_Path::IsAbsolutePath("\\\\?\\UNC\\server\\share\\file.zip"));
  EXPECT_TRUE(OSD_Path::IsUncPath("\\\\?\\UNC\\server\\share\\file.zip"));
  EXPECT_TRUE(OSD_Path::IsNtExtendedPath("\\\\?\\UNC\\server\\share\\file.zip"));
  EXPECT_TRUE(OSD_Path::IsUncExtendedPath("\\\\?\\UNC\\server\\share\\file.zip"));
}

TEST_F(OSD_PathTest, RemoteProtocolPaths)
{

  EXPECT_TRUE(OSD_Path::IsAbsolutePath("https://www.server.org/file.gif"));
  EXPECT_TRUE(OSD_Path::IsRemoteProtocolPath("https://www.server.org/file.gif"));
  EXPECT_FALSE(OSD_Path::IsUnixPath("https://www.server.org/file.gif"));
  EXPECT_FALSE(OSD_Path::IsDosPath("https://www.server.org/file.gif"));

  EXPECT_TRUE(OSD_Path::IsAbsolutePath("ftp://ftp.server.com/file.dat"));
  EXPECT_TRUE(OSD_Path::IsRemoteProtocolPath("ftp://ftp.server.com/file.dat"));

  EXPECT_TRUE(OSD_Path::IsAbsolutePath("http://example.com/path"));
  EXPECT_TRUE(OSD_Path::IsRemoteProtocolPath("http://example.com/path"));
}

TEST_F(OSD_PathTest, ContentProtocolPaths)
{

  EXPECT_TRUE(OSD_Path::IsAbsolutePath("content://file.jpg"));
  EXPECT_TRUE(OSD_Path::IsRemoteProtocolPath("content://file.jpg"));
  EXPECT_TRUE(OSD_Path::IsContentProtocolPath("content://file.jpg"));
}

TEST_F(OSD_PathTest, UnixAbsolutePaths)
{

  EXPECT_TRUE(OSD_Path::IsAbsolutePath("/home/username/file.txt"));
  EXPECT_TRUE(OSD_Path::IsUnixPath("/home/username/file.txt"));
  EXPECT_FALSE(OSD_Path::IsRelativePath("/home/username/file.txt"));
  EXPECT_FALSE(OSD_Path::IsDosPath("/home/username/file.txt"));

  EXPECT_TRUE(OSD_Path::IsAbsolutePath("/"));
  EXPECT_TRUE(OSD_Path::IsUnixPath("/"));

  EXPECT_TRUE(OSD_Path::IsAbsolutePath("/boot.bin"));
  EXPECT_TRUE(OSD_Path::IsUnixPath("/boot.bin"));
}

TEST_F(OSD_PathTest, RelativePaths)
{

  EXPECT_TRUE(OSD_Path::IsRelativePath("./subfolder/../file.txt"));
  EXPECT_FALSE(OSD_Path::IsAbsolutePath("./subfolder/../file.txt"));

  EXPECT_TRUE(OSD_Path::IsRelativePath("../file.txt"));
  EXPECT_FALSE(OSD_Path::IsAbsolutePath("../file.txt"));

  EXPECT_TRUE(OSD_Path::IsRelativePath("."));
  EXPECT_FALSE(OSD_Path::IsAbsolutePath("."));

  EXPECT_TRUE(OSD_Path::IsRelativePath(".."));
  EXPECT_FALSE(OSD_Path::IsAbsolutePath(".."));

  EXPECT_TRUE(OSD_Path::IsRelativePath("folder/file.txt"));
  EXPECT_FALSE(OSD_Path::IsAbsolutePath("folder/file.txt"));

  EXPECT_TRUE(OSD_Path::IsRelativePath("file.txt"));
  EXPECT_FALSE(OSD_Path::IsAbsolutePath("file.txt"));
}

TEST_F(OSD_PathTest, FolderAndFileFromPath_UnixPaths)
{
  TCollection_AsciiString aFolder, aFileName;

  OSD_Path::FolderAndFileFromPath("/home/username/file.txt", aFolder, aFileName);
  EXPECT_STREQ("/home/username/", aFolder.ToCString());
  EXPECT_STREQ("file.txt", aFileName.ToCString());

  OSD_Path::FolderAndFileFromPath("/file.txt", aFolder, aFileName);
  EXPECT_STREQ("/", aFolder.ToCString());
  EXPECT_STREQ("file.txt", aFileName.ToCString());

  OSD_Path::FolderAndFileFromPath("/home/username/", aFolder, aFileName);
  EXPECT_STREQ("/home/username/", aFolder.ToCString());
  EXPECT_STREQ("", aFileName.ToCString());
}

TEST_F(OSD_PathTest, FolderAndFileFromPath_DosPaths)
{
  TCollection_AsciiString aFolder, aFileName;

  OSD_Path::FolderAndFileFromPath("C:\\Users\\John\\document.txt", aFolder, aFileName);
  EXPECT_STREQ("C:\\Users\\John\\", aFolder.ToCString());
  EXPECT_STREQ("document.txt", aFileName.ToCString());

  OSD_Path::FolderAndFileFromPath("C:\\file.txt", aFolder, aFileName);
  EXPECT_STREQ("C:\\", aFolder.ToCString());
  EXPECT_STREQ("file.txt", aFileName.ToCString());

  OSD_Path::FolderAndFileFromPath("C:\\Program Files\\", aFolder, aFileName);
  EXPECT_STREQ("C:\\Program Files\\", aFolder.ToCString());
  EXPECT_STREQ("", aFileName.ToCString());
}

TEST_F(OSD_PathTest, FolderAndFileFromPath_RelativePaths)
{
  TCollection_AsciiString aFolder, aFileName;

  OSD_Path::FolderAndFileFromPath("folder/subfolder/file.txt", aFolder, aFileName);
  EXPECT_STREQ("folder/subfolder/", aFolder.ToCString());
  EXPECT_STREQ("file.txt", aFileName.ToCString());

  OSD_Path::FolderAndFileFromPath("../folder/file.txt", aFolder, aFileName);
  EXPECT_STREQ("../folder/", aFolder.ToCString());
  EXPECT_STREQ("file.txt", aFileName.ToCString());

  OSD_Path::FolderAndFileFromPath("file.txt", aFolder, aFileName);
  EXPECT_STREQ("", aFolder.ToCString());
  EXPECT_STREQ("file.txt", aFileName.ToCString());
}

TEST_F(OSD_PathTest, FolderAndFileFromPath_ProtocolPaths)
{
  TCollection_AsciiString aFolder, aFileName;

  OSD_Path::FolderAndFileFromPath("https://www.server.org/folder/file.gif", aFolder, aFileName);
  EXPECT_STREQ("https://www.server.org/folder/", aFolder.ToCString());
  EXPECT_STREQ("file.gif", aFileName.ToCString());

  OSD_Path::FolderAndFileFromPath("content://path/file.jpg", aFolder, aFileName);
  EXPECT_STREQ("content://path/", aFolder.ToCString());
  EXPECT_STREQ("file.jpg", aFileName.ToCString());
}

TEST_F(OSD_PathTest, EdgeCases)
{
  TCollection_AsciiString aFolder, aFileName;

  OSD_Path::FolderAndFileFromPath("", aFolder, aFileName);
  EXPECT_STREQ("", aFolder.ToCString());
  EXPECT_STREQ("", aFileName.ToCString());

  OSD_Path::FolderAndFileFromPath("/", aFolder, aFileName);
  EXPECT_STREQ("/", aFolder.ToCString());
  EXPECT_STREQ("", aFileName.ToCString());

  OSD_Path::FolderAndFileFromPath("\\", aFolder, aFileName);
  EXPECT_STREQ("\\", aFolder.ToCString());
  EXPECT_STREQ("", aFileName.ToCString());

  OSD_Path::FolderAndFileFromPath("/home/username/foldername", aFolder, aFileName);
  EXPECT_STREQ("/home/username/", aFolder.ToCString());
  EXPECT_STREQ("foldername", aFileName.ToCString());
}

TEST_F(OSD_PathTest, MixedSeparators)
{
  TCollection_AsciiString aFolder, aFileName;

  OSD_Path::FolderAndFileFromPath("C:/Users/John\\Documents/file.txt", aFolder, aFileName);

  EXPECT_FALSE(aFolder.IsEmpty() || aFileName.IsEmpty());
}

TEST_F(OSD_PathTest, OCC310_TrekAndUpTrek)
{
  OSD_Path                aPath("/where/you/want/tmp/qwerty/tmp/");
  TCollection_AsciiString aTrek = aPath.Trek();

  EXPECT_STREQ("|where|you|want|tmp|qwerty|tmp|", aTrek.ToCString());

  aPath.UpTrek();
  aTrek = aPath.Trek();

  EXPECT_STREQ("|where|you|want|tmp|qwerty|", aTrek.ToCString());
}

TEST_F(OSD_PathTest, OCC309_CurrentDirectoryAndUpTrek)
{
  OSD_Process             aProcess;
  OSD_Path                aPath = aProcess.CurrentDirectory();
  TCollection_AsciiString aSystemName1;
  aPath.SystemName(aSystemName1);
  EXPECT_FALSE(aSystemName1.IsEmpty());

  aPath.UpTrek();
  TCollection_AsciiString aSystemName2;
  aPath.SystemName(aSystemName2);
  EXPECT_FALSE(aSystemName2.IsEmpty());
  EXPECT_NE(aSystemName1, aSystemName2);
  EXPECT_LT(aSystemName2.Length(), aSystemName1.Length());
}
