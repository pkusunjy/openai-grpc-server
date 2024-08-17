#include <regex>
#include <string>

#include "gtest/gtest.h"

TEST(html_parse, html_parse) {
  std::string raw{
      "<article "
      "data-clipboard-cangjie=\"[&quot;root&quot;,{},[&quot;p&quot;,{},[&quot;span&quot;,{&quot;data-type&quot;:&quot;"
      "text&quot;},[&quot;span&quot;,{&quot;fonts&quot;:{&quot;asciiTheme&quot;:&quot;minorAscii&quot;,&quot;cs&quot;:&"
      "quot;Times New Roman&quot;,&quot;eastAsia&quot;:&quot;Times New "
      "Roman&quot;,&quot;hAnsiTheme&quot;:&quot;minorAscii&quot;,&quot;hint&quot;:&quot;default&quot;},&quot;sz&quot;:"
      "12,"
      "&quot;szUnit&quot;:&quot;pt&quot;,&quot;data-type&quot;:&quot;leaf&quot;},&quot;Do you like your subject? (Why? "
      "/ "
      "Why not?)&quot;]]]]\">\n<p><span style=\"font-family: arial, helvetica, sans-serif;\">Do you like your subject? "
      "(Why? / Why not?)</span></p>\n</article>"};
  std::regex tags("<.*?>");
  std::string result = std::regex_replace(raw, tags, "");
  EXPECT_EQ("\nDo you like your subject? (Why? / Why not?)\n", result);
}
