CSC 305 - Assignment 1
Prepared by Paul Hunter
2015-FEB-13

The second lab base application was modified to support the creation and transformation of polygons on a 2D plane. This short document will outline the controls and functionality included in the application. Upon running the application all controls are visible along the right side of the pane. 

Getting Started with the App
-----------------------------
[BUTTON] Create Polygon / Finish Polygon
Clicking Create Polygon will enable the canvas, shown as a black square to the left, to draw new polygons. After clicking it, left click on the canvas to add a vertex to the new polygon. Polygons have no minimum number of vertices, so this tool may also be used create lines and vertices simply by ending the polygon by clicking Finish Polygon which appears after starting a polygon. Polygons are all added to the same spatial reference regardless of the state of the work stack. 

[BUTTON] Clear Polygons
Use this button to clear all polygons from the canvas area. If you're in the midst of drawing a new polygon this button will cancel and remove your current work. 

[CHECK BOX] Apply Transformations
Use the control to toggle the application of the current transformation stack. The canvas will update to reflect these changes. 

[TEXTBOX ARRAY] New Matrix
These fields can be used to input the elements of a transformation matrix as integer or fractional numbers. 

[BUTTON] Push
Validate and push the user defined matrix onto the work stack. The input matrix array will be updated back to the identity matrix and the Result Transform will also be updated on screen. The canvas area will update to show the affect of the additional transform as well. 
If a value could not be parsed in the matrix entry form, the offending text box will be highlighted in red and the focus set for editing. If this occurs, correct the value and press push again. Note, identity matrices cannot be pushed onto the stack. 

[BUTTON] Pop
Pop the last matrix pushed onto the matrix out of the stack. This matrix will be placed in the input form for editing and can be pushed back onto the stack afterward. The change will also be reflected in the result matrix UI and canvas area.

[BUTTON] Clear Stack
This command will empty the work stack, returning the polygons to their original reference on screen. 

[TEXTBOX ARRAY] Resulting Transform
These text boxes, which are not editable, are used to display the currently final transform which is applied to each polygon, line, and vertex. When nothing is present in the stack, it will read as an identity matrix. 

Implementation Details
----------------------
The spatial reference from the original lab OpenGL widget was used, and all polygons were stored in this reference. When creating new polygons the mouse coordinate would be translated to this system using the inverse of the currently transformation. Each polygon is stored as a QVector, a dynamic array, containing QVector3D objects for each vertex. Random RGB colours are generated for each polygon and stored in a companion QVector list of a three element QVector. 
 
Helper methods were created to allow for the creation of inverse matrices and multiplication of vectors to matrices. Additional helpers were written to draw vertices and lines, these two were used in combination to draw polygons. Although not originally intended, it was simply enough to handle cases of polygons with less than three points, which was then added as a feature to allow the drawing of lines and points. 

A stack was used to store the transformations. An empty work stack actually contains a single identity matrix. The top of the stack always contains a matrix that is the resulting transform of current matrices in the stack. When a new matrix is pushed onto the stack, the result is popped off the top (or peeked if 'empty'), the new matrix is pushed onto the stack, and result is updated by multiplying it by the new matrix, and then pushed back onto the stack. 

When a matrix is popped off the stack, assuming its not empty, the result is popped off the stack, as is the matrix under it, call it A, the result is then multiplied by the inverse of A and pushed back onto the stack. Matrix A is then returned to be placed in the Input fields.

There are no limits (except memory) on the number of polygons or transformations that can be created. 

 


