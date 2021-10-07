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
// --------------------

}); // describe

function delay(time) {
  return new Promise(function (resolve) {
    setTimeout(resolve, time)
  });
}