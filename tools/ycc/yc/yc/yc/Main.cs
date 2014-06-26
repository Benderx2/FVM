using System;
using System.Text.RegularExpressions;
using System.Collections.Generic;
namespace yc
{
	class MainClass
	{
		public struct Proc {
			public string ProcName;
			public string Parent;
			public string Code;
		};
		public struct IntType
		{
			public string ClassParent;
			public string IntName;
			public Int32 Value;
		}
		public struct StringType {
			public string ClassParent;
			public string stringname;
			public string Value;
		}
		private static string SourceText;
		public static int CurrentIndex;
		private static System.Collections.Generic.List<string> ClassList;
		private static int NumberofClasses = 0;
		private static int NumberofProcs = 0;
		private static int NumberofInts = 0;
		private static int NumberofStrings = 0;
		private static int temp;
		public static List<Proc> ProcList;
		public static List<IntType> IntList;
		public static List<StringType> StringList;
		public static Proc TempProc;
		public static IntType TempInt;
		public static StringType TempString;
		public static bool whileinclass = false;
		public static bool whileinproc = false;
		public static void Main (string[] args)
		{
			SourceText = "";
			CurrentIndex = 0;
			temp = 0;
			ClassList = new System.Collections.Generic.List<string> (1024);
			ProcList = new List<Proc>(1024);
			IntList = new List<IntType>(1024);
			StringList = new List<StringType>(1024);
			TempProc = new Proc();
			TempInt = new IntType();
			TempString = new StringType();
			if (args.Length == 2) {
				System.IO.StreamWriter SourceWriter = new System.IO.StreamWriter (args [1], true);
				System.IO.TextReader SourceReader = System.IO.File.OpenText(args[0]);
				SourceText = SourceReader.ReadToEnd();
				Console.WriteLine(SourceText);
				/** Add the required stuff **/
				SourceWriter.Write("align 4");
				SourceWriter.Write("include 'a321.inc'" + Environment.NewLine );
				SourceWriter.Write("dd 0xC001E5" + Environment.NewLine);
				SourceWriter.Write("dd _start" + Environment.NewLine);
				SourceWriter.Write("dd _start" + Environment.NewLine);
				SourceWriter.Write("dd _end_start - _start" + Environment.NewLine);
				SourceWriter.Write("db 'YCOMPILR'" + Environment.NewLine);
				SourceWriter.Write("_start:" + Environment.NewLine + "PUSH R0" + Environment.NewLine + "JMPF MainClass.Main" + Environment.NewLine);
				SourceWriter.Write("MainClass.Main:" + Environment.NewLine);
				SourceWriter.Flush();
				string[] tokens = SourceText.Split(new Char [] { ' ', '\n', '\t'});
				Console.WriteLine(tokens.Length.ToString());
				int i = 0;
				bool error = false;
				/** Piece of shit Lexer. **/
				while(i != tokens.Length && error == false)
				{
					switch (tokens[i].ToString())
					{
					case "class":
						if(tokens[i+2] != "{")
						{
							Console.WriteLine("#error: expected \"{\"");
							error = true;
						}
						/** Yes we have a class that didn't end **/
						whileinclass = true;
						ClassList.Add(tokens[i+1]);
						NumberofClasses += 1;
						i += 2;
						break;
					case "proc":
						if(tokens[i+2] != "{")
						{
							Console.WriteLine("#error expected \"{\" while declaring proc");
							error = true;
						}
						whileinproc = true;
						TempProc.Parent = ClassList[NumberofClasses-1];
						TempProc.ProcName = tokens[i+1];
						i += 3;
						while(tokens[i] != "}")
						{
							TempProc.Code = TempProc.Code + tokens[i] + "\n";
							i++;
						}
						whileinproc = false;
						ProcList.Add(TempProc);
						NumberofProcs += 1;
						break;
					case "int":
						TempInt.IntName = tokens[i + 1];
						if(whileinproc == true || whileinclass == false)
						{
							Console.WriteLine("#error: attempt to declare int in a proc");
							error = true;
							break;
						}
						if(tokens[i+2] != "=")
						{
							Console.WriteLine("#error: Integer value left unassigned");
							error = true;
							break;
						}
						else {
							try {
								TempInt.Value = Convert.ToInt32(tokens[i+3]);
							}
							catch (FormatException e)
							{
								Console.WriteLine("#error: Format Exception Caught!");
								error = true;
								break;
							}
							catch (OverflowException e)
							{
								Console.WriteLine("#error OverflowException Caught!");
								error = true;
								break;
							}
							TempInt.ClassParent = ClassList[NumberofClasses - 1];
							IntList.Add(TempInt);
							NumberofInts++;
							i += 3;
							break;
						}
						break;
					case "string":
						TempString.stringname = tokens[i+1];
						if(tokens[i+2] != "=")
						{
							Console.WriteLine("#error: string is not assigned");
							error = true;
							break;
						}
						else if(whileinclass == false)
						{
							Console.WriteLine("#error: Attempt to declare string outside class");
						}
						TempString.ClassParent = ClassList[NumberofClasses - 1];
						i += 3;
						if(tokens[i] != "\"")
						{
							Console.WriteLine("#error: string assignment doesn't contain \"");
						}
						else {
							i++;
							while(tokens[i] != "\"")
							{
								TempString.Value = TempString.Value + tokens[i] + " ";
								i++;
							}
						}
						StringList.Add(TempString);
						NumberofStrings++;
						break;
					case "}":
						if(whileinproc == true)
						{
							whileinproc = false;
						}
						else if(whileinclass == true)
						{
							whileinclass = false;
						}
						else {
							Console.WriteLine("#error: Unexpected Symbol \"{\"");
							error = true;
						}
						i++;
						break;

					}

					i++;
				}
				Console.WriteLine("Printing Classes... ");
				int j = 0;
				int mainoff = 0;
				while(j < NumberofClasses)
				{
					Console.WriteLine(ClassList[j]);
					if(ClassList[j] == "MainClass")
					{
						Console.WriteLine("MainClass Found");
						break;
					}
					else {
						j++;
					}
				}
				// Find proc main()
				Console.WriteLine("Printing procs...");
				j = 0;
				while(j < NumberofProcs)
				{
					Console.WriteLine(ProcList[j].Parent + "->" + ProcList[j].ProcName + "->Code: " + ProcList[j].Code);
					if(ProcList[j].Parent == "MainClass" && ProcList[j].ProcName == "Main")
					{
						Console.WriteLine("MainClass->Main() Found");
						mainoff = j;
					}
					j++;
				}
				Console.WriteLine("Printing Data...");
				j = 0;
				while(j < NumberofInts)
				{
					Console.WriteLine(IntList[j].ClassParent + "->"  + IntList[j].IntName + " = " + IntList[j].Value);
					j++;
				}
				j = 0;
				while(j < NumberofStrings)
				{
					Console.WriteLine(StringList[j].ClassParent + "->" + StringList[j].stringname + " = " + StringList[j].Value);
					j++;
				}
				// Time for CodeGen! :)
				// First we'll parse the MainClass->Main code.
				string[] maincode = ProcList[mainoff].Code.Split(new char[]{});
				// Alright time for parsing..
				int index = 0;
				while(index < maincode.Length)
				{
					switch(maincode[index])
					{
					case "LOAD_R0":
						// Load register R0 with value
						// Let's see if it belongs to a class
						string[] parts = maincode[index+1].Split(new string[] { "->" }, StringSplitOptions.None);
						// LOAD_R0 is done in the form of class->value or proc
						int q, classstore = 0;
						for(q = 0; q < yc.MainClass.NumberofClasses; q++)
						{
							if(parts[0] == ClassList[q])
							{
								Console.WriteLine("Class Found: " + ClassList[q]);
								classstore = q;
								q = -1;
								// TODO: You know what I mean
								goto done;
							}
						}
					done:
						if(q != -1)
						{
							Console.WriteLine("#error: Class not found");
						}
						int encounteredproc = 0, encounteredstring = 0, encounteredint = 0;
						// Now let's find that proc or value.
						// First scan the proc list
						for(q = 0; q < yc.MainClass.NumberofProcs; q++)
						{
							if(parts[1] == ProcList[q].ProcName && ProcList[q].Parent == ClassList[classstore])
							{
								Console.WriteLine("#found: proc: " + ProcList[q].ProcName + "<-" + ClassList[classstore]);
								encounteredproc = 1;
								break;
							}
							else if(parts[1] == StringList[q].stringname && StringList[q].ClassParent == ClassList[classstore])
							{ 
								Console.WriteLine("#found string reference: " + StringList[q].stringname + "<-" + ClassList[classstore]);
								encounteredstring = 1;
								break;
							}
							else if(parts[1] == IntList[q].IntName && IntList[q].ClassParent == ClassList[classstore])
							{
								Console.WriteLine("#found int reference: " + IntList[q].IntName + "<-" + ClassList[classstore]);
								encounteredint = 1;
								break;
							}
						}
						if(encounteredproc == 1)
						{
							SourceWriter.Write("LOAD_R0 " + ClassList[classstore]  + "." + ProcList[q].ProcName);
							SourceWriter.Flush();
						}
						else if(encounteredint == 1)
						{
							SourceWriter.Write("LOAD_R0 " + IntList[q]);
							SourceWriter.Flush();
						}
						else if(encounteredstring == 1)
						{
							SourceWriter.WriteLine("LOAD_R0 " + ClassList[classstore] + "." + StringList[q].stringname);
							SourceWriter.WriteLine("JMPF $+" + ClassList[classstore] + "."  + StringList[q].stringname + ".strlen");
							SourceWriter.WriteLine(ClassList[classstore] + "." + StringList[q].stringname + ": db '" + StringList[q].Value + "'");
							SourceWriter.WriteLine(".strlen: dd $-" + ClassList[classstore] + "." + StringList[q].stringname);
							SourceWriter.Flush();

						}
						index += 2;
						break;
					}
					index++;
				}
			}
		}
	}
}
