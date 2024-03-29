/**
 * @file gtest_bulk.cpp
 *
 * @brief test bulk
 *  */

#include "block.h"
#include "parser.h"
#include "stdoutwriter.h"
#include "filewriter.h"
#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>


namespace {

   // NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)


  std::string get_is(const std::string &path_in, time_t t)
  {
    testing::internal::CaptureStdout();
    Block block({stdoutwriter, filewriter}, [&t](){ return t++;});
    Parser parser(3, block);
    std::ifstream ifsin(path_in);
    EXPECT_TRUE(ifsin.is_open());
    for(std::string line; std::getline(ifsin, line);) {
      parser.parse(line);
    }
    EXPECT_FALSE(ifsin.bad());
    parser.finalize();
    return testing::internal::GetCapturedStdout();
  }

  std::string get_must(const std::string &path_out)
  {
    std::string output_must;
    std::ifstream ifsout(path_out);
    EXPECT_TRUE(ifsout.is_open());
    for(std::string line; std::getline(ifsout, line);) {
      output_must += line + "\n";
    }
    EXPECT_FALSE(ifsout.bad());
    return output_must;
  }

  TEST(bulk, input1) {
    {
      std::filesystem::remove("bulk10000.log");
      std::filesystem::remove("bulk10001.log");
      EXPECT_EQ(get_is("testinput1.txt", 10000),get_must("testoutput1.txt"));
      EXPECT_TRUE(std::filesystem::exists("bulk10000.log"));
      EXPECT_TRUE(std::filesystem::exists("bulk10001.log"));
    }
  }

  TEST(bulk, input2) {
    {
      std::filesystem::remove("bulk20000.log");
      std::filesystem::remove("bulk20001.log");
      std::filesystem::remove("bulk20002.log");
      EXPECT_EQ(get_is("testinput2.txt", 20000),get_must("testoutput2.txt"));
      EXPECT_TRUE(std::filesystem::exists("bulk20000.log"));
      EXPECT_TRUE(std::filesystem::exists("bulk20001.log"));
      EXPECT_TRUE(std::filesystem::exists("bulk20002.log"));
    }
  }
    // NOLINTEND(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)
}
