// this works by removing the --bind flag... but this also breaks 'make test' with puppeteer
// so, right now, .mjs and puppeteer testing cannot happen together. We choose puppeteer then.
// maybe manually adding _malloc and other EXPORTED_FUNCTIONS... it could work together..
// at some point, this worked, but required something about wasi experimental 1... not sure why.

import {csbiginteger_welcome} from '../build/csbiginteger_raw_lib.wasm';
let out = csbiginteger_welcome(10);
console.log(out)