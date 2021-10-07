#!/bin/bash

echo "============= performing basic node tests =============="
./node-test.sh

echo ""
echo "============= performing advanced puppeteer tests =============="
echo ""
npm install
npm run build
(cd tests && npm install)
nohup npm run serve&
(cd tests && npm test)
pkill http-server #finish server
