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
			fbuild.tables.intTable = new List<fbuild.tables.s_int>();
			fbuild.tables.stringTable = new List<fbuild.tables.s_string>();
			// Open the source file for reading
			string readall = System.IO.File.ReadAllText(sourcefile);
			// Yup now start interpreting
			return fbuild.interpreter.ExecCode(readall, output);
		}
	}
}