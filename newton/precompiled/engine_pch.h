/** \file engine_pch.h
 *  \mainpage Newton Physics Engine Documentation
 *
 *  \section intro_sec Introduction
 *
 *  Welcome to the Newton Physics Engine, a lightweight and efficient physics engine designed for 2D simulations.
 *  This engine provides a robust set of tools for handling rigid body dynamics, collision detection, and resolution
 *  among common geometric shapes like circles and oriented bounding boxes (OBBs).
 *
 *  \section features_sec Features
 *
 *  - Rigid Body Dynamics: Manage the physical behavior of objects with support for both dynamic and static bodies.
 *  - Collision Detection: Efficient algorithms to detect collisions between circles and OBBs.
 *  - Collision Resolution: Realistic physical responses after collisions using impulse-based resolution.
 *  - Material Properties: Customize objects with properties such as mass, restitution, and friction.
 *  - Scene Management: Organize and manage various objects within a scene to simulate complex interactions.
 *
 *  \section structure_sec Engine Structure
 *
 *  The engine is structured around several key components:
 *  - \b Shapes: Fundamental geometric forms like `Circle` and `OBB` that define the physical boundaries of objects.
 *  - \b RigidBody: Core component that adds physical properties to shapes, allowing them to participate in physics simulations.
 *  - \b CollisionUtility: A utility class that encompasses all collision detection and resolution logic.
 *  - \b Scene: A container that holds and manages multiple rigid bodies and resolves their interactions based on physics laws.
 *
 * 
 *
 *
 */


#pragma once

#include <iostream>
#include <string>
#include <memory>


