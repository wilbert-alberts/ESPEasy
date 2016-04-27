//#######################################################################################################
//#################################### Plugin 030: CO2    ###############################################
//#######################################################################################################

#define PLUGIN_030
#define PLUGIN_ID_030         30
#define PLUGIN_NAME_030       "CO2 input"
#define PLUGIN_VALUENAME1_030 "up"
#define PLUGIN_VALUENAME2_030 "down"

volatile unsigned long lastDown=0;
volatile unsigned long lastUp=0;
volatile unsigned long downDuration=0;
volatile unsigned long upDuration=0;

static void change()
{
  if (digitalRead(0)==HIGH)
    rising();
  else
    falling();
}

static void rising()
{
  lastUp = millis();
  downDuration = lastUp - lastDown;
}

static void falling()
{
  lastDown = millis();
  upDuration = lastDown - lastUp;
}


boolean Plugin_030(byte function, struct EventStruct *event, String& string)
{
  boolean success = false;

  switch (function)
  {

    case PLUGIN_DEVICE_ADD:
      {
        Device[++deviceCount].Number = PLUGIN_ID_030;
        Device[deviceCount].Type = DEVICE_TYPE_SINGLE;
        Device[deviceCount].VType = SENSOR_TYPE_SINGLE;
        Device[deviceCount].Ports = 0;
        Device[deviceCount].PullUpOption = false;
        Device[deviceCount].InverseLogicOption = false;
        Device[deviceCount].FormulaOption = true;
        Device[deviceCount].ValueCount = 2;
        Device[deviceCount].SendDataOption = true;
        Device[deviceCount].TimerOption = true;
        Device[deviceCount].GlobalSyncOption = true;
        break;
      }

    case PLUGIN_GET_DEVICENAME:
      {
        string = F(PLUGIN_NAME_030);
        break;
      }

    case PLUGIN_GET_DEVICEVALUENAMES:
      {
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[0], PSTR(PLUGIN_VALUENAME1_030));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[1], PSTR(PLUGIN_VALUENAME2_030));
        break;
      }

    case PLUGIN_INIT:
      {
        String log = F("INIT : CO2 for pin: ");
        log += Settings.TaskDevicePin1[event->TaskIndex];
        addLog(LOG_LEVEL_INFO,log);
        pinMode(Settings.TaskDevicePin1[event->TaskIndex], INPUT_PULLUP);
        Plugin_003_pulseinit(Settings.TaskDevicePin1[event->TaskIndex], event->TaskIndex);
        attachInterrupt(digitalPinToInterrupt(Settings.TaskDevicePin1[event->TaskIndex]), change, CHANGE);        
        success = true;
        break;
      }


      
    case PLUGIN_READ:
      {
        //int value = analogRead(A0);
        UserVar[event->BaseVarIndex] = (float)upDuration;
        UserVar[event->BaseVarIndex+1] = (float)downDuration;
        String log = F("CO2  : Up duration: ");
        log += upDuration;
        addLog(LOG_LEVEL_INFO,log);
        log = F("CO2  : Down duration: ");
        log += downDuration;
        addLog(LOG_LEVEL_INFO,log);
        success = true;
        break;
      }
  }
  return success;
}


