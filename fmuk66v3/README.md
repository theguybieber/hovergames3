# PX4 (NXP FMUK66_e Post 2022)

The NXP FMUK66_e is a PX4 compatible flight manager. Generally you put a bootloader on the flight manager then use QGroundControl to update the PX4 software. 

## FMUK66 Flashing 
[link](https://nxp.gitbook.io/hovergames/developerguide/program-software-using-debugger)

MacOS Directions 
1. Install QGroundControl [here](https://d176tv9ibo4jno.cloudfront.net/latest/QGroundControl.dmg)
3. Install the latest Java JDK [here](https://www.oracle.com/java/technologies/downloads/#jdk19-mac)
4. Install JLink Commander [here](https://www.segger.com/downloads/jlink#J-LinkSoftwareAndDocumentationPack)
5. Pre 2022 software fmuk66_v3 - 
   1. Download from [here](http://ci.px4.io/job/PX4_misc/job/Firmware-compile/job/stable/lastSuccessfulBuild/artifact/build/nxp_fmuk66-v3_default/)
6. Post 2022 software fmuk66_e - 
   1. Download from [here](http://ci.px4.io/job/PX4_misc/job/Firmware-compile/job/stable/lastSuccessfulBuild/artifact/build/nxp_fmuk66-e_default/)
7.  Install the bootloader [here](https://nxp.gitbook.io/hovergames/userguide/programming)
    ```
    JLinkExe
    connect
    MK66FN2M0XXX18
    S
    4000

    loadbin <absolute path>/nxp_fmuk66-<version>.bin 0x0

8.  Install the firmware
    ```
    loadbin <absolutepath>/nxp_fmuk66-v3_default.bin 0x6000


## FMU to NAVQ+ Ethernet Connection
### PX4 Configuration 
Default 2-wire ethernet address of the FMU is 10.10.10.1
1. Via QGroundControl enter the following on the NSH NuttX Shell (nsh)
    ```
    mavlink start -x -u 14551 -o 14551 -r 200000 -t 10.0.0.1
    ```

### NAVQ+ Configuration
Default 2-wire ethernet addess of navq+ is 10.10.10.2
1. On the navq+ board run ./scripts/navq_install.sh

The "px4" command can be used to make a shell connection between the px4 and navq+.

