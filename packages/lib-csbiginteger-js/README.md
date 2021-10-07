# lib-csbiginteger-js

This is a JS port from csBigInteger C++ project.

Many initial ideas came from: https://gist.github.com/surma/b2705b6cca29357ebea1c9e6e15684cc

And obviously, from may issues in the Emscripten Project.

THANKS A LOT!

## General Idea

By using `make start`, a process will build the C++ using Emscripten and put it inside `build/` folder. After that, Webpack v4 will bundle it inside `dist/` folder.

### make start

Will build the library and open a process in `localhost:8080` using `index.html`, as a demo.

###  make node_test

If you want to test with Node, use `build/`

### make test

If you want to test on web, use with `dist/`

### make clean

Cleans folders `build/` and `dist/`

## Roadmap

This is working with Webpack v4, but couldn't make it work with Webpack v5.

Currently, Node and Web are using different builds (from `build/` and `dist/`), which is not good...
On Node, `.js` and `.mjs` also lead to some problems (conflict with puppeteer web builds, something to do with `--bind` option, I think).

These things should be better clarified and adjusted in the future.

## Copyright

MIT License - NeoResearch 2021
    