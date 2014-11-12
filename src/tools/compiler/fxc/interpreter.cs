using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;
namespace fbuild
{
	class interpreter
	{
		public static int off = 0;
		public static char a;
		public static int datcount = 0;
		public static int l_count = 0;
		public static int stack_addr = 0;
		public static tables.s_int temp_sint;
		public static tables.s_string temp_sstring;
		public static tables.s_buffer temp_sbuffer;
		public static tables.s_function temp_sfunction;
		public static List<string> TempList;
		public static System.IO.StreamWriter file;
		public const int RETURN_INT = 0x0;
		public const int RETURN_PTR = 0x1;
		public static int ExecCode(string code, string output)
		{
			TempList = new List<string>();
			file = new System.IO.StreamWriter (output);
			file.AutoFlush = true;
			// Fill up subroutines
			file.WriteLine ("include \"a32.inc\"");
			file.WriteLine ("; Flouronix Compiler Standard Library routines.");
			file.WriteLine ("_print:");
			file.WriteLine ("PUSH R0");
			file.WriteLine ("PUSH R1");
			file.WriteLine (".loop:");
			file.WriteLine ("LOAD_BYTE");
			file.WriteLine ("CMPR R1, 0");
			file.WriteLine ("JMPF_E .quit");
			file.WriteLine ("VM_CALL 0x0");
			file.WriteLine ("JMPF .loop");
			file.WriteLine (".quit:");
			file.WriteLine ("POP R1");
			file.WriteLine ("POP R0");
			file.WriteLine ("RETF");
			file.WriteLine ("_read:");
			file.WriteLine ("PUSH R0");
			file.WriteLine ("PUSH R1");
			file.WriteLine (".loop:");
			file.WriteLine ("VM_CALL 0x1");
			file.WriteLine ("CMPR R1, 13");
			file.WriteLine ("JMPF_E .quit");
			file.WriteLine ("CMPR R1, 0");
			file.WriteLine ("JMPF_E .loop");
			file.WriteLine ("VM_CALL 0x0");
			file.WriteLine ("STORE_BYTE");
			file.WriteLine ("JMPF .loop");
			file.WriteLine (".quit:");
			file.WriteLine ("POP R1");
			file.WriteLine ("POP R0");
			file.WriteLine ("RETF");
			file.WriteLine ("_strcmp:");
			file.WriteLine ("MEMCMP");
			file.WriteLine ("RETF");
			file.WriteLine ("_memcpy:");
			file.WriteLine ("MEMCPY");
			file.WriteLine ("RETF");
			file.WriteLine ("_start:");
			/** tokenize code **/
			generateTokens(code);
			int count=0;
			while (count < tables.tokens.Count) {
				if (tables.tokens [count] == "proc") {
					temp_sfunction.name = tables.tokens [count + 1];
					temp_sfunction.nargs = Convert.ToInt32 (tables.tokens [count + 2]);
					temp_sfunction.off = count + 3;
					temp_sfunction.tokens = new List<string>();
					tables.functionTable.Add (temp_sfunction);
					count += 2;
				}
				count++;
			}
			int fidx = 0;
			int j = 0;
			string temp = "";
			while (fidx<tables.functionTable.Count) {
				temp = "";
				j = tables.functionTable [fidx].off;
				while (temp!="endf") {
					temp = tables.tokens [j];
					tables.functionTable [fidx].tokens.Add (temp);
					j++;
				}
				fidx++;
			}
			fidx = 0;
			if (IfFunctionExists ("main") == false) {
				Console.WriteLine ("main - not found..");
			}
			while(fidx < tables.functionTable.Count){
				file.WriteLine ("_" + tables.functionTable [fidx].name + ":");
				int q = 0;
				while (q < tables.functionTable[fidx].tokens.Count) {
					Console.WriteLine (tables.functionTable [fidx].tokens [q]);
					q++;
				}
				Compile (tables.functionTable [fidx].tokens);
				fidx++;
			}
			file.WriteLine ("_end_start:");
			file.WriteLine ("_data:");
			for (int i=0; i < tables.DataTable.Count; i++) {
				file.WriteLine (tables.DataTable [i]);
			}
			for (int i=0; i < tables.BufferTable.Count; i++) {
				file.WriteLine (tables.BufferTable [i].name + ": times " + tables.BufferTable [i].len.ToString () + " db 0");
			}
			file.WriteLine ("_end_data:");
			file.WriteLine ("_bss:");
			file.WriteLine ("_end_bss:");
			file.Flush ();
			return 0;
		}
		public static int generateTokens(string code)
		{
			int i = 0;
			bool iscomment = false;
			bool isstring = false;
			string dynamicstr = "";
			while(i < code.Length)
			{
				dynamicstr = "";
				iscomment = false;
				// Skip newlines...
				while (a == 0 || a == '\n' || a == '\t' || a == '\r' || a == ' ') { /* just make sure we don't overflow! */ if (i >= code.Length) { return 0; } a = code[i]; i++; }
				i--;
				/** Grab the token until a separator **/
				while (a != 0 && a != '\n' && a != '\t' && a != '\r' && a != ' ' && i < code.Length)
				{
					a = code[i];
					if(a == '#')
					{
						a = 'x';
						i++;
						while (a != '#')
						{
							if (i >= code.Length) { return 0;  }
							a = code[i];
							i++;
						}
						iscomment = true;
					}
					// we need to handle strings differently...
					else if (a == '"')
					{
						a = 'x';
						dynamicstr = "";
						i++;
						while (a!='"')
						{

							a = code[i];
							if (a == '"') { }
							else
							{
								dynamicstr = dynamicstr + a;
							}
							i++;
						}
						tables.tokens.Add(dynamicstr);
						dynamicstr = "";
						i +=1;
					}
					else if(a == ' ' || a == '\n' || a == '\r' || a == '\t')
					{

					}
					// else keep processing
					else
					{
						dynamicstr = dynamicstr + a;
						i++;
					}
				}
				if (iscomment == false)
				{
					tables.tokens.Add(dynamicstr);
					dynamicstr = "";
				}
			}

			return 0;
		}
		static bool CheckToken(int cur, int no)
		{
			if (tables.tokens.Count - cur < no) { return false; }
			return true;
		}
		static string GetStringValueByName(string name)
		{
			for(int i = 0; i < tables.stringTable.Count; i++)
			{
				if(tables.stringTable[i].name == name)
				{
					return tables.stringTable[i].value;
				}
			}
			return null;
		}
		static bool IfIntExists(string name)
		{
			for (int i = 0; i < tables.intTable.Count; i++) {
				if (tables.intTable [i].name == name) {
					return true;
				}
			}
			return true;
		}
		static int GetIntValueByName(string name)
		{
			for (int i = 0; i < tables.intTable.Count; i++) {
				if (tables.intTable [i].name == name) {
					return stack_addr - tables.intTable[i].stack_addr;
				}
			}
			return 0;
		}
		static bool IfBufferExists(string name)
		{
			for(int i = 0; i < tables.BufferTable.Count; i++)
			{
				if(tables.BufferTable[i].name == name)
				{
					return true;
				}
			}
			return false;
		}
		static bool IfFunctionExists(string name)
		{
			for(int i = 0; i < tables.functionTable.Count; i++)
			{
				if(tables.functionTable[i].name == name)
				{
					return true;
				}
			}
			return false;
		}
		static void SetStringValue(string name, string value)
		{
			for (int i = 0; i < tables.stringTable.Count; i++)
			{
				if (tables.stringTable[i].name == name)
				{
					tables.s_string newstr = new tables.s_string();
					newstr.name = tables.stringTable[i].name;
					newstr.value = value;
					tables.stringTable[i] = newstr;
					return;
				}
			}
		}
		static int Compile(List<string> tokens)
		{
			Console.WriteLine ("Compilation Starting..");
			int count = 0;
			bool set_if = false;
			int set_if_count = 0;
			while (count < tokens.Count) {
				string printvalue = "";
				if (tokens [count] == "print") {
					if (tokens [count + 1] [0] == '$') {
						string temp1 = tokens [count + 1];
						temp1 = temp1.TrimStart ('$'); /*temp1 = temp1.TrimEnd(' ');*/
						string temp2 = GetStringValueByName (temp1);
						printvalue = temp2;
					} else {
						printvalue = tokens [count + 1];
					}
					string __str_name = "__" + datcount.ToString ();
					tables.DataTable.Add (__str_name + ":" + " db '" + printvalue + "', 0");
					datcount++;
			
					file.WriteLine ("LOAD_R0 " + __str_name + "\nCALLF _print");
					count += 2;
				} else if (tokens [count] == "setcolor") {
					tables.AST.Add ("setcolor");
					tables.AST.Add (tables.tokens [count + 1]);
					count += 2;
				} else if (tokens [count] == "int") {
					temp_sint.name = tokens [count + 1];
					temp_sint.value = Convert.ToInt32 (tokens [count + 2]);
					temp_sint.stack_addr = stack_addr;
					tables.intTable.Add (temp_sint);
					file.WriteLine ("PUSH " + tokens [count + 2]);
					stack_addr++;
					count += 3;
				} else if (tokens [count] == "string") {
					temp_sstring.name = tokens [count + 1];
					temp_sstring.value = tokens [count + 2];
					tables.stringTable.Add (temp_sstring);
					count += 3;

				} else if (tokens [count] == "asm") {
					file.WriteLine (tokens [count + 1]);
					count += 2;
				} else if (tokens [count] == "exit") {
					file.WriteLine ("VM_EXIT");
					count++;
				} else if (tokens [count] == "input") {
					if (IfBufferExists (tokens [count + 1]) == true) {
						file.WriteLine ("LOAD_R0 " + tokens [count + 1]);
						file.WriteLine ("CALLF _read");
						count += 2;
					} else {
						Console.WriteLine ("Buffer doesn't Exist! Name : " + tokens [count + 1]);
					}
				} else if (tokens [count] == "buffer") {
					temp_sbuffer.name = tokens [count + 1];
					temp_sbuffer.len = Convert.ToInt32 (tokens [count + 2]);
					tables.BufferTable.Add (temp_sbuffer);
					count += 3;
				} else if (tokens [count] == "endf") {
					break;
				} else if (tokens [count] == "if") {
					string op1 = tokens [count + 1];
					string cmp = tokens [count + 2];
					string op2 = tokens [count + 3];
					int nop1 = 0;
					int nop2 = 0;
					if (IfIntExists (op1) == true) {
						if (IfIntExists (op2) == true) {
							nop1 = GetIntValueByName (op1);
							nop2 = GetIntValueByName (op2);
							file.WriteLine ("LOAD_FROM_SP  " + nop1);
							file.WriteLine ("LOAD_R0 R1");
							file.WriteLine ("LOAD_FROM_SP  " + nop2);
							file.WriteLine ("CMPR R1, R0"); 
							switch (cmp) {
							case "==":
								file.WriteLine ("JMPF_E _lbl_" + l_count.ToString ());
								file.WriteLine ("JMPF @f");
								file.WriteLine ("_lbl_" + l_count.ToString () + ":");
								l_count++;
								break;
							case ">":
								file.WriteLine ("JMPF_G _lbl_" + l_count.ToString ());
								file.WriteLine ("JMPF @f");
								file.WriteLine ("_lbl_" + l_count.ToString () + ":");
								l_count++;
								break;
							case "<":
								file.WriteLine ("JMPF_L _lbl_" + l_count.ToString ());
								file.WriteLine ("JMPF @f");
								file.WriteLine ("_lbl_" + l_count.ToString () + ":");
								l_count++;
								break;
							default:
								Console.WriteLine ("Error: if statement has invalid comparison operator");
								break;
							}
							int i;
							i = count;
							while (i < tokens.Count) {
								if (tokens [i] == "endif") {
									set_if_count = i;
								}
								i++;
							}
							count += 4;
							set_if = true;
						}
					} 
				} else if (tokens [count] == "") {
					Console.WriteLine ("<EOF Reached>");
					break;
				} else if (tokens [count] == "endif") {
					count++;
				}
				else { Console.WriteLine("Error: Invalid Token - " + tokens[count]); count++; }
				if (set_if == true && count == set_if_count) {
					file.WriteLine ("@@:"); // Create anonymous label
					set_if = false;
					set_if_count = 0;
				}
			}
			return 0;
		}
	}
}