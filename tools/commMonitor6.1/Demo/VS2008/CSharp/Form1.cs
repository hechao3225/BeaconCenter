using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace CSharp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            this.Text = axCommMonitor1.Caption + " FOR VS2008 C# DEMO";
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void btnClear_Click(object sender, EventArgs e)
        {
            this.redtData.Clear();
            this.ctlData.Clear();            
        }

        private void richTextBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void statusStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        bool fActive = false;
        private void btnOpen_Click(object sender, EventArgs e)
        {
          if (!fActive)
            fActive = axCommMonitor1.StartMonitor(this.comboBox1.Text);
          else {         
            axCommMonitor1.StopMonitor();
            fActive = false;
          }

           if (fActive)  
           {
             btnOpen.Text = "Stop Monitor";
             btnOpen.ForeColor = Color.Blue;
             
           }
           else{
               btnOpen.Text = "Start Monitor";
               btnOpen.ForeColor = Color.Black;
           }
        }

        bool fPause = false;
        private void btnPause_Click(object sender, EventArgs e)
        {
              if (axCommMonitor1.PauseMonitor(fPause))
                 fPause = !fPause;
                 
              if (fPause)
            {
                btnPause.Text = "Continue";
                btnPause.ForeColor = Color.Black;
            }
              else
            {
                btnPause.Text = "Pause";
                btnPause.ForeColor = Color.Blue;
            }
        }



        long dwReadTotal = 0;
        long dwWriteTotal = 0;

        private void axCommMonitor1_OnAscii(object sender, AxCommMonitor6x.ICommMonitor6Events_OnAsciiEvent e)
        {
            const  int  IRP_MJ_CREATE                   =0x00;
            const  int  IRP_MJ_CLOSE                    =0x02;
            const  int  IRP_MJ_READ                     =0x03;
            const  int  IRP_MJ_WRITE                    =0x04;
            const  int  IRP_MJ_DEVICE_CONTROL           =0x0E;
            const  int  IRP_MJ_CLEANUP                  =0x12;
            const  int  IRP_MJ_MAXIMUM_FUNCTION         =0x1B;
            const  int  IRP_MJ_FLUSH_BUFFERS            =0x09;
        
            switch(e.dwCtrlCode)
            {
               case IRP_MJ_CLOSE:
                    this.redtData.AppendText(string.Format("{0}: Close\r\n", e.sPortName));
                    break;
               case IRP_MJ_CREATE: 
                    this.redtData.AppendText(string.Format("{0}: Open\r\n", e.sPortName));
                    break;
               case  IRP_MJ_READ:   {
                    dwReadTotal += e.dwSize;
                    this.redtData.SelectionColor = Color.Blue;
                    this.redtData.AppendText(string.Format("{0}, Read({1:D}): {2}\r\n", e.sPortName, e.dwSize, e.sData));                
                    break;
                 }
               case  IRP_MJ_WRITE: {
                    dwWriteTotal += e.dwSize;
                    this.redtData.SelectionColor = Color.Green;
                    this.redtData.AppendText(string.Format("{0}, Write({1:D}): {2}\r\n", e.sPortName, e.dwSize, e.sData));
                    break;
                 }
              default:  {
                   if (e.dwCtrlCode > 0x400)
                       ctlData.AppendText(string.Format("{0}, CTLCode({1:D}): {2}\r\n", e.sPortName, e.dwCtrlCode, e.sData));
                 break;
               }
            }
                
            if ((e.dwCtrlCode == IRP_MJ_READ)  || (e.dwCtrlCode == IRP_MJ_WRITE))
            {
                lblTip.Text = string.Format("Write:  {0:D}(Bytes), Read: {1:D}(Bytes)", dwWriteTotal, dwReadTotal);
                
            }

        }

        private void axCommMonitor1_OnClick(object sender, EventArgs e)
        {
           // axCommMonitor1.AboutBox();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            axCommMonitor1.AboutBox();
        }
    }
}
