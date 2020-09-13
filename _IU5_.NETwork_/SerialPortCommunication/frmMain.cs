using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
using PCComm;
namespace PCComm
{
    public partial class frmMain : Form
    {

        #region variables
        Timer mytimer = new Timer();//?????? ?????? ACK_UPLINK
        Timer mytimer1 = new Timer();//?????? ?????? ACK_DOWNLINK
        Timer mytimer2 = new Timer();//?????? ?????? ACK_ACTIVELINK

    
        Timer mytimer3 = new Timer();//?????? ?????? ACK_ACTIVELINK

        int CountDownLinkTry = 3; //??????? ????????? ??????????
        int CountTry = 3; // ??????? ??????????
        int CountTryActiveLink = 3; //??????? ??????? ? ?????

        CommunicationManager comm = new CommunicationManager();
        string transType = string.Empty;

        string user1; // ??? ???????????? ? 1
        string user2; // ??? ???????????? ? 2

        Form4 f = new Form4();
        private string settings_file = Application.StartupPath + @"\settings.txt"; // ???? ? ????? ????????

        #endregion

        public frmMain()
        {
            InitializeComponent();
        }

        private void frmMain_Load(object sender, EventArgs e)
        {
           f.FormClosed +=new FormClosedEventHandler(f_FormClosed);
           LoadValues();
           SetDefaults();
           SetControlState();
        }

        private void f_FormClosed(object sender, EventArgs e)
        {
            user1 = f.user1;
            user2 = f.user2;
            comm.user1 = user1;
            comm.user2 = user2;
        }

        private void cmdOpen_Click(object sender, EventArgs e)
        {
      
            CountTry = 3;
            CountTryActiveLink = 3;
            CountDownLinkTry = 3;

            comm.Parity = cboParity.Text;
            comm.StopBits = cboStop.Text;
            comm.DataBits = cboData.Text;
            comm.BaudRate = cboBaud.Text;
            comm.DisplayWindow = rtbDisplay;
            comm.PortName = cboPort.Text; 
            comm.OpenPort();

                      
            cmdOpen.Enabled = false;
            cmdClose.Enabled = true;
            cmdConnect.Enabled = true;
            cmdConnect.Select();

        }           

        private void SetDefaults()
        {
            cboPort.SelectedIndex = 0;
            cboBaud.SelectedText = "9600";
            cboParity.SelectedIndex = 0;
            cboStop.SelectedIndex = 1;
            cboData.SelectedIndex = 1;
        }

        private void LoadValues()
        {
            comm.SetPortNameValues(cboPort);
            comm.SetParityValues(cboParity);
            comm.SetStopBitValues(cboStop);
            mytimer.Tick += new EventHandler(Tick);
            mytimer1.Tick += new EventHandler(Tick_mytimer1);

         
            mytimer2.Tick += new EventHandler(Tick_mytimer2);
            mytimer.Interval = 1000;//???????? ???????? ?????? ????? ???????????? ??????????...
            mytimer1.Interval = 1000;////???????? ???????? ?????? ????? ??????? ??????????...
            mytimer2.Interval = 10000; //???????? ???????? ?????? ????? ??????????? ??????????...
           
            
            mytimer3.Tick += new EventHandler(Tick_mytimer3);
            mytimer3.Interval = 15000;

            openFileDialog1.FileOk += new CancelEventHandler(openFileDialog1_FileOk);
            openFileDialog1.FileName = "";
            
            
        }

        private void SetControlState()
        {
            cboPort.Select();
            txtSend.Enabled = false;
            cmdSend.Enabled = false;
            cmdClose.Enabled = false;
            cmdConnect.Enabled = false;
            cmdDisconnect.Enabled = false;
        }

        private void cmdSend_Click(object sender, EventArgs e)
        {
            if (txtSend.Text != "")
            {

                comm.CurrentMsg = txtSend.Text;//????????? ????????? ?????????.


                comm.WriteData(txtSend.Text, CommunicationManager.FrameType.DAT, false);

                txtSend.Clear();
                txtSend.Select();
            }
        }
        
        private void cmdClose_Click(object sender, EventArgs e)
        {
            
            CountDownLinkTry = 3;
            CountTry = 3;
            CountTryActiveLink = 3;
            
            cmdOpen.Enabled = true;
            cmdClose.Enabled = false;
            cmdSend.Enabled = false;
            cmdConnect.Enabled = false;
            cmdDisconnect.Enabled = false;
            txtSend.Clear();
            txtSend.Enabled = false;
            cboPort.Select();
            comm.ClosePort();
        }

        private void cmdConnect_Click(object sender, EventArgs e)
        {
            CountDownLinkTry = 3;
            CountTry = 3;
            CountTryActiveLink = 3;

            cmdConnect.Enabled = false;//?????? ?????? ?????? ????? ???????? ?????????? ??????????

            comm.WriteData(null, CommunicationManager.FrameType.UPLINK, false);

            comm.WriteData(null, CommunicationManager.FrameType.LINKACTIVE, false);

            
            mytimer.Start();//???? ????????? ACK_UPLINK
            mytimer2.Start();//????????? ACTIVELINK->ACK_ACTIVELINK
            
        }

        #region Timers
        /// <summary>
        /// ?????????? ??????? ????????? ?????????
        /// ???????? ????? ACK_UPLINK
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Tick(object sender, EventArgs e)
        {
            if (CountTry > 0)
            {
                if (comm.LinkActive == true)
                {
                    pictureBox1.Visible = true;
                    txtSend.Enabled = true;
                    cmdSend.Enabled = true;
                    txtSend.Clear();
                    cmdConnect.Enabled = false;
                    cmdDisconnect.Enabled = true;
                    cmdOpen.Enabled = false;
                    cmdClose.Enabled = false;

                    txtSend.Select();
                    CountTry = 3;//???????????? ????? ???????
                                                        
                    
                    mytimer.Stop();//??????? ???????????
                }
                else
                {
                    CountTry--;//?? ???????????, ???? ??? ???????
                    comm.WriteData(null, CommunicationManager.FrameType.UPLINK, false);
                }
            }
            else
            {
                DisconnectionState();
            }
        }

        /// <summary>
        /// ?????????? ??????? ????????? ????????? ????????
        /// ????? ACK_DOWNLINK
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Tick_mytimer1(object sender, EventArgs e)
        {
            if (CountDownLinkTry > 0)
            {
                if (comm.LinkActive == false)
                {
                    pictureBox1.Visible = false;
                    
                    cmdOpen.Enabled = false;
                    cmdClose.Enabled = true;
                    cmdDisconnect.Enabled = false;
                    txtSend.Clear();
                    txtSend.Enabled = false;
                    cmdSend.Enabled = false;
                    cmdConnect.Enabled = true;
                    cmdConnect.Select();
                    
                    
                    CountDownLinkTry = 3;
                    mytimer1.Stop();
                }
                else
                {
                    CountDownLinkTry--;
                    comm.WriteData(txtSend.Text, CommunicationManager.FrameType.DOWNLINK, false);
                }
            }
            else
            {
                DisconnectionState();
            }
        }

        /// <summary>
        /// ?????????? ??????? ???????? ?????????? ??????????
        /// ?????????? ??????????? - ???????? ?? ????????? ????????? ????? ACTIVELINK 
        /// ? ??????? ?????????? (??????? ??????? comm.LinkActive)
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Tick_mytimer2(object sender, EventArgs e)
        {
            
            if (CountTryActiveLink > 0)
            {
                if (comm.LinkActive == true)
                {
                    // ??????? ?????????
                    pictureBox1.Visible = true;
                    //????????? ??????? ?? ????
                    comm.WriteData(null, CommunicationManager.FrameType.LINKACTIVE, false);
                    //?????? ???????
                    CountTryActiveLink = 3;
                }
                else
                {
                    //?????????? ???, ?? ??? ???? ???????
                    pictureBox1.Visible = false;
                    CountTryActiveLink--;
                    comm.WriteData(null, CommunicationManager.FrameType.LINKACTIVE, false);
                }
            }
            else
            {
                DisconnectionState();
                txtSend.Clear();
                cboPort.Select();
            }

        }

        private void Tick_mytimer3(object sender, EventArgs e)
        {

            DateTime time = new DateTime();
            time = DateTime.Now;

            if (((time - comm.dt_new).Seconds > 20) && (comm.dt_new.Second > 0))
            {
                DisconnectionState();
                mytimer3.Stop();
                txtSend.Clear();
                cboPort.Select();
            }

        }

        private void DisconnectionState()
        {
            //?????????? ?? ??????? ??????????, ??????? ???
            comm.LinkActive = false;//?????????? ???
            pictureBox1.Visible = false;

            //??????????????? ??????? ??????/?????????/???????
            CountDownLinkTry = 3;
            CountTry = 3;
            CountTryActiveLink = 3;

            ///???????? ??? ????
            mytimer2.Stop();
            mytimer1.Stop();
            mytimer.Stop();

            txtSend.Enabled = false;
            cmdSend.Enabled = false;
            cmdConnect.Enabled = true;
            cmdDisconnect.Enabled = false;
            cmdOpen.Enabled = false;
            cmdClose.Enabled = true;
 
        }
        #endregion 

        /// <summary>
        /// ?????? ?????????? ????????? ? ???????? comm.DataReceived(???????? ??????? "Port Opened AT DateTime.NOW" 
        /// ? ??????????? ??????? ???????? ??????.
        /// 
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void rtbDisplay_TextChanged(object sender, EventArgs e)
        {
            mytimer3.Start(); // ?????? ???????? ?????????? ?????????? 
            if (comm.LinkActive == true)
            {

                pictureBox1.Visible = true;

                cmdOpen.Enabled = false;
                cmdClose.Enabled = false;
                cmdSend.Enabled = true;
                cmdConnect.Enabled = false;
                cmdDisconnect.Enabled = true;
                txtSend.Enabled = true;

            }
            else
            {
                //???????? ?????????? ?? ?? ?????????
                if (cmdDisconnect.Enabled == true && mytimer2.Enabled == false)//?????????? ???,?? ?????? ?????????? ?? ?? ???????? 
                {
                    pictureBox1.Visible = false;
                    cmdOpen.Enabled = false;
                    cmdClose.Enabled = true;
                    cmdSend.Enabled = false;
                    cmdConnect.Enabled = true;
                    cmdDisconnect.Enabled = false;
                    txtSend.Enabled = false;
                }


                if (cmdDisconnect.Enabled == true && mytimer2.Enabled == true)
                {
                    
                    mytimer2.Stop();
                    pictureBox1.Visible = false;
                    cmdOpen.Enabled = false;
                    cmdClose.Enabled = true;
                    cmdSend.Enabled = false;
                    cmdConnect.Enabled = true;
                    cmdDisconnect.Enabled = false;
                    txtSend.Enabled = false;
                }
               
            }

            
            
        }

        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            mytimer2.Stop();
            mytimer1.Stop();
            mytimer.Stop();
        }

        private void cmdDisconnect_Click(object sender, EventArgs e)
        {
            cmdDisconnect.Enabled=false;
            mytimer2.Stop();//????????????? ?????????? ??????????...
            
            //??????????????? ??????? ??????, ?????????, ????????
            CountDownLinkTry = 3;
            CountTry = 3;
            CountTryActiveLink = 3;
            
            //???? ???? ???????
            comm.WriteData(txtSend.Text, CommunicationManager.FrameType.DOWNLINK, false);
            //???????? ????
            mytimer1.Start();   
        }

        #region design

        private void ????ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Cbo_Rtb_Edit_ColorSet( System.Drawing.Color.LightBlue );
            Cmd_Cbo_FlatStyleSet(FlatStyle.Flat, FlatStyle.Flat);
            Label_GroupBox_MenuItem_Cmd_ForeColorSet(System.Drawing.Color.Gold);
            Cmd_FlatAppearanceBorderColorSet(System.Drawing.Color.Gold);
            Cmd_FlatAppearanceMouseOverBackColorSet(System.Drawing.Color.RoyalBlue);
            this.BackgroundImage = PCComm.Properties.Resources.bg;
            this.Refresh();

        }

        private void ???????ToolStripMenuItem_Click(object sender, EventArgs e)
        {

            Cbo_Rtb_Edit_ColorSet(System.Drawing.Color.PapayaWhip);
            Cmd_Cbo_FlatStyleSet(FlatStyle.Flat, FlatStyle.Flat);
            Label_GroupBox_MenuItem_Cmd_ForeColorSet(System.Drawing.Color.Black);
            Cmd_FlatAppearanceBorderColorSet(System.Drawing.Color.Black);
            Cmd_FlatAppearanceMouseOverBackColorSet(System.Drawing.Color.Orange);
            this.BackgroundImage = PCComm.Properties.Resources.bg1;
            this.Refresh();

        }

        private void ???????????ToolStripMenuItem_Click(object sender, EventArgs e)
        {

            Cbo_Rtb_Edit_ColorSet(System.Drawing.Color.White);
            Cmd_Cbo_FlatStyleSet(FlatStyle.Standard, FlatStyle.Standard);
            Label_GroupBox_MenuItem_Cmd_ForeColorSet(System.Drawing.Color.Black);
            this.BackColor = System.Drawing.Color.LightGray;
            this.BackgroundImage = null;
            this.Refresh();

        }

       


        private void Cbo_Rtb_Edit_ColorSet(Color c)
        {
            cboBaud.BackColor = c;
            cboData.BackColor = c;
            cboParity.BackColor = c;
            cboPort.BackColor = c;
            cboStop.BackColor = c;
            rtbDisplay.BackColor = c;
            txtSend.BackColor = c;
        }


        private void Cmd_Cbo_FlatStyleSet(FlatStyle fs, FlatStyle cbo_fs)
        {
            cmdOpen.FlatStyle = fs;
            cmdClose.FlatStyle = fs;
            cmdConnect.FlatStyle = fs;
            cmdDisconnect.FlatStyle = fs;
            cmdSend.FlatStyle = fs;

            cboBaud.FlatStyle = cbo_fs;
            cboData.FlatStyle = cbo_fs;
            cboParity.FlatStyle = cbo_fs;
            cboPort.FlatStyle = cbo_fs;
            cboStop.FlatStyle = cbo_fs;
        }

        private void Label_GroupBox_MenuItem_Cmd_ForeColorSet(Color c)
        {
            Label1.ForeColor = c;
            label2.ForeColor = c;
            label3.ForeColor = c;
            label4.ForeColor = c;
            label5.ForeColor = c;

            GroupBox1.ForeColor = c;
            groupBox2.ForeColor = c;
            groupBox3.ForeColor = c;

            ToolStripMenuItem1.ForeColor = c;
            toolStripMenuItem2.ForeColor = c;
            toolStripMenuItem3.ForeColor = c;

            cmdOpen.ForeColor = c;
            cmdClose.ForeColor = c;
            cmdConnect.ForeColor = c;
            cmdDisconnect.ForeColor = c;
            cmdSend.ForeColor = c;
        }

        private void Cmd_FlatAppearanceMouseOverBackColorSet(Color c)
        {
            cmdOpen.FlatAppearance.MouseOverBackColor = c;
            cmdClose.FlatAppearance.MouseOverBackColor = c;
            cmdConnect.FlatAppearance.MouseOverBackColor = c;
            cmdDisconnect.FlatAppearance.MouseOverBackColor = c;
            cmdSend.FlatAppearance.MouseOverBackColor = c;

        }

        private void Cmd_FlatAppearanceBorderColorSet(Color c)
        {
            cmdOpen.FlatAppearance.BorderColor = c;
            cmdClose.FlatAppearance.BorderColor = c;
            cmdConnect.FlatAppearance.BorderColor = c;
            cmdDisconnect.FlatAppearance.BorderColor = c;
            cmdSend.FlatAppearance.BorderColor = c;
 
        }

       

        private void ????ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
           
            UnCheckMenuItems();
            ????ToolStripMenuItem.Checked = true;
            Cbo_Rtb_Edit_ColorSet(System.Drawing.Color.LightBlue);
            Cmd_Cbo_FlatStyleSet(FlatStyle.Flat, FlatStyle.Flat);
            Label_GroupBox_MenuItem_Cmd_ForeColorSet(System.Drawing.Color.Gold);
            Cmd_FlatAppearanceBorderColorSet(System.Drawing.Color.Gold);
            Cmd_FlatAppearanceMouseOverBackColorSet(System.Drawing.Color.RoyalBlue);
            this.BackgroundImage = PCComm.Properties.Resources.bg;
            this.Visible = false;
            this.Refresh();
            this.Visible = true;
        }

        private void ???????ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
         
            UnCheckMenuItems();
            ???????ToolStripMenuItem.Checked = true;
            Cbo_Rtb_Edit_ColorSet(System.Drawing.Color.PapayaWhip);
            Cmd_Cbo_FlatStyleSet(FlatStyle.Flat, FlatStyle.Flat);
            Label_GroupBox_MenuItem_Cmd_ForeColorSet(System.Drawing.Color.Black);
            Cmd_FlatAppearanceBorderColorSet(System.Drawing.Color.Black);
            Cmd_FlatAppearanceMouseOverBackColorSet(System.Drawing.Color.Orange);
            this.BackgroundImage = PCComm.Properties.Resources.bg1;
            this.Refresh();
        }

        private void ???????????ToolStripMenuItem_Click_1(object sender, EventArgs e)
        {
           
            UnCheckMenuItems();
            ???????????ToolStripMenuItem.Checked = true;
            Cbo_Rtb_Edit_ColorSet(System.Drawing.Color.White);
            Cmd_Cbo_FlatStyleSet(FlatStyle.Standard, FlatStyle.Standard);
            Label_GroupBox_MenuItem_Cmd_ForeColorSet(System.Drawing.Color.Black);
            this.BackColor = System.Drawing.Color.LightGray;
            this.BackgroundImage = null;
            this.Refresh();

        }

        private void UnCheckMenuItems()
        {
            ????ToolStripMenuItem.Checked = false;
            ???????ToolStripMenuItem.Checked = false;
            ???????????ToolStripMenuItem.Checked = false;
        
        }

        #endregion

        private void toolStripMenuItem4_Click(object sender, EventArgs e)
        {
            Form1 f = new Form1();
            f.Show();            
        }

        

        private void button3_Click(object sender, EventArgs e)
        {
            mytimer2.Stop();           
        }

        private void frmMain_FormClosed(object sender, FormClosedEventArgs e)
        {
       
            // ?????? ??????? ??????? ? ????????? ????
            string path = Application.StartupPath + @"\" + user1 + "_" + user2  + ".txt";
            StreamWriter sw = new StreamWriter(path, true, Encoding.Default);

            for (int i = 0; i < rtbDisplay.Lines.Length; i++)
                sw.WriteLine(rtbDisplay.Lines[i]);

            sw.Close();

        }

        private void ??????????????????ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog1.Filter = "????????? ????? (*.txt)|*.txt";
            openFileDialog1.InitialDirectory = Application.StartupPath;
            openFileDialog1.ShowDialog();
        }

        private void openFileDialog1_FileOk(object sender, EventArgs e)
        {
            Form3 f = new Form3();
            f.filepath = openFileDialog1.FileName; // ???????? ? ????? 3 ???? ? ?????????? ????? ???????
            
            f.Text = "??????? ( " + openFileDialog1.SafeFileName.Replace(".txt", "") + " )"; 
            f.Show();
        }

        private void frmMain_Shown(object sender, EventArgs e)
        {
            f.Show();      
        }

    }
}