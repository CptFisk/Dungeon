#pragma once
#include <iostream>
#include <lua.hpp>
#include <string>
#include <monster/monster.hpp>
#include <engineForward.hpp>
namespace Lua {

class LuaManager {
  public:
    LuaManager(Engine::Engine& engine);
    ~LuaManager();

    lua_State*& getState();

    void createMonsterMetaTable(Monster::BaseMonster*& monster);

    bool executeScript(const std::string& script);
    bool callFunction(const std::string& func);
    std::string executeString(const std::string& code);

  protected:
  private:
    Engine::Engine& pEngine;

    //Register functions for lua interface
    void registerPlayer();
    void registerMonster();
    void registerObjectState();
    void registerUtility();

    lua_State* L;
};
}