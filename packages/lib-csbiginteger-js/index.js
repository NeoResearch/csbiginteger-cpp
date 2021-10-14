// MIT License - NeoResearch Community
// Copyleft 2021

import csbiginteger from './build/csbiginteger_raw_lib.js';
import wasm from './build/csbiginteger_raw_lib.wasm';
 
// this module is named 'csBigInteger'
// wasm module is the exported object: 'csBigInteger.wasmModule'
export var wasmModule = null; 

// ========================= HELPER WASM FUNCTIONS

// JS string to wasm pointer (char*)
// requires: EXPORTED_RUNTIME_METHODS='[\"intArrayFromString\", \"ALLOC_NORMAL\", \"allocate\", \"AsciiToString\"]'
export function strToPtr(str, wmodule) {
  var ptr = wmodule.allocate(wasmModule.intArrayFromString(str), wmodule.ALLOC_NORMAL);
  return ptr;
}

// JS hexstring to wasm pointer (unsigned char*)
// requires: EXPORTED_RUNTIME_METHODS='[\"intArrayFromString\", \"ALLOC_NORMAL\", \"allocate\", \"AsciiToString\"]'
export function hexToPtr(hex, wmodule) {
  var hi_hex = hexToBytesU8(hex);//hexToBytes(hex);
  var ptr = wmodule.allocate(hi_hex, wmodule.ALLOC_NORMAL);
  return ptr;
}

// JS hexstring to wasm pointer (unsigned char*)
// requires: EXPORTED_RUNTIME_METHODS='[\"intArrayFromString\", \"ALLOC_NORMAL\", \"allocate\", \"AsciiToString\"]'
export function sizeToPtr(sz, wmodule) {
  var hex = "";
  for(var i=0; i<sz; i+=1)
    hex += "00";
  var hi_hex = hexToBytesU8(hex);//hexToBytes(hex);
  var ptr = wmodule.allocate(hi_hex, wmodule.ALLOC_NORMAL);
  return ptr;
}

// wasm pointer (char*) to JS string
// requires: EXPORTED_RUNTIME_METHODS='[\"intArrayFromString\", \"ALLOC_NORMAL\", \"allocate\", \"AsciiToString\"]'
export function ptrToStr(ptr, wmodule) {
  var str = wmodule.AsciiToString(ptr);
  return str;
}

// wasm pointer (unsigned char*) to JS hexstring
// requires: EXPORTED_RUNTIME_METHODS='[\"intArrayFromString\", \"ALLOC_NORMAL\", \"allocate\", \"AsciiToString\"]'
export function ptrToHex(ptr, maxSize, wmodule) {
  for (var bytes = [], c = 0; c < maxSize; c += 1)
    bytes.push(wasmModule.HEAPU8[ptr+c]);  
  // the code below should work... but is buggy! Avoid AsciiToString!!
  /*
  var str = wmodule.AsciiToString(ptr);
  str=str.substr(0, maxSize);
  var bts = asciiToBytes(str);
  var hex = bytesToHex(bts);
  */
  var hex = bytesToHex(bytes);
  return hex;
}

// ========================= HELPER FUNCTIONS

// hex string to bytes (big/little endian order preserved).. if prefix '0x' exists, it is removed
export function hexToBytes(hex) {
  if((hex.length>=2) && (hex[0]=='0') && (hex[1]=='x'))
    hex = hex.substr(2); // remove '0x' prefix
  for (var bytes = [], c = 0; c < hex.length; c += 2)
    bytes.push(parseInt(hex.substr(c, 2), 16));
  return bytes;
}

export function hexToBytesU8(hex) {
  if((hex.length>=2) && (hex[0]=='0') && (hex[1]=='x'))
    hex = hex.substr(2); // remove '0x' prefix
  for (var bytes = [], c = 0; c < hex.length; c += 2)
    bytes.push(parseInt(hex.substr(c, 2), 16));
  return new Uint8Array(bytes);
}

// Convert a byte array  to a hex string (big/little endian order preserved)
export function bytesToHex(bytes) {
  for (var hex = [], i = 0; i < bytes.length; i++) {
      var current = bytes[i] < 0 ? bytes[i] + 256 : bytes[i];
      hex.push((current >>> 4).toString(16));
      hex.push((current & 0xF).toString(16));
  }
  return hex.join("");
}

// ASCII string to bytes... example: "AB\0C" -> [65, 66, 0, 67]
export function asciiToBytes(ascii) {
  for (var bytes = [], c = 0; c < ascii.length; c += 1)
    bytes.push(ascii.charCodeAt(c));
  return bytes;
}

export function revertHexString(shex)
{
   // if needs padding
   if (shex.length % 2 == 1)
      shex = "0" + shex
   var hex = shex;

   var reverthex = "";
   for (var i = 0; i < hex.length - 1; i += 2) {
      reverthex = hex.substr(i, 2) + reverthex;
   }
   return reverthex;
}

// ========================= WASM MODULE LOADER

// exported loader function is named 'csbiginteger'
// exported module is named 'csBigInteger'
export const module = csbiginteger({
  // locateFile will find corresponding .wasm and match it here
  locateFile(path) {
    if(path.endsWith('.wasm')) {
      return wasm;
    }
    return path;
  }
}).then(instance => {
    //console.log("loading wasmModule: "+JSON.stringify(instance));
    wasmModule = instance;
    //
    console.log("loaded csBigInteger.wasmModule = "+wasmModule);

    // some operations may be necessary to load wasm module
    var hi = "hello world";
    console.log("testing wasmModule: "+hi);
    var hi_ptr = strToPtr(hi, wasmModule);
    console.log("-> "+ptrToStr(hi_ptr, wasmModule));

    wasmModule._free(hi_ptr);
  }, function() {
    // error function
    console.log("wasmModule loading error!");
});
