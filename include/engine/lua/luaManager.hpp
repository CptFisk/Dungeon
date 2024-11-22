#pragma once
#include <iostream>
#include <lua.hpp>
#include <string>

namespace Engine {

class LuaManager {
  public:
    LuaManager();
    ~LuaManager();

    lua_State*& getState();

    bool executeScript(const std::string& script);
    bool callFunction(const std::string& func);
    std::string executeString(const std::string& code);

  protected:
  private:
    lua_State* L;
};
}