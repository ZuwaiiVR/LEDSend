using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace LedSend
{
    public partial class Form2 : Form
    {
        bool TogMove;
        int MValX;
        int MValY;
        public Form2()
        {
            InitializeComponent();
            
        }

        private void Form2_LocationChanged(object sender, EventArgs e)
        {
            
        }

        private void Form2_FormClosed(object sender, FormClosedEventArgs e)
        {
            this.Hide();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Hide();
        }

        private void Form2_MouseDown(object sender, MouseEventArgs e)
        {
            TogMove = true;
            MValX = e.X;
            MValY = e.Y;
        }

        private void Form2_MouseMove(object sender, MouseEventArgs e)
        {
            if (TogMove == true)
            {
                this.SetDesktopLocation(MousePosition.X - MValX, MousePosition.Y - MValY);
            }
        }

        private void Form2_MouseUp(object sender, MouseEventArgs e)
        {
            TogMove = false;
        }
    }
}
