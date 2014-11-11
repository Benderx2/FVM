using System;
using System.Collections.Generic;
using System.Text;
using System.Threading.Tasks;

namespace fbuild
{
	class iconsole
	{
		public static void setColor(int col)
		{
			switch (col)
			{
				case 0:
				Console.ForegroundColor = ConsoleColor.Black;
				break;
				case 1:
				Console.ForegroundColor = ConsoleColor.Blue;
				break;
				case 2:
				Console.ForegroundColor = ConsoleColor.Green;
				break;
				case 3:
				Console.ForegroundColor = ConsoleColor.Cyan;
				break;
				case 4:
				Console.ForegroundColor = ConsoleColor.Red;
				break;
				case 5:
				Console.ForegroundColor = ConsoleColor.Yellow;
				break;
				case 15:
				Console.ForegroundColor = ConsoleColor.White;
				break;
				default:
				Console.ForegroundColor = ConsoleColor.White;
				break;
			}
		}
	}
}