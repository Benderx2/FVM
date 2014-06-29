using System;
using System.Text.RegularExpressions;
using System.Collections.Generic;
namespace yc
{
	class MainClass
	{
		public struct PolyMorphClass {
			public string classptr;
			public string classname;
		}
		public struct Proc {
			public string ProcName;
			public string Parent;
			public string Code;
			public int used;
			public int isextern;
			public Proc (string _procname, string _parent, string _code, int _used, int _isextern)
			{
				ProcName = _procname;
				Parent = _parent;
				Code = _code;
				used = _used;
				isextern = _isextern;
			}
		};
		public struct IntType
		{
			public string ClassParent;
			public string IntName;
			public Int32 Value;
			public int used;
		}
		public struct StringType {
			public string ClassParent;
			public string stringname;
			public string Value;
			public int used;
			public StringType( string _classpar, string _name, string _value, int _used)
			{
				ClassParent = _classpar;
				stringname = _name;
				Value = _value;
				used = _used;
			}
		}
		private static string SourceText;
		public static int CurrentIndex;
		private static System.Collections.Generic.List<string> ClassList;
		private static int NumberofClasses = 0;
		private static int NumberofProcs = 0;
		private static int NumberofInts = 0;
		private static int NumberofStrings = 0;
		private static int NumberOfUsedProcs;
		public static List<Proc> ProcList;
		public static List<IntType> IntList;
		public static List<StringType> StringList;
		public static List<Proc> UsedProcs;
		public static Proc TempProc;
		public static IntType TempInt;
		public static StringType TempString;
		public static bool whileinclass = false;
		public static bool whileinproc = false;
		public static int index = 0;
		public static int isok = 0;
		public static int MinusOne = -1;
		public static string regstring = "";
		public static int q, classstore;
		public static string codegendata = "";
		public static string[] parts;
		public static int libcompile = 0;
		public static System.IO.StreamWriter SourceWriter;
		public static System.IO.TextReader SourceReader;
		public static void Main (string[] args)
		{
			SourceText = "";
			CurrentIndex = 0;
			NumberOfUsedProcs = 0;
			ClassList = new System.Collections.Generic.List<string> (1024);
			ProcList = new List<Proc>(1024);
			IntList = new List<IntType>(1024);
			UsedProcs = new List<Proc>(1024);
			StringList = new List<StringType>(1024);
			TempProc = new Proc();
			TempInt = new IntType();
			TempString = new StringType();
			if (args.Length >= 2) {
				if(System.IO.File.Exists(args[1])){
					System.IO.File.Delete(args[1]);
				}
				if(args.Length == 3)
				{
					if(args[2] == "-lib")
					{
						libcompile = 1;
					}
				}
				SourceWriter = new System.IO.StreamWriter (args [1], true);
				SourceReader = System.IO.File.OpenText(args[0]);
				SourceText = SourceReader.ReadToEnd();
				Console.WriteLine(SourceText);
				/** Add the required stuff **/
				if(libcompile != 1)
				{
				SourceWriter.Write("include 'a32.inc'"+ Environment.NewLine);
				SourceWriter.Write("_start:" + Environment.NewLine + "PUSH R0" + Environment.NewLine + "JMPF MainClass.Main" + Environment.NewLine);
				SourceWriter.Write("MainClass.Main:" + Environment.NewLine);
				SourceWriter.Flush();
				}
				string[] tokens = SourceText.Split(new Char [] { });
				Console.WriteLine(tokens.Length.ToString());
				int i = 0;
				bool error = false;
				/** Preprocessor **/
				i = 0;
				while(i != tokens.Length && error == false)
				{
					switch(tokens[i])
					{
					case "$include":
						Console.WriteLine("#include!");
						try {
						SourceReader = System.IO.File.OpenText(tokens[i+1]);
						SourceText = SourceReader.ReadToEnd() + SourceText;
						}
						catch (System.IO.FileNotFoundException)
						{
							Console.WriteLine("#error: $include file not found");
							error = true;
						}
						i++;
						break;
					}
					i++;
				}
				if(error == true)
				{
					while(true){}
				}
				// Reset vars
				i = 0;
				error = false;
				tokens = SourceText.Split(new char[] { });
				/** Piece of shit Lexer. **/
				while(i != tokens.Length && error == false)
				{
					switch (tokens[i].ToString())
					{
					case "\n":
					case "\t":
					case "\r":
						break;
					case "require":
					SourceWriter.Write("JMPF @f" + Environment.NewLine + "include " + tokens[i+1] + Environment.NewLine + "@@:");
					SourceWriter.Flush();
					i++;
						break;
					case "externproc":
						string[] eprocs = tokens[i+1].Split(new string[] { "->" }, StringSplitOptions.None);
						if (eprocs.Length != 2)
						{
							error = true;
							Console.WriteLine("error: Invalid external procedure declaration");
							break;
						}
						// add teh class
						ClassList.Add(eprocs[0]);
						NumberofClasses++;
						// class->proc form
						TempProc.Parent = eprocs[0];
						TempProc.ProcName = eprocs[1];
						TempProc.isextern = 1;
						ProcList.Add(TempProc);
						NumberofProcs++;
						index++;
						break;
					case "class":
						Console.WriteLine("class found()");
						if(tokens[i+2] != "{")
						{
							Console.WriteLine("#error: expected \"{\"");
							error = true;
						}

						/** Yes we have a class that didn't end **/
						whileinclass = true;
						ClassList.Add(tokens[i+1]);
						NumberofClasses += 1;
						i += 1;
						break;
					case "proc":
						Console.WriteLine("proc found()");
						if(tokens[i+2] != "{")
						{
							Console.WriteLine("#error expected \"{\" while declaring proc");
							error = true;
						}
						whileinproc = true;
						TempProc.Parent = ClassList[NumberofClasses - 1];
						TempProc.ProcName = tokens[i+1];
						i += 3;
						TempProc.Code = "";
						while(tokens[i] != "}")
						{
							if(tokens[i] == "/**")
							{
								while(tokens[i] != "**/")
								{
									i++;
								}
								i++;
							}
							TempProc.Code = TempProc.Code + tokens[i] + "\n";
							i++;
						}
						i++;
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
						TempString.used = 1;
						StringList.Add(TempString);
						NumberofStrings++;
						codegendata = codegendata + Environment.NewLine + TempString.ClassParent + "." + TempString.stringname + ": db '" + TempString.Value + "', 0";
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
				CodeGen(maincode);
				// Fill in the used procs
				int r = 0;
				string[] procused;
				while(r <= NumberOfUsedProcs-1)
				{
					Console.WriteLine(UsedProcs[r].Parent + "." + UsedProcs[r].ProcName + ":"+ UsedProcs[r].Code);
					SourceWriter.WriteLine(UsedProcs[r].Parent + "." + UsedProcs[r].ProcName + ":");
					procused = UsedProcs[r].Code.Split(new char[]{});
					Console.WriteLine("L"  + index + " " + procused.Length);
					CodeGen(procused);
					r++;
				}
				if(libcompile != 1)
				{
					SourceWriter.Write("_end_start:" + Environment.NewLine + "_data:" + Environment.NewLine + codegendata + Environment.NewLine + "_end_data:" + Environment.NewLine + "_bss:" + Environment.NewLine + "_end_bss:");
					SourceWriter.Flush();
					System.Diagnostics.Process.Start("fasm", args[1]);
				}
				else {
					SourceWriter.Write(Environment.NewLine + codegendata);
				}
				SourceWriter.Flush();
		}
	}
	public static void CodeGen(string[] maincode)
		{
			int callproc = 0;
			index = 0;
				// Alright time for parsing..
				while(index < maincode.Length)
				{
				bool isnumber = false;
					switch(maincode[index])
					{
					case "\n":
					case "\t":
					case "\r":
					case " ":
					Console.Write("__");
					index++;
						break;
					case "LOAD_R0":
					if(isnumber || maincode[index+1] == "R1" || maincode[index+1] == "R0" || maincode[index+1] == "R2" || maincode[index+1] == "R3" || maincode[index+1] == "R4" || maincode[index+1] == "R5")
						{
							SourceWriter.WriteLine(maincode[index] + " " + maincode[index+1]);
							index++;
							break;
						}
						isok = 1;
						regstring = "LOAD_R0";
						goto case "\0";
					case "LOAD_R1":
						if(isnumber || maincode[index+1] == "R1" || maincode[index+1] == "R0" || maincode[index+1] == "R2" || maincode[index+1] == "R3" || maincode[index+1] == "R4" || maincode[index+1] == "R5")
						{
							SourceWriter.WriteLine(maincode[index] + " " +   maincode[index+1]);
							index++;
							break;
						}						
						isok = 1;
						regstring = "LOAD_R1";
						goto case "\0";
					case "LOAD_R2":
						if(isnumber || maincode[index+1] == "R1" || maincode[index+1] == "R0" || maincode[index+1] == "R2" || maincode[index+1] == "R3" || maincode[index+1] == "R4" || maincode[index+1] == "R5")
						{
							SourceWriter.WriteLine(maincode[index] + " " + maincode[index+1]);
							index++;
							break;
						}
						isok = 1;
						regstring = "LOAD_R2";
						goto case "\0";
					case "LOAD_R3":
						if(isnumber || maincode[index+1] == "R1" || maincode[index+1] == "R0" || maincode[index+1] == "R2" || maincode[index+1] == "R3" || maincode[index+1] == "R4" || maincode[index+1] == "R5")
						{
							SourceWriter.WriteLine(maincode[index] + " " + maincode[index+1]);
							index++;
							break;
						}
						isok = 1;
						regstring = "LOAD_R3";
						goto case "\0";
					case "LOAD_R4":
						if(isnumber || maincode[index+1] == "R1" || maincode[index+1] == "R0" || maincode[index+1] == "R2" || maincode[index+1] == "R3" || maincode[index+1] == "R4" || maincode[index+1] == "R5")
						{
							SourceWriter.WriteLine(maincode[index] + " " + maincode[index+1]);
							index++;
							break;
						}
						isok = 1;
						regstring = "LOAD_R4";
						goto case "\0";
				case "LOAD_R5":
						if(isnumber || maincode[index+1] == "R1" || maincode[index+1] == "R0" || maincode[index+1] == "R2" || maincode[index+1] == "R3" || maincode[index+1] == "R4" || maincode[index+1] == "R5")
						{
							SourceWriter.WriteLine(maincode[index] + " " + maincode[index+1]);
							index++;
							break;
						}
						isok = 1;
						regstring = "LOAD_R5";
					goto case "\0";
				case "CALLF":
					isok = 1;
					regstring = "CALLF";
					goto case "\0";
					case "CMPR":
						SourceWriter.Write("CMPR " + maincode[index+1] + maincode[index+2]);
						SourceWriter.Flush();
						index += 2;
						break;
					case "ADDR":
						SourceWriter.Write("ADDR " + maincode[index+1] + maincode[index+2]);
						SourceWriter.Flush();
						index += 2;
						break;
					case "SUBR":
						SourceWriter.Write("SUBR " + maincode[index+1] + maincode[index+2]);
						SourceWriter.Flush();
						index += 2;
						break;
					case "JMPF_L":
					case "LOAD_FROM_SP":
					case "PUSH":
					case "POP":
					case "MUL":
					case "DIV":
					case "JMPF":
					case "VM_CALL":
					case "JMPF_E":
					case "JMPF_G":
						SourceWriter.Write(maincode[index]+ " " + maincode[index+1]);
						SourceWriter.Flush();
						index++;
						break;
				case "CALLPROC":
					callproc = 1;
					regstring = "CALLF";
					goto case "\0";
					default:
						// Console.WriteLine("WARNING: UD2");
						SourceWriter.WriteLine(maincode[index]);
						SourceWriter.Flush();
						break;
				case "\0":
						Console.WriteLine(index);
						 parts = maincode[index+1].Split(new string[] { "->" }, StringSplitOptions.None);
						// LOAD_R0 is done in the form of class->value or proc
						q = 0; classstore = 0;
						for(q = 0; q <= yc.MainClass.NumberofClasses; q++)
						{
							if(parts.Length != 2)
							{
							Console.WriteLine("F>>K OFF");
							Console.WriteLine("Expected parts.length is 2 but: " + parts.Length  + " Unwanted puke: "+ parts[parts.Length-1]);
							while(true)
							{
							}
							}
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
						int x = 0;
						int encounteredproc = 0, encounteredstring = 0, encounteredint = 0;
						// Now let's find that proc or value.
						// First scan the proc list
						for(q = 0; q < yc.MainClass.NumberofProcs; q++)
						{
							if(parts[1] == ProcList[q].ProcName && ProcList[q].Parent == ClassList[classstore])
							{
								Console.WriteLine("#found: proc: " + ProcList[q].ProcName + "<-" + ClassList[classstore]);
								encounteredproc = 1;
								encounteredint = 0;
								encounteredstring = 0;
								x = q;
								break;
							}
						}

						for(q = 0; q < yc.MainClass.NumberofStrings; q += 0)
						{
							if(parts[1] == StringList[q].stringname && StringList[q].ClassParent == ClassList[classstore])
							{ 
								Console.WriteLine("#found string reference: " + StringList[q].stringname + "<-" + ClassList[classstore]);
								encounteredstring = 1;
								encounteredproc = 0;
								encounteredint = 0;
								x = q;
								break;
							}
							q++;
						}
						for(q = 0; q < yc.MainClass.NumberofInts; q++)
						{
							if(parts[1] == IntList[q].IntName && IntList[q].ClassParent == ClassList[classstore])
							{
								Console.WriteLine("#found int reference: " + IntList[q].IntName + "<-" + ClassList[classstore]);
								encounteredint = 1;
								encounteredproc = 0;
								encounteredstring = 0;
							x = q;
								break;
							}
						}
						if(encounteredproc == 1)
						{
						//q--;
							if(ProcList[x].used == 0 && ProcList[x].isextern != 1)
							{
								UsedProcs.Add(ProcList[x] );
								NumberOfUsedProcs++;
								ProcList[x] = new Proc(ProcList[x].ProcName, ProcList[x].Parent, ProcList[x].Code, /** Used Parameter **/ 1, ProcList[x].isextern);
							}
						Console.WriteLine("FICKING " + ProcList[x].ProcName + " NUM:" + x);
							if(callproc == 1)
							{
							string[] args = maincode[index+2].Split(new char[] { ',' });
							int e3 = 0;
							callproc = 0;
							string[] classandproc;
							if(args.Length == 0)
							{
								Console.WriteLine("#ERROR: CALLPROC with not arguments, use CALLF instead");
							}
							while(e3 <= args.Length - 1)
							{
								classandproc = args[e3].Split(new string[] { "->" }, StringSplitOptions.None);
								if(classandproc.Length != 2)
								{
									Console.WriteLine("#ERROR: CALLPROC isn't in class->int/string, class->proc format");
									Console.WriteLine(classandproc.Length);
								}
									int isint = 0;
									isint = 0;
									// Let's see if it's an int
									int xt = 0;
									if(classandproc[0][0] == '$')
									{
										classandproc[0] = classandproc[0].Substring(1);
										Console.WriteLine("Found $");
									Console.WriteLine(classandproc[0]);
										// Yup
										while(xt < NumberofInts)
										{
										if(IntList[xt].ClassParent == classandproc[0] && IntList[xt].IntName == classandproc[1])
											{
											//Console.WriteLine(IntList[xt].ClassParent + "fuck");
												isint = 1;
												break;
											}
											xt++;
										}
									}
									if(isint == 0)
									{
										SourceWriter.WriteLine("PUSH " + classandproc[0] + "." + classandproc[1]);
									}
									else {
										SourceWriter.WriteLine("PUSH " + IntList[xt].Value.ToString());
									}

								e3++;
							}
							index++;
							}
							SourceWriter.Write(regstring + " " + ClassList[classstore]  + "." + ProcList[x].ProcName);
							SourceWriter.Flush();
						}
						else if(encounteredint == 1)
						{
							SourceWriter.Write(regstring + " " + IntList[x].Value.ToString());
							SourceWriter.Flush();
						}
						else if(encounteredstring == 1)
						{
							
							SourceWriter.WriteLine(regstring + " " + ClassList[classstore] + "." + StringList[x].stringname);
							//SourceWriter.WriteLine("JMPF " + ClassList[classstore] + "."  + StringList[q].stringname + ".next");
							if(StringList[x].used == 0)
							{
								codegendata = codegendata + Environment.NewLine + ClassList[classstore] + "." + StringList[x].stringname + ": db '" + StringList[x].Value + "'" + ", 0";
								StringList[x] = new StringType(StringList[x].ClassParent, StringList[x].stringname, StringList[x].Value, 1);
							}
							
							SourceWriter.Flush();
						}
						index++;
						break;
					}
					index++;
				}
			}
		}
}
