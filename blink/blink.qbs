import qbs

Product
{
    name: "blink"

    Properties
    {
        condition: qbs.buildVariant === "debug"
        type: ["application", "hex"] //for build
    }

    Properties
    {
        condition: qbs.buildVariant === "release"
        type: ["application", "hex", "flash"] //for deploy to board
    }

    Depends{name: "cpp"}
    Depends{name: "stm32f1"}
    Depends{name: "mdk"}
    Depends{name: "uart"}
    Depends{name: "core"}
    cpp.cxxLanguageVersion: "c++11"

    cpp.includePaths: [project.sourceDirectory]
    files:
    [
        "command.h",
        "controller.cpp",
        "controller.h",
        "main.cpp",
        "stm32f1.cpp",
    ]
}

