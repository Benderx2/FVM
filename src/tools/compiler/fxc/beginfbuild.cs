using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace fbuild
{
	class beginfbuild
	{
		public static int buildall(string sourcefile, string output)
		{
			// build tables
			tables.tokens = new List<string>();
			tables.intTable = new List<tables.s_int>();
			tables.stringTable = new List<tables.s_string>();
			tables.DataTable = new List<string>();
			tables.BufferTable = new List<tables.s_buffer>();
			tables.functionTable = new List<tables.s_function>();
			tables.TempFunctionTable = new List<string>();
			// Open the source file for reading
			string readall = System.IO.File.ReadAllText(sourcefile);
			// Yup now start interpreting
			return fbuild.interpreter.ExecCode(readall, output);
		}
	}
}