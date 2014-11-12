using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace fbuild
{
	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("Flouronix Compiler 2.01");
			if (args.Length != 2) { Console.WriteLine("Error: Build file not found"); Console.ReadKey(); return; }
			fbuild.beginfbuild.buildall(args[0], args[1]);
			Console.WriteLine ("Build Complete");
			Console.ReadLine();
		}
	}
}