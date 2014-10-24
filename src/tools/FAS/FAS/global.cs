using System;

namespace FAS
{
	public class Global
	{
		/** Hash Table for storing out our Labels **/
		public static System.Collections.Hashtable LabelTable;
		public static int CurrentIndex;
		public static uint AsLength;
		public static bool IsEnd;
		public static UInt32 OriginAddress;
		/** CPU Registers **/
		public enum Registers {
			 R0 = 0,
			 R1 = 0,
			 R2 = 0,
			 R3 = 0,
			 R4 = 0,
			 R5 = 0,
			 SP = 0,
			 IP = 0
		}
	}
}

