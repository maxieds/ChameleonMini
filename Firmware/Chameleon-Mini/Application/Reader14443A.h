#ifndef READER14443A_H
#define READER14443A_H

#include "Application.h"
#include "Codec/Codec.h"

#define CRC_INIT 0x6363

extern uint8_t ReaderSendBuffer[];
extern uint16_t ReaderSendBitCount;

void Reader14443AAppInit(void);
void Reader14443AAppReset(void);
void Reader14443AAppTask(void);
void Reader14443AAppTick(void);
void Reader14443AAppTimeout(void);

uint16_t Reader14443AAppProcess(uint8_t *Buffer, uint16_t BitCount);

uint16_t addParityBits(uint8_t *Buffer, uint16_t bits);
uint16_t removeParityBits(uint8_t *Buffer, uint16_t BitCount);
bool checkParityBits(uint8_t *Buffer, uint16_t BitCount);
uint16_t ISO14443_CRCA(uint8_t *Buffer, uint8_t ByteCount);

typedef enum {
    Reader14443_Do_Nothing,
    Reader14443_Send,
    Reader14443_Send_Raw,
    Reader14443_Get_UID,
    Reader14443_Autocalibrate,
    Reader14443_Read_MF_Ultralight,
    Reader14443_Identify,
    Reader14443_Identify_Clone,
    Reader14443_Clone_MF_Ultralight
} Reader14443Command;

/* Define common fields here so the static card data fields stored in the C source are reusable 
 * (can be read / copied) from external sources (i.e., for use in setting up 
 *"custom defaults" for the new manufacturer data bytes to represent these 
 * particular tag types):
 */

typedef enum {
    CardType_NXP_MIFARE_Mini = 0, // do NOT assign another CardType item with a specific value since there are loops over this type
    CardType_NXP_MIFARE_Classic_1k,
    CardType_NXP_MIFARE_Classic_4k,
    CardType_NXP_MIFARE_Ultralight,
//   CardType_NXP_MIFARE_Ultralight_C,
//   CardType_NXP_MIFARE_Ultralight_EV1,
    CardType_NXP_MIFARE_DESFire,
    CardType_NXP_MIFARE_DESFire_EV1,
    CardType_IBM_JCOP31,
    CardType_IBM_JCOP31_v241,
    CardType_IBM_JCOP41_v22,
    CardType_IBM_JCOP41_v231,
    CardType_Infineon_MIFARE_Classic_1k,
    CardType_Gemplus_MPCOS,
    CardType_Innovision_Jewel,
    CardType_Nokia_MIFARE_Classic_4k_emulated_6212,
    CardType_Nokia_MIFARE_Classic_4k_emulated_6131
} CardType;

typedef struct {
    uint16_t ATQA;
    bool ATQARelevant;
    uint8_t SAK;
    bool SAKRelevant;
    uint8_t ATS[16];
    uint8_t ATSSize;
    bool ATSRelevant;
    char Manufacturer[16];
    char Type[64];
} CardIdentificationType;

extern const CardIdentificationType PROGMEM CardIdentificationList[];

#endif //READER14443A_H
