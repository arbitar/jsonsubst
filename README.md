# jsonsubst

Tiny C program that takes text in from stdin, replaces {{ key.name.tokens }} with data from a JSON file (passed by argument), and outputs the result.

## Usage
Very simple. One argument: JSON file.

`./jsonsubst data.json <input.txt >output.txt`

Or, in a pipeline of some kind...

`cat input.txt | ./jsonsubst data.json | tee output.txt`

## Notes
No runtime dependencies, so it should run anywhere. Which means it'll run inside your quick-and-dirty Docker stuff without complaint.
