import qbs 1.0

StaticLibrary
{
    name: "console"
    Depends { name:"cpp"}
    Depends { name:"stm32f1"}
    Depends { name:"mdk"}
    Depends { name:"core"}

    cpp.includePaths:
    [
        project.sourceDirectory,
    ]
    cpp.cxxLanguageVersion: "c++11"

    files:
    [
        "command.h",
        "command.h",
        "controller.h",
        "controller.cpp",
        "event.h",
        "model.h",
        "stm32f1.cpp",
        "stm32f1.h",
    ]
}


