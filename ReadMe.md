# ErikaOS Version 2 port for the EV3 Mindstorm

This port was created as a bachelor thesis at the Leibniz University Hannover for the Systems Research and Architecture Group ([here](https://sra.uni-hannover.de/Theses/2022/BA-Mindstorms.html)). 

The ErikaOS sources were used from the public SVN-Repository ([here](https://svn.tuxfamily.org/viewvc.cgi/erika_erikae/repos/ee/trunk/ee/)).

A port of the OIL-Compiler RT-Druid is not included. OIL-files are still usable by using a work around. This is not relevant for users of this port. For more information on that workaround see Chapter 3.2.1 from the [thesis](./thesis.pdf).

This thesis also covers how to develop and deploy a baremetal hello world application for the EV3 Mindstorm using two different deployment methods. These can be found in the respective folder (see below) and were the first step in developing this port.

For further information see the *ReadMe's* in the subdirectories!

| Folder name  | Contains                                                                                                                     |
|--------------|------------------------------------------------------------------------------------------------------------------------------|
| erika         | All files for the ErikaOS Port |
| hello_world        | Hello World Showcase for EV3 Mindstorm with SD-card deployment                    |
| hello_world_v2.0        | Hello World Showcase for EV3 Mindstorm with C-Kermit deployment                     |
