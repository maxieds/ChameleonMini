/*
The DESFire stack portion of this firmware source
is free software written by Maxie Dion Schmidt (@maxieds):
You can redistribute it and/or modify
it under the terms of this license.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

The complete source distribution of
this firmware is available at the following link:
https://github.com/maxieds/ChameleonMiniFirmwareDESFireStack.

Based in part on the original DESFire code created by
@dev-zzo (GitHub handle) [Dmitry Janushkevich] available at
https://github.com/dev-zzo/ChameleonMini/tree/desfire.

This notice must be retained at the top of all source files where indicated.
*/

/*
 * DESFirePICCControl.h :
 * Maxie D. Schmidt (github.com/maxieds)
 */

#ifndef __DESFIRE_PICC_CONTROL_H__
#define __DESFIRE_PICC_CONTROL_H__

#include "../../Configuration.h"

#include "DESFireFirmwareSettings.h"
#include "DESFirePICCHeaderLayout.h"
#include "DESFireInstructions.h"
#include "DESFireApplicationDirectory.h"
#include "DESFireFile.h"
#include "DESFireCrypto.h"

/* Build-time (make-time) DESFire tag spec defaults: */
#ifdef DESFIRE_DEFAULT_PICC_UID
    #define ENABLE_DESFIRE_DEFAULT_PICC_UID               (1)
#else
    #define ENABLE_DESFIRE_DEFAULT_PICC_UID               (0)
    #define DESFIRE_DEFAULT_PICC_UID                      ((uint8_t *) { 0x00 })
#endif
#define BYTELEN_DESFIRE_DEFAULT_PICC_UID                  (7)

#ifdef DESFIRE_DEFAULT_PICC_ATS
    #define ENABLE_DESFIRE_DEFAULT_PICC_ATS               (1)
#else
    #define ENABLE_DESFIRE_DEFAULT_PICC_ATS               (0)
    #define DESFIRE_DEFAULT_PICC_ATS                      ((uint8_t *) { 0x00 })
#endif
#define BYTELEN_DESFIRE_DEFAULT_PICC_ATS                  (6)

#ifdef DESFIRE_DEFAULT_PICC_ATQA
    #define ENABLE_DESFIRE_DEFAULT_PICC_ATQA              (1)
#else
    #define ENABLE_DESFIRE_DEFAULT_PICC_ATQA              (0)
    #define DESFIRE_DEFAULT_PICC_ATQA                     ((uint8_t *) { 0x00 })
#endif
#define BYTELEN_DESFIRE_DEFAULT_PICC_ATQA                 (4)

#ifdef DESFIRE_DEFAULT_PICC_MANUID
    #define ENABLE_DESFIRE_DEFAULT_PICC_MANUID            (1)
#else
    #define ENABLE_DESFIRE_DEFAULT_PICC_MANUID            (0)
    #define DESFIRE_DEFAULT_PICC_MANUID                   ((uint8_t *) { 0x00 })
#endif
#define BYTELEN_DESFIRE_DEFAULT_PICC_MANUID               (1)

#ifdef DESFIRE_DEFAULT_PICC_HWTYPE
    #define ENABLE_DESFIRE_DEFAULT_PICC_HWTYPE            (1)
#else
    #define ENABLE_DESFIRE_DEFAULT_PICC_HWTYPE            (0)
    #define DESFIRE_DEFAULT_PICC_HWTYPE                   ((uint8_t *) { 0x00 })
#endif
#define BYTELEN_DESFIRE_DEFAULT_PICC_HWTYPE               (1)

#ifdef DESFIRE_DEFAULT_PICC_HWSUBTYPE
    #define ENABLE_DESFIRE_DEFAULT_PICC_HWSUBTYPE         (1)
#else
    #define ENABLE_DESFIRE_DEFAULT_PICC_HWSUBTYPE         (0)
    #define DESFIRE_DEFAULT_PICC_HWSUBTYPE                ((uint8_t *) { 0x00 })
#endif
#define BYTELEN_DESFIRE_DEFAULT_PICC_HWSUBTYPE            (1)

#ifdef DESFIRE_DEFAULT_PICC_HWPROTOTYPE
    #define ENABLE_DESFIRE_DEFAULT_PICC_HWPROTOTYPE       (1)
#else
    #define ENABLE_DESFIRE_DEFAULT_PICC_HWPROTOTYPE       (0)
    #define DESFIRE_DEFAULT_PICC_HWPROTOTYPE              ((uint8_t *) { 0x00 })
#endif
#define BYTELEN_DESFIRE_DEFAULT_PICC_HWPROTOTYPE          (1)

#ifdef DESFIRE_DEFAULT_PICC_HWVERS
    #define ENABLE_DESFIRE_DEFAULT_PICC_HWVERS            (1)
#else
    #define ENABLE_DESFIRE_DEFAULT_PICC_HWVERS            (0)
    #define DESFIRE_DEFAULT_PICC_HWVERS                   ((uint8_t *) { 0x00 })
#endif
#define BYTELEN_DESFIRE_DEFAULT_PICC_HWVERS               (2)

#ifdef DESFIRE_DEFAULT_PICC_SWTYPE
    #define ENABLE_DESFIRE_DEFAULT_PICC_SWTYPE            (1)
#else
    #define ENABLE_DESFIRE_DEFAULT_PICC_SWTYPE            (0)
    #define DESFIRE_DEFAULT_PICC_SWTYPE                   ((uint8_t *) { 0x00 })
#endif
#define BYTELEN_DESFIRE_DEFAULT_PICC_SWTYPE               (1)

#ifdef DESFIRE_DEFAULT_PICC_SWSUBTYPE
    #define ENABLE_DESFIRE_DEFAULT_PICC_SWSUBTYPE         (1)
#else
    #define ENABLE_DESFIRE_DEFAULT_PICC_SWSUBTYPE         (0)
    #define DESFIRE_DEFAULT_PICC_SWSUBTYPE                ((uint8_t *) { 0x00 })
#endif
#define BYTELEN_DESFIRE_DEFAULT_PICC_SWSUBTYPE            (1)

#ifdef DESFIRE_DEFAULT_PICC_SWPROTOTYPE
    #define ENABLE_DESFIRE_DEFAULT_PICC_SWPROTOTYPE       (1)
#else
    #define ENABLE_DESFIRE_DEFAULT_PICC_SWPROTOTYPE       (0)
    #define DESFIRE_DEFAULT_PICC_SWPROTOTYPE              ((uint8_t *) { 0x00 })
#endif
#define BYTELEN_DESFIRE_DEFAULT_PICC_SWPROTOTYPE          (1)

#ifdef DESFIRE_DEFAULT_PICC_SWVERS
    #define ENABLE_DESFIRE_DEFAULT_PICC_SWVERS            (1)
#else
    #define ENABLE_DESFIRE_DEFAULT_PICC_SWVERS            (0)
    #define DESFIRE_DEFAULT_PICC_SWVERS                   ((uint8_t *) { 0x00 })
#endif
#define BYTELEN_DESFIRE_DEFAULT_PICC_SWVERS               (2)

#ifdef DESFIRE_DEFAULT_PICC_BATCHNO
    #define ENABLE_DESFIRE_DEFAULT_PICC_BATCHNO           (1)
#else
    #define ENABLE_DESFIRE_DEFAULT_PICC_BATCHNO           (0)
    #define DESFIRE_DEFAULT_PICC_BATCHNO                  ((uint8_t *) { 0x00 })
#endif
#define BYTELEN_DESFIRE_DEFAULT_PICC_BATCHNO              (10)

#ifdef DESFIRE_DEFAULT_PICC_PRODDATE
    #define ENABLE_DESFIRE_DEFAULT_PICC_PRODDATE          (1)
#else
    #define ENABLE_DESFIRE_DEFAULT_PICC_PRODDATE          (0)
    #define DESFIRE_DEFAULT_PICC_PRODDATE                 ((uint8_t *) { 0x00 })
#endif
#define BYTELEN_DESFIRE_DEFAULT_PICC_PRODDATE             (2)

/*
 * Internal state variables:
 */

/* Cached data: flush to FRAM or relevant EEPROM addresses if changed */
extern DESFirePICCInfoType Picc;
extern DESFireAppDirType AppDir;

/* Cached app data */
extern SelectedAppCacheType SelectedApp;
extern SelectedFileCacheType SelectedFile;

typedef void (*TransferSourceFuncType)(BYTE *Buffer, BYTE Count);
typedef void (*TransferSinkFuncType)(BYTE *Buffer, BYTE Count);
typedef BYTE(*TransferEncryptFuncType)(BYTE *Buffer, BYTE Count);
typedef TransferStatus(*PiccToPcdTransferFilterFuncType)(BYTE *Buffer);
typedef BYTE(*PcdToPiccTransferFilterFuncType)(BYTE *Buffer, BYTE Count);

/* Stored transfer state for all transfers */
typedef union DESFIRE_FIRMWARE_PACKING {
    struct DESFIRE_FIRMWARE_ALIGNAT {
        BYTE NextIndex;
    } GetApplicationIds;
    BYTE BlockBuffer[CRYPTO_MAX_BLOCK_SIZE];
    struct DESFIRE_FIRMWARE_ALIGNAT {
        SIZET BytesLeft;
        struct DESFIRE_FIRMWARE_ALIGNAT {
            TransferSourceFuncType Func;
            SIZET Pointer; /* in FRAM */
        } Source;
    } ReadData;
    struct DESFIRE_FIRMWARE_ALIGNAT {
        SIZET BytesLeft;
        struct DESFIRE_FIRMWARE_ALIGNAT {
            TransferSinkFuncType Func;
            SIZET Pointer; /* in FRAM */
        } Sink;
    } WriteData;
} TransferStateType;
extern TransferStateType TransferState;

/* Transfer routines */
void SyncronizePICCInfo(void);
TransferStatus PiccToPcdTransfer(uint8_t *Buffer);
uint8_t PcdToPiccTransfer(uint8_t *Buffer, uint8_t Count);

/* Setup routines */
uint8_t ReadDataFilterSetup(uint8_t CommSettings);
uint8_t WriteDataFilterSetup(uint8_t CommSettings);

/* PICC management */
void FormatPicc(void);
void CreatePiccApp(void);

void InitialisePiccBackendEV0(uint8_t StorageSize, bool formatPICC);
void InitialisePiccBackendEV1(uint8_t StorageSize, bool formatPICC);
void InitialisePiccBackendEV2(uint8_t StorageSize, bool formatPICC);

void FactoryFormatPiccEV0(void);
void FactoryFormatPiccEV1(uint8_t StorageSize);
void FactoryFormatPiccEV2(uint8_t StorageSize);

void ResetPiccBackend(void);

bool IsEmulatingEV1(void);

void GetPiccHardwareVersionInfo(uint8_t *Buffer);
void GetPiccSoftwareVersionInfo(uint8_t *Buffer);
void GetPiccManufactureInfo(uint8_t *Buffer);
uint8_t GetPiccKeySettings(void);

void GetPiccUid(ConfigurationUidType Uid);
void SetPiccUid(ConfigurationUidType Uid);

#endif
