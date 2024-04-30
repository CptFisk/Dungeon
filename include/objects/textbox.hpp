#pragma once
#include <string>
#include <vector>

namespace Objects{

class TextBox{
  public:
    TextBox(const std::vector<std::string> textlist);
  private:
  protected:
    const std::vector<std::string> mTextlist;
};
}