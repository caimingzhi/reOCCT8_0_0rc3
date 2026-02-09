

#include <StepData_StepWriter.hpp>
#include <TCollection_AsciiString.hpp>

#include <gtest/gtest.h>

TEST(StepData_StepWriterTest, CleanTextForSend_BasicEscaping)
{

  TCollection_AsciiString anInput1("text with 'single quotes'");
  TCollection_AsciiString aResult1 = StepData_StepWriter::CleanTextForSend(anInput1);
  EXPECT_STREQ(aResult1.ToCString(), "text with ''single quotes''");

  TCollection_AsciiString anInput2("path\\with\\backslashes");
  TCollection_AsciiString aResult2 = StepData_StepWriter::CleanTextForSend(anInput2);
  EXPECT_STREQ(aResult2.ToCString(), "path\\\\with\\\\backslashes");

  TCollection_AsciiString anInput3("line1\nline2");
  TCollection_AsciiString aResult3 = StepData_StepWriter::CleanTextForSend(anInput3);
  EXPECT_STREQ(aResult3.ToCString(), "line1\\N\\line2");

  TCollection_AsciiString anInput4("text\twith\ttabs");
  TCollection_AsciiString aResult4 = StepData_StepWriter::CleanTextForSend(anInput4);
  EXPECT_STREQ(aResult4.ToCString(), "text\\T\\with\\T\\tabs");
}

TEST(StepData_StepWriterTest, CleanTextForSend_ControlDirectivePreservation)
{

  TCollection_AsciiString anInput1("text with \\XA7\\ section sign");
  TCollection_AsciiString aResult1 = StepData_StepWriter::CleanTextForSend(anInput1);
  EXPECT_STREQ(aResult1.ToCString(), "text with \\XA7\\ section sign");

  TCollection_AsciiString anInput2("\\X2\\03C0\\X0\\ is pi");
  TCollection_AsciiString aResult2 = StepData_StepWriter::CleanTextForSend(anInput2);
  EXPECT_STREQ(aResult2.ToCString(), "\\X2\\03C0\\X0\\ is pi");

  TCollection_AsciiString anInput3("emoji \\X4\\001F600\\X0\\ face");
  TCollection_AsciiString aResult3 = StepData_StepWriter::CleanTextForSend(anInput3);
  EXPECT_STREQ(aResult3.ToCString(), "emoji \\X4\\001F600\\X0\\ face");

  TCollection_AsciiString anInput4("text with \\S\\ directive");
  TCollection_AsciiString aResult4 = StepData_StepWriter::CleanTextForSend(anInput4);
  EXPECT_STREQ(aResult4.ToCString(), "text with \\S\\ directive");

  TCollection_AsciiString anInput5("\\PA\\ code page setting");
  TCollection_AsciiString aResult5 = StepData_StepWriter::CleanTextForSend(anInput5);
  EXPECT_STREQ(aResult5.ToCString(), "\\PA\\ code page setting");
}

TEST(StepData_StepWriterTest, CleanTextForSend_ExistingDirectivePreservation)
{

  TCollection_AsciiString anInput1("line1\\N\\line2");
  TCollection_AsciiString aResult1 = StepData_StepWriter::CleanTextForSend(anInput1);
  EXPECT_STREQ(aResult1.ToCString(), "line1\\N\\line2");

  TCollection_AsciiString anInput2("text\\T\\with\\T\\tab");
  TCollection_AsciiString aResult2 = StepData_StepWriter::CleanTextForSend(anInput2);
  EXPECT_STREQ(aResult2.ToCString(), "text\\T\\with\\T\\tab");
}

TEST(StepData_StepWriterTest, CleanTextForSend_MixedContent)
{

  TCollection_AsciiString anInput1("see \\XA7\\ section and 'quotes'");
  TCollection_AsciiString aResult1 = StepData_StepWriter::CleanTextForSend(anInput1);
  EXPECT_STREQ(aResult1.ToCString(), "see \\XA7\\ section and ''quotes''");

  TCollection_AsciiString anInput2("\\XA7\\ and path\\file");
  TCollection_AsciiString aResult2 = StepData_StepWriter::CleanTextForSend(anInput2);
  EXPECT_STREQ(aResult2.ToCString(), "\\XA7\\ and path\\\\file");

  TCollection_AsciiString anInput3("prefix \\X2\\03B103B2\\X0\\ 'text' with\ttab");
  TCollection_AsciiString aResult3 = StepData_StepWriter::CleanTextForSend(anInput3);
  EXPECT_STREQ(aResult3.ToCString(), "prefix \\X2\\03B103B2\\X0\\ ''text'' with\\T\\tab");
}

TEST(StepData_StepWriterTest, CleanTextForSend_EdgeCases)
{

  TCollection_AsciiString anInput1("");
  TCollection_AsciiString aResult1 = StepData_StepWriter::CleanTextForSend(anInput1);
  EXPECT_STREQ(aResult1.ToCString(), "");

  TCollection_AsciiString anInput2("''");
  TCollection_AsciiString aResult2 = StepData_StepWriter::CleanTextForSend(anInput2);
  EXPECT_STREQ(aResult2.ToCString(), "''''");

  TCollection_AsciiString anInput3("\\XA7\\");
  TCollection_AsciiString aResult3 = StepData_StepWriter::CleanTextForSend(anInput3);
  EXPECT_STREQ(aResult3.ToCString(), "\\XA7\\");

  TCollection_AsciiString anInput4("\\XA7\\\\XB6\\");
  TCollection_AsciiString aResult4 = StepData_StepWriter::CleanTextForSend(anInput4);
  EXPECT_STREQ(aResult4.ToCString(), "\\XA7\\\\XB6\\");
}

TEST(StepData_StepWriterTest, CleanTextForSend_MalformedInput)
{

  TCollection_AsciiString anInput1("incomplete \\X and 'quotes'");
  TCollection_AsciiString aResult1 = StepData_StepWriter::CleanTextForSend(anInput1);
  EXPECT_STREQ(aResult1.ToCString(), "incomplete \\\\X and ''quotes''");

  TCollection_AsciiString anInput2("partial \\XA and more");
  TCollection_AsciiString aResult2 = StepData_StepWriter::CleanTextForSend(anInput2);
  EXPECT_STREQ(aResult2.ToCString(), "partial \\\\XA and more");
}

TEST(StepData_StepWriterTest, CleanTextForSend_HexSequenceDetection)
{

  TCollection_AsciiString anInput1("\\X2\\03B103B203B3\\X0\\");
  TCollection_AsciiString aResult1 = StepData_StepWriter::CleanTextForSend(anInput1);
  EXPECT_STREQ(aResult1.ToCString(), "\\X2\\03B103B203B3\\X0\\");

  TCollection_AsciiString anInput2("\\X4\\001F600001F638\\X0\\");
  TCollection_AsciiString aResult2 = StepData_StepWriter::CleanTextForSend(anInput2);
  EXPECT_STREQ(aResult2.ToCString(), "\\X4\\001F600001F638\\X0\\");

  TCollection_AsciiString anInput3("start \\X2\\03C0\\X0\\ end");
  TCollection_AsciiString aResult3 = StepData_StepWriter::CleanTextForSend(anInput3);
  EXPECT_STREQ(aResult3.ToCString(), "start \\X2\\03C0\\X0\\ end");
}
