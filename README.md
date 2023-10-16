# Santa's Workshop Simulation - A POSIX Threads (pthreads) Project

In this project, we created a Santa's Workshop simulation using POSIX threads (pthreads). The simulation involves the operation of Santa's workshop with limited resources and various gift types. The goal is to ensure a safe and deadlock-free environment for gift manufacturing, customization, and delivery.

## Part I - Santa's Workshop Simulation

### Overview
- The simulation operates in real-time using a specified time unit (t = 1 second).
- Gifts of different types arrive at the workshop with specific processing requirements.
- Elves (Elf A and Elf B) and Santa perform various tasks.
- Task prioritization ensures efficient handling of gift processing.
- Each task has a specific time duration (e.g., painting, assembly, packaging, delivery, and QA).
- Command-line argument `-s` specifies the total simulation time (e.g., `-s 200` for 200 seconds).

### Gift Processing
- Gift requests arrive at the workshop every t seconds, based on probabilities.
- Different gift types (1 to 5) require specific tasks.
- Task sequences for gift types 1, 2, and 3 are strictly one after the other.
- Gift types 4 and 5 allow concurrent QA with painting or assembly.

## Part II - Preventing Starvation

- Initially, part I may cause QA tasks to starve, as Santa prioritizes delivery.
- To prevent starvation, a solution is implemented for QA tasks.
- Santa performs QA if one of the following conditions is met:
  - No more presents are waiting to be delivered.
  - Three or more GameStations are waiting for QA.

## Part III - Priority for New Zealand

- To address the urgency of gift requests from New Zealand, every 30t (t = 1 second) New Zealand requests are given priority for processing.

## Keeping Logs

- A log is maintained to track events and worker activities.
- The `events.log` file records task and gift details, such as task type, time, and turnaround time.
- Logs help with debugging and understanding the efficiency of Santa's plan.

## Implementation

- We are provided with starter code outlining the project structure, but we are free to make changes as needed.
- Queues are used to manage tasks and gifts.
- Random number generation is used to simulate gift arrivals based on specified probabilities.
- Each worker (Elves A and B, Santa) is represented as a separate thread.
- Pthread synchronization mechanisms, including semaphores, mutexes, and condition variables, are used for coordination.
- The project is developed incrementally, starting with simple scenarios and adding complexity to ensure no deadlocks or race conditions.
