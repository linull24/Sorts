#!/bin/bash
# Open results file with default text editor
if [ -f "results.txt" ]; then
    xdg-open results.txt
else
    echo "results.txt not found. Run the program first."
fi