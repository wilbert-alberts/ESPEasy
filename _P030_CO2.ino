//#######################################################################################################
//#################################### Plugin 030: CO2    ###############################################
//#######################################################################################################

#define PLUGIN_030
#define PLUGIN_ID_030         30
#define PLUGIN_NAME_030       "CO2 input"
#define PLUGIN_VALUENAME1_030 "CO2"
boolean Plugin_030(byte function, struct EventStruct *event, String& string)
{
  boolean success = false;

  switch (function)
  {

    case PLUGIN_DEVICE_ADD:
      {
        Device[++deviceCount].Number = PLUGIN_ID_030;
        Device[deviceCount].Type = DEVICE_TYPE_ANALOG;
        Device[deviceCount].VType = SENSOR_TYPE_SINGLE;
        Device[deviceCount].Ports = 0;
        Device[deviceCount].PullUpOption = false;
        Device[deviceCount].InverseLogicOption = false;
        Device[deviceCount].FormulaOption = true;
        Device[deviceCount].ValueCount = 1;
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
        break;
      }
      
    case PLUGIN_READ:
      {
        int value = analogRead(A0);
        UserVar[event->BaseVarIndex] = (float)value;
        String log = F("ADC  : Analog value: ");
        log += value;
        addLog(LOG_LEVEL_INFO,log);
        success = true;
        break;
      }
  }
  return success;
}
