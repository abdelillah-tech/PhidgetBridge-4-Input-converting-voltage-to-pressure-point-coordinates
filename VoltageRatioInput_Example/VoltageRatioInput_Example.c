#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <phidget22.h>
#include "PhidgetHelperFunctions.h"

/**
* Configures the device's DataInterval and ChangeTrigger.
* Displays info about the attached Phidget channel.
* Fired when a Phidget channel with onAttachHandler registered attaches
*
* @param ph The Phidget channel that fired the attach event
* @param *ctx Context pointer. Used to pass information to the event handler.
*/
int chan = 100;
const float a1=2414.90639 ,a2=2511.14513 ,a3=2365.24126 ,a4=2384.04533 ,b1= 4.132401 ,b2= -3.533242 ,b3=-1.350703 ,b4= 3.699914;
float f1=0 ,f2=0 ,f3=0 ,f4=0;
float f1x=0 ,f2x=0 ,f3x=0 ,f4x=0,f1y=0 ,f2y=0 ,f3y=0 ,f4y=0;
const int x1=-48 ,x2=48 ,x3=-48 ,x4=48 ,y1=-48 ,y2=-48 ,y3=48 ,y4=48;
int x=0 ,y=0;
int i = 0;
float v1=0 ,v2=0 ,v3=0 ,v4= 0;

static void CCONV onAttachHandler(PhidgetHandle ph, void *ctx) {
	PhidgetReturnCode prc; //Used to catch error codes from each Phidget function call
	Phidget_ChannelSubclass channelSubclass;
	Phidget_DeviceClass deviceClass;
	const char* channelClassName;
	int32_t serialNumber;
	int32_t hubPort;
	int32_t channel;

	//If you are unsure how to use more than one Phidget channel with this event, we recommend going to
	//www.phidgets.com/docs/Using_Multiple_Phidgets for information
    
	printf("\nAttach Event: ");
	/*
	* Get device information and display it.
	*/
	prc = Phidget_getDeviceSerialNumber(ph, &serialNumber);
	CheckError(prc, "Getting DeviceSerialNumber", (PhidgetHandle *)&ph);

	prc = Phidget_getChannel(ph, &channel);
	CheckError(prc, "Getting Channel", (PhidgetHandle *)&ph);

	prc = Phidget_getChannelClassName(ph, &channelClassName);
	CheckError(prc, "Getting Channel Class Name", (PhidgetHandle *)&ph);

	prc = Phidget_getDeviceClass(ph, &deviceClass);
	CheckError(prc, "Getting Device Class", (PhidgetHandle *)&ph);

	if (deviceClass == PHIDCLASS_VINT) {
		prc = Phidget_getHubPort(ph, &hubPort);
		CheckError(prc, "Getting HubPort", (PhidgetHandle *)&ph);

		printf("\n\t-> Channel Class: %s\n\t-> Serial Number: %d\n\t-> Hub Port: %d\n\t-> Channel %d\n\n", channelClassName, serialNumber, hubPort, channel);
	} else { //Not VINT
		printf("\n\t-> Channel Class: %s\n\t-> Serial Number: %d\n\t-> Channel %d\n\n", channelClassName, serialNumber, channel);
	}

	/*
	*	Set the DataInterval inside of the attach handler to initialize the device with this value.
	*	DataInterval defines the minimum time between VoltageRatioChange events.
	*	DataInterval can be set to any value from MinDataInterval to MaxDataInterval.
	*/
	printf("\tSetting DataInterval to 1000ms\n");
	prc = PhidgetVoltageRatioInput_setDataInterval((PhidgetVoltageRatioInputHandle)ph, 1000);
	CheckError(prc, "Setting DataInterval", (PhidgetHandle *)&ph);

	/*
	*	Set the VoltageRatioChangeTrigger inside of the attach handler to initialize the device with this value.
	*	VoltageRatioChangeTrigger will affect the frequency of VoltageRatioChange events, by limiting them to only occur when
	*	the voltage ratio changes by at least the value set.
	*/
	printf("\tSetting VoltageRatio ChangeTrigger to 0.0\n");
	prc = PhidgetVoltageRatioInput_setVoltageRatioChangeTrigger((PhidgetVoltageRatioInputHandle)ph, 0.0);
	CheckError(prc, "Setting ChangeTrigger", (PhidgetHandle *)&ph);

	/**
	* Set the SensorType inside of the attach handler to initialize the device with this value.
	* You can find the appropriate SensorType for your sensor in its User Guide and the VoltageRatioInput API
	* SensorType will apply the appropriate calculations to the voltage ratio reported by the device
	* to convert it to the sensor's units.
	* SensorType can only be set for Sensor Port voltageRatio inputs(VINT Ports and Analog Input Ports)
	*/
	prc = Phidget_getChannelSubclass(ph, &channelSubclass);
	CheckError(prc, "Getting ChannelSubClass", (PhidgetHandle *)&ph);

	if (channelSubclass == PHIDCHSUBCLASS_VOLTAGEINPUT_SENSOR_PORT) {
		printf("\tSetting VoltageRatio SensorType\n");
		prc = PhidgetVoltageRatioInput_setSensorType((PhidgetVoltageRatioInputHandle)ph, SENSOR_TYPE_VOLTAGE);
		CheckError(prc, "Setting SensorType", (PhidgetHandle *)&ph);
	}
    //hnaaaaaaaaaa
    
}

/**
* Displays info about the detached Phidget channel.
* Fired when a Phidget channel with onDetachHandler registered detaches
*
* @param ph The Phidget channel that fired the detach event
* @param *ctx Context pointer. Used to pass information to the event handler.
*/
static void CCONV onDetachHandler(PhidgetHandle ph, void *ctx) {
	PhidgetReturnCode prc; //Used to catch error codes from each Phidget function call
	Phidget_DeviceClass deviceClass;
	const char* channelClassName;
	int32_t serialNumber;
	int32_t hubPort;
	int32_t channel;

	//If you are unsure how to use more than one Phidget channel with this event, we recommend going to
	//www.phidgets.com/docs/Using_Multiple_Phidgets for information

	printf("\nDetach Event: ");
	/*
	* Get device information and display it.
	*/
	prc = Phidget_getDeviceSerialNumber(ph, &serialNumber);
	CheckError(prc, "Getting DeviceSerialNumber", (PhidgetHandle *)&ph);

	prc = Phidget_getChannel(ph, &channel);
	CheckError(prc, "Getting Channel", (PhidgetHandle *)&ph);

	prc = Phidget_getChannelClassName(ph, &channelClassName);
	CheckError(prc, "Getting Channel Class Name", (PhidgetHandle *)&ph);

	prc = Phidget_getDeviceClass(ph, &deviceClass);
	CheckError(prc, "Getting Device Class", (PhidgetHandle *)&ph);

	if (deviceClass == PHIDCLASS_VINT) {
		prc = Phidget_getHubPort(ph, &hubPort);
		CheckError(prc, "Getting HubPort", (PhidgetHandle *)&ph);

		printf("\n\t-> Channel Class: %s\n\t-> Serial Number: %d\n\t-> Hub Port: %d\n\t-> Channel %d\n\n", channelClassName, serialNumber, hubPort, channel);
	} else { //Not VINT
		printf("\n\t-> Channel Class: %s\n\t-> Serial Number: %d\n\t-> Channel %d\n\n", channelClassName, serialNumber, channel);
	}
}

/**
* Writes Phidget error info to stderr.
* Fired when a Phidget channel with onErrorHandler registered encounters an error in the library
*
* @param ph The Phidget channel that fired the error event
* @param *ctx Context pointer. Used to pass information to the event handler.
* @param errorCode the code associated with the error of enum type Phidget_ErrorEventCode
* @param *errorString string containing the description of the error fired
*/
static void CCONV onErrorHandler(PhidgetHandle ph, void *ctx, Phidget_ErrorEventCode errorCode, const char *errorString) {

	fprintf(stderr, "[Phidget Error Event] -> %s (%d)\n", errorString, errorCode);
}

/**
* Outputs the VoltageRatioInput's most recently reported voltage ratio.
* Fired when a VoltageRatioInput channel with onVoltageRatioChangeHandler registered meets DataInterval and ChangeTrigger criteria
*
* @param ph The VoltageRatioInput channel that fired the VoltageRatioChange event
* @param *ctx Context pointer. Used to pass information to the event handler.
* @param voltageRatio The reported voltage ratio from the VoltageRatioInput channel
*/
static void CCONV onVoltageRatioChangeHandler(PhidgetVoltageRatioInputHandle ph, void *ctx, double voltageRatio) {

	//If you are unsure how to use more than one Phidget channel with this event, we recommend going to
	//www.phidgets.com/docs/Using_Multiple_Phidgets for information
    PhidgetReturnCode prc;
    int channel;
    prc = Phidget_getChannel(ph, &channel);
    CheckError(prc, "Getting Channel", (PhidgetHandle *)&ph);
    
    if(channel == 0){
        //printf("[VoltageRatio Event] -> VoltageRatio sensor, Channel %d : %.4g\n",channel+1,voltageRatio);
        printf("\n|Channel %d : %.4g | ",channel+1,voltageRatio);
        if(i==0)
            v1 = voltageRatio;
        f1 = a1*voltageRatio*1000+b1-(a1*v1*1000+b1);
        f1x = f1 * x1;
        f1y = f1 * y1;
        chan = channel;
    }else if(channel == chan+1){
        //if(channel == 3){
        printf("Channel %d : %.4g | ",channel+1,voltageRatio);
        if(channel == 1){
            if(i==0)
                v2 = voltageRatio;
            f2 = a2*voltageRatio*1000+b2-(a2*v2*1000+b2);
            f2x = f2 * x2;
            f2y = f2 * y2;
        }
        if(channel == 2){
            if(i==0)
                v3 = voltageRatio;
            f3 = a3*voltageRatio*1000+b3-(a3*v3*1000+b3);
            f3x = f3 * x3;
            f3y = f3 * y3;
        }
        if(channel == 3){
            if(i==0)
                v4 = voltageRatio;
            f4 = a4*voltageRatio*1000+b4-(a4*v4*1000+b4);
            f4x = f4 * x4;
            f4y = f4 * y4;
            
            x = (f1x+f2x+f3x+f4x)/(f1+f2+f3+f4);
            y = (f1y + f2y + f3y + f4y)/(f1 + f2 + f3 + f4);
            
            if((f1+f2+f3+f4)<=3 && (f1+f2+f3+f4)>=(-3)){
                printf("( 0 ; 0 ) | ");
            }else
                printf("( %d ; %d ) | ", x, y);
            
            f1=0;f2=0;f3=0;f4=0 ;f1x=0;f2x=0;f3x=0;f4x=0 ;f1y=0;f2y=0;f3y=0;f4y=0 ;x=0;y=0;i=1;
        }
        chan = channel;
    }else{
        if(channel == 1){
            printf("\n|                      | Channel %d : %.4g | ",channel+1,voltageRatio);
            chan = channel;
        }else if(channel == 2){
            printf("\n|                      |                       | Channel %d : %.4g | ",channel+1,voltageRatio);
            chan = channel;
        }else if(channel == 3){
            printf("\n|                      |                       |                   | Channel %d : %.4g | ",channel+1,voltageRatio);
            chan = channel;
        }
    }
}

/**
* Outputs the VoltageRatioInput's most recently reported sensor value.
* Fired when a VoltageRatioInput channel with onSensorChangeHandler registered meets DataInterval and ChangeTrigger criteria
*
* @param ph The VoltageRatioInput channel that fired the SensorChange event
* @param *ctx Context pointer. Used to pass information to the event handler.
* @param sensorValue The reported sensor value from the VoltageRatioInput channel
*/
static void CCONV onSensorChangeHandler(PhidgetVoltageRatioInputHandle ph, void *ctx, double sensorValue, Phidget_UnitInfo *unitInfo) {

	//If you are unsure how to use more than one Phidget channel with this event, we recommend going to
	//www.phidgets.com/docs/Using_Multiple_Phidgets for information
	printf("[Sensor Event] -> Sensor Value: %.4f %s\n", sensorValue, unitInfo->symbol);
}

/**
* Prints descriptions of the available events for this class
*/
void PrintEventDescriptions() {

	printf("\n--------------------\n"
		"\n  | VoltageRatio change events will call their associated function every time new voltage ratio data is received from the device.\n"
		"  | The rate of these events can be set by adjusting the DataInterval for the channel.\n");

	printf(
		"\n  | Sensor change events contain the most recent sensor value received from the device.\n"
		"  | Sensor change events will occur instead of VoltageRatio change events if the SensorType is changed from the default.\n"
		"  | Press ENTER once you have read this message.");
	getchar();

	printf("\n--------------------\n");
}

/**
* Creates, configures, and opens a VoltageRatioInput channel.
* Displays voltage ratio change events for 10 seconds
* Closes out VoltageRatioInput channel
*
* @return 0 if the program exits successfully, 1 if it exits with errors.
*/
int main() {
    
	PhidgetVoltageRatioInputHandle ch[4];
    
	ChannelInfo channelInfo; //Information from AskForDeviceParameters(). May be removed when hard-coding parameters.
    
	PhidgetReturnCode prc; //Used to catch error codes from each Phidget function call

    int Serial_number = 410789; //Serial Number
	/*
	* Allocate a new Phidget Channel object
	*/
    for (int i = 0; i < 4; i++) {
        prc = PhidgetVoltageRatioInput_create(&ch[i]);
        CheckError(prc, "Creating Channel", (PhidgetHandle *)&ch[i]);
    }

    
	/*
	* Set addressing parameters to specify which channel to open
	*/

	//You can safely remove this line and hard-code the parameters to make the program can start without user input
	//AskForDeviceParameters(&channelInfo, (PhidgetHandle *)&ch);
    for (int i = 0; i < 4; i++) {
        prc = Phidget_setDeviceSerialNumber((PhidgetHandle)ch[i], Serial_number);
        CheckError(prc, "Setting DeviceSerialNumber", (PhidgetHandle *)&ch[i]);
    }
    
    for (int i = 0; i < 4; i++) {
        prc = Phidget_setHubPort((PhidgetHandle)ch[i], channelInfo.hubPort);
        CheckError(prc, "Setting HubPort", (PhidgetHandle *)&ch[i]);
    }

    for (int i = 0; i < 4; i++) {
        prc = Phidget_setIsHubPortDevice((PhidgetHandle)ch[i], channelInfo.isHubPortDevice);
        CheckError(prc, "Setting IsHubPortDevice", (PhidgetHandle *)&ch[i]);
    }
    
    for (int i = 0; i < 4; i++) {
        prc = Phidget_setChannel((PhidgetHandle)ch[i], /*channelInfo.channel*/ i);
        CheckError(prc, "Setting Channel", (PhidgetHandle *)&ch);
    }

    
	/*if (channelInfo.netInfo.isRemote) {
		prc = Phidget_setIsRemote((PhidgetHandle)ch, channelInfo.netInfo.isRemote);
		CheckError(prc, "Setting IsRemote", (PhidgetHandle *)&ch);
		if (channelInfo.netInfo.serverDiscovery) {
			prc = PhidgetNet_enableServerDiscovery(PHIDGETSERVER_DEVICEREMOTE);
			CheckEnableServerDiscoveryError(prc, (PhidgetHandle *)&ch);
		} else {
			prc = PhidgetNet_addServer("Server", channelInfo.netInfo.hostname,
				channelInfo.netInfo.port, channelInfo.netInfo.password, 0);
			CheckError(prc, "Adding Server", (PhidgetHandle *)&ch);
		}
	}
    */

	/*
	* Add event handlers before calling open so that no events are missed.
	*/

	printf("\n--------------------------------------\n");
	printf("\nSetting OnAttachHandler...\n");
    for (int i = 0; i < 4; i++) {
        prc = Phidget_setOnAttachHandler((PhidgetHandle)ch[i], onAttachHandler, NULL);
        CheckError(prc, "Setting OnAttachHandler", (PhidgetHandle *)&ch[i]);
    }
    
	printf("Setting OnDetachHandler...\n");
    for (int i = 0; i < 4; i++) {
        prc = Phidget_setOnDetachHandler((PhidgetHandle)ch[i], onDetachHandler, NULL);
        CheckError(prc, "Setting OnDetachHandler", (PhidgetHandle *)&ch[i]);
    }
    
	printf("Setting OnErrorHandler...\n");
    for (int i = 0; i < 4; i++) {
        prc = Phidget_setOnErrorHandler((PhidgetHandle)ch[i], onErrorHandler, NULL);
        CheckError(prc, "Setting OnErrorHandler", (PhidgetHandle *)&ch[i]);
    }
    
	//This call may be harmlessly removed
	//PrintEventDescriptions();

	printf("Setting OnVoltageRatioChangeHandler...\n");
    for (int i = 0; i < 4; i++) {
        prc = PhidgetVoltageRatioInput_setOnVoltageRatioChangeHandler(ch[i], onVoltageRatioChangeHandler, NULL);
        CheckError(prc, "Setting OnVoltageRatioChangeHandler", (PhidgetHandle *)&ch[i]);
    }

	printf("Setting OnSensorChangeHandler...\n");
    for (int i = 0; i < 4; i++) {
        prc = PhidgetVoltageRatioInput_setOnSensorChangeHandler(ch[i], onSensorChangeHandler, NULL);
        CheckError(prc, "Setting OnSensorChangeHandler", (PhidgetHandle *)&ch[i]);
    }

	/*
	* Open the channel with a timeout
	*/
	printf("Opening and Waiting for Attachment...\n");
    printf("\n--------------------------------------\n");
    for (int i = 0; i < 4; i++) {
        //printf("\n sensor %d \n",i+1);
        prc = Phidget_openWaitForAttachment((PhidgetHandle)ch[i], 5000);
        CheckOpenError(prc, (PhidgetHandle *)&ch[i]);
    }
    char k;
    while(1){
        Sleep(1);
    }

	/*
	* To find additional functionality not included in this example,
	* be sure to check the API for your device.
	*/

	printf("Sampling data for 10 seconds...\n");
    
    //Sleep(10000);
	/*
	* Perform clean up and exit
	*/
	printf("\nDone Sampling...\n");
	printf("Cleaning up...\n");
    
    for (int i = 0; i < 4; i++) {
        prc = Phidget_close((PhidgetHandle)ch[i]);
        CheckError(prc, "Closing Channel", (PhidgetHandle *)&ch[i]);
        prc = PhidgetVoltageRatioInput_delete(&ch[i]);
        CheckError(prc, "Deleting Channel", (PhidgetHandle *)&ch[i]);
    }
    printf("\nExiting...\n");
    printf("Press ENTER to end program.\n");
    getchar();

	return 0;
}
