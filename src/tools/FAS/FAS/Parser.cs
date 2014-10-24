using System;
using System.IO;
namespace FAS
{
	// Parser
	public class Parser
	{
		public static void Parse (BinaryWriter Output)
		{
			FAS.Global.CurrentIndex = 0;
			while (FAS.Global.IsEnd == false) {
				LScan (Output, true);
			}
			FAS.Global.IsEnd = false;
			FAS.Global.CurrentIndex = 0;
			FAS.Global.AsLength = Convert.ToUInt32 (Global.OriginAddress);
			while (Global.IsEnd == false) {
				LScan(Output, true);
			}
		}
		public static void LScan (BinaryWriter Output, bool IsLabelScan)
		{
			if (char.IsLetter (FAS.Assembler.SourceText [FAS.Global.CurrentIndex])) {
				if(IsLabelScan){ FAS.Global.LabelTable.Add(GetLabelName(), FAS.Global.AsLength);}
				while(FAS.Assembler.SourceText[FAS.Global.CurrentIndex] != '\n')
					FAS.Global.CurrentIndex++;
				FAS.Global.CurrentIndex++;
				return;
			}
			EatWhiteSpaces();
			ReadMneumonic(Output, IsLabelScan);

		}
		public static string GetLabelName()
		{
			string labelname = "";
		}
		public static void ReadMneumonic (BinaryWriter Outputfile, bool IsLabelScan)
		{
			string Mneumonic = "";
			while (!char.IsWhiteSpace(Assembler.SourceText[Global.CurrentIndex])) {
				Mneumonic = Mneumonic + Assembler.SourceText [Global.CurrentIndex];
				Global.CurrentIndex++;
			}
			if (Mneumonic.ToUpper () == "LD0") {

			}
		}
	}
}

