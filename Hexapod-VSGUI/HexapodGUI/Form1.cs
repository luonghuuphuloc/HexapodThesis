using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
namespace HexapodGUI
{

    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            isConnectSTM = false;
            isFirstRun = false;

        }
        int intlen = 0;
        string[] dir = new string[6];
        string CmdFrStm;
        bool isConnectSTM = false;
        bool isFirstRun = false;
        float[] float_pos_to_matlab = new float[6];
        float[] float_pos_to_matlab_temp = new float[6];

        float[] HOME_OFFSET = { 33.65f , 34.29f, 30.39f, 28.73f, 31.57f, 31.77f };
        float[] MAX_OF_TRIP = { 144.977f, 150.024f, 146.865f, 140.612f, 147.100f, 147.818f };
        private void button2_Click(object sender, EventArgs e)
        {
            try
            {
                if (btnComOpen.Text == "Open")
                {

                    COM.PortName = cbb_Com.Text;
                    COM.Open();
                    lb_ConnectStatus.Text = "Status: Opened";
                    btnComOpen.Text = "Close";
                    lb_ConnectStatus.ForeColor = Color.Green;
                }
                else
                {
                    COM.DiscardInBuffer();
                    COM.Close();
                    lb_ConnectStatus.Text = "Status: Closed";
                    lb_ConnectStatus.ForeColor = Color.Red;
                    btnComOpen.Text = "Open";
                    btnConnectToSTM.Text = "Connect to STM";
                    txb_status_system.Clear();

                }
            }
            catch
            {
                lb_ConnectStatus.Text = "Error Connection";
            }
        }

        private void timerComUpdate_Tick(object sender, EventArgs e)
        {
            string[] ports = SerialPort.GetPortNames();
            if (intlen != ports.Length)
            {
                intlen = ports.Length;
                cbb_Com.Items.Clear();
                cbb_comMatlab.Items.Clear();
                for (int i = 0; i < intlen; i++)
                {
                    cbb_Com.Items.Add(ports[i]);
                    cbb_comMatlab.Items.Add(ports[i]);
                }

            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            string[] s = new string[6];

            s[0] = StringProcessingTestingMode(txt_q0.Text.ToString(), 0);
            s[1] = StringProcessingTestingMode(txt_q1.Text.ToString(), 1); 
            s[2] = StringProcessingTestingMode(txt_q2.Text.ToString(), 2); 
            s[3] = StringProcessingTestingMode(txt_q3.Text.ToString(), 3);
            s[4] = StringProcessingTestingMode(txt_q4.Text.ToString(), 4);
            s[5] = StringProcessingTestingMode(txt_q5.Text.ToString(), 5);

            txt_q0.Text = s[0];
            txt_q1.Text = s[1];
            txt_q2.Text = s[2];
            txt_q3.Text = s[3];
            txt_q4.Text = s[4];
            txt_q5.Text = s[5];

            try
            {
                COM.Write(SendMsgProcessing("p-t-" + s[0] + s[1] + s[2]
                    + s[3] + s[4] + s[5]));
            }
            catch
            {
                lb_ConnectStatus.ForeColor = Color.Red;
                lb_ConnectStatus.Text = "Error Sending";
            }

        }

        private void btnHomeScan_Click(object sender, EventArgs e)
        {
            try
            {


                string s;
                s = "p-hs-" + "rlrlrl";
               
                COM.Write(SendMsgProcessing(s));
                btnHomeScan.Enabled = false;
                lbHomeStatus.Text = "Scanning Home...";
                lbHomeStatus.BackColor = Color.Black;
                lbHomeStatus.ForeColor = Color.Yellow;
                timeroutScanHome.Enabled = true;



            }
            catch
            {
                lbHomeStatus.Text = "Scan Error";
                lbHomeStatus.ForeColor = Color.Red;
            }
        }



        private void COM_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            
                CmdFrStm = COM.ReadLine();
                COM.DiscardInBuffer();
                this.Invoke(new EventHandler(StmEvent));
            
            
        }
        private void StmEvent(object sender, EventArgs e)
        {
            //int count_cmd = 1;
            try
            {
                string[] cmd = CmdFrStm.Split('-');
                //for (int i = 0; i < CmdFrStm.Length; i++)
                //{
                //    if (CmdFrStm[i] == '-')
                //    {
                //        count_cmd++;
                //    }
                //}
                for (int i = 0; i < cmd.Length; i++)
                {
                    switch (cmd[i][0])
                    {
                        case 'h':
                            if (cmd[i][1] == 'f')
                            {
                                if (cmd[i][2] == 'a')
                                {
                                    lbHomeStatus.Text = "Home scan for all motor \nfinished.";
                                    isFirstRun = true;
                                    timeroutScanHome.Enabled = false;
                                    txt_q0.Text = HOME_OFFSET[0].ToString();
                                    txt_q1.Text = HOME_OFFSET[1].ToString();
                                    txt_q2.Text = HOME_OFFSET[2].ToString();
                                    txt_q3.Text = HOME_OFFSET[3].ToString();
                                    txt_q4.Text = HOME_OFFSET[4].ToString();
                                    txt_q5.Text = HOME_OFFSET[5].ToString();

                                    try
                                    {
                                        COM.Write(SendMsgProcessing("p-he"));
                                        btnHomeScan.Enabled = true;
                                    }
                                    catch
                                    {
                                        lb_ConnectStatus.ForeColor = Color.Red;
                                        lb_ConnectStatus.Text = "Error Sending";
                                    }
                                }
                            }
                            break;

                        case 'e':
                            {
                                int len = 1;
                                lb_enc_q0.Text = CmdFrStm.Substring(len, 7);
                                len += 7;
                                lb_enc_q1.Text = CmdFrStm.Substring(len, 7);
                                len += 7;
                                lb_enc_q2.Text = CmdFrStm.Substring(len, 7);
                                len += 7;
                                lb_enc_q3.Text = CmdFrStm.Substring(len, 7);
                                len += 7;
                                lb_enc_q4.Text = CmdFrStm.Substring(len, 7);
                                len += 7;
                                lb_enc_q5.Text = CmdFrStm.Substring(len, 7);

                                float.TryParse(lb_enc_q0.Text, out float_pos_to_matlab[0]);
                                float.TryParse(lb_enc_q1.Text, out float_pos_to_matlab[1]);
                                float.TryParse(lb_enc_q2.Text, out float_pos_to_matlab[2]);
                                float.TryParse(lb_enc_q3.Text, out float_pos_to_matlab[3]);
                                float.TryParse(lb_enc_q4.Text, out float_pos_to_matlab[4]);
                                float.TryParse(lb_enc_q5.Text, out float_pos_to_matlab[5]);

                                for(int j = 0; j < 6; j++)
                                {
                                    if(float_pos_to_matlab[j] == 0)
                                    {
                                        float_pos_to_matlab[j] = float_pos_to_matlab_temp[j];
                                    }
                                    else
                                    {
                                        float_pos_to_matlab_temp[j] = float_pos_to_matlab[j];
                                    }
                                }

                            }
                            break;
                        case 'l':
                            {
                                string s = cmd[i];
                                string multiline_text = s.Remove(0, 1);
                                switch (multiline_text)
                                {
                                    case "STM and VSGUI connected":
                                        {
                                            btnConnectToSTM.Text = "Disconnect to STM";
                                            isConnectSTM = true;
                                            break;
                                        }
                                    case "Android is running":
                                        {
                                            btnConnectToSTM.Text = "Connect to STM";
                                            isConnectSTM = false;
                                            break;
                                        }
                                    case "Tracking Mode activated":
                                        {
                                            btnConnectToSTM.Text = "Connect to STM";
                                            isConnectSTM = false;
                                            break;
                                        }
                                }

                                txb_status_system.AppendText(System.DateTime.Now.ToShortTimeString() + ": " + multiline_text + "\r\n");

                            }
                            break;


                    }
                }
            }
            catch
            {
            }

        }


        private void btnTestInverseKinematic_Click(object sender, EventArgs e)
        {
            string[] s = new string[6];

            s[0] = StringProcessingKinematicMode(txbX.Text.ToString(), 0);
            s[1] = StringProcessingKinematicMode(txbY.Text.ToString(), 1);
            s[2] = StringProcessingKinematicMode(txbZ.Text.ToString(), 2);
            s[3] = StringProcessingKinematicMode(txbRoll.Text.ToString(), 3);
            s[4] = StringProcessingKinematicMode(txbPitch.Text.ToString(), 4);
            s[5] = StringProcessingKinematicMode(txbYaw.Text.ToString(), 5);

            txbX.Text = s[0];
            txbY.Text = s[1];
            txbZ.Text = s[2];
            txbRoll.Text = s[3];
            txbPitch.Text = s[4];
            txbYaw.Text = s[5];

            try
            {
                COM.Write(SendMsgProcessing("p-ki" + s[0] + s[1] + s[2]
                    + s[3] + s[4] + s[5]));
            }
            catch
            {
                lb_ConnectStatus.ForeColor = Color.Red;
                lb_ConnectStatus.Text = "Error Sending";
            }
        }

        private void button1_Click_1(object sender, EventArgs e)
        {

        }

        private void txb_status_system_TextChanged(object sender, EventArgs e)
        {

        }

        private string StringProcessingTestingMode(string s_in, int motor_num)
        {
            string s_out;
            //s_in = s_in.Replace('.', ',');
            float f;
            float.TryParse(s_in, out f);

            if (f >= MAX_OF_TRIP[motor_num] - 2.0f)
                f = MAX_OF_TRIP[motor_num] - 2.0f;
            else if (f <= HOME_OFFSET[motor_num] + 2.0f)
                f = HOME_OFFSET[motor_num] + 2.0f;

            s_out = string.Format("{0:000.000}", f);

            return s_out;
        }
        private string StringProcessingKinematicMode(string s_in, int motor_num)
        {
            string s_out;
            //s_in = s_in.Replace('.', ',');
            float f;
            float.TryParse(s_in, out f);

            if(f >= 0)
             s_out = string.Format("{0:000.000}", f);
            else
             s_out = string.Format("{0:00.000}", f);

            return s_out ;
        }
        private string SendMsgProcessing(string str_input)
        {
            int str_len = str_input.Length;
            if(str_len < 52)
            {
                for(int i = 0; i < 51 - str_len; i++)
                {
                    str_input = String.Concat(str_input, "-");
                }
                str_input = String.Concat(str_input, "\n");
            }
            return str_input;
        }

        private void timeroutScanHome_Tick(object sender, EventArgs e)
        {
            btnHomeScan.Enabled = true;
            lbHomeStatus.Text = "Scan Failed";
            timeroutScanHome.Enabled = false;
        }

        private void btnSavePos_Click(object sender, EventArgs e)
        {
            try
            {
                COM.Write(SendMsgProcessing("p-s"));
            }
            catch
            {
                lb_ConnectStatus.ForeColor = Color.Red;
                lb_ConnectStatus.Text = "Error Sending";
            }
        }

        private void btnConnectToSTM_Click(object sender, EventArgs e)
        {
            if(isConnectSTM == false)
            {

                try
                {
                    COM.Write(SendMsgProcessing("p-cr"));
                }
                catch
                {
                    lb_ConnectStatus.ForeColor = Color.Red;
                    lb_ConnectStatus.Text = "Error Sending";
                }

            }
            else
            {
                btnConnectToSTM.Text = "Connect to STM";
                try
                {
                    COM.Write(SendMsgProcessing("p-cd"));
                }
                catch
                {
                    lb_ConnectStatus.ForeColor = Color.Red;
                    lb_ConnectStatus.Text = "Error Sending";
                }
                isConnectSTM = false;
            }

        }

        private void txt_q4_TextChanged(object sender, EventArgs e)
        {

        }

        private void btnComMatlabOpen_Click(object sender, EventArgs e)
        {
            try
            {
                if (btnComMatlabOpen.Text == "Open")
                {

                    COMMatlab.PortName = cbb_comMatlab.Text;
                    COMMatlab.Open();
                    lb_ConnectMatlab_status.Text = "Status: Opened";
                    btnComMatlabOpen.Text = "Close";
                    lb_ConnectMatlab_status.ForeColor = Color.Green;
                    timer_send_tomatlab.Enabled = true;
                }
                else
                {
                    COMMatlab.DiscardInBuffer();
                    COMMatlab.Close();
                    lb_ConnectMatlab_status.Text = "Status: Closed";
                    lb_ConnectMatlab_status.ForeColor = Color.Red;
                    btnComMatlabOpen.Text = "Open";
                    txb_status_system.Clear();
                    timer_send_tomatlab.Enabled = false;

                }
            }
            catch
            {
                lb_ConnectMatlab_status.Text = "Error Connection";
            }
        }

        private void timer_send_tomatlab_Tick(object sender, EventArgs e)
        {
            string s = "m";
            for (int i = 0; i < 6; i++)
                s += string.Format("{0:000000}", float_pos_to_matlab[i]*1000); 
            if(s.Length == 37 )
                COMMatlab.Write(s);
        }
    }
}
