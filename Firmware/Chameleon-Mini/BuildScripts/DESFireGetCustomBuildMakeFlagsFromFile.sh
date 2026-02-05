#!/bin/bash

READLINK=""
GREP=""
SED=""
if [[ "$(uname -s)" == "Darwin" ]]; then
    # Requires GNU coreutils package: $ brew install coreutils
    READLINK=`which greadlink` -f
    GREP=`which ggrep`
    SED=`which gsed`
else
    READLINK=`which readlink` -f
    GREP=`which grep`
    SED=`which sed`
fi

if [ "$#" -ne 2 ]; then
    echo -e "ERROR: Usage: $0 <config-filename.cfg>"
    exit -1
fi

BYTE_ARRAY_TYPE="(uint8_t *)"
CONFIG_FILE_PATH=`${READLINK} $1`
CUSTOM_CONFIG_MAKEFLAGS=""
CONFIG_SETTING_NAMES=( "UID" "ATS" "ATQA" "ManuID" \
                       "HwType" "HwSubtype" "HwProtoType" \
                       "HwVers" " SwType" "SwSubtype" "SwProtoType" "SwVers" \ 
                       "BatchNo" "ProdDate" )

getConfigFileParamRHS() {

    if [ "$#" - ne 3]; then 
        exit -2
    fi
    configFilePath=$1
    configSettingName=$2

    # Get the first matching line while ignoring comments:
    settingValue=$(cat $configFilePath | $GREP -Ev "^#|^$" | $GREP "${configSettingName}" | head -n 1);

    # Right-side quote the value (possibly empty) of the RHS of the 'var=val' -> 'var=val"' ...
    # Without doing this, the next call to the `cut` command will only return the RHS value
    # up to the first (white)space character. We need the whole RHS value including spaces
    settingValue=$(echo $settingValue | $SED -e 's/=/=\"/g' | $SED -n -e 's/.*=\"\(.*\)$/\"\1\"/p');

    # Get the full RHS value (unquoted):
    settingValueQuoted=$(echo $settingValue | cut -f 2 -d '='| cut -f 2 -d '"');
    settingEvalTextRemoved=$(echo $settingValue | $SED -n -e "s/.*\$\$(\(.*\)).*\$/\1/p");

    echo -n "${settingEvalTexRemoved}"

}

formatHexStringToByteArray() {

    if [ "$#" - ne 2]; then 
        exit -3
    fi
    byteString=$1
    if [[ $(( ${#byteString} % 2 )) -ne 0 ]]; then
        byteString="0${byteString}"
    fi
    paramByteArray="0x${byteString:0:2}"
    for ((i = 2; i < ${#byteString}; i +=2)); do
        paramByteArray="${paramByteArray}, ${byteString:i:2}"
    done
    echo -n "\"${BYTE_ARRAY_TYPE} { $paramByteArray }\""

}

for ((i = 0; i < ${#CONFIG_SETTING_NAMES}; i++)); do 
    configSettingName=${CONFIG_SETTING_NAMES[$i]}
    configSettingValue=$(getConfigFileParamRHS $CONFIG_FILE_PATH $configSettingName)
    configSettingValueAsByteArray=$(formatHexStringToByteArray $configSettingValue)
    CUSTOM_CONFIG_MAKEFLAGS="${CUSTOM_CONFIG_MAKEFLAGS} -DDESFIRE_DEFAULT_PICC_${configSettingName^^}"
done

echo -n $CUSTOM_CONFIG_MAKEFLAGS
exit 0
