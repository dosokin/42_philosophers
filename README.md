# Philosophers

Implementation of the classic *Dining Philosophers* concurrency problem, developed as part of the 42 School curriculum.

## Overview

The goal of this project is to solve the **Dining Philosophers problem**, a classical synchronization challenge illustrating issues such as race conditions and deadlocks.

Multiple philosophers sit at a table and alternate between thinking, eating, and sleeping. Each philosopher needs two forks to eat, which must be shared with neighboring philosophers.
The implementation must ensure correct synchronization between threads while preventing deadlocks and starvation.

## Tech Stack

* C
* POSIX Threads (pthreads)
* Mutexes
* Makefile

## Features

* Multithreaded simulation of philosophers
* Fork synchronization using mutexes
* Timing management for actions (eat, sleep, think)
* Detection of philosopher death
* Deadlock prevention

## Learning Outcomes

* Multithreading with POSIX threads
* Thread synchronization using mutexes
* Avoiding race conditions
* Deadlock and starvation prevention
* Managing concurrent simulations
