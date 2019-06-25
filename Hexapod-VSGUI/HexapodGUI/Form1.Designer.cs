namespace HexapodGUI
{
    partial class Form1
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
            this.components = new System.ComponentModel.Container();
            this.btnTestStart = new System.Windows.Forms.Button();
            this.txt_q1 = new System.Windows.Forms.TextBox();
            this.txt_q2 = new System.Windows.Forms.TextBox();
            this.txt_q3 = new System.Windows.Forms.TextBox();
            this.txt_q4 = new System.Windows.Forms.TextBox();
            this.txt_q5 = new System.Windows.Forms.TextBox();
            this.txt_q0 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.lb_ConnectStatus = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.lb_ConnectMatlab_status = new System.Windows.Forms.Label();
            this.btnComMatlabOpen = new System.Windows.Forms.Button();
            this.cbb_comMatlab = new System.Windows.Forms.ComboBox();
            this.cbb_Com = new System.Windows.Forms.ComboBox();
            this.btnComOpen = new System.Windows.Forms.Button();
            this.timerComUpdate = new System.Windows.Forms.Timer(this.components);
            this.COM = new System.IO.Ports.SerialPort(this.components);
            this.btnHomeScan = new System.Windows.Forms.Button();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.lbHomeStatus = new System.Windows.Forms.Label();
            this.txbYaw = new System.Windows.Forms.TextBox();
            this.txbPitch = new System.Windows.Forms.TextBox();
            this.txbRoll = new System.Windows.Forms.TextBox();
            this.txbX = new System.Windows.Forms.TextBox();
            this.txbZ = new System.Windows.Forms.TextBox();
            this.txbY = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.btnTestInverseKinematic = new System.Windows.Forms.Button();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.lb_enc_q0 = new System.Windows.Forms.Label();
            this.lb_enc_q1 = new System.Windows.Forms.Label();
            this.lb_enc_q2 = new System.Windows.Forms.Label();
            this.lb_enc_q3 = new System.Windows.Forms.Label();
            this.lb_enc_q4 = new System.Windows.Forms.Label();
            this.lb_enc_q5 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.label16 = new System.Windows.Forms.Label();
            this.label17 = new System.Windows.Forms.Label();
            this.label18 = new System.Windows.Forms.Label();
            this.groupBox5 = new System.Windows.Forms.GroupBox();
            this.txb_status_system = new System.Windows.Forms.TextBox();
            this.timeroutScanHome = new System.Windows.Forms.Timer(this.components);
            this.btnSavePos = new System.Windows.Forms.Button();
            this.btnConnectToSTM = new System.Windows.Forms.Button();
            this.COMMatlab = new System.IO.Ports.SerialPort(this.components);
            this.timer_send_tomatlab = new System.Windows.Forms.Timer(this.components);
            this.label19 = new System.Windows.Forms.Label();
            this.label20 = new System.Windows.Forms.Label();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox5.SuspendLayout();
            this.SuspendLayout();
            // 
            // btnTestStart
            // 
            this.btnTestStart.Location = new System.Drawing.Point(48, 245);
            this.btnTestStart.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btnTestStart.Name = "btnTestStart";
            this.btnTestStart.Size = new System.Drawing.Size(101, 52);
            this.btnTestStart.TabIndex = 7;
            this.btnTestStart.Text = "START";
            this.btnTestStart.UseVisualStyleBackColor = true;
            this.btnTestStart.Click += new System.EventHandler(this.button1_Click);
            // 
            // txt_q1
            // 
            this.txt_q1.Location = new System.Drawing.Point(48, 78);
            this.txt_q1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.txt_q1.Name = "txt_q1";
            this.txt_q1.Size = new System.Drawing.Size(100, 25);
            this.txt_q1.TabIndex = 2;
            // 
            // txt_q2
            // 
            this.txt_q2.Location = new System.Drawing.Point(48, 112);
            this.txt_q2.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.txt_q2.Name = "txt_q2";
            this.txt_q2.Size = new System.Drawing.Size(100, 25);
            this.txt_q2.TabIndex = 3;
            // 
            // txt_q3
            // 
            this.txt_q3.Location = new System.Drawing.Point(48, 144);
            this.txt_q3.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.txt_q3.Name = "txt_q3";
            this.txt_q3.Size = new System.Drawing.Size(100, 25);
            this.txt_q3.TabIndex = 4;
            // 
            // txt_q4
            // 
            this.txt_q4.Location = new System.Drawing.Point(48, 179);
            this.txt_q4.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.txt_q4.Name = "txt_q4";
            this.txt_q4.Size = new System.Drawing.Size(100, 25);
            this.txt_q4.TabIndex = 5;
            this.txt_q4.TextChanged += new System.EventHandler(this.txt_q4_TextChanged);
            // 
            // txt_q5
            // 
            this.txt_q5.Location = new System.Drawing.Point(48, 211);
            this.txt_q5.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.txt_q5.Name = "txt_q5";
            this.txt_q5.Size = new System.Drawing.Size(100, 25);
            this.txt_q5.TabIndex = 6;
            // 
            // txt_q0
            // 
            this.txt_q0.Location = new System.Drawing.Point(48, 46);
            this.txt_q0.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.txt_q0.Name = "txt_q0";
            this.txt_q0.Size = new System.Drawing.Size(100, 25);
            this.txt_q0.TabIndex = 1;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(14, 118);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(31, 17);
            this.label1.TabIndex = 2;
            this.label1.Text = "q2:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(14, 51);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(31, 17);
            this.label2.TabIndex = 2;
            this.label2.Text = "q0:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(14, 85);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(31, 17);
            this.label3.TabIndex = 2;
            this.label3.Text = "q1:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(14, 184);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(31, 17);
            this.label4.TabIndex = 2;
            this.label4.Text = "q4:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(14, 151);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(31, 17);
            this.label5.TabIndex = 2;
            this.label5.Text = "q3:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(14, 218);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(31, 17);
            this.label7.TabIndex = 2;
            this.label7.Text = "q5:";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label7);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.txt_q5);
            this.groupBox1.Controls.Add(this.txt_q4);
            this.groupBox1.Controls.Add(this.txt_q3);
            this.groupBox1.Controls.Add(this.txt_q0);
            this.groupBox1.Controls.Add(this.txt_q2);
            this.groupBox1.Controls.Add(this.txt_q1);
            this.groupBox1.Controls.Add(this.btnTestStart);
            this.groupBox1.ForeColor = System.Drawing.Color.Cyan;
            this.groupBox1.Location = new System.Drawing.Point(11, 233);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBox1.Size = new System.Drawing.Size(168, 317);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Test Mode ";
            // 
            // lb_ConnectStatus
            // 
            this.lb_ConnectStatus.AutoSize = true;
            this.lb_ConnectStatus.Location = new System.Drawing.Point(14, 133);
            this.lb_ConnectStatus.Name = "lb_ConnectStatus";
            this.lb_ConnectStatus.Size = new System.Drawing.Size(18, 20);
            this.lb_ConnectStatus.TabIndex = 6;
            this.lb_ConnectStatus.Text = "...";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label20);
            this.groupBox2.Controls.Add(this.label19);
            this.groupBox2.Controls.Add(this.lb_ConnectMatlab_status);
            this.groupBox2.Controls.Add(this.btnComMatlabOpen);
            this.groupBox2.Controls.Add(this.cbb_comMatlab);
            this.groupBox2.Controls.Add(this.cbb_Com);
            this.groupBox2.Controls.Add(this.btnComOpen);
            this.groupBox2.Controls.Add(this.lb_ConnectStatus);
            this.groupBox2.ForeColor = System.Drawing.Color.Coral;
            this.groupBox2.Location = new System.Drawing.Point(11, 42);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBox2.Size = new System.Drawing.Size(328, 160);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Port Connection";
            // 
            // lb_ConnectMatlab_status
            // 
            this.lb_ConnectMatlab_status.AutoSize = true;
            this.lb_ConnectMatlab_status.Location = new System.Drawing.Point(197, 133);
            this.lb_ConnectMatlab_status.Name = "lb_ConnectMatlab_status";
            this.lb_ConnectMatlab_status.Size = new System.Drawing.Size(18, 20);
            this.lb_ConnectMatlab_status.TabIndex = 18;
            this.lb_ConnectMatlab_status.Text = "...";
            // 
            // btnComMatlabOpen
            // 
            this.btnComMatlabOpen.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnComMatlabOpen.Location = new System.Drawing.Point(197, 86);
            this.btnComMatlabOpen.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btnComMatlabOpen.Name = "btnComMatlabOpen";
            this.btnComMatlabOpen.Size = new System.Drawing.Size(83, 28);
            this.btnComMatlabOpen.TabIndex = 17;
            this.btnComMatlabOpen.Text = "Open";
            this.btnComMatlabOpen.UseVisualStyleBackColor = true;
            this.btnComMatlabOpen.Click += new System.EventHandler(this.btnComMatlabOpen_Click);
            // 
            // cbb_comMatlab
            // 
            this.cbb_comMatlab.FormattingEnabled = true;
            this.cbb_comMatlab.Location = new System.Drawing.Point(197, 57);
            this.cbb_comMatlab.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.cbb_comMatlab.Name = "cbb_comMatlab";
            this.cbb_comMatlab.Size = new System.Drawing.Size(121, 27);
            this.cbb_comMatlab.TabIndex = 16;
            // 
            // cbb_Com
            // 
            this.cbb_Com.FormattingEnabled = true;
            this.cbb_Com.Location = new System.Drawing.Point(18, 57);
            this.cbb_Com.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.cbb_Com.Name = "cbb_Com";
            this.cbb_Com.Size = new System.Drawing.Size(121, 27);
            this.cbb_Com.TabIndex = 15;
            // 
            // btnComOpen
            // 
            this.btnComOpen.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnComOpen.Location = new System.Drawing.Point(18, 86);
            this.btnComOpen.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btnComOpen.Name = "btnComOpen";
            this.btnComOpen.Size = new System.Drawing.Size(83, 28);
            this.btnComOpen.TabIndex = 3;
            this.btnComOpen.Text = "Open";
            this.btnComOpen.UseVisualStyleBackColor = true;
            this.btnComOpen.Click += new System.EventHandler(this.button2_Click);
            // 
            // timerComUpdate
            // 
            this.timerComUpdate.Enabled = true;
            this.timerComUpdate.Tick += new System.EventHandler(this.timerComUpdate_Tick);
            // 
            // COM
            // 
            this.COM.BaudRate = 115200;
            this.COM.PortName = "COM4";
            this.COM.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.COM_DataReceived);
            // 
            // btnHomeScan
            // 
            this.btnHomeScan.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnHomeScan.Location = new System.Drawing.Point(14, 34);
            this.btnHomeScan.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btnHomeScan.Name = "btnHomeScan";
            this.btnHomeScan.Size = new System.Drawing.Size(144, 52);
            this.btnHomeScan.TabIndex = 8;
            this.btnHomeScan.Text = "START SCAN";
            this.btnHomeScan.UseVisualStyleBackColor = true;
            this.btnHomeScan.Click += new System.EventHandler(this.btnHomeScan_Click);
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.lbHomeStatus);
            this.groupBox3.Controls.Add(this.btnHomeScan);
            this.groupBox3.ForeColor = System.Drawing.Color.CornflowerBlue;
            this.groupBox3.Location = new System.Drawing.Point(384, 42);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBox3.Size = new System.Drawing.Size(173, 160);
            this.groupBox3.TabIndex = 10;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Scan Home";
            // 
            // lbHomeStatus
            // 
            this.lbHomeStatus.AutoSize = true;
            this.lbHomeStatus.ForeColor = System.Drawing.Color.Green;
            this.lbHomeStatus.Location = new System.Drawing.Point(11, 109);
            this.lbHomeStatus.Name = "lbHomeStatus";
            this.lbHomeStatus.Size = new System.Drawing.Size(89, 20);
            this.lbHomeStatus.TabIndex = 10;
            this.lbHomeStatus.Text = "Do Nothing";
            // 
            // txbYaw
            // 
            this.txbYaw.Location = new System.Drawing.Point(56, 201);
            this.txbYaw.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.txbYaw.Name = "txbYaw";
            this.txbYaw.Size = new System.Drawing.Size(100, 25);
            this.txbYaw.TabIndex = 13;
            // 
            // txbPitch
            // 
            this.txbPitch.Location = new System.Drawing.Point(56, 169);
            this.txbPitch.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.txbPitch.Name = "txbPitch";
            this.txbPitch.Size = new System.Drawing.Size(100, 25);
            this.txbPitch.TabIndex = 12;
            // 
            // txbRoll
            // 
            this.txbRoll.Location = new System.Drawing.Point(56, 135);
            this.txbRoll.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.txbRoll.Name = "txbRoll";
            this.txbRoll.Size = new System.Drawing.Size(100, 25);
            this.txbRoll.TabIndex = 11;
            // 
            // txbX
            // 
            this.txbX.Location = new System.Drawing.Point(56, 36);
            this.txbX.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.txbX.Name = "txbX";
            this.txbX.Size = new System.Drawing.Size(100, 25);
            this.txbX.TabIndex = 8;
            // 
            // txbZ
            // 
            this.txbZ.Location = new System.Drawing.Point(56, 103);
            this.txbZ.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.txbZ.Name = "txbZ";
            this.txbZ.Size = new System.Drawing.Size(100, 25);
            this.txbZ.TabIndex = 10;
            // 
            // txbY
            // 
            this.txbY.Location = new System.Drawing.Point(56, 68);
            this.txbY.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.txbY.Name = "txbY";
            this.txbY.Size = new System.Drawing.Size(100, 25);
            this.txbY.TabIndex = 9;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(22, 42);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(23, 17);
            this.label6.TabIndex = 18;
            this.label6.Text = "X:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(6, 205);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(42, 17);
            this.label8.TabIndex = 19;
            this.label8.Text = "Yaw:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(6, 139);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(41, 17);
            this.label9.TabIndex = 20;
            this.label9.Text = "Roll:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.Location = new System.Drawing.Point(6, 172);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(49, 17);
            this.label10.TabIndex = 21;
            this.label10.Text = "Pitch:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label11.Location = new System.Drawing.Point(22, 75);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(23, 17);
            this.label11.TabIndex = 22;
            this.label11.Text = "Y:";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label12.Location = new System.Drawing.Point(22, 108);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(23, 17);
            this.label12.TabIndex = 23;
            this.label12.Text = "Z:";
            // 
            // btnTestInverseKinematic
            // 
            this.btnTestInverseKinematic.Location = new System.Drawing.Point(56, 236);
            this.btnTestInverseKinematic.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btnTestInverseKinematic.Name = "btnTestInverseKinematic";
            this.btnTestInverseKinematic.Size = new System.Drawing.Size(101, 52);
            this.btnTestInverseKinematic.TabIndex = 14;
            this.btnTestInverseKinematic.Text = "START";
            this.btnTestInverseKinematic.UseVisualStyleBackColor = true;
            this.btnTestInverseKinematic.Click += new System.EventHandler(this.btnTestInverseKinematic_Click);
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.btnTestInverseKinematic);
            this.groupBox4.Controls.Add(this.label6);
            this.groupBox4.Controls.Add(this.label8);
            this.groupBox4.Controls.Add(this.label9);
            this.groupBox4.Controls.Add(this.label10);
            this.groupBox4.Controls.Add(this.label11);
            this.groupBox4.Controls.Add(this.label12);
            this.groupBox4.Controls.Add(this.txbYaw);
            this.groupBox4.Controls.Add(this.txbPitch);
            this.groupBox4.Controls.Add(this.txbRoll);
            this.groupBox4.Controls.Add(this.txbX);
            this.groupBox4.Controls.Add(this.txbZ);
            this.groupBox4.Controls.Add(this.txbY);
            this.groupBox4.ForeColor = System.Drawing.Color.Crimson;
            this.groupBox4.Location = new System.Drawing.Point(184, 233);
            this.groupBox4.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBox4.Size = new System.Drawing.Size(179, 315);
            this.groupBox4.TabIndex = 24;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Inverse Kinematic Test";
            // 
            // lb_enc_q0
            // 
            this.lb_enc_q0.AutoSize = true;
            this.lb_enc_q0.Location = new System.Drawing.Point(78, 29);
            this.lb_enc_q0.Name = "lb_enc_q0";
            this.lb_enc_q0.Size = new System.Drawing.Size(48, 20);
            this.lb_enc_q0.TabIndex = 25;
            this.lb_enc_q0.Text = "---.---";
            // 
            // lb_enc_q1
            // 
            this.lb_enc_q1.AutoSize = true;
            this.lb_enc_q1.Location = new System.Drawing.Point(78, 61);
            this.lb_enc_q1.Name = "lb_enc_q1";
            this.lb_enc_q1.Size = new System.Drawing.Size(48, 20);
            this.lb_enc_q1.TabIndex = 25;
            this.lb_enc_q1.Text = "---.---";
            // 
            // lb_enc_q2
            // 
            this.lb_enc_q2.AutoSize = true;
            this.lb_enc_q2.Location = new System.Drawing.Point(78, 94);
            this.lb_enc_q2.Name = "lb_enc_q2";
            this.lb_enc_q2.Size = new System.Drawing.Size(48, 20);
            this.lb_enc_q2.TabIndex = 25;
            this.lb_enc_q2.Text = "---.---";
            // 
            // lb_enc_q3
            // 
            this.lb_enc_q3.AutoSize = true;
            this.lb_enc_q3.Location = new System.Drawing.Point(78, 127);
            this.lb_enc_q3.Name = "lb_enc_q3";
            this.lb_enc_q3.Size = new System.Drawing.Size(48, 20);
            this.lb_enc_q3.TabIndex = 25;
            this.lb_enc_q3.Text = "---.---";
            // 
            // lb_enc_q4
            // 
            this.lb_enc_q4.AutoSize = true;
            this.lb_enc_q4.Location = new System.Drawing.Point(78, 161);
            this.lb_enc_q4.Name = "lb_enc_q4";
            this.lb_enc_q4.Size = new System.Drawing.Size(48, 20);
            this.lb_enc_q4.TabIndex = 25;
            this.lb_enc_q4.Text = "---.---";
            // 
            // lb_enc_q5
            // 
            this.lb_enc_q5.AutoSize = true;
            this.lb_enc_q5.Location = new System.Drawing.Point(78, 194);
            this.lb_enc_q5.Name = "lb_enc_q5";
            this.lb_enc_q5.Size = new System.Drawing.Size(48, 20);
            this.lb_enc_q5.TabIndex = 25;
            this.lb_enc_q5.Text = "---.---";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label13.Location = new System.Drawing.Point(29, 94);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(31, 17);
            this.label13.TabIndex = 2;
            this.label13.Text = "q2:";
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label14.Location = new System.Drawing.Point(29, 61);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(31, 17);
            this.label14.TabIndex = 2;
            this.label14.Text = "q1:";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label15.Location = new System.Drawing.Point(29, 161);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(31, 17);
            this.label15.TabIndex = 2;
            this.label15.Text = "q4:";
            // 
            // label16
            // 
            this.label16.AutoSize = true;
            this.label16.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label16.Location = new System.Drawing.Point(29, 127);
            this.label16.Name = "label16";
            this.label16.Size = new System.Drawing.Size(31, 17);
            this.label16.TabIndex = 2;
            this.label16.Text = "q3:";
            // 
            // label17
            // 
            this.label17.AutoSize = true;
            this.label17.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label17.Location = new System.Drawing.Point(29, 194);
            this.label17.Name = "label17";
            this.label17.Size = new System.Drawing.Size(31, 17);
            this.label17.TabIndex = 2;
            this.label17.Text = "q5:";
            // 
            // label18
            // 
            this.label18.AutoSize = true;
            this.label18.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label18.Location = new System.Drawing.Point(29, 28);
            this.label18.Name = "label18";
            this.label18.Size = new System.Drawing.Size(31, 17);
            this.label18.TabIndex = 2;
            this.label18.Text = "q0:";
            // 
            // groupBox5
            // 
            this.groupBox5.Controls.Add(this.label18);
            this.groupBox5.Controls.Add(this.lb_enc_q5);
            this.groupBox5.Controls.Add(this.label17);
            this.groupBox5.Controls.Add(this.lb_enc_q4);
            this.groupBox5.Controls.Add(this.label16);
            this.groupBox5.Controls.Add(this.lb_enc_q3);
            this.groupBox5.Controls.Add(this.label15);
            this.groupBox5.Controls.Add(this.label14);
            this.groupBox5.Controls.Add(this.lb_enc_q2);
            this.groupBox5.Controls.Add(this.label13);
            this.groupBox5.Controls.Add(this.lb_enc_q1);
            this.groupBox5.Controls.Add(this.lb_enc_q0);
            this.groupBox5.ForeColor = System.Drawing.Color.Cornsilk;
            this.groupBox5.Location = new System.Drawing.Point(646, 42);
            this.groupBox5.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBox5.Name = "groupBox5";
            this.groupBox5.Padding = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.groupBox5.Size = new System.Drawing.Size(176, 253);
            this.groupBox5.TabIndex = 26;
            this.groupBox5.TabStop = false;
            this.groupBox5.Text = "Servo position";
            // 
            // txb_status_system
            // 
            this.txb_status_system.AcceptsReturn = true;
            this.txb_status_system.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.txb_status_system.Location = new System.Drawing.Point(384, 313);
            this.txb_status_system.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.txb_status_system.Multiline = true;
            this.txb_status_system.Name = "txb_status_system";
            this.txb_status_system.ReadOnly = true;
            this.txb_status_system.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.txb_status_system.Size = new System.Drawing.Size(439, 219);
            this.txb_status_system.TabIndex = 27;
            this.txb_status_system.TextChanged += new System.EventHandler(this.txb_status_system_TextChanged);
            // 
            // timeroutScanHome
            // 
            this.timeroutScanHome.Interval = 20000;
            this.timeroutScanHome.Tick += new System.EventHandler(this.timeroutScanHome_Tick);
            // 
            // btnSavePos
            // 
            this.btnSavePos.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnSavePos.ForeColor = System.Drawing.Color.DarkBlue;
            this.btnSavePos.Location = new System.Drawing.Point(11, 579);
            this.btnSavePos.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btnSavePos.Name = "btnSavePos";
            this.btnSavePos.Size = new System.Drawing.Size(99, 62);
            this.btnSavePos.TabIndex = 28;
            this.btnSavePos.Text = "Save position";
            this.btnSavePos.UseVisualStyleBackColor = true;
            this.btnSavePos.Click += new System.EventHandler(this.btnSavePos_Click);
            // 
            // btnConnectToSTM
            // 
            this.btnConnectToSTM.Font = new System.Drawing.Font("Microsoft Sans Serif", 7.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btnConnectToSTM.ForeColor = System.Drawing.Color.CornflowerBlue;
            this.btnConnectToSTM.Location = new System.Drawing.Point(154, 579);
            this.btnConnectToSTM.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.btnConnectToSTM.Name = "btnConnectToSTM";
            this.btnConnectToSTM.Size = new System.Drawing.Size(120, 62);
            this.btnConnectToSTM.TabIndex = 29;
            this.btnConnectToSTM.Text = "Connect to STM";
            this.btnConnectToSTM.UseVisualStyleBackColor = true;
            this.btnConnectToSTM.Click += new System.EventHandler(this.btnConnectToSTM_Click);
            // 
            // COMMatlab
            // 
            this.COMMatlab.BaudRate = 115200;
            // 
            // timer_send_tomatlab
            // 
            this.timer_send_tomatlab.Tick += new System.EventHandler(this.timer_send_tomatlab_Tick);
            // 
            // label19
            // 
            this.label19.AutoSize = true;
            this.label19.Location = new System.Drawing.Point(14, 34);
            this.label19.Name = "label19";
            this.label19.Size = new System.Drawing.Size(42, 20);
            this.label19.TabIndex = 19;
            this.label19.Text = "STM:";
            // 
            // label20
            // 
            this.label20.AutoSize = true;
            this.label20.Location = new System.Drawing.Point(194, 34);
            this.label20.Name = "label20";
            this.label20.Size = new System.Drawing.Size(60, 20);
            this.label20.TabIndex = 20;
            this.label20.Text = "Matlab:";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 19F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.BackColor = System.Drawing.Color.Black;
            this.ClientSize = new System.Drawing.Size(853, 684);
            this.Controls.Add(this.btnConnectToSTM);
            this.Controls.Add(this.btnSavePos);
            this.Controls.Add(this.txb_status_system);
            this.Controls.Add(this.groupBox5);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Font = new System.Drawing.Font("Microsoft YaHei", 7.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Margin = new System.Windows.Forms.Padding(3, 4, 3, 4);
            this.Name = "Form1";
            this.Text = "HexapodGUI";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.groupBox5.ResumeLayout(false);
            this.groupBox5.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button btnTestStart;
        private System.Windows.Forms.TextBox txt_q1;
        private System.Windows.Forms.TextBox txt_q2;
        private System.Windows.Forms.TextBox txt_q3;
        private System.Windows.Forms.TextBox txt_q4;
        private System.Windows.Forms.TextBox txt_q5;
        private System.Windows.Forms.TextBox txt_q0;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label lb_ConnectStatus;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Timer timerComUpdate;
        private System.IO.Ports.SerialPort COM;
        private System.Windows.Forms.Button btnHomeScan;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Label lbHomeStatus;
        private System.Windows.Forms.ComboBox cbb_Com;
        private System.Windows.Forms.Button btnComOpen;
        private System.Windows.Forms.TextBox txbYaw;
        private System.Windows.Forms.TextBox txbPitch;
        private System.Windows.Forms.TextBox txbRoll;
        private System.Windows.Forms.TextBox txbX;
        private System.Windows.Forms.TextBox txbZ;
        private System.Windows.Forms.TextBox txbY;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Button btnTestInverseKinematic;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Label lb_enc_q0;
        private System.Windows.Forms.Label lb_enc_q1;
        private System.Windows.Forms.Label lb_enc_q2;
        private System.Windows.Forms.Label lb_enc_q3;
        private System.Windows.Forms.Label lb_enc_q4;
        private System.Windows.Forms.Label lb_enc_q5;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.Label label16;
        private System.Windows.Forms.Label label17;
        private System.Windows.Forms.Label label18;
        private System.Windows.Forms.GroupBox groupBox5;
        private System.Windows.Forms.TextBox txb_status_system;
        private System.Windows.Forms.Timer timeroutScanHome;
        private System.Windows.Forms.Button btnSavePos;
        private System.Windows.Forms.Button btnConnectToSTM;
        private System.Windows.Forms.Label lb_ConnectMatlab_status;
        private System.Windows.Forms.Button btnComMatlabOpen;
        private System.Windows.Forms.ComboBox cbb_comMatlab;
        private System.IO.Ports.SerialPort COMMatlab;
        private System.Windows.Forms.Timer timer_send_tomatlab;
        private System.Windows.Forms.Label label20;
        private System.Windows.Forms.Label label19;
    }
}

