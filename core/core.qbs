import qbs 1.0

StaticLibrary
{
    name: "core"
    Depends { name:"cpp"}
    Depends { name:"stm32f1"}
    Depends { name:"mdk"}

    Export
    {
        Depends { name:"cpp"}
        cpp.includePaths:[product.sourceDirectory]
    }

    cpp.includePaths:
    [
        product.sourceDirectory
    ]
    cpp.cxxLanguageVersion: "c++11"

    files:
    [
        "queue.h",
        "component.h",
        "config.h",
        "engine.cpp",
        "engine.h",
        "task.cpp",
        "task.h",
    ]
}


