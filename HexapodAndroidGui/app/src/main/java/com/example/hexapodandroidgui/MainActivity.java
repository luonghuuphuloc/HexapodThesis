package com.example.hexapodandroidgui;

import android.content.SharedPreferences;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.text.method.ScrollingMovementMethod;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Scroller;
import android.widget.TextView;

import org.eclipse.paho.client.mqttv3.IMqttDeliveryToken;
import org.eclipse.paho.client.mqttv3.MqttCallbackExtended;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Timer;
import java.util.TimerTask;

public class MainActivity extends AppCompatActivity {

    private TextView  tv_HexaStatus;
    private TextView  tv_ConnectionStatus;
    private TextView  tv_MotorPosition;
    private EditText edt_TestX;
    private EditText edt_TestY;
    private EditText edt_TestZ;
    private EditText edt_TestRoll;
    private EditText edt_TestPitch;
    private EditText edt_TestYaw;
    private Button btn_TestStart;
    private Button btn_ConnectSTM;
    private Button btn_HomeScan;
    private Button btn_InvKinetic;
    private Button btn_SavePos;

    private String str_mqtt_cmd = "";
    private String[] str_mqtt_msg;
    private String str_log = "";
    private String str_motor_pos = "";
    private String str_tv = "";
    private boolean isMotorPosShowEnabled = false;
    private boolean isLogShowEnabled = false;
    private boolean isMqttMsgProcessingFinished = true;
    private boolean isConnectSTM;
    private boolean allow_write_log_flag = false;
    MqttHelper mqttHelper;

    DateFormat df;

    Timer timer;
    TimerTask timerTask;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        tv_HexaStatus = (TextView) findViewById(R.id.tvHexaStatus);
        tv_ConnectionStatus = (TextView) findViewById(R.id.tvConnectionStatus);
        tv_MotorPosition = (TextView) findViewById(R.id.tvMotorPosition);
        edt_TestX = (EditText) findViewById(R.id.edtTestX);
        edt_TestY = (EditText) findViewById(R.id.edtTestY);
        edt_TestZ = (EditText) findViewById(R.id.edtTestZ);
        edt_TestRoll = (EditText) findViewById(R.id.edtTestRoll);
        edt_TestPitch = (EditText) findViewById(R.id.edtTestPitch);
        edt_TestYaw = (EditText) findViewById(R.id.edtTestYaw);
        btn_TestStart = (Button) findViewById(R.id.btnTestStart);
        btn_ConnectSTM = (Button) findViewById(R.id.btnConnectSTM);
        btn_HomeScan = (Button) findViewById(R.id.btnHomeScanStart);
        btn_InvKinetic = (Button) findViewById(R.id.btnInvKinematicStart);
        btn_SavePos = (Button) findViewById(R.id.btnSavePosition);

        tv_HexaStatus.setMovementMethod(new ScrollingMovementMethod());
        str_mqtt_msg = new String[10];
        str_tv = new String();
        isLogShowEnabled = false;
        isMotorPosShowEnabled = false;
        timer = new Timer();
        timerTask = new TimerTask() {
            @Override
            public void run() {
                    tv_MotorPosition.post(new Runnable() {
                        @Override
                        public void run() {
                            tv_MotorPosition.setText(str_motor_pos);
                        }
                    });

                    tv_HexaStatus.post(new Runnable() {
                        @Override
                        public void run() {
                            tv_HexaStatus.setText(str_log);
                        }
                    });



                }

        };
        timer.schedule(timerTask, 2000, 30);
        isConnectSTM = false;
        isMqttMsgProcessingFinished = true;

        mqttHelper = new MqttHelper(getApplicationContext());

        df = new SimpleDateFormat("h:mm:ss a");

        btn_SavePos.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mqttHelper.publish("androidcontrol", "a-s");
            }
        });

        btn_TestStart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                str_mqtt_cmd = Edt2Float(edt_TestX) + Edt2Float(edt_TestY)
                    + Edt2Float(edt_TestZ) + Edt2Float(edt_TestRoll) + Edt2Float(edt_TestPitch)
                    + Edt2Float(edt_TestYaw) ;
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        if(isConnectSTM)
                            mqttHelper.publish("androidcontrol", "a-t-" + str_mqtt_cmd);
                    }
                }).start();


            }
        });

        btn_ConnectSTM.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(isConnectSTM == false) {
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            mqttHelper.publish("androidcontrol", "a-cr");
                        }
                    }).start();

                }
                else
                {
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            mqttHelper.publish("androidcontrol", "a-cd");
                        }
                    }).start();
                    btn_ConnectSTM.post(new Runnable() {
                        @Override
                        public void run() {
                            btn_ConnectSTM.setText("CONNECT TO STM");
                        }
                    });
                    isConnectSTM = false;
                }
            }
        });

        btn_HomeScan.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        if(isConnectSTM)
                            mqttHelper.publish("androidcontrol", "a-hs-rlrlrl");
                    }
                }).start();

            }
        });

        btn_InvKinetic.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                str_mqtt_cmd = Edt2Float(edt_TestX) + Edt2Float(edt_TestY)
                        + Edt2Float(edt_TestZ) + Edt2Float(edt_TestRoll) + Edt2Float(edt_TestPitch)
                        + Edt2Float(edt_TestYaw) ;
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        if(isConnectSTM)
                            mqttHelper.publish("androidcontrol", "a-ki" + str_mqtt_cmd);
                    }
                }).start();

            }
        });
        mqttHelper.setCallback(new MqttCallbackExtended() {
            @Override
            public void connectComplete(boolean reconnect, String serverURI) {
                Log.w("mqtt", "Connected");
                allow_write_log_flag = true;
                tv_HexaStatus.post(new Runnable() {
                    @Override
                    public void run() {
                        tv_HexaStatus.append(df.format(Calendar.getInstance().getTime()) + ": Mqtt connected.\n");
                    }
                });

            }

            @Override
            public void connectionLost(Throwable cause) {
                Log.w("mqtt", "Disconnected");
                allow_write_log_flag = true;
                tv_HexaStatus.post(new Runnable() {
                    @Override
                    public void run() {
                        tv_HexaStatus.append(df.format(Calendar.getInstance().getTime()) + ": Mqtt disconnected.\n");
                    }
                });

            }

            @Override
            public void messageArrived(String topic, final MqttMessage message) throws Exception {
                Log.w("mqtt", "Received");

                str_mqtt_msg = message.toString().split("-");

                if(isMqttMsgProcessingFinished) {
                    new Thread(new Runnable() {
                        @Override
                        public void run() {
                            isMqttMsgProcessingFinished = false;
                            MqttMsgProcessing(str_mqtt_msg);
                        }
                    }).start();
                }
            }

            @Override
            public void deliveryComplete(IMqttDeliveryToken token) {
                Log.w("mqtt", "Delivered");
                //tv_HexaStatus.append(df.format(Calendar.getInstance().getTime()) + ": Mqtt delivered a message.\n");
            }
        });
    }

    void MqttMsgProcessing(String[] strarr_msg) {
        int parts_count = strarr_msg.length;
        for(int i = 0; i < parts_count - 1; i++) {
            str_motor_pos = "";
            char[] chars_motor_pos = new char[7];
            char[] chars_msg = new char[100];
            String msg_display = new String();
            strarr_msg[i].getChars(0, strarr_msg[i].length(), chars_msg, 0);
            switch (chars_msg[2]) {
                case 'l': {
                    for (int j = 3; j < strarr_msg[i].length(); j++)
                        msg_display += strarr_msg[i].charAt(j);
                    switch (msg_display) {
                        case "STM Ready":
                        {
                            str_tv = "Tracking Mode";
                            btn_ConnectSTM.post(new Runnable() {
                                @Override
                                public void run() {
                                    btn_ConnectSTM.setText("CONNECT TO STM");
                                }
                            });
                            isConnectSTM = false;
                            break;
                        }
                        case "SAAC": { //STM and Android connected
                            msg_display = "STM and Android connected";
                            str_tv = "Remote Mode";
                            btn_ConnectSTM.post(new Runnable() {
                                @Override
                                public void run() {
                                    btn_ConnectSTM.setText("DISCONNECT TO STM");
                                }
                            });
                            isConnectSTM = true;
                            break;
                        }
                        case "PIR": { //PC is running
                            msg_display = "PC is running";
                            str_tv = "Tracking Mode";
                            btn_ConnectSTM.post(new Runnable() {
                                @Override
                                public void run() {
                                    btn_ConnectSTM.setText("CONNECT TO STM");
                                }
                            });
                            isConnectSTM = false;
                            break;
                        }
                        case "TMA": { //Tracking Mode activated
                            msg_display = "Tracking Mode activated";
                            str_tv = "Tracking Mode";
                            btn_ConnectSTM.post(new Runnable() {
                                @Override
                                public void run() {
                                    btn_ConnectSTM.setText("CONNECT TO STM");
                                }
                            });
                            isConnectSTM = false;
                            break;
                        }
                        case "ISTPS": {
                            msg_display = "I saved the position successfully";
                            break;
                        }
                        case "PIW": {
                            msg_display = "PC is waiting";
                            break;
                        }
                        case "PID": {
                            msg_display = "PC is disconnected";
                            break;
                        }
                        case "IAIIM": {
                            msg_display = "I am in Idle Mode";
                            break;
                        }
                        case "IAITM": {
                            msg_display = "I am in Testing Mode";
                            break;
                        }
                        case "IAIHSM": {
                            msg_display = "I am in Home Scan Mode";
                            break;
                        }
                        case "IAIIKM": {
                            msg_display = "I am in Inverse Kinematic Mode";
                            break;
                        }
                        case "ICNCIK": {
                            msg_display = "I can not calculate inverse kinematic";
                            break;
                        }

                    }
                    tv_ConnectionStatus.post(new Runnable() {
                        @Override
                        public void run() {
                            tv_ConnectionStatus.setText(str_tv);
                        }
                    });

                    str_log += df.format(Calendar.getInstance().getTime()) + ": " + msg_display + "\n";
                    break;
                }
                case 'e': {
                    int j = 0;
                    for (int k = 0; k < 6; k++) {
                        strarr_msg[i].getChars(3 + k + j, 10 + k + j, chars_motor_pos, 0);
                        if (k != 5)
                            str_motor_pos += String.copyValueOf(chars_motor_pos) + ";";
                        else {
                            str_motor_pos += String.copyValueOf(chars_motor_pos);
                        }
                        j += 6;
                    }
                    break;
                }
                case 'h':
                {
                    if((chars_msg[3] == 'f') && (chars_msg[4] == 'a'))
                    {
                        new Thread(new Runnable() {
                            @Override
                            public void run() {
                                mqttHelper.publish("androidcontrol", "a-he");
                                str_log += df.format(Calendar.getInstance().getTime()) + ": Home Scan finished.\n";
                            }
                        }).start();
                    }
                }
                default: {
                    isLogShowEnabled = false;
                    isMotorPosShowEnabled = false;
                    break;
                }
            }

        }

        isMqttMsgProcessingFinished = true;
    }


    String Edt2Float(EditText txt)
    {
        DecimalFormat df1 = new DecimalFormat("000.000");
        DecimalFormat df2 = new DecimalFormat("00.000");
        String ret;
        float val;
        try
        {
            val = Float.valueOf(txt.getText().toString());
            if(val > 999.999f)
                val = 999.999f;
            else if(val < -99.999f)
                val = -99.999f;
            if(val >= 0.0f)
                ret = df1.format(val);
            else
                ret = df2.format(val);
            return ret;
        }
        catch(Exception e)
        {
            ret = df1.format(0.0f);
            return ret;
        }
    }
}

