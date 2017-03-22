# RBE4915
Collaborative robotics

## Industrial Robotics II: Collaboration

This document outlines a proposal for RBE 4915, Industrial Robots II: Collaboration; an Independent Study Project. The project has two main objectives of study: PLC and Industrial Collaborative Robotics. Primarily an opportunity for research into the use of the above, secondary objectives will include: investigating use of PLC for teaching, use of the RRP robot systems in Washburn, developing a collaborative system with sensor suite onboard the robot. This project was developed out of personal curiosity and subject matter interest.

Industrial robots are typically very dangerous to operate around humans, and as such find themselves behind walls or light fences designed to separate the two. "Hard robots" currently installed in factories and workcells everywhere are especially dangerous when compared to “soft robots.” Where the soft versions are designed to work next to people with plastic shells and force limiting actuators, “hard robots” are designed to be big, bad, and dangerous. Finding a way to interface the safety of soft robots with the ease of integration of hard robots is key to bringing humans and robots closer together.

## Objectives

### PLC

In Washburn shops there are approximately four discrete industrial robotic systems: the ABB IRB 1600, the Fanuc M710, the Fanuc LR Mate 200, and two Adept RRP arms. The Adept robots are not fully operational yet, but all other systems are fully functioning. A goal of this project would be to attempt to bring the RRPs online.

At present, it seems that the Adept robots are only lacking a 24v power supply that has been acquired by Professor Putnam. Hopefully, upon installation of this power supply the arms should be able to be controlled and actuated fully. Introduction to the RRP robots will be required as with the PLC, as with any system I am sure they have their own programming language and constraints. Introduction to a new robotic system could be demonstrated by a basic pick and place application as is typical for learning such devices. 

Finally, integrating the Adept robots with the PLC will bring the two technologies together. I expect that establishing communication between the two devices will be a major challenge here. Integration between older devices of different manufacturer is, in my experience, a challenging endeavor in the best of cases; with these industrial-designed systems too, the type of online assistance typically available with open source technology likely won’t be present. The bridge here is important to interface the robots with the sensor suite associated with the final part of the course.

### Industrial Robots

Learning the basics of PLC is a first step to being comfortable with their application. Beginning with the controllers will mean the basics first, connecting to the devices and producing functions of "hello_world" type. An obvious choice will be to use the devices currently attached to the Fanuc Robot in WB108, assuming that space can be made to share with the current students working with the robot. Starting will be a key step for me to become acquainted with a new tool, and can lead into the second section of the PLC work.

The second step with PLC will be to create a brief curriculum for students to use to become familiar with the devices and their use. WPI’s Lehr und Kunst motto emphasizes the theoretical and the practical; a major portion of the curriculum, therefore, should focus less on *how* to use PLC and more on *when *to use them. Labwork, can be focused on how to use PLC, with brief introduction into their use, and some instruction on how to perform basic tasks. I’ve both never constructed coursework, nor used PLC, so the end result may require refinement or animal testing before application to actual student. 

The final step will be to integrate PLC into the final project of the course, a collaborative robotic system. Using PLC as an interface between the robot and the sensors onboard will be a key experiment and practice in integration between the three classes of device. 

### Collaboration

The final part of the project is the blend of the first two sections, using the PLC to direct the actions of the RRP arms. The goal is to have two types of collaboration with the arms, robot-robot and robot-human. The biggest goal is to achieve a safe robot human collaboration, giving the robots a sensorsuite to detect human presence, and directing them to safely interact with the human. As a demonstration, one of the robots will accept an object given by a person and pass it to the second robot who will then return it to the human. Interaction at any point of the process will result in the system making itself safe for the person’s presence. 

The sensor suite required for the robots is still undecided. Several solutions have been recommended, but further research is required. The three current options for proximity detection are: 

* Vision 

* RADAR 

* SONAR 

* Infrared Reflection

It is unclear yet which would provide the best solution, but there are several factors to keep in mind: price, ease of integration, and feasibility. 

First, funding is expected to be scarce here, as there is no official sponsor for this project; possibly finding funding within the robotics department is a possibility, but likely not one that can be counted on. Keeping things cheap or finding a donor is key. 

Second, ease of integration is a high priority. The purpose of this project is not to learn how to write a vision system for detecting the proximity of humans to a robot. Keeping things focused will mean finding the right solution that is within reach of the person doing the task. 

Finally, the sensors will also have to work. That is to say that they will have to be able to actually determine if a person is within a working distance of the robot, and be able to relay that to the PLC.

## Criteria of Completion

Details on the actual implementation are yet to be decided, but following the above guidelines will hopefully produce a demonstration and research into the feasibility of robotic collaboration with "hard robots." Demonstrating experience with PLC and industrial collaboration are key to completion, and producing progress towards the final goal an important indication of that. There are significant roadblocks in this project, and with only seven weeks to complete it will be a challenge to keep pace. It’s an exciting premise, but also a very advanced sprint into a field dominated by teams of skilled roboticists; my hopes are high, but remain realistic. 

