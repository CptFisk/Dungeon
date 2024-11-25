#pragma once
#include <iostream>
#include <lua.hpp>
#include <string>
#include <monster/monster.hpp>

namespace Lua {

class LuaManager {
  public:
    LuaManager();
    ~LuaManager();

    lua_State*& getState();

    void createMonsterMetaTable(Monster::BaseMonster*& monster);

    bool executeScript(const std::string& script);
    bool callFunction(const std::string& func);
    std::string executeString(const std::string& code);

  protected:
  private:
    void registerMonster();
    lua_State* L;
};
}