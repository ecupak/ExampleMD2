## Summary
This is for a school project. The purpose of this repo is to share with classmates how to integrate and implement MD2 model loading and animations.

I used the beautiful MD2 model, shader program family, and vertex buffer object code from https://github.com/michalbb1/opengl4-tutorials-mbsoftworks.git. I have credited him in each of the used files per his license, but am new to this, so if there is something else I should add please let me know.

I used X11 and EGL to render the window. GLES 3.1 is used since this is intended to run on a RaspberryPi 4.

## Setup
This project is setup to run on WSL2 Debian. Please change the config to match your needs. You will at least need to change the username in the include path starting with '/home'.

You should have git clone'd stb and glm into the /home/<username>/ directory. You should have installed GLES and X11 into your WSL2 environment.

## Usage
Running the app will display an animated warrior model. Use left/right arrows to cycle through the animations.

Use W/S to move the camera forward/backward. Use Shift + W/S to move up/down. Use A/D to move left/right. Use Space + W/S to pitch up and down. Use Space + A/D to yaw left and right.


## Issues
Sometimes the input doesn't detect a key release and the camera will keep moving. Just press that input direction again to stop it. I'll fix it later.

This does not close gracefully. You will get a segmentation fault error once you close the window or stop the app. I'll fix it later.
