var module = require('../build/csbiginteger_raw_lib.js')

module().then(
    wasmModule => {
        //console.log(wasmModule);
        //console.log(wasmModule);
        
        var x = wasmModule._csbiginteger_welcome(10);
        console.log(x);
        /*
        var hi = "hello222";
        var hi_ptr = wasmModule.allocate(wasmModule.intArrayFromString(hi), wasmModule.ALLOC_NORMAL);
        var out_ptr = wasmModule.allocate(wasmModule.intArrayFromString("123456789"), wasmModule.ALLOC_NORMAL);
        
        var out_ptr_size = wasmModule._Pequeno_teste(hi_ptr, out_ptr);
        console.log(out_ptr);
        console.log(out_ptr_size);
        console.log("utf8 -> "+wasmModule.AsciiToString(out_ptr));

        wasmModule._free(hi_ptr);
        wasmModule._free(out_ptr);
        */
    }
);
