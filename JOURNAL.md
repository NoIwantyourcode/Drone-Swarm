**Total time: 70.5 hours**

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

# NOTE: FROM THIS POINT ONWARDS ALL MY JOURNALS MAY NOT BE THE MOST ACCURATE AS I AM RECALLING FROM MEMORY, HOWEVER I DID WORK ON SAID PROJECT NEARLY EVERYDAY - HENCE I WILL BE JOURNALLING IN 10 - 11 DAY INCREMENTS, I WAS NOT ABLE TO TAKE MANY PICTURES BECAUSE I WAS TOO BUSY TRYING TO MAKE THE DRONE WORK

# June 19th - June 29th - 20 HOURS - Tested FCU

This week I tested my drone FCU to see if all the sensors work and tuned the software to work with the MPU while I wait for the rest of my parts to arrive.
I ended up with code which could accurately read my Gyro, Accelerometer and magnetometer

# June 29 - July 9th - 22 Hours - Assembled and made the drone work

This week I recieved all my parts and started to fully assemble the drone, along the way I realised that my drone frame was a little too heavy and I wasn't able to make the drone work, After I went back and changed the drone frame to be lighter and 3D printed it on my 3D printer I was very delighted that my drones worked!

here is an image of my drones new frame:
<img width="760" height="642" alt="image" src="https://github.com/user-attachments/assets/3dfda1ec-3c19-4d82-801b-55eafe3812e0" />

However, sadly after assembling the 2nd drone which would fly, while testing it I forgot to turn off my ceiling fan and it flew into it, it was broken into pieces
<img width="3000" height="4000" alt="IMG_20260706_120405" src="https://github.com/user-attachments/assets/c6313b41-3b60-4d4f-86e2-b7f754f89329" />


# July 21st to July 31st - 10 hours - Drone broken once again!

So, When I was coming back from outpost + open sauce, American baggage handling kinda slammed my suitcase super hard and broke the drone inside out of it which was the only one that was working, after coming back I ordered some spare parts and attempted to fix my drone however it didn't work I tried my best to see if I could even get it to fly but it was to no avail

heres an image of my broken drone
<img width="3000" height="4000" alt="IMG_20260706_120405" src="https://github.com/user-attachments/assets/c6313b41-3b60-4d4f-86e2-b7f754f89329" />
# note that this image has been reused

# August 1st to August 10th - 15 hours - Different software

I tried different software like Betaflight and ESP-Drone but even they didn't work as well, I am trying my best and will take everything I learnt from this to design my own firmware

Once I tried to integrate my findings into my own software, I think that the problem may be with my repair parts as the drone was not powerful enough:

But for now I am pretty tired so I will be taking a short break before I try to make my drone work once again


# August 18th to 28th - 2 hours - New spare parts

I refined my software a little more to integrate failsafes while I wait for more spare parts to arrive, I changed the motor back to the original models as I found that the ones I currently have are very inefficient and not powerful enough

These are the spare parts I ordered:
<img width="1205" height="612" alt="image" src="https://github.com/user-attachments/assets/f46030ea-bf3a-4212-b8c7-40cda43315ae" />

# September 20th - 5 hours

I finally got the drone to work by swapping in the motors for a new pair, the problem were the motors all along as they were far too inefficient and did not deliver enough power.
here is a picture of the drone with the swapped out motors:
<img width="3472" height="4624" alt="drone" src="https://github.com/user-attachments/assets/bf246149-26de-4b6b-9ecd-d788485b884e" />





