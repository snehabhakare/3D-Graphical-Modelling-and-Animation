# Music Box - Modelling (Phineas and Perry)

## Team members:
Sneha Bhakare - 150050040, Sukanya Bhattacharjee - 174050012

## Youtube link:
https://www.youtube.com/watch?v=p9IwyA2sZ44

## Disclaimer
The code in the repository is completely our work and not copied from any where. The tutorials 5,6 and 7 codes are used as the basecode. Online reference used for saving frames as PPM files.

## Key Controls

1. ESCAPE - close the window
2. I/i 
- switch from inspection(global rotation about object's centroid) to individual(individual model rotation) mode and vice versa
- to get back the objects in view frustrum in case they go out of view after certain transformations
3. G/g - cycle between Light 1, Light 2, or both being on/off
4. P/p - enable/disable perspective, by default perspective is enabled
5. F/f - delete last control point
6. Left mouse click - set a control point
7. Enter - save configuration of keyframe
8. SpaceBar - play the animation
9. Minus - play camera animation
10. Equal to - cycle between render/not render camera path
11. Tab - to save the animated frames

| Keys    | Global Mode (Rotation of all the models)     | Individual Mode (Translation of camera)   |
|---------|----------------------------------------------|-------------------------------------------|
| A/a     | anticlockwise global rotation in x-direction | increment translation value in x direction|
| D/d     | clockwise global rotation in x-direction     | decrement translation value in x direction|
| Z/z     | anticlockwise global rotation in y-direction | increment translation value in y direction|
| C/c     | clockwise global rotation in y-direction     | decrement translation value in y direction|
| S/s     | anticlockwise global rotation in z-direction | increment translation value in z direction|
| X/x     | clockwise global rotation in z-direction     | decrement translation value in z direction|

Individual Rotation Mode: Select one model at a time for inspection

| Keys     | Select Model as Current Model (Select root node as current node) |
|----------|------------------------------------------------------------------|
| B/b      | Box                                                              |
| N/n      | Phineas                                                          |
| M/m      | Perry                                                            |
| V/v      | Door                                                            |

| Keys     | Translation Controls for Current Model (Root node should be selected as current node) |
|----------|--------------------------------------------|
| J/j      | decrement translation value in y direction |
| U/u      | increment translation value in y direction |
| H/h      | decrement translation value in x direction |
| K/k      | increment translation value in x direction |
| O/o      | decrement translation value in z direction |
| L/l      | increment translation value in z direction |

| Keys     | Select current node (current Model should be Box) | 
|----------|---------------------------------------|
| 0        | Box Body                              |
| 1        | Box Lid                               |

| Keys     | Select current node (current Model should be Perry) | 
|----------|----------------------------------------------|
| 0        | Body                                         |
| 1        | Left Thigh                                   |
| 2        | Right Thigh                                  |
| 3        | Left Upper Arm                               |
| 4        | Right Upper Arm                              |
| 5        | Tail                                         |

| Keys     | Select current node (current Model should be Phineas) | 
|----------|------------------------------------------------|
| 0        | Body                                           |
| 1        | Left Thigh                                     |
| 2        | Left Leg                                       |
| 3        | Left Foot                                      |
| 4        | Right Thigh                                    |
| 5        | Right Leg                                      |
| 6        | Right Foot                                     |
| 7        | Torso                                          |
| 8        | Left Upper Arm                                 |
| 9        | Left Lower Arm                                 |
| Q/q      | Left Hand                                      |
| W/w      | Right Upper Arm                                |
| E/e      | Right Lower Arm                                |
| R/r      | Right Hand                                     |
| T/t      | Neck                                           |
| Y/y      | Head                                           |

| Keys     | Rotation Controls for current node |
|----------|------------------------------------|
| LEFT     | decrement rotation value in y direction |
| RIGHT    | increment rotation value in y direction |
| UP       | decrement rotation value in x direction |
| DOWN     | increment rotation value in x direction |
| PAGEUP   | decrement rotation value in z direction |
| PAGEDOWN | increment rotation value in z direction |
