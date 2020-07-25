import qbs 1.0

StaticLibrary
{
    name: "uart"
    Depends { name:"cpp"}
    Depends { name:"stm32f1"}
    Depends { name:"mdk"}
    Depends { name:"core"}

    Export
    {
        Depends { name:"cpp"}
        cpp.includePaths:[product.sourceDirectory]
    }

    cpp.includePaths:
    [
        project.sourceDirectory,
    ]

    cpp.cxxLanguageVersion: "c++11"

    files:
    [
        "command.h",
        "controller.h",
        "controller.cpp",
        "event.h",
        "stm32f1.cpp",
        "stm32f1.h",
    ]
}


