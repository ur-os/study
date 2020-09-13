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
    public partial class Form3 : Form
    {

        public string filepath; // путь к файлу истории

        public Form3()
        {
            InitializeComponent();
        }

        private void Form3_Load(object sender, EventArgs e)
        {
            // открытие файла истории в окне ричтекстбокса
            StreamReader sr = new StreamReader (filepath, Encoding.Default);
            richTextBox1.Text = sr.ReadToEnd();
            sr.Close();
        }

        private void копироватьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Clipboard.Clear();
            Clipboard.SetText(richTextBox1.SelectedText);
        }

        private void выделитьВсеToolStripMenuItem_Click(object sender, EventArgs e)
        {
            richTextBox1.SelectAll();
        }

    }
}
