# Minemonics

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

