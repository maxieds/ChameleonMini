/* ManufacturerHeaderData.h */

#ifndef __CHAMTAGEMU_MANUHDRDATA_H_
#define __CHAMTAGEMU_MANUHDRDATA_H_

#define __STRUCT_PACKED     __attribute__((packed))
#define __STRUCT_ALIGNED1   __attribute__((aligned(1)))

extern bool __IS_CUSTOM_MANUDATA_SUPPORTED;

typedef struct __STRUCT_PACKED __STRUCT_ALIGNED1 {
     uint8_t sak[1];
     uint8_t atqa[2];
     uint8_t ats_size;
     uint8_t ats[13];
     uint8_t hwvers[4];
     uint8_t swvers[4];
     uint8_t batchno[10];
     uint8_t prodate[2];
} ChameleonTagManuData_t;

extern ChameleonTagManuData_t PROGMEM __ActiveConfigManuData;

enum {
     MANUDATA_PROP_SAK       = 0,
     MANUDATA_PROP_ATQA      = 1, 
     MANUDATA_PROP_ATS       = 4, 
     MANUDATA_PROP_HWVERS    = 17, 
     MANUDATA_PROP_SWVERS    = 21,
     MANUDATA_PROP_BATCHNO   = 25,
     MANUDATA_PROP_PRODATE   = 35,
} ChameleonTagManuDataOffsets;

void ResetManufacturerGlobalStorageToDefaults(const char *tagType = NULL, bool useGlobals = true);
uint16_t GetActiveConfigManufacturerDataByField(uint16_t fieldOffset, uint8_t **returnedFieldSize);
bool ParseTerminalManuDataArgument(const char *argPrefix, const char *argPayload, ChameleonTagManuData_t * &manuDataStorage);

#endif
