jest.setTimeout(30000);
describe('Compilation', () => {
  beforeAll(async () => {
    await page.goto('http://127.0.0.1:8080');
  });


  test('testConversionToVerification', async () => {
    await async function() {
      await delay(100);
      expect(1).toBe(2);
      const output = await page.evaluate(() => testConversionToVerification());
      expect(output).toBe({"out_ptr_size": 7, "str_out": "other2"});     
      //expect(output).toEqual({"out_ptr_size": 6, "str_out": "other2"});     
    }
  });


  /*
  test('testCompilation2', async () => {
    await async function() {
      await delay(100);
      await test_local(); 
    }
  });

  async function test_local() {
    await delay(100);
    const output = await page.evaluate(() => testConversionToVerification());
    expect(output).toBe({"out_ptr_size": 6, "str_out": "other2"});     
  }
*/

// --------------------

test('test_utils_hexToBytes', async () => {
  await test_utils_hexToBytes();
}); // test

async function test_utils_hexToBytes() {
  await delay(100);
  const output1 = await page.evaluate(
    () => csBigInteger.hexToBytes("00010203")
  );
  expect(output1).toEqual([0,1,2,3]);    

  const output2 = await page.evaluate(
    () => csBigInteger.hexToBytes("0x030201")
  );
  expect(output2).toEqual([3,2,1]);    
}

// --------------------

test('test_utils_bytesToHex', async () => {
  await test_utils_bytesToHex();
}); // test

async function test_utils_bytesToHex() {
  await delay(100);
  const output1 = await page.evaluate(
    () => csBigInteger.bytesToHex([0,1,2,3])
  );
  expect(output1).toBe("00010203");    

  const output2 = await page.evaluate(
    () => csBigInteger.bytesToHex([3,2,1])
  );
  expect(output2).toBe("030201");   
}

// --------------------

test('test_utils_asciiToBytes', async () => {
  await test_utils_asciiToBytes();
}); // test

async function test_utils_asciiToBytes() {
  await delay(100);
  const output1 = await page.evaluate(
    () => csBigInteger.asciiToBytes("AB\0C")
  );
  expect(output1).toEqual([65,66,0,67]); 

  const output2 = await page.evaluate(
    () => csBigInteger.asciiToBytes("\u0001\u0002\u0003")
  );
  expect(output2).toEqual([1,2,3]); 
}


// --------------------

test('test_utils_revertHexString', async () => {
  await test_utils_revertHexString();
}); // test

async function test_utils_revertHexString() {
  await delay(100);
  const output1 = await page.evaluate(
    () => csBigInteger.revertHexString("0102030405")
  );
  expect(output1).toEqual("0504030201"); 
}


// --------------------

test('test_wasm_utils_strToPtr_ptrToStr', async () => {
  await test_wasm_utils_strToPtr_ptrToStr();
}); // test

async function test_wasm_utils_strToPtr_ptrToStr() {
  await delay(100);
  const output1 = await page.evaluate(
    () => { 
             var ptr = csBigInteger.strToPtr("hello", csBigInteger.wasmModule); 
             csBigInteger.wasmModule._free(ptr); // free
             return ptr; // copy should be fine
          }
  );

  // how deterministic is it? 5267176? 5267208?
  // 5 million?
  expect(output1).toBeGreaterThanOrEqual(5000000);

  const output2 = await page.evaluate(
    () => 
    { 
      var ptr = csBigInteger.strToPtr("hello", csBigInteger.wasmModule); 
      var str = csBigInteger.ptrToStr(ptr, csBigInteger.wasmModule);
      csBigInteger.wasmModule._free(ptr); // free
      return str;
    }
  );
  expect(output2).toBe("hello");
}

// --------------------

test('test_wasm_utils_hexToPtr_ptrToHex', async () => {
  await test_wasm_utils_hexToPtr_ptrToHex();
}); // test

async function test_wasm_utils_hexToPtr_ptrToHex() {
  await delay(100);
  const output1 = await page.evaluate(
    () => { 
             var ptr = csBigInteger.hexToPtr("0x010203", csBigInteger.wasmModule); 
             csBigInteger.wasmModule._free(ptr); // free
             return ptr; // copy should be fine
          }
  );
    // how deterministic is it? 5267176? 5267224?
  // 5 million?
  expect(output1).toBeGreaterThanOrEqual(5000000);

  const output2 = await page.evaluate(
    () => 
    { 
      var ptr = csBigInteger.hexToPtr("0x01020003", csBigInteger.wasmModule); 
      var str = csBigInteger.ptrToHex(ptr, 4, csBigInteger.wasmModule);
      csBigInteger.wasmModule._free(ptr); // free
      return csBigInteger.hexToBytes(str);
    }
  );
  expect(output2).toEqual([1,2,0,3]);

  // let's try to mix things a little bit... char* and unsigned char*
  const output3 = await page.evaluate(
    () => 
    { 
      // ptr is char*
      var ptr = csBigInteger.strToPtr("ABC\0ABC\0", csBigInteger.wasmModule); 
      // ptrToHex expects unsigned char*
      var str = csBigInteger.ptrToHex(ptr, 8, csBigInteger.wasmModule);
      csBigInteger.wasmModule._free(ptr); // free
      return csBigInteger.hexToBytes(str);
    }
  );
  expect(output3).toEqual([65,66,67,0,65,66,67,0]);
}


// --------------------

test('test_wasm_utils_sizeToPtr_ptrToHex', async () => {
  await test_wasm_utils_sizeToPtr_ptrToHex();
}); // test

async function test_wasm_utils_sizeToPtr_ptrToHex() {
  await delay(100);
  const output1 = await page.evaluate(
    () => { 
             var ptr = csBigInteger.sizeToPtr(5, csBigInteger.wasmModule); 
             csBigInteger.wasmModule._free(ptr); // free
             return ptr; // copy should be fine
          }
  );
    // how deterministic is it? 5267176? 5267224?
  // 5 million?
  expect(output1).toBeGreaterThanOrEqual(5000000);

  const output2 = await page.evaluate(
    () => 
    { 
      var ptr = csBigInteger.sizeToPtr(5, csBigInteger.wasmModule); 
      var str = csBigInteger.ptrToHex(ptr, 5, csBigInteger.wasmModule);
      csBigInteger.wasmModule._free(ptr); // free
      return csBigInteger.hexToBytes(str);
    }
  );
  expect(output2).toEqual([0,0,0,0,0]);
}

// --------------------

test('test_csbiginteger_init_s_from_decimal_to_hex', async () => {
  await test_csbiginteger_init_s_from_decimal_to_hex();
}); // test

async function test_csbiginteger_init_s_from_decimal_to_hex() {
  await delay(100);
  const output1 = await page.evaluate(
    () => { 
            var str = "123456789012345678901234";
            var sz_alloc = str.length+1;
            var bts_ptr = csBigInteger.sizeToPtr(sz_alloc, csBigInteger.wasmModule);
            var str_ptr = csBigInteger.strToPtr(str, csBigInteger.wasmModule);
            // invoke initialize big integer (second parameter is 'base', not 'size')
            var sz_real = csBigInteger.wasmModule._csbiginteger_init_s(str_ptr, 10, bts_ptr, sz_alloc);
            var hex = csBigInteger.ptrToHex(bts_ptr, sz_real, csBigInteger.wasmModule);
            //
            csBigInteger.wasmModule._free(bts_ptr); // free
            csBigInteger.wasmModule._free(str_ptr); // free
            //
            hex = "0x" + csBigInteger.revertHexString(hex);
            return {hex, sz_real, sz_alloc};
          }
  );
  //
  expect(output1).toEqual({"hex": "0x1a249b1f10a06c96aff2", "sz_real": 10, "sz_alloc": 25});
  //
  const output2 = await page.evaluate(
    () => { 
            var str = "123456789012345678901234567890";
            var sz_alloc = str.length+1;
            var bts_ptr = csBigInteger.sizeToPtr(sz_alloc, csBigInteger.wasmModule);
            var str_ptr = csBigInteger.strToPtr(str, csBigInteger.wasmModule);
            // invoke initialize big integer (second parameter is 'base', not 'size')
            var sz_real = csBigInteger.wasmModule._csbiginteger_init_s(str_ptr, 10, bts_ptr, sz_alloc);
            var hex = csBigInteger.ptrToHex(bts_ptr, sz_real, csBigInteger.wasmModule);
            //
            csBigInteger.wasmModule._free(bts_ptr); // free
            csBigInteger.wasmModule._free(str_ptr); // free
            //
            hex = "0x" + csBigInteger.revertHexString(hex);
            return {hex, sz_real, sz_alloc};
          }
  );
  //
  expect(output2).toEqual({"hex": "0x018ee90ff6c373e0ee4e3f0ad2", "sz_real": 13, "sz_alloc": 31});
}

// --------------------

test('test_csbiginteger_init_s_from_hex_to_hex', async () => {
  await test_csbiginteger_init_s_from_hex_to_hex();
}); // test

async function test_csbiginteger_init_s_from_hex_to_hex() {
  await delay(100);
  const output1 = await page.evaluate(
    () => { 
            var str = "0x1a249b1f10a06c96aff2";
            var sz_alloc = 3*str.length+1;
            var bts_ptr = csBigInteger.sizeToPtr(sz_alloc, csBigInteger.wasmModule);
            var str_ptr = csBigInteger.strToPtr(str, csBigInteger.wasmModule);
            // invoke initialize big integer (second parameter is 'base', not 'size')
            var sz_real = csBigInteger.wasmModule._csbiginteger_init_s(str_ptr, 16, bts_ptr, sz_alloc);
            var hex = csBigInteger.ptrToHex(bts_ptr, sz_real, csBigInteger.wasmModule);
            //
            csBigInteger.wasmModule._free(bts_ptr); // free
            csBigInteger.wasmModule._free(str_ptr); // free
            //
            hex = "0x" + csBigInteger.revertHexString(hex);
            return {hex, sz_real, sz_alloc};
          }
  );
  //
  expect(output1).toEqual({"hex": "0x1a249b1f10a06c96aff2", "sz_real": 10, "sz_alloc": 67});
  //
  const output2 = await page.evaluate(
    () => { 
            var str = "0x018ee90ff6c373e0ee4e3f0ad2";
            var sz_alloc = 3*str.length+1;
            var bts_ptr = csBigInteger.sizeToPtr(sz_alloc, csBigInteger.wasmModule);
            var str_ptr = csBigInteger.strToPtr(str, csBigInteger.wasmModule);
            // invoke initialize big integer (second parameter is 'base', not 'size')
            var sz_real = csBigInteger.wasmModule._csbiginteger_init_s(str_ptr, 16, bts_ptr, sz_alloc);
            var hex = csBigInteger.ptrToHex(bts_ptr, sz_real, csBigInteger.wasmModule);
            //
            csBigInteger.wasmModule._free(bts_ptr); // free
            csBigInteger.wasmModule._free(str_ptr); // free
            //
            hex = "0x" + csBigInteger.revertHexString(hex);
            return {hex, sz_real, sz_alloc};
          }
  );
  //
  expect(output2).toEqual({"hex": "0x018ee90ff6c373e0ee4e3f0ad2", "sz_real": 13, "sz_alloc": 85});
}


// --------------------

test('test_csbiginteger_to_string_10', async () => {
  await test_csbiginteger_to_string_10();
}); // test

async function test_csbiginteger_to_string_10() {
  await delay(100);
  const output1 = await page.evaluate(
    () => { 
            var str = "0x1a249b1f10a06c96aff2";
            var sz_alloc = 3*str.length+1;
            var bts_ptr = csBigInteger.sizeToPtr(sz_alloc, csBigInteger.wasmModule);
            var str_ptr = csBigInteger.strToPtr(str, csBigInteger.wasmModule);
            //
            // invoke initialize big integer (second parameter is 'base', not 'size')
            var sz_real = csBigInteger.wasmModule._csbiginteger_init_s(str_ptr, 16, bts_ptr, sz_alloc);
            
            var str_dec_ptr = csBigInteger.sizeToPtr(sz_alloc, csBigInteger.wasmModule);
            //
            // to string
            var good = csBigInteger.wasmModule._csbiginteger_to_string(
              bts_ptr, sz_real, 10, str_dec_ptr, sz_alloc);
            //
            var dec = csBigInteger.ptrToStr(str_dec_ptr, csBigInteger.wasmModule);
            //
            csBigInteger.wasmModule._free(bts_ptr); // free
            csBigInteger.wasmModule._free(str_ptr); // free
            csBigInteger.wasmModule._free(str_dec_ptr); // free
            //
            return {dec, sz_real, sz_alloc, good};
          }
  );
  //
  expect(output1).toEqual({"dec": "123456789012345678901234", "sz_real": 10,
                    "sz_alloc": 67, "good": 1});
  //
  const output2 = await page.evaluate(
    () => { 
            var str = "0x018ee90ff6c373e0ee4e3f0ad2";
            var sz_alloc = 3*str.length+1;
            var bts_ptr = csBigInteger.sizeToPtr(sz_alloc, csBigInteger.wasmModule);
            var str_ptr = csBigInteger.strToPtr(str, csBigInteger.wasmModule);
            //
            // invoke initialize big integer (second parameter is 'base', not 'size')
            var sz_real = csBigInteger.wasmModule._csbiginteger_init_s(str_ptr, 16, bts_ptr, sz_alloc);
            
            var str_dec_ptr = csBigInteger.sizeToPtr(sz_alloc, csBigInteger.wasmModule);
            //
            // to string
            var good = csBigInteger.wasmModule._csbiginteger_to_string(
              bts_ptr, sz_real, 10, str_dec_ptr, sz_alloc);
            //
            var dec = csBigInteger.ptrToStr(str_dec_ptr, csBigInteger.wasmModule);
            //
            csBigInteger.wasmModule._free(bts_ptr); // free
            csBigInteger.wasmModule._free(str_ptr); // free
            csBigInteger.wasmModule._free(str_dec_ptr); // free
            //
            return {dec, sz_real, sz_alloc, good};
          }
  );
  //
  expect(output2).toEqual({"dec": "123456789012345678901234567890", "sz_real": 13,
                    "sz_alloc": 85, "good": 1});
  //
}

// --------------------

test('test_csbiginteger_engine', async () => {
  await test_csbiginteger_engine();
}); // test

async function test_csbiginteger_engine() {
  await delay(100);
  const output1 = await page.evaluate(
    () => { 
            var sz_alloc = 100;
            var bts_ptr = csBigInteger.sizeToPtr(sz_alloc, csBigInteger.wasmModule);
            //
            // invoke big integer getEngine()
            var good = csBigInteger.wasmModule._csbiginteger_engine(bts_ptr, sz_alloc);
            //
            var str = csBigInteger.ptrToStr(bts_ptr, csBigInteger.wasmModule);
            //
            csBigInteger.wasmModule._free(bts_ptr); // free
            //
            return {str, good};
          }
  );
  //
  expect(output1).toEqual({"str": "HandBigInt", "good": 1});
}

// --------------------
// --------------------

}); // describe

function delay(time) {
  return new Promise(function (resolve) {
    setTimeout(resolve, time)
  });
}