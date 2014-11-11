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
		public static tables.s_int temp_sint;
		public static tables.s_string temp_sstring;
		public static tables.s_buffer temp_sbuffer;
		public static int ExecCode(string code, string output)
		{
			System.IO.StreamWriter file = new System.IO.StreamWriter (output);
			file.AutoFlush = true;
			// Fill up subroutines
			file.WriteLine ("include \"a32.inc\"");
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
			file.WriteLine ("_memcpy");
			file.WriteLine ("PUSH R0");
			file.WriteLine ("PUSH R1");
			file.WriteLine ("PUSH R2");
			file.WriteLine ("PUSH R4");
			file.WriteLine (".loop:");
			file.WriteLine ("_start:");
			/** Intialize tables **/
			tables.tokens = new List<string>();
			tables.intTable = new List<tables.s_int>();
			tables.stringTable = new List<tables.s_string>();
			tables.DataTable = new List<string> ();
			tables.BufferTable = new List<tables.s_buffer> ();
			/** tokenize code **/
			generateTokens(code);
			for (int i = 0; i < tables.tokens.Count; i++)
			{
				Console.WriteLine("token: " + tables.tokens[i]);
			}
			int count=0;
			while (count < tables.tokens.Count) {
				string printvalue = "";
				if (tables.tokens [count] == "print") {
					if (tables.tokens [count + 1] [0] == '$') {
						string temp1 = tables.tokens [count + 1];
						temp1 = temp1.TrimStart ('$'); /*temp1 = temp1.TrimEnd(' ');*/
						string temp2 = GetStringValueByName (temp1);
						printvalue = temp2;
					} else {
						printvalue = tables.tokens [count + 1];
					}
					string __str_name = "__" + datcount.ToString ();
					tables.DataTable.Add (__str_name + ":" + " db '" + printvalue + "'");
					datcount++;
					file.WriteLine ("LOAD_R0 " + __str_name + "\nCALLF _print");
					count += 2;
				} else if (tables.tokens [count] == "setcolor") {
					tables.AST.Add ("setcolor");
					tables.AST.Add (tables.tokens [count + 1]);
					count += 2;
				} else if (tables.tokens [count] == "int") {
					temp_sint.name = tables.tokens [count + 1];
					temp_sint.value = Convert.ToInt32 (tables.tokens [count + 2]);
					tables.intTable.Add (temp_sint);
					count += 3;
				} else if (tables.tokens [count] == "string") {
					temp_sstring.name = tables.tokens [count + 1];
					temp_sstring.value = tables.tokens [count + 2];
					tables.stringTable.Add (temp_sstring);
					count += 3;
				
				}
				else if(tables.tokens[count]=="asm"){
					file.WriteLine (tables.tokens [count + 1]);
					count += 2;
			    } else if (tables.tokens [count] == "exit") {
					file.WriteLine ("VM_EXIT");
					count++;
				} else if (tables.tokens [count] == "input") {
					if (IfBufferExists (tables.tokens [count + 1]) == true) {
						file.WriteLine ("LOAD_R0 " + tables.tokens [count + 1]);
						file.WriteLine ("CALLF _read");
						count += 2;
					} else {
						Console.WriteLine ("Buffer doesn't Exist! Name : " + tables.tokens [count + 1]);
					}
				} 
				else if(tables.tokens[count] == "buffer"){
					temp_sbuffer.name = tables.tokens [count + 1];
					temp_sbuffer.len = Convert.ToInt32 (tables.tokens [count + 2]);
					tables.BufferTable.Add (temp_sbuffer);
					count += 3;
				} else if (tables.tokens [count] == "") {
					Console.WriteLine ("<EOF Reached>");
					break;
				}
				else { Console.WriteLine("Error: Invalid Token - " + tables.tokens[count]); count++; }

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
	}
}