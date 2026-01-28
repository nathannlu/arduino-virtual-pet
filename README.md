# Arduino Virtual Pet Game (Tamagotchi clone)

A virtual pet game running on Arduino Nano.
This repository contains code, 3d printing files, and game assets used in the project.

<div style="display: flex; flex-wrap: wrap;">
  <img alt="Arduino Tamagotchi" style="width: 49%;" src="https://github.com/user-attachments/assets/8d030368-10ca-4c6f-8679-de727097fbb4" />
  <img alt="Arduino Virtual Pet" style="width: 49%;" src="https://github.com/user-attachments/assets/44e9c6cb-5013-44df-86aa-639f2e07e491" />
</div>


### Video Demo

https://github.com/user-attachments/assets/822a2750-46d9-452c-813a-99ff8e9d6c07

## Resources
- <a href="https://github.com/nathannlu/arduino-pet/tree/main/stl">3d printing files</a>
- <a href="https://github.com/nathannlu/arduino-pet/tree/main/sprites">Game assets</a>

Note:
You can use https://javl.github.io/image2cpp/ to convert the .svg in
the sprites folder into bitmap images, then paste the output into
PetGame/Sprites.h


## Build

### Circuit diagram
![circuit diagram](https://github.com/user-attachments/assets/b1bf57c7-741f-485d-920c-ca338eda14b1)

### 3D printed enclosure assembly instructions
1. Hot glue the buttons (button.stl caps on 12mm buttons) onto the button holder.stl's bridge
2. Hot glue the button holder.stl onto the top of box.stl
3. Add the main circuit, solder the buttons to the circuit, then hot glue the box lid.stl onto box.stl
4. Hot glue battery holder.stl to the back of box.stl

![3d printed parts diagram](https://github.com/user-attachments/assets/52d7e54c-fe36-4c63-81ff-954491c958f0)
