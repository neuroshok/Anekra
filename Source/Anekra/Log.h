#pragma once

#define PRK_STRINGIFY(x) #x
#define PRK_TOSTRING(x) PRK_STRINGIFY(x)
#define NB_LINE __FILE__ ":" PRK_TOSTRING(__LINE__)

DECLARE_LOG_CATEGORY_EXTERN(LogAnekra, Log, All);

#define ANK_LOG(message, ...) UE_LOG(LogAnekra, Display, TEXT(message), __VA_ARGS__)
#define ANK_ERROR(message, ...) UE_LOG(LogAnekra, Error, TEXT(message), __VA_ARGS__)