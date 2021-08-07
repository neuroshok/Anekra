#pragma once

#define PRK_STRINGIFY(x) #x
#define PRK_TOSTRING(x) PRK_STRINGIFY(x)
#define NB_LINE __FILE__ ":" PRK_TOSTRING(__LINE__)

DECLARE_LOG_CATEGORY_EXTERN(LogPrankman, Log, All);

#define PM_LOG(message, ...) UE_LOG(LogPrankman, Display, TEXT(message), __VA_ARGS__)
#define PM_ERROR(message, ...) UE_LOG(LogPrankman, Error, TEXT(message), __VA_ARGS__)