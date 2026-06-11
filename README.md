# Drone Swarm

This is a group of 2 drones which are autonoumously controlled by a ground controller to fly in specific patterns, the drone swarm will have 2 drones (this is expandable) and a ground controller, They ground controller will supply instructions to the drone on how to fly and where to fly, The drones will you use their Accelerometers, Gyroscopes and magnetometers to carry out these instructions and fly in a pattern.

# How does it work?

The drones are individually controlled by an onboard flight controller, Each flight controller is connected to the ESP32-S3 ground station which supplies commands to the drones for them to perform it. The ground station recieves input data on the drones location, height and distance from each other from 2 phones, one under and one below which track the the drones. this allows the ground station to have accurate locations for the drones and direct them individually!

The ground station is currently a bare ESP32-S3 DevBoard which is connected to my computer, It features nothing special but it does connect to both drones in a shared connection to supply commands to them. The commands have id's so so the both drones will not follow the same command. There is no case to increase connection strength as the connection won't be blocked by the plastic

# How is it powered

The ground station is connected to my computer and that how it recieves power, The dones have an onboard Lithium-Ion battery at 3.7v to power them for roughly 4 -5 minutes of flght time!

# Why I made this?

I made this as it links to my passion in aviation and I think it is a great way to get started with autonomous flight!

# Schematics
<img width="2160" height="1533" alt="Screenshot 2026-06-09 202325" src="https://github.com/user-attachments/assets/557283d4-4eaf-4d81-bb28-c01b16bdfae1" />

# PCB
<img width="956" height="1135" alt="Screenshot 2026-06-09 202235" src="https://github.com/user-attachments/assets/00250a64-975c-41f8-a788-47a9add87944" />

# PCB rendered
<img width="1045" height="1168" alt="Screenshot 2026-06-09 202305" src="https://github.com/user-attachments/assets/a1aca1ad-8325-4631-b1d0-e0734473bf18" />
<img width="1144" height="1249" alt="Screenshot 2026-06-09 202247" src="https://github.com/user-attachments/assets/b165dcf1-74bc-42ac-bf39-e81ed53cf22d" />

# Drone frame
<img width="1026" height="961" alt="Screenshot 2026-06-10 102537" src="https://github.com/user-attachments/assets/af2d47c8-a085-4b7b-9e79-24a63d60db90" />

# Assembled view
<img width="1680" height="1277" alt="Screenshot 2026-06-10 102524" src="https://github.com/user-attachments/assets/3b04ce50-7d2b-47ad-8b5c-6b01c6d08be4" />

# Note for reviewer
The PCB in my assembled view doesn't contain any 3D files for the components as freeCAD would not let me export the components it gathered from my raw PCB file.
The board is also 4 layers and has components on both sides

Lapse also wasn't working for a big part of the design so I wasn't really a record a ton. I only got the first ~1h20mins

Using JLCPCB to 3D print my drone frame as it is in ABS, If I can't use JLC3DP I'll try to find someone through printing legion
