#pragma once

#define PRK_STRINGIFY(x) #x
#define PRK_TOSTRING(x) PRK_STRINGIFY(x)
#define NB_LINE __FILE__ ":" PRK_TOSTRING(__LINE__)

#define PM_LOG(message, ...) UE_LOG(LogTemp, Display, TEXT(message), __VA_ARGS__)
#define PM_ERROR(message) UE_LOG(LogTemp, Error, TEXT(message)) UE_LOG(LogTemp, Display, TEXT(NB_LINE))

//#define bp_check(pointer) if (pointer == nullptr) { UE_LOG(LogTemp, Error, TEXT("bp pointer missing")); UE_LOG(LogTemp, Error, TEXT(NB_LINE)); return; }
//#define bp_check_ret(pointer, ret) if (pointer == nullptr) { UE_LOG(LogTemp, Error, TEXT("bp pointer missing")); UE_LOG(LogTemp, Error, TEXT(NB_LINE)); return ret; }