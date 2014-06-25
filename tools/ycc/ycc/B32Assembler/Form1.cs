using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace B32Assembler
{
    public partial class frmMainForm : Form
    {
        private string SourceProgram;
        private System.Collections.Hashtable LabelTable;
        private int CurrentNdx;
        private ushort AsLength;
        private bool IsEnd;
        private ushort ExecutionAddress;

        private enum Registers
        {
            Unknown = 0,
            A = 4,
            B = 2,
            D = 1,
            X = 16,
            Y = 8
        }

        public frmMainForm()
        {
            InitializeComponent();

            LabelTable = new System.Collections.Hashtable(50);
            CurrentNdx = 0;
            AsLength = 0;
            ExecutionAddress = 0;
            IsEnd = false;
            SourceProgram = "";
            txtOrigin.Text = "1000";
        }

        private void btnSourceBrowse_Click(object sender, EventArgs e)
        {
            this.fdSourceFile.ShowDialog();
            this.txtSourceFileName.Text = fdSourceFile.FileName;
        }

        private void btnOutputBrowse_Click(object sender, EventArgs e)
        {
            this.fdDestinationFile.ShowDialog();
            this.txtOutputFileName.Text = fdDestinationFile.FileName;
        }

        private void btnAssemble_Click(object sender, EventArgs e)
        {
            AsLength = Convert.ToUInt16(this.txtOrigin.Text, 16);
            System.IO.BinaryWriter output;
            System.IO.TextReader input;
            System.IO.FileStream fs = new System.IO.FileStream(this.txtOutputFileName.Text, System.IO.FileMode.Create);

            output = new System.IO.BinaryWriter(fs);

            input = System.IO.File.OpenText(this.txtSourceFileName.Text);
            SourceProgram = input.ReadToEnd();
            input.Close();

            output.Write('B');
            output.Write('3');
            output.Write('2');
            output.Write(Convert.ToUInt16(this.txtOrigin.Text, 16));
            output.Write((ushort)0);
            Parse(output);

            output.Seek(5, System.IO.SeekOrigin.Begin);
            output.Write(ExecutionAddress);
            output.Close();
            fs.Close();
            MessageBox.Show("Done!");
        }

        private void Parse(System.IO.BinaryWriter OutputFile)
        {
            CurrentNdx = 0;
            while (IsEnd == false)
                LabelScan(OutputFile, true);

            IsEnd = false;
            CurrentNdx = 0;
            AsLength = Convert.ToUInt16(this.txtOrigin.Text, 16);

            while (IsEnd == false)
                LabelScan(OutputFile, false);
        }

        private void LabelScan(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {

            if (char.IsLetter(SourceProgram[CurrentNdx]))
            {
                // Must be a label
                if (IsLabelScan) LabelTable.Add(GetLabelName(), AsLength);
                while (SourceProgram[CurrentNdx] != '\n')
                    CurrentNdx++;
                CurrentNdx++;
                return;
            }
            EatWhiteSpaces();
            ReadMneumonic(OutputFile, IsLabelScan);
        }

        private void ReadMneumonic(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            string Mneumonic = "";

            while (!(char.IsWhiteSpace(SourceProgram[CurrentNdx])))
            {
                Mneumonic = Mneumonic + SourceProgram[CurrentNdx];
                CurrentNdx++;
            }
            if (Mneumonic.ToUpper() == "LDX") InterpretLDX(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "LDA") InterpretLDA(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "STA") InterpretSTA(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "CMPA") InterpretCMPA(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "CMPB") InterpretCMPB(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "CMPX") InterpretCMPX(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "CMPY") InterpretCMPY(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "CMPD") InterpretCMPD(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "JMP") InterpretJMP(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "JEQ") InterpretJEQ(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "JNE") InterpretJNE(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "JGT") InterpretJGT(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "JLT") InterpretJLT(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "LDY") InterpretLDY(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "LDB") InterpretLDB(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "INCA") InterpretINCA(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "INCB") InterpretINCB(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "INCX") InterpretINCX(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "INCY") InterpretINCY(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "INCD") InterpretINCD(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "DECA") InterpretDECA(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "DECB") InterpretDECB(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "DECX") InterpretDECX(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "DECY") InterpretDECY(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "DECD") InterpretDECD(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "ROLA") InterpretROLA(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "ROLB") InterpretROLB(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "RORA") InterpretRORA(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "RORB") InterpretRORB(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "ADCA") InterpretADCA(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "ADCB") InterpretADCB(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "ADDA") InterpretADDA(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "ADDB") InterpretADDB(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "ADDAB") InterpretADDAB(OutputFile, IsLabelScan);
            if (Mneumonic.ToUpper() == "END") { IsEnd = true; DoEnd(OutputFile, IsLabelScan); EatWhiteSpaces(); ExecutionAddress = (ushort)LabelTable[(GetLabelName())]; return; }

            while (SourceProgram[CurrentNdx] != '\n')
            {
                CurrentNdx++;
            }
            CurrentNdx++;
        }

        private void DoEnd(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            AsLength++;
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x04);
            }
        }

        private void InterpretLDA(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                byte val = ReadByteValue();
                AsLength += 2;
                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x01);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretLDB(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                byte val = ReadByteValue();
                AsLength += 2;
                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x22);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretLDY(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                ushort val = ReadWordValue();
                AsLength += 3;
                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x23);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretLDX(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                ushort val = ReadWordValue();
                AsLength += 3;
                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x02);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretSTA(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == ',')
            {
                Registers r;
                byte opcode = 0x00;

                CurrentNdx++;
                EatWhiteSpaces();
                r = ReadRegister();
                switch (r)
                {
                    case Registers.X:
                        opcode = 0x03;
                        break;
                }
                AsLength += 1;
                if (!IsLabelScan)
                {
                    OutputFile.Write(opcode);
                }
            }
        }

        private Registers ReadRegister()
        {
            Registers r = Registers.Unknown;

            if ((SourceProgram[CurrentNdx] == 'X') ||
                (SourceProgram[CurrentNdx] == 'x')) r = Registers.X;
            if ((SourceProgram[CurrentNdx] == 'Y') ||
                (SourceProgram[CurrentNdx] == 'y')) r = Registers.Y;
            if ((SourceProgram[CurrentNdx] == 'D') ||
                (SourceProgram[CurrentNdx] == 'd')) r = Registers.D;
            if ((SourceProgram[CurrentNdx] == 'A') ||
                (SourceProgram[CurrentNdx] == 'a')) r = Registers.A;
            if ((SourceProgram[CurrentNdx] == 'B') ||
                (SourceProgram[CurrentNdx] == 'b')) r = Registers.B;

            CurrentNdx++;
            return r;
        }

        private ushort ReadWordValue()
        {
            ushort val = 0;
            bool IsHex = false;
            string sval = "";

            if (SourceProgram[CurrentNdx] == '$')
            {
                CurrentNdx++;
                IsHex = true;
            }

            if ((IsHex == false) && (char.IsLetter(SourceProgram[CurrentNdx])))
            {
                val = (ushort)LabelTable[GetLabelName()];
                return val;
            }

            while (char.IsLetterOrDigit(SourceProgram[CurrentNdx]))
            {
                sval = sval + SourceProgram[CurrentNdx];
                CurrentNdx++;
            }
            if (IsHex)
            {
                val = Convert.ToUInt16(sval, 16);
            }
            else
            {
                val = ushort.Parse(sval);
            }

            return val;
        }

        private byte ReadByteValue()
        {
            byte val = 0;
            bool IsHex = false;
            string sval = "";

            if (SourceProgram[CurrentNdx] == '$')
            {
                CurrentNdx++;
                IsHex = true;
            }

            while (char.IsLetterOrDigit(SourceProgram[CurrentNdx]))
            {
                sval = sval + SourceProgram[CurrentNdx];
                CurrentNdx++;
            }
            if (IsHex)
            {
                val = Convert.ToByte(sval, 16);
            }
            else
            {
                val = byte.Parse(sval);
            }

            return val;
        }

        private void EatWhiteSpaces()
        {
            while (char.IsWhiteSpace(SourceProgram[CurrentNdx]))
            {
                CurrentNdx++;
            }
        }

        private string GetLabelName()
        {
            string lblname = "";

            while (char.IsLetterOrDigit(SourceProgram[CurrentNdx]))
            {
                if (SourceProgram[CurrentNdx] == ':')
                {
                    CurrentNdx++;
                    break;
                }

                lblname = lblname + SourceProgram[CurrentNdx];
                CurrentNdx++;
            }

            return lblname.ToUpper();
        }

        private void InterpretCMPA(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                byte val = ReadByteValue();
                AsLength += 2;
                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x05);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretCMPB(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                byte val = ReadByteValue();
                AsLength += 2;
                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x06);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretCMPX(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                ushort val = ReadWordValue();
                AsLength += 3;
                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x07);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretCMPY(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                ushort val = ReadWordValue();
                AsLength += 3;
                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x08);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretCMPD(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                ushort val = ReadWordValue();
                AsLength += 3;
                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x09);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretJMP(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                AsLength += 3;
                if (IsLabelScan) return;
                ushort val = ReadWordValue();

                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x0A);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretJEQ(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                AsLength += 3;
                if (IsLabelScan) return;
                ushort val = ReadWordValue();

                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x0B);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretJNE(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                AsLength += 3;
                if (IsLabelScan) return;
                ushort val = ReadWordValue();

                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x0C);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretJGT(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                AsLength += 3;
                if (IsLabelScan) return;
                ushort val = ReadWordValue();

                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x0D);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretJLT(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                AsLength += 3;
                if (IsLabelScan) return;
                ushort val = ReadWordValue();

                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x0E);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretINCA(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x0F);
            }
            AsLength++;
        }

        private void InterpretINCB(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x10);
            }
            AsLength++;
        }

        private void InterpretINCX(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x11);
            }
            AsLength++;
        }

        private void InterpretINCY(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x12);
            }
            AsLength++;
        }

        private void InterpretINCD(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x13);
            }
            AsLength++;
        }

        private void InterpretDECA(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x14);
            }
            AsLength++;
        }

        private void InterpretDECB(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x15);
            }
            AsLength++;
        }

        private void InterpretDECX(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x16);
            }
            AsLength++;
        }

        private void InterpretDECY(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x17);
            }
            AsLength++;
        }

        private void InterpretDECD(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x18);
            }
            AsLength++;
        }

        private void InterpretADCA(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x1D);
            }
            AsLength++;
        }

        private void InterpretADCB(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x1E);
            }
            AsLength++;
        }

        private void InterpretADDA(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                AsLength += 2;
                if (IsLabelScan) return;
                ushort val = ReadByteValue();

                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x1F);
                    OutputFile.Write(val);
                }
            }           
        }

        private void InterpretADDB(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            EatWhiteSpaces();
            if (SourceProgram[CurrentNdx] == '#')
            {
                CurrentNdx++;
                AsLength += 2;
                if (IsLabelScan) return;
                ushort val = ReadByteValue();

                if (!IsLabelScan)
                {
                    OutputFile.Write((byte)0x20);
                    OutputFile.Write(val);
                }
            }
        }

        private void InterpretROLB(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x1A);
            }
            AsLength++;
        }

        private void InterpretROLA(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x19);
            }
            AsLength++;
        }

        private void InterpretRORB(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x1C);
            }
            AsLength++;
        }

        private void InterpretRORA(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x1B);
            }
            AsLength++;
        }

        private void InterpretADDAB(System.IO.BinaryWriter OutputFile, bool IsLabelScan)
        {
            if (!IsLabelScan)
            {
                OutputFile.Write((byte)0x21);
            }
            AsLength++;
        }
    }
}
