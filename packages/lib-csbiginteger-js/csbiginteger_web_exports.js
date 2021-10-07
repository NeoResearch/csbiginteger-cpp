mergeInto(
  LibraryManager.library, {
  csbiginteger_external_welcome: function (ptr_str1, ptr_str_out, ptr_out) {
    // 'Pointer_stringify' is deprecated... now use 'UTF8ToString'
    vstr1 = Module.UTF8ToString(ptr_str1);
    // https://emscripten.org/docs/api_reference/preamble.js.html

    console.log("js csbiginteger_external_welcome: ptr_str1=" + vstr1);

    var rstr = vstr1; // copy size

    // var myLib = Module["CryptoJS"]; // Take module from 'prefix-node-require.js'

    console.log("requires some bytes: " + lengthBytesUTF8(rstr));
    console.log("out space is '" + lengthBytesUTF8(Module.UTF8ToString(ptr_str_out)) + "'");
    console.log("out value is '" + Module.UTF8ToString(ptr_str_out) + "'");
    //
    stringToUTF8(rstr, ptr_str_out, rstr.length + 1);
    //
    console.log("out value is '" + Module.UTF8ToString(ptr_str_out) + "'");

    // second test with unsigned char*
    const myUint8Array = new Uint8Array([3,2,1]);
    //
    Module.HEAPU8.set(myUint8Array, ptr_out);

    console.log("should compute input+"+lengthBytesUTF8(rstr)+ "+"+ myUint8Array[0]);

    return lengthBytesUTF8(rstr);
  }
}); // mergeInto