Cyrus FPS Assignment

A simple Unreal Engine C++ FPS prototype where the player shoots boxes that are spawned dynamically using data from a remote JSON file. Each box has different properties such as color, health, and score value.

The project demonstrates gameplay programming, JSON parsing, HTTP requests, actor spawning, and UI updates using Unreal Engine C++ and Blueprint.
________________________________________________________________________________________________

Features

Gameplay

First-person player shooting system using Line Trace

Target boxes with health and score values

Boxes are destroyed when health reaches zero

Score is awarded when a box is destroyed

Dynamic Data System

Box types and spawn positions are loaded from a remote JSON file

JSON is fetched using Unreal Engine's HTTP module

Data parsed using FJsonObject and FJsonSerializer

Visual System

Box colors are dynamically applied using Dynamic Material Instances

Boxes scale, rotate, and position based on JSON transform data

UI System

Real-time score display

Score updates when boxes are destroyed

________________________________________________________________________________________________


Project Structure

Source/

BoxSpawner.cpp / BoxSpawner.h

TargetBox.cpp / TargetBox.h

BoxSpawner

Responsible for:

Fetching JSON data using HTTP

Parsing JSON

Spawning boxes dynamically

Applying type data to spawned boxes

TargetBox

Represents the destructible box.

Handles:

Health system

Damage logic

Score reward

Dynamic material color

________________________________________________________________________________________________

JSON Data Format

The project reads data from a JSON file structured like this:

{
"types": [
{
"name": "Red",
"color": [255, 0, 0],
"health": 3,
"score": 10
}
],
"objects": [
{
"type": "Red",
"transform": {
"location": [0,0,100],
"rotation": [0,0,0],
"scale": [1,1,1]
}
}
]
}

types

Defines box properties:

color

health

score value

objects

Defines spawn data:

type reference

transform information

________________________________________________________________________________________________

Core Gameplay Flow

Game Start
↓
HTTP request fetches JSON data
↓
JSON parsed into box types
↓
Objects array processed
↓
TargetBox actors spawned
↓
Player shoots box
↓
Box takes damage
↓
Box destroyed
↓
Score awarded
↓
UI updates

________________________________________________________________________________________________

Key C++ Systems
HTTP Request

Uses Unreal's HTTP module to fetch JSON.

JSON Parsing

Data is parsed using:

FJsonSerializer

FJsonObject

TJsonReader

Actor Spawning

Boxes are spawned dynamically using SpawnActor.

Damage System

Each box handles its own health through the function:

TakeBoxDamage(int32 DamageAmount)

If health reaches zero the box is destroyed and returns a score value.

________________________________________________________________________________________________

Technologies Used

Unreal Engine 5

C++

Blueprint

HTTP Module

JSON Parsing

Dynamic Materials

________________________________________________________________________________________________

How to Run the Project

Clone the repository

git clone https://github.com/YOUR_USERNAME/CyrusFPSAssignment.git

Open the .uproject file in Unreal Engine 5

Compile the project if required

Press Play

Shoot the boxes to destroy them and gain score

________________________________________________________________________________________________

Future Improvements

Possible improvements for this project:

Sound effects when hitting targets

Particle effects on box destruction

Improved UI design

Local JSON fallback if HTTP request fails

Weapon recoil or firing effects

________________________________________________________________________________________________

Author

Created as part of a game developer internship technical assignment.

________________________________________________________________________________________________

License

This project is intended for educational and evaluation purposes.
