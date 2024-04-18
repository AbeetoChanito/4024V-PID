# Writing Autonomous Routines

## Where to Write Autons
Autonomous routines are written in the files in `src/autons/*` directory, which the function in each file corresponding to its autonomous routine.

## How to Write Autons
Each auton function (drive, turn, swing) has it's own function on the chassis object. They can be called like this:

```cpp
chassis.turn(90); // turn to a heading of 90 degrees
chassis.move(25); // move forward/backward the specified distance
chassis.swing(45, SwingType::LeftSwing); // swing using the specified side of the drivetrain
```

## Using Headings

The starting heading can be specified like this:
```cpp
chassis.setHeading(315); // start at 315 degrees
```

The special things about headings in this codebase is that a full revolution does not come back to 0 degrees. Instead, the heading simply increases by 360 degrees. This can allow for special turns. Here are a few examples of this behavior:

```cpp
// example 1: 90 degrees clockwise
chassis.turn(90);

// example 2: 270 degrees clockwise
chassis.turn(270);

// example 2: 90 degrees counterclockwise
chassis.turn(-90);
```