--------------------------
Getting Started 
--------------------------

Welcome to Samurai 2 - a 3D sword-fighting game. Blog post: (https://gregorykimball.me/2014/01/15/samurai-ii/)

This game is based on a free-motion sword-fighting concept and uses an engine based on tutorials 
from Rastertek (http://www.rastertek.com/tutdx10.html).

Requires DirectX Software Development Kit.  Tested with "DXSDK_Jun10.exe" 
from microsoft.com but more recent versions may work as well.

Recommend building with Visual Studio Community (tested with 2019, version 
16.3.4).  

The texture mapping and 3d object pipeline is based on Blender "https://www.blender.org/"
and uses a custom vector format with normals included.

"Arte_of_Defence" project includes the game code
"OBJ_Importer" project contains converters for Blender models into game models
"arduino sword" contains code for an Arduino accelerometer to control sword position


--------------------------
Troubleshooting
--------------------------

You may encounter "S1023" error when you install the DirectX SDK (June 2010).  
This means that you have a later version of "Microsoft Visual C++ 2010 Redistributable"
installed on your computer.  See:
https://support.microsoft.com/en-us/help/2728613/s1023-error-when-you-install-the-directx-sdk-june-2010



--------------------------
What to do in game
--------------------------


Press "g" to spawn team 1 characters.
Press "h" to spawn team 2 characters.
Use "[" and "]" to switch the active character controlled by the user.

Move with QWEASD, swing the sword with the mouse.




--------------------------
Credits
--------------------------


Chap Percival for teaching us the tutorial library "DrawBox" in C++.  
(https://gregorykimball.me/2014/01/02/samurai/)

Shiva Raisinghani for telling me to clean up this project.
