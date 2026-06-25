#!/bin/bash

SEEDS="16 24 32 36 42"

OUTPUT="resultados.txt"
> "$OUTPUT"

for SEED in $SEEDS; do
  make run \
    ALPHA=1.0 \
    INITIAL_TEMPERATURE=5000 \
    COOLING_RATE=0.98 \
    MAX_ITERATIONS=1000000 \
    COOLING_INTERVAL=50 \
    MAX_STAGNATION=20000 \
    SEED=$SEED 2>&1 | grep -v "^\\./mdvrptw" >> "$OUTPUT"

  echo "" >> "$OUTPUT"

done