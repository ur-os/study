using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using MathNet.Numerics;
using MathNet.Numerics.LinearAlgebra;
using MathNet.Numerics.LinearAlgebra.Single;


namespace Hamming
{
    //15,11 Hamming code class for usage in data link layer
    //encoding and decoding implementations are in HammingCode class
    public class HammingCoder
    {
        private short[] encodingTable; //lookup table for all possible encodings;
        private short[] decodingTable; //lookup table for all possible decodes;

        private HammingCode ham;

        private const int ParityBits = 4; //There are 4 parity bits in 15,11 code

        public HammingCoder()
        {
            ham = new HammingCode(ParityBits);
            //Construct encoding lookup table
            CreateEncodingTable();
            //Construct decoding lookup table
            CreateDecodingTable();
        }

        //setup lookup table for all possible encodings 
        private void CreateEncodingTable()
        {
            int permutations = (int)Math.Pow(2, ham.K);
            encodingTable = new short[permutations];

            for (short i = 0; i < permutations; i++)
            {
                var vector = ConvertUtils.VectorFromShort(i, ham.K);
                var codeword = ham.Encode(vector);
                encodingTable[i] = ConvertUtils.ShortFromVector(codeword);
            }
        }

        //setup lookup table for all possible decodings 
        private void CreateDecodingTable()
        {
            int permutations = (int)Math.Pow(2, ham.N);
            decodingTable = new short[permutations];
            for (int i = 0; i < permutations; i++)
            {
                var codeword = ConvertUtils.VectorFromShort((short)i, ham.N);
                var source = ham.DecodeNoError(codeword);
                //if same vector is returned => errors
                if (source == codeword)
                {
                    decodingTable[i] = short.MinValue;
                }
                else
                {
                    decodingTable[i] = ConvertUtils.ShortFromVector(source);
                }
                //var source = ham.Decode(codeword);
                //decodingTable[i] = ConvertUtils.ShortFromVector(source);
            }
        }

        //Encodes byte array with hamming code, returns byte array
        public byte[] Encode(byte[] source)
        {
            var shorts = new short[source.Length];
            for (int i = 0; i < source.Length; i++)
            {
                shorts[i] = encodingTable[source[i]];
            }
            return ConvertUtils.ToByteArray(shorts);
        }

        //Decodes byte array with hamming code, returns byte array
        public byte[] Decode(byte[] output)
        {
            var codewords = ConvertUtils.ToShortArray(output);
            byte[] bytes = new byte[codewords.Length];
            for (int i = 0; i < codewords.Length; i++)
            {
                //if the codeword contains errors return empty array
                if (decodingTable[codewords[i]] == short.MinValue)
                    return Array.Empty<byte>();
                bytes[i] = (byte)decodingTable[codewords[i]];
            }
            return bytes;
        }
    }

    
    public class HammingCode
    {
        private readonly int j; //Number of Hamming code parity bits with n = 2 ^ j - 1 and k = n - j
        private int n; //number of total bits/block
        private int k; //number of source bits/block

        private Matrix<float> g; //G: Systematic generator matrix with left-side identity matrix
        private Matrix<float> h; //H: Systematic parity-check matrix with right-side identity matrix
        private Matrix<float> r; //R: k x k identity matrix

        private Dictionary<Vector<float>, int> errorPos; //lookup table to get index of error;

        public int N { get => n; set => n = value; }
        public int K { get => k; set => k = value; }

        public HammingCode(int j)
        {
            if (j < 3)
                throw new ArgumentOutOfRangeException("j must be > 2");
            this.j = j;
            GenerateHamming();
            //Construct errorPos lookup table
            CreateErrorTable();            
        }

        // initialize lookup table for decode method
        private void CreateErrorTable()
        {
            //get iterator over H and zip it with index array to create dictionary
            errorPos = h.EnumerateColumnsIndexed().ToDictionary(tuple => tuple.Item2, tuple => tuple.Item1);
        }


        /*
        Generates parity check matrix(H) and generator
        matrix(G). 
        
        Parameters
        ----------
        j: Number of Hamming code parity bits with n = 2 ^ j - 1 and k = n - j
        */
        private void GenerateHamming()
        {
            // calculate codeword length
            n = (int)Math.Pow(2, j) - 1;

            //calculate source bit length
            k = n - j;

            //Allocate memory for Matrices
            g = Matrix<float>.Build.Dense(k, n);
            h = Matrix<float>.Build.Dense(j, n);
            //Build Identity matrix
            r = Matrix<float>.Build.DenseIdentity(k, k);

            //Encode parity-check matrix columns with binary 1-n
            for (short i = 1; i <= n; i++)
            {
                //convert number to binary vector
                var vector = ConvertUtils.VectorFromShort(i, j);
                h.SetColumn(i - 1, vector);
            }

            //Construct array of indices to permutate columns in matrix
            int[] indices = Enumerable.Range(0, n).ToArray();
            int powerOfTwo = 1;
            //exchange values equal power of two to comprise identity matrix in the end
            for (int i = 0; i < j; i++)
            {
                int tmp = indices[powerOfTwo - 1];
                indices[powerOfTwo - 1] = indices[n - 1 - i];
                indices[n - 1 - i] = tmp;

                powerOfTwo *= 2;
            }
            //Reformat H to be systematic
            Permutation hp = new Permutation(indices);
            h.PermuteColumns(hp);



            // Get parity matrix from H
            Matrix<float> p = h.SubMatrix(0, j, 0, k);

            Console.WriteLine(p.Transpose());
            //Use P to calcuate generator matrix P
            g = r.Append(p.Transpose());

            Console.WriteLine(h.ToString());
            Console.WriteLine(g.ToString());
            Console.WriteLine(r.ToString());
            Console.ReadLine();
        }


        /*Encodes vector using hamming block code.
        
        parameters
        ----------
        source: vector to encode


        returns
        -------
        codeword: code word generated by generator matrix G and vector source.
        */
        public Vector<float> Encode(Vector<float> source)
        {
            if (source.Count != k)
                throw new ArgumentException("source length must be" + k);
            //multiple source vector and g to get encoded word and apply modulus of 2
            return (source * g).Modulus(2);

        }

        /*
        Decode hamming encoded codewords.Make sure code words are of
        the appropriate length for the object.


        parameters
        ---------
        codeword: vector to decode


        returns
        -------
        source: vector of decoded source data
        */
        public Vector<float> Decode(Vector<float> codeword)
        {
            if (codeword.Count != n)
                throw new ArgumentException("codeword length must be" + n);
            //find the syndrome of codeword and normalize by modulus
            Vector<float> syndrome = (h * codeword).Modulus(2);

            //correct error if present
            if (errorPos.ContainsKey(syndrome))
            {
                //invert bit of vector
                codeword[errorPos[syndrome]] = ConvertUtils.InvertFloat(codeword[errorPos[syndrome]]);
            }

            //Decode the corrected codeword
            return codeword.SubVector(0, k);
        }


        /*
        Decode hamming encoded codewords without correcting errors.
        If error occured returns parameter vector back


        parameters
        ---------
        codeword: vector to decode


        returns
        -------
        source: vector of decoded source data
        */
        public Vector<float> DecodeNoError(Vector<float> codeword)
        {
            if (codeword.Count != n)
                throw new ArgumentException("codeword length must be" + n);
            //find the syndrome of codeword and normalize by modulus
            Vector<float> syndrome = (h * codeword).Modulus(2);

            //correct error if present
            if (errorPos.ContainsKey(syndrome))
                return codeword;

            //Decode the corrected codeword
            return codeword.SubVector(0, k);
        }

    }


    //Helper class with collection of convert methods between several data types
    internal static class ConvertUtils
    {
        public const int BitsPerByte = 8;
        
        //invert float imitating boolean invert
        public static float InvertFloat(float num)
        {
            bool invert = !Convert.ToBoolean(num);
            return Convert.ToSingle(invert);
        }

        
        public static short ShortFromVector(Vector<float> vector)
        {
            int powerOfTwo = 1;
            int number = 0;
            foreach (float bit in vector.Reverse())
            {
                number += Convert.ToInt16(bit) * powerOfTwo;
                powerOfTwo *= 2;
            }
            return (short)number;
        }

        //converts short number to vector representation with normalizing length
        public static Vector<float> VectorFromShort(short number, int normLength)
        {
            //convert number to bit representation
            var bitNumber = new BitArray(new int[] { number });
            //normalize length
            bitNumber.Length = normLength;
            //get array of bools and reverse bits to natural order
            var boolBits = new bool[normLength];
            bitNumber.CopyTo(boolBits, 0);
            Array.Reverse(boolBits);
            //convert bool array to float vector
            var vector = DenseVector.Create(normLength, i => Convert.ToSingle(boolBits[i++]));
            return vector;
        }

        /*converts bytes array to array of shorts by combining neighbour elements

        throws ArgumentException if array.Length is not even
        */
        public static short[] ToShortArray(byte[] bytes)
        {
            if (bytes.Length % 2 != 0)
                throw new ArgumentException("bytes length should be even!");
            short[] shorts = new short[bytes.Length / 2];
            //block copy of memory to short array
            Buffer.BlockCopy(bytes, 0, shorts, 0, bytes.Length);
            return shorts;
        }

        /*converts shorts array to array of bytes
        */
        public static byte[] ToByteArray(short[] shorts)
        {
            byte[] bytes = new byte[shorts.Length*2];
            //block copy of memory to bytes array
            Buffer.BlockCopy(shorts, 0, bytes, 0, bytes.Length);
            return bytes;
        }
        
    }



}
