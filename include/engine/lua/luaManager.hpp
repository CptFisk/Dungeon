#pragma once
#include <iostream>
#include <lua.hpp>
#include <monster/monster.hpp>
#include <string>
#include <unordered_map>
namespace Lua {

class LuaManager {
  public:
    LuaManager();
    ~LuaManager();

    lua_State*& getState();

    void createMonsterMetaTable(Monster::BaseMonster*& monster) const;

    bool                         executeScript(const std::string& script);
    [[maybe_unused]] bool        callFunction(const std::string& func);
    [[maybe_unused]] std::string executeString(const std::string& code);

  protected:
  private:
    // Register functions for lua interface
    void registerPlayer();
    void registerMonster();
    void registerObjectState();
    void registerUtility();
    void registerProjectile();

    lua_State*                                   L;
    std::unordered_map<size_t, std::string> mScripts; // Store lua file data so we dont need to re-read them
};
}