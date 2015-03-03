CSC 305 - Assignment 2
Prepared by Paul Hunter
2015-MAR-02

The second lab base application was modified to support user interaction with a scene containing a single cube. User mouse movement is interpretted to adjust the position of the camera. THe camera itself tracks a point on the ground, the azimuth, elevation, and distance can be adjusted. Three buttons have been included to quickly snap to three arbitrary view points. 

Mouse Controls
--------------
Press and hold the Right Mouse Button to adjust the Azimuth with horizontal mouse movement, and the elevation with vertical mouse movement. Use the scroll wheel to dolly the camera towards and away from the cube in the scene. 

Implementation Details
----------------------
A single cube object consisting of 12 triangles we created on the origin of the world space. The XZ plane was used as the ground plane, upon which the cube sits, on the positive Y side of the surface. The Axes and ground plane are drawn in the scene. 

Viewing Transformations were created using the techniques covered in class and in the text. With the movement of the mouse, the camera attributes are updated and the transformation recalculated. The points of the cube are then translated to the screen of the current camera using this transform. Helper methods for matrix and vector operations were created where they did not exist in the Qt libraries. 




