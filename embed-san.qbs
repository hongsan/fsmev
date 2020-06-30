import qbs

Project
{
    name: "embed"
    minimumQbsVersion: "1.6.0"
    property string gccPath: ""
    property string openOCDExe: "openocd"
    property string openOCDPath: "/usr/share/openocd"
    references:
    [
        /*library*/
        "modules/stm32f1/mdk.qbs",
        "core/core.qbs",
        "uart/uart.qbs",
        "blink/blink.qbs",
    ]
}
