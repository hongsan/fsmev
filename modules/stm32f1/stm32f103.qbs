import qbs 1.0
import qbs.FileInfo

Module
{
    Depends{name: "cpp"}
    property string optimization: "small"
    cpp.positionIndependentCode: false
    cpp.enableExceptions: false
    cpp.executableSuffix: ".elf"
    cpp.cxxFlags: ["-std=c++11"]
    cpp.cFlags: ["-std=gnu99"]

    Properties
    {
        condition: qbs.buildVariant === "debug"
        cpp.defines: outer.concat(["DEBUG=1"])
        cpp.debugInformation: true
        cpp.optimization: "none"
    }

    Properties
    {
        condition: qbs.buildVariant === "release"
        cpp.debugInformation: false
        cpp.optimization: optimization
    }

    cpp.driverFlags:
    [
        "-mlittle-endian",
        "-mcpu=cortex-m3",
        "-mthumb",
        "-mfloat-abi=soft",
        "-fno-strict-aliasing",
        "-specs=nano.specs",
        "-specs=nosys.specs",
    ]

    cpp.commonCompilerFlags:
    [
        "-fdata-sections",
        "-ffunction-sections"
    ]

    cpp.linkerFlags:
        [
        "--gc-sections",
        "-L"+ path + "/system/ld",
        "-T" + path + "/system/ld/STM32F103C8Tx_FLASH.ld",
        "-lnosys",
        "-lgcc",
        "-lc",
        "-lstdc++",
        "-lm"
    ]

    Rule
    {
        inputs: ["application"]

        Artifact
        {
            filePath: project.buildDirectory + product.name + ".hex"
            fileTags: "hex"
        }

        prepare:
        {
            var argsSize = [input.filePath]
            var argsObjcopy = ["-O", "ihex", input.filePath, output.filePath]

            var cmdSize = new Command(project.gccPath+"arm-none-eabi-size", argsSize)
            var cmdObjcopy = new Command(project.gccPath+"arm-none-eabi-objcopy", argsObjcopy)

            cmdSize.description = "Size of sections:"
            cmdSize.highlight = "linker"

            cmdObjcopy.description = "convert to bin..."
            cmdObjcopy.highlight = "linker"

            return [cmdSize, cmdObjcopy]
        }
    }

    Rule
    {
        inputs: ["hex"]

        Artifact
        {
            filePath: "-"
            fileTags: "flash"
        }

        prepare:
        {
            var OpenOCDInterface = "stlink-v2.cfg"
            var OpenOCDTarget = "stm32f1x.cfg"

            var argsFlashing =
                    [
                        "-f", project.openOCDPath + "/scripts/interface/" + OpenOCDInterface,
                        "-f", project.openOCDPath + "/scripts/target/" + OpenOCDTarget,
                        "-c", "init",
                        "-c", "reset halt",
                        "-c", "sleep 100",
                        "-c", "wait_halt 2",
                        "-c", "flash write_image erase " + input.filePath,
                        "-c", "sleep 100",
                        "-c", "reset",
                        "-c", "shutdown"
                    ]


            var cmdFlash = new Command(project.openOCDExe, argsFlashing);
            cmdFlash.description = "download firmware to uC..."
            cmdFlash.highlight = "linker"

            return [cmdFlash]
        }
    }
}

