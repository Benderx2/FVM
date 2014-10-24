using System;
/* System.IO is used by the assembler, for input/output */
using System.IO;
namespace FAS
{
	public class Assembler
	{
		public static string SourceText = "";
		public static void Assemble(string outputfilename, string inputfilename, UInt32 originaddress)
		{
			FAS.Global.OriginAddress = originaddress;
			//! And Let's get started.
			BinaryWriter output;
			TextReader input;
			/** Create the Output File **/
			FileStream fs = new FileStream(outputfilename, FileMode.Create);
			output = new System.IO.BinaryWriter(fs);
			input = File.OpenText(inputfilename);
			SourceText = input.ReadToEnd();
			/* Done with the source file... */
			input.Close();
			/* Magic Header :) */
			output.Write((UInt32)0xC00C1E5); // COOKIES (not for you btw)
			
		}
	}
}

