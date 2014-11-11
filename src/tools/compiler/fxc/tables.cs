using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace fbuild
{
	class tables
	{
		public struct s_int
		{
			public int value;
			public string name;
		}
		public struct s_string
		{
			public string value;
			public string name;
		}
		public struct s_buffer {
			public string name;
			public int len;
		}
		public static List<string> tokens;
		public static List<string> AST;
		public static List<string> DataTable;
		public static List<s_buffer> BufferTable;
		public static List<s_int> intTable;
		public static List<s_string> stringTable;
	}
}