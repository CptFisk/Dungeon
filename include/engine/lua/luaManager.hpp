#pragma once
#include <iostream>
#include <lua.hpp>
#include <monster/monster.hpp>
#include <string>
namespace Lua {

class LuaManager {
  public:
    LuaManager();
    ~LuaManager();

    lua_State*& getState();

    void createMonsterMetaTable(Monster::BaseMonster*& monster) const;

    bool        executeScript(const std::string& script) const;
    bool        callFunction(const std::string& func);
    std::string executeString(const std::string& code);

  protected:
  private:
    // Register functions for lua interface
    void registerPlayer();
    void registerMonster();
    void registerObjectState();
    void registerUtility();

    lua_State* L;
};
}