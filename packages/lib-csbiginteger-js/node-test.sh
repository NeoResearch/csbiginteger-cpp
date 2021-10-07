#!/bin/bash

echo "test with nodejs .js"
(cd node_tests && node test.js)

echo ""
echo "test with nodejs modules .mjs"
echo "WARNING: this is disabled! because --bind is breaking things..."
#(cd node_tests && node --experimental-modules  --experimental-wasm-modules test.mjs)

