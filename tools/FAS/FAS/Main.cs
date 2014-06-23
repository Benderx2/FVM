using System;
namespace FAS
{
	class MainClass
	{
		public static string outputfile, sourcefile;
		public static void Main (string[] args)
		{
			if (args.Length < 4) {
				Console.WriteLine ("Help - FAS: FVM Assembler");
				Console.WriteLine ("Usage:");
				Console.WriteLine ("fas [source file] [output ROM file] [origin address]");
			} else {
				/* Save Command Line Arguments */
				sourcefile = args [0];
				outputfile = args [1];
				UInt32 originaddress = UInt32.Parse(args[2]);
				// Assemble it.
				FAS.Assembler.Assemble(outputfile, sourcefile, originaddress);
			}
		}
	}
}
