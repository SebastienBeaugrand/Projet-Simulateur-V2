#include <QApplication>
#include <stdio.h>
#include <stdlib.h>
#include "QProcess"
#include <math.h>
#define PI 3.14

extern "C" {
    #include "extApi.h"
}

void SimStartCheck();
void WaitPoint();
void Close();
void Open();
void Conveyor();
void PickupPoint();
void PickAndPlace1A();
void PickAndPlace1B();
void PickAndPlace2A();
void PickAndPlace2B();
void PickAndPlace3A();
void PickAndPlace3B();
void PickAndPlace4A();
void PickAndPlace4B();
void PickAndPlace5A();
void PickAndPlace5B();
void PickAndPlace6A();
void PickAndPlace6B();

int main()
{


    QProcess::startDetached("C:/Program Files/CoppeliaRobotics/CoppeliaSimPro/coppeliaSim.exe");
    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    SimStartCheck();

    uchar DetectionState = 0;
    float DetectedPoint;
    int DetectedObjectHandle;
    float DetectedSurfaceNormalVector;
    int ConteurBloc = 0;
    int ProxSensorSignal;

    while(ConteurBloc<6){
        simxFinish(-1);
        int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

        simxGetObjectHandle(ClientID, "/conveyor/Proximity_sensor", &ProxSensorSignal, simx_opmode_blocking);
        simxReadProximitySensor(ClientID, ProxSensorSignal, &DetectionState, &DetectedPoint, &DetectedObjectHandle, &DetectedSurfaceNormalVector, simx_opmode_blocking);

        if (DetectionState!=0){
            PickupPoint();
            switch(++ConteurBloc){
                case (1):
                    PickAndPlace1A();
                    extApi_sleepMs(1000);
                    PickAndPlace1B();
                    Open();
                    extApi_sleepMs(500);
                    PickAndPlace1A();
                    extApi_sleepMs(500);
                    WaitPoint();
                break;
                case (2):
                    PickAndPlace2A();
                    extApi_sleepMs(1000);
                    PickAndPlace2B();
                    Open();
                    extApi_sleepMs(500);
                    PickAndPlace2A();
                    extApi_sleepMs(500);
                    WaitPoint();
               break;
                case (3):
                    PickAndPlace3A();
                    extApi_sleepMs(1000);
                    PickAndPlace3B();
                    Open();
                    extApi_sleepMs(500);
                    PickAndPlace3A();
                    extApi_sleepMs(500);
                    WaitPoint();
                break;
                case (4):
                    PickAndPlace4A();
                    extApi_sleepMs(1000);
                    PickAndPlace4B();
                    Open();
                    extApi_sleepMs(500);
                    PickAndPlace4A();
                    extApi_sleepMs(500);
                    WaitPoint();
                break;
                case (5):
                    PickAndPlace5A();
                    extApi_sleepMs(1000);
                    PickAndPlace5B();
                    Open();
                    extApi_sleepMs(500);
                    PickAndPlace5A();
                    extApi_sleepMs(500);
                    WaitPoint();
                break;
                case (6):
                    PickAndPlace6A();
                    extApi_sleepMs(1000);
                    PickAndPlace6B();
                    Open();
                    extApi_sleepMs(500);
                    PickAndPlace6A();
                    extApi_sleepMs(500);
                    WaitPoint();
               break;
                }
            }
        }
    simxFinish(ClientID);
}

void SimStartCheck(){
    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);
    int x = 0;
    int TestResultHandle;
    float TestResultPos=0;

    while (x < 1) {
        simxGetObjectHandle(ClientID, "/TargetDummy", &TestResultHandle, simx_opmode_blocking);
        simxGetObjectPosition(ClientID, TestResultHandle, -1, &TestResultPos, simx_opmode_streaming);
        if (TestResultPos!=0){
            x++;
        }

    }

    simxFinish(ClientID);
}

void Open(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int motorHandle;
    float motorVelocity=0.25;
    int motorForce=30;

    simxGetObjectHandle(ClientID, "RG2_openCloseJoint#0", &motorHandle, simx_opmode_blocking);
    simxSetJointMaxForce(ClientID, motorHandle,motorForce,simx_opmode_blocking);
    simxSetJointTargetVelocity(ClientID,motorHandle,motorVelocity,simx_opmode_blocking);

    simxFinish(ClientID);
}

void Close(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int motorHandle;
    float motorVelocity=-0.25;
    int motorForce=30;

    simxGetObjectHandle(ClientID, "RG2_openCloseJoint#0", &motorHandle, simx_opmode_blocking);
    simxSetJointMaxForce(ClientID, motorHandle,motorForce,simx_opmode_blocking);
    simxSetJointTargetVelocity(ClientID,motorHandle,motorVelocity,simx_opmode_blocking);

    extApi_sleepMs(1000);
    simxFinish(ClientID);
}

void WaitPoint(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int joint1= 0;
    int joint2= 0;
    int joint3= 0;
    int joint4= 0;
    int joint5= 0;
    int joint6= 0;
    double V1= 0.5;

    simxGetObjectHandle(ClientID, "UR5_joint1", &joint1, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint2", &joint2, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint3", &joint3, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint4", &joint4, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint5", &joint5, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint6", &joint6, simx_opmode_oneshot_wait);

    simxSetJointTargetVelocity(ClientID, joint1, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint2, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint3, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint4, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint5, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint6, V1, simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(ClientID, joint1, 0.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint2, 0.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint3, 0.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint4, 0.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint5, 0.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint6, 0.0* (PI / 180), simx_opmode_oneshot_wait);

    extApi_sleepMs(500);
    simxFinish(ClientID);
}

void PickupPoint(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int joint1= 0;
    int joint2= 0;
    int joint3= 0;
    int joint4= 0;
    int joint5= 0;
    int joint6= 0;
    double V1= 0.5;

    simxGetObjectHandle(ClientID, "UR5_joint1", &joint1, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint2", &joint2, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint3", &joint3, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint4", &joint4, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint5", &joint5, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint6", &joint6, simx_opmode_oneshot_wait);

    simxSetJointTargetVelocity(ClientID, joint1, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint2, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint3, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint4, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint5, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint6, V1, simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(ClientID, joint1, 90.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint2, 0.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint3, 90.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint4, 70.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint5, 90.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint6, 0.0* (PI / 180), simx_opmode_oneshot_wait);

    extApi_sleepMs(1000);
    simxSetJointTargetPosition(ClientID, joint2, 20.0* (PI / 180), simx_opmode_oneshot_wait);
    extApi_sleepMs(500);
    Close();
    extApi_sleepMs(500);
    simxFinish(ClientID);
}

void PickAndPlace1A(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int joint1= 0;
    int joint2= 0;
    int joint3= 0;
    int joint4= 0;
    int joint5= 0;
    int joint6= 0;
    double V1= 0.5;

    simxGetObjectHandle(ClientID, "UR5_joint1", &joint1, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint2", &joint2, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint3", &joint3, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint4", &joint4, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint5", &joint5, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint6", &joint6, simx_opmode_oneshot_wait);

    simxSetJointTargetVelocity(ClientID, joint1, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint2, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint3, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint4, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint5, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint6, V1, simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(ClientID, joint1, 0.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint2, 15.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint3, 78.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint4, -25.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint5, 270.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint6, 0.0* (PI / 180), simx_opmode_oneshot_wait);

    simxFinish(ClientID);
}

void PickAndPlace1B(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int joint1= 0;
    int joint2= 0;
    int joint3= 0;
    int joint4= 0;
    int joint5= 0;
    int joint6= 0;
    double V1= 0.5;

    simxGetObjectHandle(ClientID, "UR5_joint1", &joint1, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint2", &joint2, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint3", &joint3, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint4", &joint4, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint5", &joint5, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint6", &joint6, simx_opmode_oneshot_wait);

    simxSetJointTargetVelocity(ClientID, joint1, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint2, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint3, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint4, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint5, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint6, V1, simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(ClientID, joint1, 0.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint2, 33.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint3, 78.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint4, -25.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint5, 270.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint6, 0.0* (PI / 180), simx_opmode_oneshot_wait);

    simxFinish(ClientID);
}
void PickAndPlace2A(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int joint1= 0;
    int joint2= 0;
    int joint3= 0;
    int joint4= 0;
    int joint5= 0;
    int joint6= 0;
    double V1= 0.5;

    simxGetObjectHandle(ClientID, "UR5_joint1", &joint1, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint2", &joint2, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint3", &joint3, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint4", &joint4, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint5", &joint5, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint6", &joint6, simx_opmode_oneshot_wait);

    simxSetJointTargetVelocity(ClientID, joint1, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint2, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint3, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint4, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint5, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint6, V1, simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(ClientID, joint1, 6.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint2, 16.8* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint3, 75.3* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint4, -25.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint5, 270.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint6, 7.5* (PI / 180), simx_opmode_oneshot_wait);

    simxFinish(ClientID);
}

void PickAndPlace2B(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int joint1= 0;
    int joint2= 0;
    int joint3= 0;
    int joint4= 0;
    int joint5= 0;
    int joint6= 0;
    double V1= 0.5;

    simxGetObjectHandle(ClientID, "UR5_joint1", &joint1, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint2", &joint2, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint3", &joint3, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint4", &joint4, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint5", &joint5, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint6", &joint6, simx_opmode_oneshot_wait);

    simxSetJointTargetVelocity(ClientID, joint1, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint2, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint3, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint4, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint5, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint6, V1, simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(ClientID, joint1, 6.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint2, 34.8* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint3, 75.3* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint4, -25.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint5, 270.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint6, 7.5* (PI / 180), simx_opmode_oneshot_wait);

    simxFinish(ClientID);
}

void PickAndPlace3A(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int joint1= 0;
    int joint2= 0;
    int joint3= 0;
    int joint4= 0;
    int joint5= 0;
    int joint6= 0;
    double V1= 0.5;

    simxGetObjectHandle(ClientID, "UR5_joint1", &joint1, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint2", &joint2, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint3", &joint3, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint4", &joint4, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint5", &joint5, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint6", &joint6, simx_opmode_oneshot_wait);

    simxSetJointTargetVelocity(ClientID, joint1, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint2, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint3, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint4, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint5, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint6, V1, simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(ClientID, joint1, 11.8* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint2, 20.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint3, 69.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint4, -20.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint5, 270.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint6, 11.0* (PI / 180), simx_opmode_oneshot_wait);

    simxFinish(ClientID);
}

void PickAndPlace3B(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int joint1= 0;
    int joint2= 0;
    int joint3= 0;
    int joint4= 0;
    int joint5= 0;
    int joint6= 0;
    double V1= 0.5;

    simxGetObjectHandle(ClientID, "UR5_joint1", &joint1, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint2", &joint2, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint3", &joint3, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint4", &joint4, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint5", &joint5, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint6", &joint6, simx_opmode_oneshot_wait);

    simxSetJointTargetVelocity(ClientID, joint1, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint2, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint3, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint4, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint5, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint6, V1, simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(ClientID, joint1, 11.8* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint2, 38.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint3, 69.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint4, -20.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint5, 270.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint6, 11.0* (PI / 180), simx_opmode_oneshot_wait);

    simxFinish(ClientID);
}

void PickAndPlace4A(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int joint1= 0;
    int joint2= 0;
    int joint3= 0;
    int joint4= 0;
    int joint5= 0;
    int joint6= 0;
    double V1= 0.5;

    simxGetObjectHandle(ClientID, "UR5_joint1", &joint1, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint2", &joint2, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint3", &joint3, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint4", &joint4, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint5", &joint5, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint6", &joint6, simx_opmode_oneshot_wait);

    simxSetJointTargetVelocity(ClientID, joint1, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint2, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint3, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint4, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint5, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint6, V1, simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(ClientID, joint1, -6.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint2, 15.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint3, 77.5* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint4, -22.5* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint5, 270.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint6, -6.0* (PI / 180), simx_opmode_oneshot_wait);

    simxFinish(ClientID);
}

void PickAndPlace4B(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int joint1= 0;
    int joint2= 0;
    int joint3= 0;
    int joint4= 0;
    int joint5= 0;
    int joint6= 0;
    double V1= 0.5;

    simxGetObjectHandle(ClientID, "UR5_joint1", &joint1, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint2", &joint2, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint3", &joint3, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint4", &joint4, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint5", &joint5, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint6", &joint6, simx_opmode_oneshot_wait);

    simxSetJointTargetVelocity(ClientID, joint1, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint2, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint3, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint4, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint5, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint6, V1, simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(ClientID, joint1, -6.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint2, 33.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint3, 77.5* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint4, -22.5* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint5, 270.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint6, -6.0* (PI / 180), simx_opmode_oneshot_wait);

    simxFinish(ClientID);
}

void PickAndPlace5A(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int joint1= 0;
    int joint2= 0;
    int joint3= 0;
    int joint4= 0;
    int joint5= 0;
    int joint6= 0;
    double V1= 0.5;

    simxGetObjectHandle(ClientID, "UR5_joint1", &joint1, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint2", &joint2, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint3", &joint3, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint4", &joint4, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint5", &joint5, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint6", &joint6, simx_opmode_oneshot_wait);

    simxSetJointTargetVelocity(ClientID, joint1, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint2, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint3, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint4, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint5, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint6, V1, simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(ClientID, joint1, -12.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint2, 15.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint3, 77.5* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint4, -22.5* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint5, 270.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint6, -14.0* (PI / 180), simx_opmode_oneshot_wait);

    simxFinish(ClientID);
}

void PickAndPlace5B(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int joint1= 0;
    int joint2= 0;
    int joint3= 0;
    int joint4= 0;
    int joint5= 0;
    int joint6= 0;
    double V1= 0.5;

    simxGetObjectHandle(ClientID, "UR5_joint1", &joint1, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint2", &joint2, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint3", &joint3, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint4", &joint4, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint5", &joint5, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint6", &joint6, simx_opmode_oneshot_wait);

    simxSetJointTargetVelocity(ClientID, joint1, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint2, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint3, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint4, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint5, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint6, V1, simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(ClientID, joint1, -12.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint2, 33.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint3, 77.5* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint4, -22.5* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint5, 270.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint6, -14.0* (PI / 180), simx_opmode_oneshot_wait);

    simxFinish(ClientID);
}

void PickAndPlace6A(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int joint1= 0;
    int joint2= 0;
    int joint3= 0;
    int joint4= 0;
    int joint5= 0;
    int joint6= 0;
    double V1= 0.5;

    simxGetObjectHandle(ClientID, "UR5_joint1", &joint1, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint2", &joint2, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint3", &joint3, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint4", &joint4, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint5", &joint5, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint6", &joint6, simx_opmode_oneshot_wait);

    simxSetJointTargetVelocity(ClientID, joint1, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint2, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint3, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint4, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint5, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint6, V1, simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(ClientID, joint1, -18.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint2, 15.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint3, 77.5* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint4, -24.5* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint5, 270.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint6, -20.0* (PI / 180), simx_opmode_oneshot_wait);

    simxFinish(ClientID);
}

void PickAndPlace6B(){

    simxFinish(-1);
    int ClientID = simxStart("127.0.0.1", 19997, true,true,2000,5);

    int joint1= 0;
    int joint2= 0;
    int joint3= 0;
    int joint4= 0;
    int joint5= 0;
    int joint6= 0;
    double V1= 0.5;

    simxGetObjectHandle(ClientID, "UR5_joint1", &joint1, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint2", &joint2, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint3", &joint3, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint4", &joint4, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint5", &joint5, simx_opmode_oneshot_wait);
    simxGetObjectHandle(ClientID, "UR5_joint6", &joint6, simx_opmode_oneshot_wait);

    simxSetJointTargetVelocity(ClientID, joint1, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint2, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint3, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint4, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint5, V1, simx_opmode_oneshot_wait);
    simxSetJointTargetVelocity(ClientID, joint6, V1, simx_opmode_oneshot_wait);

    simxSetJointTargetPosition(ClientID, joint1, -18.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint2, 33.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint3, 77.5* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint4, -24.5* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint5, 270.0* (PI / 180), simx_opmode_oneshot_wait);
    simxSetJointTargetPosition(ClientID, joint6, -20.0* (PI / 180), simx_opmode_oneshot_wait);

    simxFinish(ClientID);
}




