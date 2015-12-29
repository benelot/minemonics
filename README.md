# Minemonics (Alpha Stage, work in progress)

An open-source 3D virtual creature evolution simulator built with OGRE3D rendering engine in C++. For the Evolutionary Algorithm Shark machine learning will probably be used, furthermore MathGL (http://mathgl.sourceforge.net/doc_en/Website.html) and Igraph (http://igraph.org) for graph plotting, FFmpeg (https://www.ffmpeg.org/) for capturing video, Bullet3 for the physics and Boost for logging and testing. In the future, a library for Deep neural networks will also be needed.

Several aspects are taken with reference from Karl Sims (http://www.karlsims.com/) original paper called: ["Artificial Evolution for Computer Graphics"](http://www.karlsims.com/papers/siggraph91.html). But it is not a replication of that. Other aspects are taken with reference from [Lee Graham' 3D Virtual Creature Evolution](https://en.wikipedia.org/wiki/3D_Virtual_Creature_Evolution). But it is not a replication of that either. It just contains some aspects from each of them which I found to be very intelligently chosen. 

***



## Milestone 1: Genomic Structure

To evolve creatures in a population and alter them with the aid of evolutionary algorithms, it is necessary to have an encoding of the brain and body of the creature. The chosen genomic structure used in this project uses an indirect encoding. This means that the genome contains the structure of a creature in a compressed form and can only be transcribed by following the rules defined in the genome. 


## Milestone 2: Environments

The evolved creatures are preforming their tasks in a so called physics engine. The name is a bit misleading, as the framework does not simulate all physics that is going on but is built to simulate Newtonian Physics i.e. the classical mechanics of how rigid and softbodies interact and react to external forces. The interaction is reduced to the most important components that are usually necessary to keep the simulation runnable in real-time. For this simulation, several environments are implemented to observe the locomotion of creatures in different environments.

The first two basic environments are a plane which is entirely flat and a hills environment which automatically generates a hilly infinite environment that gets generated as creatures reach it.


## Milestone 3: Body model

The body model is created from general primitives such as cubes and capsules, which are connected together via joints. The joints in fact are motion constraints defined in the physics engine that restrict the motion of the primitive bodies in ways similar to classical mechanical joints. The joint defines which degrees of freedom are either fully locked or restricted to move only within a certain range of angle in case of angular joint movement or within a distance range in the case of linear joint movement. The body model defined in the physics engine is then graphically rendered into a visual model of the body to represent the creature's movements in the environment.

![Some of the first generation creatures](Minemonics/doc/presentations/%5B2015%5D%20Auditory%20Informatics/figs/creatures/Minemonics-05112015_184631057.jpg?raw=true "Some of the first generation creatures")

![Some of the first generation creatures](Minemonics/doc/presentations/%5B2015%5D%20Auditory%20Informatics/figs/creatures/Minemonics-05112015_190654362.jpg?raw=true "Some of the first generation creatures")

![Some of the first generation creatures](Minemonics/doc/presentations/%5B2015%5D%20Auditory%20Informatics/figs/creatures/Minemonics-05112015_190853660.jpg?raw=true "Some of the first generation creatures")

![Some of the first generation creatures](Minemonics/doc/presentations/%5B2015%5D%20Auditory%20Informatics/figs/creatures/Minemonics-05112015_190947481.jpg?raw=true "Some of the first generation creatures")


![Some of the first generation creatures](Minemonics/doc/presentations/%5B2015%5D%20Auditory%20Informatics/figs/creatures/Minemonics-05112015_191706383.jpg?raw=true "Some of the first generation creatures")

## Milestone 4: Evolutionary Algorithm

The genome of the creatures must have a certain scheme that can be modified via variability operators. The variability operators, as the name suggests, increase the variability within the population of creatures by generating new genomes. A simple variability operator is the mutator that simply changes a certain gene in the genome by changing some of the features randomly. The mutation can obviously render a gene useless by for instance decoupling it from the developmental process, so that it is never actually expressed. On the other hand, this can also improve the components encoded in the gene so that the resulting creature can perform better according to the measure of the fitness function.

## 2015-05-13 First presentation of the simulator at the Auditory Informatics Seminar
The presentation shows a the context the simulator works in, describes some of its features and shows some visuals of it. The feedback was generally very good, people were very interested in the project. Ruedi Stoop proposed that we would meet for the project in about two weeks to discuss the possibilities of it in the long run. The only reminder was that I should cite the pictures properly which is done but not with numbers at every pictures to make the slides very cluttered. But it will be done for the next presentation, maybe master's apero.

Topics covered in the talk:

* Are we alone in the universe?
* Simple limiter theory
* Methods
    * Evolving 3D creatures
    * Genetic language
    * Fitness evaluation
    * Evolution
    * Controller
    * Why is periodicity important?
* Meet \& Greet with the Creatures
* Outlook
    * Extensions: Evolutionary Algorithm
    * Extensions: Controllers
    * Other settings

Here is a link to the presentation: [Emergent gait periodicity in artificially evolved creatures on unknown terrains](Minemonics/doc/presentations/[2015] Auditory Informatics/Minemonics-AuditoryInformatics.pdf?raw=true)

(You need to download the figs folder as well, because otherwise you can not find the videos that are linked in the presentation)

Results from an early run showing the changes of an evolutionary step to another:
![A population of 6 creatures in 3 generations](Minemonics/doc/visuals/Milestone 4 - Evolutionary Algorithm/3Gx6I-Evolution.png?raw=true "A population of 6 creatures in 3 generations")

A population of 10 creatures were evolved of which 6 were chosen for the visualization to show their details.
The fitness function for creature selection is the number of limbs they have. The last in the row has obviously only one limb and is therefore rated the lowest by the fitness function. It therefore gets culled and replaced twice until it has more limbs.

## Milestone 5: Chaotic Systems and Simple Limiter Control

Chaotic Systems are dynamical systems that are highly sensitive to initial conditions. They show high variability because small differences in the initial conditions yield widely diverging outcomes which make long-term prediction impossible, even though the system is deterministic. Additionally the system shows topological mixing, which means that the system evolves over time so that any given region or open set of its phase space will eventually overlap with any other given region.

In chaotic control, approaches to control chaotic systems are designed. Their main goal is to stabilize periodic orbits. A strange attractor contains an infinite number of unstable, periodic orbits. Chaotic dynamics consists of a motion of the system state near one of these unstable orbits and stays in its neighborhood for a while, then reaches the neighborhood of a different unstable periodic orbit in which it remains for a limited amount of time and so forth. This results in a complicated and unpredictable wandering over longer periods of time. 

Many of those chaotic control approaches exist and generally model parts of the original system to control, thereby reaching sometimes even higher complexity than the chaotic system itself. This leads to a specification of the chaos control system and renders the control system useless when facing another chaotic system. Another difficulty is that for fast dynamics of certain systems, the perfect timing of the control signal is crucial and can generally not be achieved by a computational control system.

Simple limiter control on the other hand is based on an entirely different approach which might be more natural and general. 

Chaotic behavior can be seen in different natural phenomena such as weather and climate or neural circuits and computations. Our hypothesis relates to motor-control and states that complex oscillatory gait patterns can arise from only using chaotic control signals that are then either limited in the chaotic system space or the state space of the controlled limb.


<!---
## Milestone 5: Graphs and Data Logging

To be defined. Come back in May.


## Milestone 6: Experiments on Gait Periodicity
To be defined. Come back in May.


## Milestone 7: Sensory Feedback
To be defined. Come back in June.


## Milestone 8: Neural Controllers
To be defined. Come back in June.


## Milestone 9: Reinforcement Learning
To be defined. Come back in July.
-->

