#include <string>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "redactor.h"

bool debugFlag = true;

/**
 * Log a message to the console.
 */
void log(std::string message) {
    std::cout << "[LOG] " << message << std::endl;
}

/**
 * Log a debug message to the console.
 */
void debug(std::string message) {
    if (debugFlag) {
        std::cout << "[DEBUG] " << message << std::endl;
    }
}

/**
 * Get a pre-defined document for testing purposes.
 */
rapidjson::Document getTestDocument(Redactor redactor) {
    const char* jsonString = "{\"metadata\":{\"latency\":1,\"logFileName\":\"wsmpforward.coer\",\"payloadType\":\"us.dot.its.jpo.ode.model.OdeBsmPayload\",\"receivedAt\":\"2017-08-02T19:56:45.822Z[UTC]\",\"sanitized\":false,\"schemaVersion\":1,\"serialId\":{\"bundleId\":4,\"bundleSize\":1,\"recordId\":2,\"serialNumber\":0,\"streamId\":\"0bfda39b-0bf1-4e2e-a1f1-b858426f7408\"},\"validSignature\":false},\"payload\":{\"data\":{\"coreData\":{\"accelSet\":{\"accelYaw\":0},\"accuracy\":{\"semiMajor\":12.7,\"semiMinor\":12.7},\"brakes\":{\"abs\":\"unavailable\",\"auxBrakes\":\"unavailable\",\"brakeBoost\":\"unavailable\",\"scs\":\"unavailable\",\"traction\":\"unavailable\",\"wheelBrakes\":{\"leftFront\":false,\"leftRear\":false,\"rightFront\":false,\"rightRear\":false,\"unavailable\":true}},\"heading\":321.0125,\"id\":\"G1\",\"msgCnt\":1,\"position\":{\"elevation\":154.7,\"latitude\":35.94911,\"longitude\":-83.928343},\"secMark\":36799,\"size\":{\"length\":250,\"width\":150},\"speed\":22.1},\"partII\":[{\"id\":\"VEHICLESAFETYEXT\",\"value\":{\"pathHistory\":{\"crumbData\":[{\"elevationOffset\":-19.8,\"latOffset\":7.55e-5,\"lonOffset\":0.0002609,\"timeOffset\":32.2},{\"elevationOffset\":-25.8,\"latOffset\":7.32e-5,\"lonOffset\":0.0003135,\"timeOffset\":34},{\"elevationOffset\":-34.5,\"latOffset\":0.0001027,\"lonOffset\":0.0004479,\"timeOffset\":37.2},{\"elevationOffset\":-128.2,\"latOffset\":0.000232,\"lonOffset\":0.0011832,\"timeOffset\":73.44}]},\"pathPrediction\":{\"confidence\":50,\"radiusOfCurve\":0}}},{\"id\":\"SUPPLEMENTALVEHICLEEXT\",\"value\":{\"classDetails\":{\"fuelType\":\"UNKNOWNFUEL\",\"hpmsType\":\"NONE\",\"keyType\":0,\"regional\":[],\"role\":\"BASICVEHICLE\"},\"regional\":[],\"vehicleData\":{\"bumpers\":{\"front\":0.5,\"rear\":0.6},\"height\":1.9},\"weatherProbe\":{},\"accelLong\":\"test\",\"accelLat\":\"test\",\"accelVert\":\"test\",\"yawRate\":\"test\",\"steeringWheelAngle\":\"test\",\"leftTurnSignalOn\":\"test\",\"rightTurnSignalOn\":\"test\",\"hazardSignalOn\":\"test\",\"fogLightOn\":\"test\",\"lowBeamHeadlightsOn\":\"test\",\"highBeamHeadlightsOn\":\"test\",\"automaticLightControlOn\":\"test\",\"daytimeRunningLightsOn\":\"test\",\"parkingLightsOn\":\"test\",\"wiperStatusFront\":\"test\",\"wiperStatusRear\":\"test\",\"wiperRateFront\":\"test\",\"wiperRateRear\":\"test\",\"eventAirBagDeployment\":\"test\",\"sunSensor\":\"test\",\"coefficientOfFriction\":\"test\",\"ambientAirTemperature\":\"test\",\"ambientAirPressure\":\"test\",\"transmissionState\":\"test\",\"vehicleSpeed\":\"test\",\"antiLockBrakeStatus\":\"test\",\"stabilityControlStatus\":\"test\",\"tractionControlStatus\":\"test\",\"brakeBoostApplied\":\"test\",\"brakeAppliedStatus\":\"test\",\"auxiliaryBrakeStatus\":\"test\",\"tirePressure\":\"test\",\"acceleratorPedalPosition\":\"test\",\"brakePedalPosition\":\"test\",\"disabledVehicle\":\"test\",\"stalledVehicle\":\"test\",\"airBagDeployment\":\"test\"}}]},\"dataType\":\"us.dot.its.jpo.ode.plugin.j2735.J2735Bsm\",\"schemaVersion\":1},\"schemaVersion\":1}";
    return redactor.getDocumentFromString(jsonString);
}

int main() {
    Redactor redactor;

    rapidjson::Document document = getTestDocument(redactor);
    // redactor.printDocument(document);

    std::string members[] = { 
                                "accelLong",
                                "accelLat",
                                "accelVert",
                                "yawRate",
                                "steeringWheelAngle",
                                "leftTurnSignalOn",
                                "rightTurnSignalOn",
                                "hazardSignalOn",
                                "fogLightOn",
                                "lowBeamHeadlightsOn",
                                "highBeamHeadlightsOn",
                                "automaticLightControlOn",
                                "daytimeRunningLightsOn",
                                "parkingLightsOn",
                                "wiperStatusFront",
                                "wiperStatusRear",
                                "wiperRateFront",
                                "wiperRateRear",
                                "eventAirBagDeployment",
                                "sunSensor",
                                "coefficientOfFriction",
                                "ambientAirTemperature",
                                "ambientAirPressure",
                                "transmissionState",
                                "vehicleSpeed",
                                "antiLockBrakeStatus",
                                "stabilityControlStatus",
                                "tractionControlStatus",
                                "brakeBoostApplied",
                                "brakeAppliedStatus",
                                "auxiliaryBrakeStatus",
                                "tirePressure",
                                "acceleratorPedalPosition",
                                "brakePedalPosition",
                                "disabledVehicle",
                                "stalledVehicle",
                                "airBagDeployment",
                            };

    auto& payload = document["payload"];
    auto& data = payload["data"];
    auto& partII = data["partII"];

    // get num members present that should be redacted before redaction
    int numMembersPresentBeforeRedaction = 0;
    for (int i = 0 ; i < sizeof(members)/sizeof(members[0]); i++) {
        std::string member = members[i];

        bool success = false;
        redactor.isMemberPresent(partII, member, success);

        numMembersPresentBeforeRedaction += success;
    }
    log("Num members present before redaction: " + std::to_string(numMembersPresentBeforeRedaction));

    // redact members
    int numRedactions = 0;
    for (int i = 0 ; i < sizeof(members)/sizeof(members[0]); i++) {
        std::string member = members[i];

        bool psuccess1 = false;
        redactor.isMemberPresent(partII, member, psuccess1);

        bool rsuccess = false;
        redactor.redactMemberByName(partII, member, rsuccess);

        bool psuccess2 = false;
        redactor.isMemberPresent(partII, member, psuccess2);

        numRedactions += rsuccess;
    }
    log("Num members redacted: " + std::to_string(numRedactions));

    // get num members present that should have been redacted after redaction
    int numMembersPresentAfterRedaction = 0;
    for (int i = 0 ; i < sizeof(members)/sizeof(members[0]); i++) {
        std::string member = members[i];

        bool success = false;
        redactor.isMemberPresent(partII, member, success);

        numMembersPresentAfterRedaction += success;
    }
    log("Num members present after redaction: " + std::to_string(numMembersPresentAfterRedaction));

    if (numMembersPresentBeforeRedaction == numMembersPresentAfterRedaction + numRedactions) {
        log("Redaction successful!");
    } else {
        log("Redaction failed!");
    }
    return 0;
}