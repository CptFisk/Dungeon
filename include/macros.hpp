#pragma once
#include <nlohmann/json.hpp>

#define DEFINE_ENUM_AND_JSON_SERIALIZATION(EnumName, ...) \
    enum EnumName { __VA_ARGS__ }; \
    const char* const get##EnumName##Strings[] = { #__VA_ARGS__ }; \
    NLOHMANN_JSON_SERIALIZE_ENUM(EnumName, { __VA_ARGS__ })

#define DEFINE_STRING_ARRAY(EnumName, ...) \
    const char* const get##EnumName##Strings[] = { __VA_ARGS__ }

#define DEFINE_JSON_SERIALIZATION(EnumName, ...) \
    NLOHMANN_JSON_SERIALIZE_ENUM(EnumName, { __VA_ARGS__ })

#define QUOTE(arg) #arg
#define QUOTE_AND_COMMA(arg) QUOTE(arg),


