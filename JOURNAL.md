Note: As of 9th June 2026, I have only been able to record one of my sessions with lapse, others been journaled, I confirm that the time spent on this project is as accurate as I am able to provide

**Total time: 11.5 hours**

# June 7th 2026 - I completed the schematics: 3 hours

I completed the schematics for the slave drones which will be controlled by the Ground station, I have decided to use an ESP32 as it is easy to use and already boasts powerful wifi/bluetooth, I have also added 2 sensors, the QMC5883P which is a magnetometer will help the drone saty aligned and the MPU6500 is an Accelerometer + Gyroscope IMU which will help the drone sense its position, I plan to use these to make the drones fly in simple patterns

Picture:
<img width="2160" height="1533" alt="Screenshot 2026-06-09 202325" src="https://github.com/user-attachments/assets/7b479beb-036b-4db9-aae7-c9a26c4def81" />

# June 7th 2026 - Routed the PCB: 3 hours

I completely routed the PCB to fit in a board 32mm by 32mm, This will allow it to fit into many widely availible whoop drone frames, The 2mm screw holes are also placed in a 25.5mm by 25.5mm grid which will allow them to screw into any existing whoop drone frame, I have also placed components on both sides of the PCB as it allows me to make it small and light which is very important in order for me be able to fly these drones without having to deal with legal issues.

Picture:
<img width="1282" height="1325" alt="Screenshot 2026-06-07 174942" src="https://github.com/user-attachments/assets/f2a67be4-47f7-407f-96dc-8191b7f22f44" />

# June 8th 2026 - Made the case - 2 hours

I made the PCB case today as I realised that with the way I mounted the ESP32 I wouldn't be able to mount it at a 45 degree angle, here is a pciture of the case, It has a main 32mmx32mm platform for the flight controller and then 4 arms + propeller guards for the motors

Pictures:
<img width="1086" height="1113" alt="Screenshot 2026-06-09 202408" src="https://github.com/user-attachments/assets/a76aa73f-4606-4706-8367-904c00ae4629" />
<img width="1970" height="1242" alt="Screenshot 2026-06-09 202203" src="https://github.com/user-attachments/assets/5d9c8dc9-31ac-4dfa-8f1b-a9680528a581" />

# June 9th 2026 - Fixing the PCB + firmware - 3.5 hours

When I tried to export the board as step file, KiCAD gave me the error code 3, failed to load board, I went down a massive rabbit whole of trying fix it where I thought that something was off with my footprints, when I didn't find anything there I checked to see it the 3D viewer still works and it did, I tried various combinations to get the thing to work but they all failed eventually I even attempted to re-route the whole board but failed as it gave me the same error (even though I made a new file). I also deleted and reinstalled KiCAD thinking that was the problem but that didn't work either, In the end I ended up getting the step file by using an extension to get it into FreeCAD and then exporting the board out of freeCAD, However, I wasn't able to retain any components.
I also made the firmware today for both the drones however it is an early version and will need to be tweaked later on

Pictues of the board from FreeCAD, It wouldn't let me export components for some reason:
<img width="1354" height="1344" alt="image" src="https://github.com/user-attachments/assets/9d9c1bfb-46a0-4f13-9b31-efbd87c7a99b" />


