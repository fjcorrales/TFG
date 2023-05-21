In this folder is kept the final result of the TFG. 
You can find the DronePawnCom, the .cpp and .h files, which compose the pawn created for Unreal Engine 5. 
Also you can find the ros2_package, which contains the files of the ros2 project of the publisher and the talker nodes. IMPORTANT, this project must be compiled before the execution of the gamemode with the pawn, as it needs the library of the listener.

**On that note, there are some strings that may need to be changed inside the DronePawnCom.cpp file, as in here there is a dlopen, where the path to the library mentioned before must be written and is personal to each computer.

 Apart of all these, there is also a folder with a mesh of a drone to use in the blueprint and a coordinates.txt which contains a samll set of coordinates to send via the talker. Important remark, the talker takes the coordinates from a file which you must set the path to.
 
 On the topic of importing this to an Unreal project, the safest option is to create a pawn in your project and copy the code inside the DronePawnCom.cpp and .h files. Once that is done, import the mesh, create a blueprint instance of your pawn and set the mesh component of the blueprint to the desired mesh. Also you might need to set the blueprint as the default pawn of the level in order for it to function correctly. This must be done through code inside the gamemodeBase file of your project. On the .h create a constructor function and on the .cpp set the default pawn as the blueprint created. 
