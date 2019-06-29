using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing.Imaging;
using System.Drawing;
using System.Net.Sockets;

namespace LedSend
{
    public partial class Form1 : Form
    {
        int x_loc, y_loc;
        Bitmap captureBitmap;
        UdpClient udpClient;
        Form2 form2 = new Form2();
        bool connect;
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                if (connect == false)
                {
                    udpClient = new UdpClient();
                    udpClient.Connect(textBox2.Text, 11000);
                    connect = true;
                    button1.Text = "Disconnect";
                    button1.BackColor = Color.Green;
                    timer1.Interval = 1;
                    timer1.Enabled = true;
                }else if(connect == true){
                    udpClient.Close();
                    udpClient.Dispose();
                    button1.Text = "Connect";
                    button1.BackColor = Color.Red;
                    connect = false;
                    timer1.Enabled = false;
                }
            }
            catch
            {

            }
        }
        private void CaptureMyScreen(int xheight, int xwidth, int xl, int yl)

        {
            try

            {
           
                captureBitmap = new Bitmap(xheight, xwidth, PixelFormat.Format24bppRgb);
                Rectangle captureRectangle = Screen.AllScreens[0].Bounds;
                Graphics captureGraphics = Graphics.FromImage(captureBitmap);
                captureGraphics.CopyFromScreen(xl, yl, 0, 0, captureRectangle.Size);
                pictureBox1.Image = captureBitmap;
                BitmapData bData = captureBitmap.LockBits(new Rectangle(0, 0, captureBitmap.Width, captureBitmap.Height), ImageLockMode.ReadWrite, captureBitmap.PixelFormat);
              
                int size = bData.Stride * bData.Height;
                byte[] data = new byte[size];
                System.Runtime.InteropServices.Marshal.Copy(bData.Scan0, data, 0, size);
        
                if(connect) sendimage(data,size);
                captureBitmap.UnlockBits(bData);
                
                

            }
            catch (Exception ex)

            {
                MessageBox.Show(ex.Message);
            }
        }

        void sendimage(byte[] img, int sizu)
        {
                  
            try
            {

                   Byte[] sendBytes = Encoding.ASCII.GetBytes("Begin");
                if(checkBox2.Checked == true)
                {
                    sendBytes[1] = 1;
                }
                    
                byte[] array1 = new byte[1354];
                byte[] array2 = new byte[1354];
                byte[] array3 = new byte[1354];
                byte[] array4 = new byte[1354];
                byte[] array5 = new byte[1354];
                byte[] array6 = new byte[1354];
           
                for(int i = 0;i < 1352; i++)
                {
                    array1[i+1] = img[i];
                    array2[i + 1] = img[i + (1 * 1352) ];
                    array3[i + 1] = img[i + (2 * 1352) ];
                    array4[i + 1] = img[i + (3 * 1352) ];
                    array5[i + 1] = img[i + (4 * 1352) ];
                    array6[i + 1] = img[i + (5 * 1352) ];
                 }
                array1[0] = 1;
                array2[0] = 2;
                array3[0] = 3;
                array4[0] = 4;
                array5[0] = 5;
                array6[0] = 6;

                int sended;
                sended =  udpClient.Send(sendBytes, sendBytes.Length);  
                udpClient.Send(array1, 1353);
                udpClient.Send(array2, 1353);
                udpClient.Send(array3, 1353);
                udpClient.Send(array4, 1353);
                udpClient.Send(array5, 1353);
                udpClient.Send(array6, 1353);

            }
            catch (Exception e)
            {
                Console.WriteLine(e.ToString());
            }

        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (checkBox1.Checked)
            {
                x_loc = form2.Location.X;
                y_loc = form2.Location.Y;
            }

            CaptureMyScreen(52,52,x_loc+4, y_loc+4);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            BitmapData bData = captureBitmap.LockBits(new Rectangle(0, 0, captureBitmap.Width, captureBitmap.Height), ImageLockMode.ReadWrite, captureBitmap.PixelFormat);
            String st;
        
            int size = bData.Stride * bData.Height;
            byte[] data = new byte[size];
            System.Runtime.InteropServices.Marshal.Copy(bData.Scan0, data, 0, size);
            st = "rgb";
            for (int i = 0;i < 10; i++)
            {
                
                st += data[i].ToString();
                st += " ";

            }
            st += "\r\n";
            textBox1.AppendText(st);
            captureBitmap.UnlockBits(bData);
        }

        private void button3_Click(object sender, EventArgs e)
        {
            checkBox1.Checked = true;
            form2.Show();
            form2.BringToFront();
            
        }

        private void textBox2_TextChanged(object sender, EventArgs e)
        {

        }

        private void checkBox3_CheckedChanged(object sender, EventArgs e)
        {
            if (checkBox3.Checked) form2.TopMost = true;
            if (!checkBox3.Checked) form2.TopMost = false;
        }

        public Form1()
        {
            InitializeComponent();
            x_loc = 100;
            y_loc = 100;
            button1.BackColor = Color.Red;
        }
    }
}
