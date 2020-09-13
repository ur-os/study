using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;
using System.IO;
namespace PCComm
{
    public partial class Form4 : Form
    {
        public string user1;
        public string user2;
        private string settings_file = Application.StartupPath + @"\settings.txt";
        
        public Form4()
        {
            InitializeComponent();  
        }

        private void button1_Click(object sender, EventArgs e)
        {
 
            user1 = textBox1.Text;
            user2 = textBox2.Text;

            using (StreamWriter file = new StreamWriter(settings_file))
            {

                file.WriteLine(user1);
                file.WriteLine(user2);
            }
            Form4.ActiveForm.Close();
    
        }

        private void Form4_Shown(object sender, EventArgs e)
        {
    
            if (File.Exists(settings_file))
            {
                StreamReader sr = new StreamReader(settings_file);
                textBox1.Text = sr.ReadLine();
                textBox2.Text = sr.ReadLine();
                sr.Close();
                this.Refresh();
            }
            
        }

    }
}
