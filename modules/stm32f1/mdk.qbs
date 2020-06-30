import qbs 1.0

StaticLibrary
{
    name: "mdk"
    Depends { name:"cpp"}
    Depends { name:"stm32f1"}

    cpp.defines:
    [
        'STM32F103xB',
        '___int16_t_defined',
        '___int8_t_defined',
        '___int32_t_defined',
        '___int64_t_defined',
    ]
    cpp.cxxLanguageVersion: "c++11"

    cpp.includePaths:
    [
        "system/include",
		"system/cmsis/inc",
        "system/cmsis/inc",
    ]

    Export
    {
        Depends { name:"cpp"}
        cpp.includePaths:
        [
            "system/",
            "core/",
			"system/include",
			"system/cmsis/inc",
        ]

        cpp.defines:
        [
            'STM32F103xB',
            '___int16_t_defined',
            '___int8_t_defined',
            '___int32_t_defined',
            '___int64_t_defined',
        ]

    }

    files:
    [
        "system/cmsis/inc/*.h",
        "system/startup_stm32f103xb.s",
        "system/system_stm32f1xx.c",
        "system/include/*.h"
    ]
}


