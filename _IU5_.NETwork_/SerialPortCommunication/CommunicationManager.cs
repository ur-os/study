

using System;
using System.Text;
using System.Drawing;
using System.IO.Ports;
using System.Windows.Forms;
using CyclicCode;
using Hamming;


namespace PCComm
{

    class CommunicationManager
    {
        #region Manager Enums
        public enum MessageType { Incoming, Outgoing, Normal, Warning, Error };
        #endregion

        #region Frame
        public enum FrameType:byte   //тип кадра
        {
                                
                                UPLINK,     //кадр установки соединения
                                ACK_UPLINK,
                                ACK,
                                ACK_DOWNLINK,
                                ACK_LINKACTIVE,//кадры -квитанция
                                RET_UPLINK,
                                RET_DOWNLINK,                                
                                RET_LINKACITVE,
                                RET,//кадры - ARQ
                                DOWNLINK,    //кадр разрыва соединения
                                LINKACTIVE,
                                DAT
        }
        
        const byte START=0xFF;//стартовый байт
        #endregion

        #region Manager Variables
        
        private string _baudRate = string.Empty;
        private string _parity = string.Empty;
        private string _stopBits = string.Empty;
        private string _dataBits = string.Empty;
        private string _portName = string.Empty;
        private RichTextBox _displayWindow;
        private Color[] MessageColor = { Color.Blue, Color.Green, Color.Black, Color.Orange, Color.Red };      
        private SerialPort comPort = new SerialPort();
        private bool _linkActive=false;
        private string _currentMsg = string.Empty;//последнее напечатанное сообщение
        public DateTime dt_new = new DateTime();// "засечка" времени 
        public string user1;
        public string user2;

        private HammingCoder ham = new HammingCoder();

        #endregion

        #region Manager Properties
        public string BaudRate
        {
            get { return _baudRate; }
            set { _baudRate = value; }
        }

        public string CurrentMsg
        {
            get { return _currentMsg; }
            set { _currentMsg = value; }
        }

        public bool LinkActive
        {
            get { return _linkActive; }
            set { _linkActive = value; }
        }


        public string Parity
        {
            get { return _parity; }
            set { _parity = value; }
        }


        public string StopBits
        {
            get { return _stopBits; }
            set { _stopBits = value; }
        }

 
        public string DataBits
        {
            get { return _dataBits; }
            set { _dataBits = value; }
        }


        public string PortName
        {
            get { return _portName; }
            set { _portName = value; }
        }
       

        public RichTextBox DisplayWindow
        {
            get { return _displayWindow; }
            set { _displayWindow = value; }
        }
        #endregion

        #region FrameAnalise
        public void FrameAnalysis(byte mybyte)
        {
            switch (mybyte)
            {
                case (byte)FrameType.UPLINK:
                    
                    LinkActive = true;
                    DisplayData(MessageType.Normal, DateTime.Now + " UPLINK \n");
                    WriteData(null, FrameType.ACK_UPLINK, false);  
                    break;

                case (byte)FrameType.DOWNLINK:

                    LinkActive = false;
                    DisplayData(MessageType.Normal, DateTime.Now + " DOWNLINK \n");
                    WriteData(null, FrameType.ACK_DOWNLINK, false);
                    break;

                case (byte)FrameType.ACK:

                    DisplayData(MessageType.Normal, DateTime.Now + " ACK \n");
                    break;

                case (byte)FrameType.ACK_DOWNLINK:

                    LinkActive = false;
                    DisplayData(MessageType.Normal, DateTime.Now + " ACK_DOWNLINK \n");                    
                    break;

                case (byte)FrameType.ACK_LINKACTIVE:

                    LinkActive = true; 
                    DisplayData(MessageType.Normal, DateTime.Now + " ACK_LINKACTIVE \n");
                    break;

                case (byte)FrameType.ACK_UPLINK:

                    LinkActive = true;
                    DisplayData(MessageType.Normal, DateTime.Now + " ACK_UPLINK \n");
                    break;

                case (byte)FrameType.RET:

                    DisplayData(MessageType.Normal, DateTime.Now + " RET \n");
                    WriteData(_currentMsg, FrameType.DAT, true);
                    break;

                case (byte)FrameType.RET_DOWNLINK:

                    LinkActive = false;
                    DisplayData(MessageType.Normal, DateTime.Now + " RET_DOWNLINK \n");
                    WriteData(null, FrameType.DOWNLINK, false);
                    break;

                case (byte)FrameType.RET_LINKACITVE:

                    LinkActive = false;
                    DisplayData(MessageType.Normal, DateTime.Now + " RET_LINKACITVE \n");
                    WriteData(null, FrameType.LINKACTIVE, false);
                    break;

                case (byte)FrameType.RET_UPLINK:

                    LinkActive = false;
                    DisplayData(MessageType.Normal, DateTime.Now + " RET_UPLINK \n");                    
                    WriteData(null, FrameType.UPLINK, false);
                    break;

                case (byte)FrameType.LINKACTIVE:

                    LinkActive = true;
                    DisplayData(MessageType.Normal, DateTime.Now + " LINKACTIVE \n");
                    WriteData(null, FrameType.ACK_LINKACTIVE, false);     
                    break;

                case (byte)FrameType.DAT:
                    
                    DisplayData(MessageType.Normal, DateTime.Now + " DAT \n");
                    int bytes = comPort.BytesToRead;                                          
                    byte[] comBuffer = new byte[bytes];
                   
                    // записываем в массив данные от ком порта
                    comPort.Read(comBuffer, 0, bytes);

                    //отображаем информацию для пользователя
                    var source = ham.Decode(comBuffer);
                    var decodedStr = "";
                    if (source.Length != 0)
                        decodedStr = Encoding.Unicode.GetString(source);
                    if (decodedStr == "") WriteData(null, FrameType.RET, false);//неуспешно приняли просим повторно 
                    else
                    {
                        WriteData(null, FrameType.ACK, false);//успешно приняли отправляем квитанцию
                        DisplayData(MessageType.Incoming, user2 + " [ " + DateTime.Now + " ] \n" + decodedStr + "\n");
                    }
                    break;

                default:
                    DisplayData(MessageType.Normal,DateTime.Now+" unknow frame \n");
                    break;
            }
        }
        
        #endregion

        #region Manager Constructors

        public CommunicationManager(string baud, string par, string sBits, string dBits, string name, RichTextBox rtb)
        {
            _baudRate = baud;
            _parity = par;
            _stopBits = sBits;
            _dataBits = dBits;
            _portName = name;
            _displayWindow = rtb;            
            comPort.DataReceived += new SerialDataReceivedEventHandler(comPort_DataReceived);

        }

 
        public CommunicationManager()
        {
            _baudRate = string.Empty;
            _parity = string.Empty;
            _stopBits = string.Empty;
            _dataBits = string.Empty;
            _portName = "COM1";
            _displayWindow = null;           
            comPort.DataReceived += new SerialDataReceivedEventHandler(comPort_DataReceived);
 
        }
        #endregion

        #region WriteData
        public void WriteData(string msg,FrameType CurrentFrameType, bool msg_no_display)
        {
            byte[]FrameFields={START,(byte)CurrentFrameType};//заполняем первые два поля кадра стартовый и тип
            
            switch (CurrentFrameType)
            {
                case FrameType.DAT:
                    try
                    {
                        //преобразуем сообщение в массив типа byte
                        var bytes = Encoding.Unicode.GetBytes(msg);
                        byte[] newMsg = ham.Encode(bytes);
                        comPort.Write(FrameFields,0,2);
                        //отсылаем сообщение в порт
                        comPort.Write(newMsg, 0, newMsg.Length);
                        if (!msg_no_display) DisplayData(MessageType.Outgoing, user1+" [ " + DateTime.Now + " ] \n" + msg + "\n");
                    }
                    catch (FormatException ex)
                    {
                        DisplayData(MessageType.Error, ex.Message);
                    }
                
                    break;
                default:
                    
                    if (!(comPort.IsOpen == true)) comPort.Open();
                    comPort.Write(FrameFields, 0, 2);               
                    break;
                    
            }
        }
        #endregion
        
        #region DisplayData
        [STAThread]
        private void DisplayData(MessageType type, string msg)
        {
            _displayWindow.Invoke(new EventHandler(delegate
            {
                _displayWindow.SelectedText = string.Empty;
                _displayWindow.SelectionFont = new Font(_displayWindow.SelectionFont, FontStyle.Bold);
                _displayWindow.SelectionColor = MessageColor[(int)type];
                _displayWindow.AppendText(msg);
                _displayWindow.ScrollToCaret();
           
            }));
        }
        #endregion

        #region OpenPort
        public bool OpenPort()
        {
            try
            {

                if (comPort.IsOpen == true) comPort.Close();

                //установка параметров ком порта
                comPort.BaudRate = int.Parse(_baudRate);    
                comPort.DataBits = int.Parse(_dataBits);   
                comPort.StopBits = (StopBits)Enum.Parse(typeof(StopBits), _stopBits);    
                comPort.Parity = (Parity)Enum.Parse(typeof(Parity), _parity);   
                comPort.PortName = _portName; 
                
                
                comPort.RtsEnable = true;
                comPort.Open();
           
              

                
                //отображение сообщения
                DisplayData(MessageType.Normal, "Порт открыт " + DateTime.Now + "\n");
                return true;
            }
            catch (Exception ex)
            {
                DisplayData(MessageType.Error, ex.Message);
                return false;
            }
        }
        #endregion

        #region SetParityValues
        public void SetParityValues(object obj)
        {
            foreach (string str in Enum.GetNames(typeof(Parity)))
            {
                ((ComboBox)obj).Items.Add(str);
            }
        }
        #endregion

        #region SetStopBitValues
        public void SetStopBitValues(object obj)
        {
            foreach (string str in Enum.GetNames(typeof(StopBits)))
            {
                ((ComboBox)obj).Items.Add(str);
            }
        }
        #endregion

        #region SetPortNameValues
        public void SetPortNameValues(object obj)
        {

            foreach (string str in SerialPort.GetPortNames())
            {
                ((ComboBox)obj).Items.Add(str);
            }
        }
        #endregion

        #region comPort_DataReceived

        void comPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {

            dt_new = DateTime.Now;

            switch(comPort.ReadByte())
            {
                case START:
                    {
                        FrameAnalysis((byte)comPort.ReadByte());
                    }
                    break;

                default:
                    {
                        WriteData(null, FrameType.RET, false);
                    }
                    break;
            }        

           
        }
        #endregion

        #region ClosePort
        public bool ClosePort()
        {
            try
            {
                if (comPort.IsOpen == true) comPort.Close();

                DisplayData(MessageType.Normal, "Порт закрыт " + DateTime.Now + "\n");
                return true;
            }
            catch (Exception ex)
            {
                DisplayData(MessageType.Error, ex.Message);
                return false;
            }
        }
        #endregion
    }
}
