Minemonics
==========

An open-source 3D virtual creature evolution simulator built with OGRE3D rendering engine in C++. For the Evolutionary Algorithm Shark machine learning will probably be used, furthermore MathGL (http://mathgl.sourceforge.net/doc_en/Website.html) and Igraph (http://igraph.org) for graph plotting, FFmpeg (https://www.ffmpeg.org/) for capturing video, Bullet3 for the physics and Boost for logging and testing. In the future, a library for Deep neural networks will also be needed.

Several aspects are taken with reference from Karl Sims (http://www.karlsims.com/) original paper called: ["Artificial Evolution for Computer Graphics"](http://www.karlsims.com/papers/siggraph91.html). But it is not a replication of that. Other aspects are taken with reference from [Lee Graham' 3D Virtual Creature Evolution](https://en.wikipedia.org/wiki/3D_Virtual_Creature_Evolution). But it is not a replication of that either. It just contains some aspects from each of them which I found to be very intelligently chosen. 

***

**Milestone 1: Genomic Structure**

***

To evolve creatures in a population and alter them with the aid of evolutionary algorithms, it is necessary to have an encoding of the brain and body of the creature. The chosen genomic structure used in this project uses an indirect encoding. This means that the genome contains the structure of a creature in a compressed form and can only be transcribed by following the rules defined in the genome. 




**Milestone 2: Environments**

***

**Milestone 3: Body model**
***

**Milestone 4: Evolutionary Algorithm**

The genome of the creatures must have a certain scheme that can be modified via variability operators. The variability operators, as the name suggests, increase the variability within the population of creatures by generating new genomes. A simple variability operator is the mutator that simply changes a certain gene in the genome by changing some of the features randomly. The mutation can obviously render a gene useless by for instance decoupling it from the developmental process, so that it is never actually expressed. On the other hand, this can also improve the components encoded in the gene so that the resulting creature can perform better according to the measure of the fitness function.
***

**Milestone 5: Graphs and Data Logging**
***

**Milestone 6: Experiments on Gait Periodicity**
***

**Milestone 7: Sensory Feedback**
***

**Milestone 8: Neural Controllers**
***

**Milestone 9: Reinforcement Learning**
***
