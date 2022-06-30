# References
This file contains a list of sources i used and required in order to create this project.



## ErikaOS
| Name                        | Description                                                      | URL                                                                                                     |
|-----------------------------|------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------|
| ErikaOS porting guide       | A rough and incomplete step by step guide to port ErikaOs        | http://erika.tuxfamily.org/wiki/index.php?title=Porting_ERIKA_Enterprise_and_RT-Druid_to_a_new_microcontroller |
| ErikaOS OIL specification   | ErikaOS v3 OIL specification (mostly the same as for v2)         | https://www.erika-enterprise.com/wiki/index.php/ERIKA3_OIL_specification                                |
| ErikaOS API manual          | A description of the API calls provided by ErikaOS               | http://download.tuxfamily.org/erika/webdownload/manuals_pdf/ee_minimal_refman_1_1_3.pdf                 |
| ErikaOS Kernel presentation | An overview of the ErikaOS kernel in form of presentation slides | http://www.artist-embedded.org/docs/Events/2010/RT_Kernels_Pisa/slides/S2-erika-Gai.pdf                 |
| ErikaOS Sources             | Contains instruction how to obtain ErikaOS v2 Sources            | http://erika.tuxfamily.org/wiki/index.php?title=ERIKA_Enterprise_and_RT-Druid_SVN_Access                |


## AM1808
| Name                       | Description                                                          | URL                                             |
|----------------------------|----------------------------------------------------------------------|-------------------------------------------------|
| AM1808 Datasheet           | Contains a overview of all features of the AM1808 MCU                | https://www.ti.com/lit/ds/symlink/am1808.pdf    |
| AM1808 Technical Manaul    | Contains a complete description of the AM1808 MCU and its components | https://www.ti.com/lit/ug/spruh82c/spruh82c.pdf |
| Simple RTOS Implementation | A project of the University of Potsdamm; simple RTOS implemtation for the ev3 Mindstorm | https://publishup.uni-potsdam.de/opus4-ubp/frontdoor/deliver/index/docId/7063/file/tbhpi90.pdf |
| Git for the project above| Simple RTOS implemtation for the ev3 Mindstorm | https://github.com/ninjastorms/ninjastorms |

## VersatilePB
| Name                                    | Description                                                              | URL                                                             |
|-----------------------------------------|--------------------------------------------------------------------------|-----------------------------------------------------------------|
| versatilepb qemu overview               | Contains a description of what components the versatilepb QEMU supports  | https://qemu.readthedocs.io/en/latest/system/arm/versatile.html |
| versatilepb interrupt controller manual | Contains a complete description of the PL190 interrupt controller        | https://developer.arm.com/documentation/ddi0181/e               |
| versatilepb timer controller manual     | Contains complete description of the SP804 timer controller              | https://developer.arm.com/documentation/ddi0271/d/              |

## ARM9, OSEK and Tools
| Name                 | Description                                                 | URL                                                                                           |
|----------------------|-------------------------------------------------------------|-----------------------------------------------------------------------------------------------|
| OSEK specification   | Outdated but mostly accurate OSKE OS specification          | https://www.irisa.fr/alf/downloads/puaut/TPNXT/images/os223.pdf                               |
| ARM926ej-s           | Specification of the specific CPU used in the ev3 Mindstorm | https://developer.arm.com/documentation/ddi0198/e/introduction/about-the-arm926ej-s-processor |
| C-Kermit homepage    | Contains information about the C-Kermit project             | http://www.columbia.edu/kermit/ck90.html                                                      |
| U-BOOT documentation | Contains information about the U-BOOT project               | https://u-boot.readthedocs.io/en/latest/                                                      |