# To-do list

Here is a list of important tasks to do to have a fonctional Starcraft bot. Those implies that the skeleton of the bot loop is already in place, but it might be slightly modified if deemed appropriate.

## Behavious Trees

We will basically need to decide how to create and attribute Behavious Trees. It might depend on the situation (e.g. making a static method for the IDLE manager's BT), but having a class collecting generic BT and using pointer of those might be the easiest.
It's an **essential** task for now as it will be used for almost all the other tasks.

## PMRBot


 - [x] (**Essential**) Develop a task attribuer algorithm.
 - [x] (**Essential**) Create UnitAgent on Unit creation.
 - [ ] Communicate useful events to the event manager.
 - [ ] Develop the IDLE manager.

## Task
 - [x] (**Essential**) Create a few basic tasks for testing.
 - [ ] (**Essential**) Implement the different conditions and actions for the tasks
 - [ ] Decide on a reward estimation algorithm.

## Task emitters
 - [x] (**Essential**) Create a basic task emitter for testing (e.g. scouting).
 - [ ] Decide on a role repartition for the different TEs.
 - [ ] Develop all necessary TEs.

## Units agents
 - [x] (**Essential**) Develop a unit execution method handling fleeing, working and idling.
 - [ ] Develop a BT deciding if the UnitAgent should flee.
 - [ ] Decide on a balancing for unit interest in tasks.
 - [ ] Develop the `computeInterest()` method.

## Event manager

The event manager is empty for now. It should be done but only once the other basic task emitters have been implemented, as it might need a lot of edge-case work and won't be useful for basic integration and tests.
That said, here are the important task:
 - [x] Task completion (NOTE: handled by every task emitter instead).
 - [ ] Mobile unit death.

After that, here are other useful features:
 - [ ] Enemy unit apparition.
 - [ ] New unit creation (building evolution for instance).
 - [ ] Building unit destruction.