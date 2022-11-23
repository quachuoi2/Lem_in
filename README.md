# Lem_in

Lem_in is a network flow algorithm project. 

## Objective

Distribute the data (ants) via nodes (rooms) within a network graph (ant farm) using the minimum amount of steps needed.

Rules:

- The ants start at the beginning room (source), and must all go to the end room (sink)
- Each room can only hold one ant at a time, meaning the room must be empty before a new ant moves in (except for the sink)
- For every turn, each ant can only move exactly once. A turn is displayed on a single line in the output

## Input

The input must follow the exact order as follow:

- number_of_ants
- rooms x_coodinate y_coordinate
- links

## Output

Each line displays one turn. For every turn, only the ants that moved are displayed, and in the following format:

L(ant_name)-(room_name)

## Installation

`make`

`./lem-in < "map_name"`

## Example

![map2](https://user-images.githubusercontent.com/78841468/203453511-a215448a-9a09-4743-bfa4-79458e2e618c.png)

![3](https://user-images.githubusercontent.com/78841468/203452566-df2f597d-960a-4b69-89d1-192a7f937ce0.gif)

![4](https://user-images.githubusercontent.com/78841468/203452581-a5b741af-c023-4bb0-871f-807329083ace.gif)

