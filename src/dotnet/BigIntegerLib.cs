using System;
using System.Numerics;
using System.Globalization; // NumberStyles
using System.Collections.Generic; // IEnumerable
using System.Text; // StringBuilder


namespace csbiglib
{
    public class BigIntegerLib
    {
        public BigInteger zero()
        {
            return new BigInteger(0);
        }

        public byte[] from_float(float x)
        {
            BigInteger big = new BigInteger(x);
            return big.ToByteArray();
        }

        public BigInteger from_int32(int x)
        {
            return new BigInteger(x);
        }

        public BigInteger from_int64(long x)
        {
            return new BigInteger(x);
        }

        public int to_int32(byte[] big)
        {
            BigInteger bg = new BigInteger(big);
            return (int)bg;
        }

        public long to_int64(byte[] big)
        {
            BigInteger bg = new BigInteger(big);
            return (long)bg;
        }

        public BigInteger from_bytes(byte[] x)
        {
            return new BigInteger(x);
        }

        public byte[] to_bytes(BigInteger big)
        {
            return big.ToByteArray();
        }

        public BigInteger from_string(string x, int b)
        {
            Console.WriteLine($"from_string {x} base={b}");
            if (b == 10)
                return BigInteger.Parse(x);
            // assuming base 16 (bigendian '0x prefixed')
            // small or poor formatted (do not raise exception)
            if ((x.Length < 2) || (x.Length % 2 == 1))
                return new BigInteger(0);
            if ((x.Substring(0, 2) == "0x") || (x.Substring(0, 2) == "0X"))
                x = x.Substring(2, x.Length - 2);
            byte[] bigend = Helper.HexToBytes(x);
            Array.Reverse(bigend, 0, bigend.Length);
            return new BigInteger(bigend); // now is little endian
        }

        public byte[] from_string_to_bytes(string x, int b)
        {
            BigInteger big = from_string(x, b);
            Console.WriteLine(big.ToString());
            byte[] r = big.ToByteArray();
            Console.WriteLine(BitConverter.ToString(r));
            return r;
        }

        public string to_string16(object big1, int b)
        {
            BigInteger big = (BigInteger) big1;
            if (b == 10)
            {
                return big.ToString();
            }
            // assume base 16
            byte[] little = big.ToByteArray();
            Array.Reverse(little, 0, little.Length); // now bigendian
            Console.WriteLine(Helper.ToHexString(little));
            return "0x" + Helper.ToHexString(little);
        }

        public string to_string(byte[] big1, int b)
        {
            BigInteger big = new BigInteger(big1);
            if (b == 10)
            {
                return big.ToString();
            }
            // assume base 16
            byte[] little = big.ToByteArray();
            Array.Reverse(little, 0, little.Length); // now bigendian
            Console.WriteLine(Helper.ToHexString(little));
            return "0x" + Helper.ToHexString(little);
        }

        public byte[] add(byte[] big1, byte[] big2)
        {
            return BigInteger.Add(new BigInteger(big1), new BigInteger(big2)).ToByteArray();
        }

        public byte[] sub(byte[] big1, byte[] big2)
        {
            return BigInteger.Subtract(new BigInteger(big1), new BigInteger(big2)).ToByteArray();
        }

        public byte[] mul(byte[] big1, byte[] big2)
        {
            return BigInteger.Multiply(new BigInteger(big1), new BigInteger(big2)).ToByteArray();
        }

        public byte[] div(byte[] big1, byte[] big2)
        {
            Console.WriteLine("  ------> div()");
            /*
            BigInteger _big1 = new BigInteger(big1);
            Console.WriteLine(BitConverter.ToString(big1));
            Console.WriteLine(_big1.ToString());
            BigInteger _big2 = new BigInteger(big2);
            Console.WriteLine(BitConverter.ToString(big2));
            Console.WriteLine(_big2.ToString());
            BigInteger big3 = _big1 / _big2;
            Console.WriteLine(big3.ToString());
            return big3.ToByteArray();
            */
            Console.WriteLine("will divide");
            return BigInteger.Divide(new BigInteger(big1), new BigInteger(big2)).ToByteArray();
        }

        public byte[] mod(byte[] big1, byte[] big2)
        {
            Console.WriteLine("  ------> mod()");
            BigInteger _big1 = new BigInteger(big1);
            BigInteger _big2 = new BigInteger(big2);
            return (_big1 % _big2).ToByteArray();
        }

        public byte[] shr(byte[] big1, byte[] big2)
        {
            BigInteger _big1 = new BigInteger(big1);
            BigInteger _big2 = new BigInteger(big2);
            return (_big1 >> (int)_big2).ToByteArray();
        }


        public byte[] shl(byte[] big1, byte[] big2)
        {
            BigInteger _big1 = new BigInteger(big1);
            BigInteger _big2 = new BigInteger(big2);
            return (_big1 << (int)_big2).ToByteArray();
        }

        public bool lt(byte[] big1, byte[] big2)
        {
            BigInteger _big1 = new BigInteger(big1);
            BigInteger _big2 = new BigInteger(big2);
            return (_big1 < _big2);
        }

        public bool gt(byte[] big1, byte[] big2)
        {
            BigInteger _big1 = new BigInteger(big1);
            BigInteger _big2 = new BigInteger(big2);
            return (_big1 > _big2);
        }


        public byte[] pow(byte[] big1, int exp)
        {
            return BigInteger.Pow(new BigInteger(big1), exp).ToByteArray();
        }

    }
}

public class Helper
{
    public static byte[] HexToBytes(string value)
    {
        if (value == null || value.Length == 0)
            return new byte[0];
        if (value.Length % 2 == 1)
            throw new FormatException();
        byte[] result = new byte[value.Length / 2];
        for (int i = 0; i < result.Length; i++)
            result[i] = byte.Parse(value.Substring(i * 2, 2), NumberStyles.AllowHexSpecifier);
        return result;
    }

    public static string ToHexString(IEnumerable<byte> value)
    {
        StringBuilder sb = new StringBuilder();
        foreach (byte b in value)
            sb.AppendFormat("{0:x2}", b);
        return sb.ToString();
    }
}
