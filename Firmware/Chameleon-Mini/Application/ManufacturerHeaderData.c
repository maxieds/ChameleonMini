/* ManufacturerHeaderData.c */

#include "ManufacturerHeaderData.h"
#include "Reader14443A.h"

#ifdef IS_CUSTOM_MANUDATA_SUPPORTED_MAKEFILE_DEFINE
     __IS_CUSTOM_MANUDATA_SUPPORTED = IS_CUSTOM_MANUDATA_SUPPORTED_MAKEFILE_DEFINE;
#else
     __IS_CUSTOM_MANUDATA_SUPPORTED = false; /// Default to use the internal versions for unsupported tag types.
#endif

ChameleonTagManuData_t PROGMEM __ActiveConfigManuData {
     #ifdef ACTIVE_CONFIG_MANUDATA_CARDTYPE_MAKEFILE_DEFINE
     .sak      = { CardIdentificationList[ACTIVE_CONFIG_MANUDATA_CARDTYPE_MAKEFILE_DEFINE].SAK },
     .atqa     = { (CardIdentificationList[ACTIVE_CONFIG_MANUDATA_CARDTYPE_MAKEFILE_DEFINE].ATQA & 0x0000ff00) >> 8, 
                   CardIdentificationList[ACTIVE_CONFIG_MANUDATA_CARDTYPE_MAKEFILE_DEFINE].ATQA & 0x000000ff },
     .ats_size =   CardIdentificationList[ACTIVE_CONFIG_MANUDATA_CARDTYPE_MAKEFILE_DEFINE].ATSRelevant ? 
                   CardIdentificationList[ACTIVE_CONFIG_MANUDATA_CARDTYPE_MAKEFILE_DEFINE].ATSSize : 0;
     .ats      =   CardIdentificationList[ACTIVE_CONFIG_MANUDATA_CARDTYPE_MAKEFILE_DEFINE].ATS, 
     #else
     .sak      = { 0x00 },
     .atqa     = { 0x00, 0x00 },
     .ats_size = 0,
     .ats      = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
     #endif
     .hwvers   = { 0x00, 0x00 },
     .swvers   = { 0x00, 0x00 },
     .batchno  = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
     .prodate  = { 0x00, 0x00 },
}

void ResetManufacturerGlobalStorageToDefaults(const char *tagType, bool useGlobals) {
     // TODO
}

uint16_t GetActiveConfigManufacturerDataByField(uint16_t fieldOffset, uint8_t **returnedFieldSize) {
     // TODO
     return 0;
}

bool ParseTerminalManuDataArgument(const char *argPrefix, const char *argPayload, ChameleonTagManuData_t * &manuDataStorage) {
     // TODO
     return false;
}
