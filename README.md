# NoC Pin-Accurate SystemC Performance Model 

## NoC Basics

This project demonstrates a pin-accurate 4x4 NoC (Network on chip) with mesh topology. Following diagram illustrates a typical mesh topology where nodes are arranged in a rectangular fashion (typically a square). Each node on the NoC is a Processing Element (PE). A PE is basically a chiplet. It could be a CPU core, Memory Controller, Accelerators, etc. These PEs are connected to each other using routers. Routers job is to transmit packets from source node to the destination node across this mesh. Routers take care of sending the packet on correct port as per the destination. There are many routing algorithms that can be used to enhance the design. 

A packet is split into multiple chunks called Flits. First flit is called head flit, followed by payload flits and tail flit as shown below.

Routers are connected to 4 other routers in 4 directions as North, East, South and West. The 5th connection of the router is with its home node (Local node). 


## Building this project

This project utilizes CMake inorder to build. I assume that your enviornment has been setup using SystemC+WSL+VSCode set up that I have explained in previous post [here](https://pgudadhe.github.io/).
Follow the steps in these articles to build the model.

## Implementation

I recently came across an interesting class project offered in Computer Engineering course at Toronto Metropolitan University. They have laid all the important framework for implementing such ecosystem. I took the reference of this project to create this NoC model. I would recommend reading it in details [here](https://www.ee.torontomu.ca/~courses/coe838/).

## Running the model

Upon running users would be prompted to enter source and destination nodes as below. It would also ask the simulation time.

```bash
        SystemC 3.0.1-Accellera --- Jul 23 2025 08:22:58
        Copyright (c) 1996-2024 by all Contributors,
        ALL RIGHTS RESERVED
Enter source node [0:15]: 3
Enter Destination node [0:15]: 15
Enter simulation duration [in nanoseconds. 1000ns for 47 packets]: 1000
```
Once entered it would start running the model and in the end show how the packets were routed across which nodes and how many packets were transmitted and received. 

```bash
...
                        New Pkt:  1027 is received from source: 3 by sink:  15
New Pkt: 1028 is sent by source: 3  to Destination:   15
3 -> 7 -> 11 -> 15 -> 
                        New Pkt:  1028 is received from source: 3 by sink:  15
New Pkt: 1029 is sent by source: 3  to Destination:   15
3 -> 7 -> 11 -> 15 -> 
...
---------------------------------------------------
Simulation ended...
Total Tx: 47
Total Rx: 47

```

## Future Enchancements

Currently this project only supports single source and single destination. I am planning to add multiple source and destinations so that we can have parallel traffic flowing across the whole mesh system creating some interesting arbitration and routing scenarios.

