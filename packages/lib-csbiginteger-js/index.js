// MIT License - NeoResearch Community
// Copyleft 2021

import csbiginteger from './build/csbiginteger_raw_lib.js';
import wasm from './build/csbiginteger_raw_lib.wasm';
 
// this module is named 'csBigIntegerLib'
// wasm module is the exported object: 'csBigIntegerLib.wasmModule'
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

// ======================== operations

// converts input into 0x big endian, if little endian hexstring (no '0x' prefix)
export function to0xBigEndian(hex) {
  if(hex.length < 2) {
    console.log("WARNING: to0xBigEndian expects '0x' prefix, or at least a single byte");
    return "0x00";
  }
  // if big endian, ok
  if((hex.length>=2) && (hex[0]=='0') && (hex[1]=='x'))
    return hex;
  // little endian must reverse
  hex = "0x"+revertHexString(hex);
  return hex;
}

// from little-endian hex (or prefixed '0x' big endian) to decimal
export function convert16to10(lehex)
{
  // ensure input is big endian
  lehex = to0xBigEndian(lehex);
  //
  var sz_alloc = 3*lehex.length+1;
  var bts_ptr = sizeToPtr(sz_alloc, wasmModule);
  var str_ptr = strToPtr(lehex, wasmModule);
  //
  // invoke initialize big integer (second parameter is 'base', not 'size')
  var sz_real = wasmModule._csbiginteger_init_s(str_ptr, 16, bts_ptr, sz_alloc);
  
  var str_dec_ptr = sizeToPtr(sz_alloc, wasmModule);
  //
  // to string
  var good = wasmModule._csbiginteger_to_string(
    bts_ptr, sz_real, 10, str_dec_ptr, sz_alloc);
  //
  var dec = ptrToStr(str_dec_ptr, wasmModule);
  //
  wasmModule._free(bts_ptr); // free
  wasmModule._free(str_ptr); // free
  wasmModule._free(str_dec_ptr); // free
  //
  return dec;
}


// from decimal to prefixed '0x' big endian
export function convert10to16(dec)
{
  if(dec.length < 1)
    dec = "0";
  //
  var str = dec;
  var sz_alloc = str.length+1;
  var bts_ptr = sizeToPtr(sz_alloc, wasmModule);
  var str_ptr = strToPtr(str, wasmModule);
  // invoke initialize big integer (second parameter is 'base', not 'size')
  var sz_real = wasmModule._csbiginteger_init_s(str_ptr, 10, bts_ptr, sz_alloc);
  var hex = ptrToHex(bts_ptr, sz_real, wasmModule);
  //
  wasmModule._free(bts_ptr); // free
  wasmModule._free(str_ptr); // free
  //
  hex = "0x" + revertHexString(hex);
  return hex;
}

export function op2(lehex1, lehex2, sizeOut, csbiginteger_func)
{
  // ensure inputs are big endian
  lehex1 = to0xBigEndian(lehex1);
  lehex2 = to0xBigEndian(lehex2);
  // sizeOut for add/sub could be lehex1.length + lehex2.length + 2
  var sz_alloc = sizeOut;
  var bts_ptr = sizeToPtr(sz_alloc, wasmModule);
  var sz1 = lehex1.length/2+1;
  var sz2 = lehex2.length/2+1;
  var bts_ptr1 = sizeToPtr(sz1, wasmModule);
  var bts_ptr2 = sizeToPtr(sz2, wasmModule);
  var str_ptr1 = strToPtr(lehex1, wasmModule);
  var str_ptr2 = strToPtr(lehex2, wasmModule);
  //
  // invoke initialize big integer (second parameter is 'base', not 'size')
  var sz_real1 = wasmModule._csbiginteger_init_s(str_ptr1, 16, bts_ptr1, sz1);
  var sz_real2 = wasmModule._csbiginteger_init_s(str_ptr2, 16, bts_ptr2, sz2);
  if(sz_real1 != sz1){
    //console.log("WARNING: different sizes for first number: " + sz_real1 + " != " + sz1);
  }
  if(sz_real2 != sz2) {
    //console.log("WARNING: different sizes for first number: " + sz_real2 + " != " + sz2);
  }

  // invoke real operation
  var sz_real_out = csbiginteger_func(
      bts_ptr1, sz_real1, bts_ptr2, sz_real2, bts_ptr, sizeOut);
  var out_hex = ptrToHex(bts_ptr, sz_real_out, wasmModule);
  //
  csBigIntegerLib.wasmModule._free(bts_ptr); // free
  csBigIntegerLib.wasmModule._free(bts_ptr1); // free
  csBigIntegerLib.wasmModule._free(bts_ptr2); // free
  //
  return to0xBigEndian(out_hex);

}
//csbiginteger_add


// ========================= WASM MODULE LOADER

// exported loader function is named 'csbiginteger'
// exported module is named 'csBigIntegerLib'
export const myModule = csbiginteger({
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
    console.log("loaded csBigIntegerLib.wasmModule = "+wasmModule);

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
