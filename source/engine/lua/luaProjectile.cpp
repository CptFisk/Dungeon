#include <engine/lua/luaProjectile.hpp>
#include <string>
#include <SDL.h>
#include <global.hpp>
#include <engine/engine.hpp>

int
projectile_spawnEnemy(lua_State* L) {
    /**
     * Parameters as follows:
     * 1 = Texture
     * 2 = Effect (optional)
     * 3 = Start point X
     * 4 = Start point y
     * 5 = Angle
     * 6 = Duration
     * 7 = Velocity
     * 8 = Damage
     */
    if (!lua_isstring(L, 1) || !lua_isstring(L, 2) || !lua_isnumber(L, 3) || !lua_isnumber(L, 4) || !lua_isnumber(L, 5) ||
        !lua_isinteger(L, 6) || !lua_isnumber(L, 7) || !lua_isinteger(L, 8)) {
        const auto p1 = luaL_checkstring(L,2);
        const auto p2 = luaL_checkstring(L,3);
        luaL_error(L, "Parameters incorrect");
        lua_pushnil(L);
    }
    const auto textureName = std::string(luaL_checkstring(L,1));
    const auto effectName = std::string(luaL_checkstring(L,2));
    const auto startPoint = SDL_FPoint{ FLOAT(luaL_checknumber(L,3)), FLOAT(luaL_checknumber(L,4))};
    const auto angle = luaL_checknumber(L, 5);
    const auto duration = INT(luaL_checkinteger(L, 6));
    const auto velocity = FLOAT(luaL_checknumber(L, 7));
    const auto damage = INT(luaL_checkinteger(L,8));

    //Fetching textures, effect only if name is blank
    extern Engine::Engine engine;
    auto texture = dynamic_cast<Graphics::AnimatedTexture*>(engine.getGraphics().getTexture(textureName));

    Graphics::AnimatedTexture* effect = nullptr;
    if(!effectName.empty())
        effect = dynamic_cast<Graphics::AnimatedTexture*>(engine.getGraphics().getTexture(effectName));
    engine.createProjectile(false, texture, effect, startPoint, angle, duration, velocity, damage);
    return 1;
}