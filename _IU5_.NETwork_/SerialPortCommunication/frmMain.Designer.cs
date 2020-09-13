namespace PCComm
{
    partial class frmMain
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(frmMain));
            this.cboData = new System.Windows.Forms.ComboBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.cmdClose = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.cboStop = new System.Windows.Forms.ComboBox();
            this.GroupBox1 = new System.Windows.Forms.GroupBox();
            this.cmdSend = new System.Windows.Forms.Button();
            this.txtSend = new System.Windows.Forms.TextBox();
            this.rtbDisplay = new System.Windows.Forms.RichTextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label2 = new System.Windows.Forms.Label();
            this.cboParity = new System.Windows.Forms.ComboBox();
            this.Label1 = new System.Windows.Forms.Label();
            this.cboBaud = new System.Windows.Forms.ComboBox();
            this.cboPort = new System.Windows.Forms.ComboBox();
            this.cmdOpen = new System.Windows.Forms.Button();
            this.cmdConnect = new System.Windows.Forms.Button();
            this.cmdDisconnect = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.‡Í‚‡ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ÁÓÎÓÚÓÈToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ÒÚ‡Ì‰‡ÚÌ˚ÈToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.ÓÚÍ˚Ú¸‘‡ÈÎ»ÒÚÓËËToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem4 = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.groupBox3.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.GroupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // cboData
            // 
            this.cboData.FormattingEnabled = true;
            this.cboData.Items.AddRange(new object[] {
            "7",
            "8",
            "9"});
            this.cboData.Location = new System.Drawing.Point(9, 195);
            this.cboData.Name = "cboData";
            this.cboData.Size = new System.Drawing.Size(76, 21);
            this.cboData.TabIndex = 14;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.ForeColor = System.Drawing.Color.Black;
            this.label4.Location = new System.Drawing.Point(7, 139);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(56, 13);
            this.label4.TabIndex = 18;
            this.label4.Text = "—ÚÓÔ·ËÚ˚";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.ForeColor = System.Drawing.Color.Black;
            this.label5.Location = new System.Drawing.Point(6, 179);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(73, 13);
            this.label5.TabIndex = 19;
            this.label5.Text = "¡ËÚ˚ ‰‡ÌÌ˚ı";
            // 
            // cmdClose
            // 
            this.cmdClose.BackColor = System.Drawing.Color.Transparent;
            this.cmdClose.Enabled = false;
            this.cmdClose.FlatAppearance.BorderColor = System.Drawing.Color.Gold;
            this.cmdClose.FlatAppearance.BorderSize = 2;
            this.cmdClose.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.cmdClose.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.cmdClose.FlatAppearance.MouseOverBackColor = System.Drawing.Color.RoyalBlue;
            this.cmdClose.ForeColor = System.Drawing.Color.Black;
            this.cmdClose.Location = new System.Drawing.Point(433, 357);
            this.cmdClose.Name = "cmdClose";
            this.cmdClose.Size = new System.Drawing.Size(100, 25);
            this.cmdClose.TabIndex = 5;
            this.cmdClose.Text = "«‡Í˚Ú¸ ÔÓÚ";
            this.cmdClose.UseVisualStyleBackColor = false;
            this.cmdClose.Click += new System.EventHandler(this.cmdClose_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.Transparent;
            this.groupBox3.Controls.Add(this.pictureBox1);
            this.groupBox3.ForeColor = System.Drawing.Color.Black;
            this.groupBox3.Location = new System.Drawing.Point(541, 290);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(96, 60);
            this.groupBox3.TabIndex = 7;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "—ÓÂ‰ËÌÂÌËÂ";
            // 
            // pictureBox1
            // 
            this.pictureBox1.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("pictureBox1.BackgroundImage")));
            this.pictureBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.pictureBox1.Location = new System.Drawing.Point(23, 17);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(49, 41);
            this.pictureBox1.TabIndex = 0;
            this.pictureBox1.TabStop = false;
            this.pictureBox1.Visible = false;
            // 
            // cboStop
            // 
            this.cboStop.FormattingEnabled = true;
            this.cboStop.Location = new System.Drawing.Point(9, 155);
            this.cboStop.Name = "cboStop";
            this.cboStop.Size = new System.Drawing.Size(76, 21);
            this.cboStop.TabIndex = 13;
            // 
            // GroupBox1
            // 
            this.GroupBox1.BackColor = System.Drawing.Color.Transparent;
            this.GroupBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.GroupBox1.Controls.Add(this.cmdSend);
            this.GroupBox1.Controls.Add(this.txtSend);
            this.GroupBox1.Controls.Add(this.rtbDisplay);
            this.GroupBox1.Location = new System.Drawing.Point(14, 63);
            this.GroupBox1.Name = "GroupBox1";
            this.GroupBox1.Size = new System.Drawing.Size(521, 288);
            this.GroupBox1.TabIndex = 4;
            this.GroupBox1.TabStop = false;
            this.GroupBox1.UseCompatibleTextRendering = true;
            // 
            // cmdSend
            // 
            this.cmdSend.Enabled = false;
            this.cmdSend.FlatAppearance.BorderColor = System.Drawing.Color.Gold;
            this.cmdSend.FlatAppearance.BorderSize = 2;
            this.cmdSend.FlatAppearance.MouseDownBackColor = System.Drawing.Color.RoyalBlue;
            this.cmdSend.ForeColor = System.Drawing.Color.Black;
            this.cmdSend.Location = new System.Drawing.Point(436, 259);
            this.cmdSend.Name = "cmdSend";
            this.cmdSend.Size = new System.Drawing.Size(75, 23);
            this.cmdSend.TabIndex = 5;
            this.cmdSend.Text = "ŒÚÔ‡‚ËÚ¸";
            this.cmdSend.UseVisualStyleBackColor = true;
            this.cmdSend.Click += new System.EventHandler(this.cmdSend_Click);
            // 
            // txtSend
            // 
            this.txtSend.Location = new System.Drawing.Point(7, 259);
            this.txtSend.Name = "txtSend";
            this.txtSend.Size = new System.Drawing.Size(411, 20);
            this.txtSend.TabIndex = 4;
            // 
            // rtbDisplay
            // 
            this.rtbDisplay.BackColor = System.Drawing.Color.White;
            this.rtbDisplay.Location = new System.Drawing.Point(7, 16);
            this.rtbDisplay.Name = "rtbDisplay";
            this.rtbDisplay.ReadOnly = true;
            this.rtbDisplay.Size = new System.Drawing.Size(504, 234);
            this.rtbDisplay.TabIndex = 3;
            this.rtbDisplay.Text = "";
            this.rtbDisplay.TextChanged += new System.EventHandler(this.rtbDisplay_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.ForeColor = System.Drawing.Color.Black;
            this.label3.Location = new System.Drawing.Point(6, 98);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(73, 13);
            this.label3.TabIndex = 17;
            this.label3.Text = "¡ËÚ ˜ÂÚÌÓÒÚË";
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Transparent;
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.cboData);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.cboStop);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.cboParity);
            this.groupBox2.Controls.Add(this.Label1);
            this.groupBox2.Controls.Add(this.cboBaud);
            this.groupBox2.Controls.Add(this.cboPort);
            this.groupBox2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(204)));
            this.groupBox2.ForeColor = System.Drawing.Color.Black;
            this.groupBox2.Location = new System.Drawing.Point(541, 63);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(108, 221);
            this.groupBox2.TabIndex = 6;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Õ‡ÒÚÓÈÍË ÔÓÚ‡";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.ForeColor = System.Drawing.Color.Black;
            this.label2.Location = new System.Drawing.Point(6, 58);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(55, 13);
            this.label2.TabIndex = 16;
            this.label2.Text = "—ÍÓÓÒÚ¸";
            // 
            // cboParity
            // 
            this.cboParity.FormattingEnabled = true;
            this.cboParity.Location = new System.Drawing.Point(9, 114);
            this.cboParity.Name = "cboParity";
            this.cboParity.Size = new System.Drawing.Size(76, 21);
            this.cboParity.TabIndex = 12;
            // 
            // Label1
            // 
            this.Label1.AutoSize = true;
            this.Label1.BackColor = System.Drawing.Color.Transparent;
            this.Label1.ForeColor = System.Drawing.Color.Black;
            this.Label1.Location = new System.Drawing.Point(6, 18);
            this.Label1.Name = "Label1";
            this.Label1.Size = new System.Drawing.Size(32, 13);
            this.Label1.TabIndex = 15;
            this.Label1.Text = "œÓÚ";
            // 
            // cboBaud
            // 
            this.cboBaud.FormattingEnabled = true;
            this.cboBaud.Items.AddRange(new object[] {
            "300",
            "600",
            "1200",
            "2400",
            "4800",
            "9600",
            "14400",
            "28800",
            "36000",
            "115000"});
            this.cboBaud.Location = new System.Drawing.Point(9, 74);
            this.cboBaud.Name = "cboBaud";
            this.cboBaud.Size = new System.Drawing.Size(76, 21);
            this.cboBaud.TabIndex = 11;
            // 
            // cboPort
            // 
            this.cboPort.FormattingEnabled = true;
            this.cboPort.Location = new System.Drawing.Point(9, 34);
            this.cboPort.Name = "cboPort";
            this.cboPort.Size = new System.Drawing.Size(76, 21);
            this.cboPort.TabIndex = 10;
            // 
            // cmdOpen
            // 
            this.cmdOpen.BackColor = System.Drawing.Color.Transparent;
            this.cmdOpen.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.cmdOpen.FlatAppearance.BorderColor = System.Drawing.Color.Gold;
            this.cmdOpen.FlatAppearance.BorderSize = 2;
            this.cmdOpen.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.cmdOpen.FlatAppearance.MouseDownBackColor = System.Drawing.Color.Transparent;
            this.cmdOpen.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Orange;
            this.cmdOpen.ForeColor = System.Drawing.Color.Black;
            this.cmdOpen.Location = new System.Drawing.Point(539, 357);
            this.cmdOpen.Name = "cmdOpen";
            this.cmdOpen.Size = new System.Drawing.Size(100, 25);
            this.cmdOpen.TabIndex = 8;
            this.cmdOpen.Text = "ŒÚÍ˚Ú¸ ÔÓÚ";
            this.cmdOpen.UseVisualStyleBackColor = false;
            this.cmdOpen.Click += new System.EventHandler(this.cmdOpen_Click);
            // 
            // cmdConnect
            // 
            this.cmdConnect.BackColor = System.Drawing.Color.Transparent;
            this.cmdConnect.Enabled = false;
            this.cmdConnect.FlatAppearance.BorderColor = System.Drawing.Color.Gold;
            this.cmdConnect.FlatAppearance.BorderSize = 2;
            this.cmdConnect.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.cmdConnect.FlatAppearance.MouseDownBackColor = System.Drawing.Color.RoyalBlue;
            this.cmdConnect.FlatAppearance.MouseOverBackColor = System.Drawing.Color.RoyalBlue;
            this.cmdConnect.ForeColor = System.Drawing.Color.Black;
            this.cmdConnect.Location = new System.Drawing.Point(327, 357);
            this.cmdConnect.Name = "cmdConnect";
            this.cmdConnect.Size = new System.Drawing.Size(100, 25);
            this.cmdConnect.TabIndex = 9;
            this.cmdConnect.Text = "œÓ‰ÍÎ˛˜ËÚ¸Òˇ";
            this.cmdConnect.UseVisualStyleBackColor = false;
            this.cmdConnect.Click += new System.EventHandler(this.cmdConnect_Click);
            // 
            // cmdDisconnect
            // 
            this.cmdDisconnect.BackColor = System.Drawing.Color.Transparent;
            this.cmdDisconnect.Enabled = false;
            this.cmdDisconnect.FlatAppearance.BorderColor = System.Drawing.Color.Gold;
            this.cmdDisconnect.FlatAppearance.BorderSize = 2;
            this.cmdDisconnect.FlatAppearance.CheckedBackColor = System.Drawing.Color.Transparent;
            this.cmdDisconnect.FlatAppearance.MouseDownBackColor = System.Drawing.Color.RoyalBlue;
            this.cmdDisconnect.FlatAppearance.MouseOverBackColor = System.Drawing.Color.Olive;
            this.cmdDisconnect.ForeColor = System.Drawing.Color.Black;
            this.cmdDisconnect.Location = new System.Drawing.Point(221, 357);
            this.cmdDisconnect.Name = "cmdDisconnect";
            this.cmdDisconnect.Size = new System.Drawing.Size(100, 25);
            this.cmdDisconnect.TabIndex = 10;
            this.cmdDisconnect.Text = "–‡Á˙Â‰ËÌËÚ¸";
            this.cmdDisconnect.UseVisualStyleBackColor = false;
            this.cmdDisconnect.Click += new System.EventHandler(this.cmdDisconnect_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.Color.Transparent;
            this.menuStrip1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ToolStripMenuItem1,
            this.toolStripMenuItem2,
            this.toolStripMenuItem3});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(653, 24);
            this.menuStrip1.TabIndex = 14;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // ToolStripMenuItem1
            // 
            this.ToolStripMenuItem1.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.‡Í‚‡ToolStripMenuItem,
            this.ÁÓÎÓÚÓÈToolStripMenuItem,
            this.ÒÚ‡Ì‰‡ÚÌ˚ÈToolStripMenuItem});
            this.ToolStripMenuItem1.ForeColor = System.Drawing.Color.Black;
            this.ToolStripMenuItem1.Name = "ToolStripMenuItem1";
            this.ToolStripMenuItem1.Size = new System.Drawing.Size(38, 20);
            this.ToolStripMenuItem1.Text = "¬Ë‰";
            // 
            // ‡Í‚‡ToolStripMenuItem
            // 
            this.‡Í‚‡ToolStripMenuItem.Name = "‡Í‚‡ToolStripMenuItem";
            this.‡Í‚‡ToolStripMenuItem.Size = new System.Drawing.Size(155, 22);
            this.‡Í‚‡ToolStripMenuItem.Text = "¿Í‚‡";
            this.‡Í‚‡ToolStripMenuItem.Click += new System.EventHandler(this.‡Í‚‡ToolStripMenuItem_Click_1);
            // 
            // ÁÓÎÓÚÓÈToolStripMenuItem
            // 
            this.ÁÓÎÓÚÓÈToolStripMenuItem.Name = "ÁÓÎÓÚÓÈToolStripMenuItem";
            this.ÁÓÎÓÚÓÈToolStripMenuItem.Size = new System.Drawing.Size(155, 22);
            this.ÁÓÎÓÚÓÈToolStripMenuItem.Text = "«ÓÎÓÚÓÈ";
            this.ÁÓÎÓÚÓÈToolStripMenuItem.Click += new System.EventHandler(this.ÁÓÎÓÚÓÈToolStripMenuItem_Click_1);
            // 
            // ÒÚ‡Ì‰‡ÚÌ˚ÈToolStripMenuItem
            // 
            this.ÒÚ‡Ì‰‡ÚÌ˚ÈToolStripMenuItem.Checked = true;
            this.ÒÚ‡Ì‰‡ÚÌ˚ÈToolStripMenuItem.CheckState = System.Windows.Forms.CheckState.Checked;
            this.ÒÚ‡Ì‰‡ÚÌ˚ÈToolStripMenuItem.Name = "ÒÚ‡Ì‰‡ÚÌ˚ÈToolStripMenuItem";
            this.ÒÚ‡Ì‰‡ÚÌ˚ÈToolStripMenuItem.Size = new System.Drawing.Size(155, 22);
            this.ÒÚ‡Ì‰‡ÚÌ˚ÈToolStripMenuItem.Text = "—Ú‡Ì‰‡ÚÌ˚È";
            this.ÒÚ‡Ì‰‡ÚÌ˚ÈToolStripMenuItem.Click += new System.EventHandler(this.ÒÚ‡Ì‰‡ÚÌ˚ÈToolStripMenuItem_Click_1);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ÓÚÍ˚Ú¸‘‡ÈÎ»ÒÚÓËËToolStripMenuItem});
            this.toolStripMenuItem2.ForeColor = System.Drawing.Color.Black;
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(61, 20);
            this.toolStripMenuItem2.Text = "»ÒÚÓËˇ";
            // 
            // ÓÚÍ˚Ú¸‘‡ÈÎ»ÒÚÓËËToolStripMenuItem
            // 
            this.ÓÚÍ˚Ú¸‘‡ÈÎ»ÒÚÓËËToolStripMenuItem.Name = "ÓÚÍ˚Ú¸‘‡ÈÎ»ÒÚÓËËToolStripMenuItem";
            this.ÓÚÍ˚Ú¸‘‡ÈÎ»ÒÚÓËËToolStripMenuItem.Size = new System.Drawing.Size(204, 22);
            this.ÓÚÍ˚Ú¸‘‡ÈÎ»ÒÚÓËËToolStripMenuItem.Text = "ŒÚÍ˚Ú¸ Ù‡ÈÎ ËÒÚÓËË";
            this.ÓÚÍ˚Ú¸‘‡ÈÎ»ÒÚÓËËToolStripMenuItem.Click += new System.EventHandler(this.ÓÚÍ˚Ú¸‘‡ÈÎ»ÒÚÓËËToolStripMenuItem_Click);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem4});
            this.toolStripMenuItem3.ForeColor = System.Drawing.Color.Black;
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(62, 20);
            this.toolStripMenuItem3.Text = "—Ô‡‚Í‡";
            // 
            // toolStripMenuItem4
            // 
            this.toolStripMenuItem4.Name = "toolStripMenuItem4";
            this.toolStripMenuItem4.Size = new System.Drawing.Size(149, 22);
            this.toolStripMenuItem4.Text = "Œ ÔÓ„‡ÏÏÂ";
            this.toolStripMenuItem4.Click += new System.EventHandler(this.toolStripMenuItem4_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.LightGray;
            this.ClientSize = new System.Drawing.Size(653, 443);
            this.Controls.Add(this.cmdOpen);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.cmdClose);
            this.Controls.Add(this.cmdConnect);
            this.Controls.Add(this.cmdDisconnect);
            this.Controls.Add(this.GroupBox1);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.menuStrip1);
            this.ForeColor = System.Drawing.Color.Black;
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStrip1;
            this.MaximizeBox = false;
            this.MaximumSize = new System.Drawing.Size(1024, 719);
            this.Name = "frmMain";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "◊‡Ú";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmMain_FormClosing);
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.frmMain_FormClosed);
            this.Load += new System.EventHandler(this.frmMain_Load);
            this.Shown += new System.EventHandler(this.frmMain_Shown);
            this.groupBox3.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.GroupBox1.ResumeLayout(false);
            this.GroupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ComboBox cboData;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Button cmdClose;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.ComboBox cboStop;
        private System.Windows.Forms.GroupBox GroupBox1;
        private System.Windows.Forms.Button cmdSend;
        private System.Windows.Forms.TextBox txtSend;
        private System.Windows.Forms.RichTextBox rtbDisplay;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.ComboBox cboParity;
        private System.Windows.Forms.Label Label1;
        private System.Windows.Forms.ComboBox cboBaud;
        private System.Windows.Forms.ComboBox cboPort;
        private System.Windows.Forms.Button cmdOpen;
        private System.Windows.Forms.Button cmdConnect;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button cmdDisconnect;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem ToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem4;
        private System.Windows.Forms.ToolStripMenuItem ‡Í‚‡ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ÁÓÎÓÚÓÈToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ÒÚ‡Ì‰‡ÚÌ˚ÈToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem ÓÚÍ˚Ú¸‘‡ÈÎ»ÒÚÓËËToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;

            
    }
}