#include <Arduino.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <credentials.h>

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

//Default Values
double power = 300.843;
double volt = 255;
double current = 12.678;

void CallbackFunc(TokenInfo info){
  Serial.printf("Token Info: type = %s, status = %s\n", getTokenType(info).c_str(),getTokenStatus(info).c_str() );
  return;
}

void firebaseInit(){
    Serial.println("Establishing Connection to FireStore...\n");
    config.api_key = FIRE_API_KEY;

    auth.user.email = FIRE_AUTH_EMAIL;

    auth.user.password = FIRE_AUTH_PASS;

    config.token_status_callback = CallbackFunc;

    Firebase.begin(&config, &auth);
    Firebase.reconnectWiFi(true);

    Serial.println("Firebase Initialization Successful");
}

//Order to learn for documentPath -> Collection - Document - collection - Document
void createDocument(String documentPath){
    if(Firebase.ready()){
        FirebaseJson content;
        content.set("fields/power/doubleValue",String(power).c_str());
        content.set("fields/volt/doubleValue",String(volt).c_str());
        content.set("fields/current/doubleValue",String(current).c_str());
        if(Firebase.Firestore.createDocument(&fbdo, FIRE_PROJECT_ID,"", documentPath.c_str(), content.raw())){
            Serial.printf("ok\n%s\n\n",fbdo.payload().c_str());
            return;
        }
        else{
            Serial.println(fbdo.errorReason());
            return;
        }
    }
    else{
        Serial.println("Firebase Not Initialized Properly \n");
        return;
    }
}

//Order to learn for documentPath -> Collection - Document - collection - Document
void updateDocument(String documentPath, String fieldName, float newVal){
    if(Firebase.ready()){
        FirebaseJson content;
        
        content.set("fields/" + String(fieldName) + "/doubleValue",String(newVal).c_str());
        
        if(Firebase.Firestore.patchDocument(&fbdo, FIRE_PROJECT_ID, "", documentPath.c_str(), content.raw(), fieldName)){
            Serial.printf("ok\n%s\n\n",fbdo.payload().c_str());
            return;
        }
        else{
            Serial.println("Document Update failed due to: \n");
            Serial.println(fbdo.errorReason());
            return;
        }
    }
    else{
        Serial.println("Firebase Not Initialized Properly \n");
        return;
    }

}

String readDocument(String documentPathBeforcollectionId , String collectionId,  String fieldName){
    if(Firebase.ready()){
        FirebaseJson query;

        query.set("select/fields/[0]/fieldsPath", fieldName);
        query.set("from/collectionId", collectionId);
        query.set("from/allDescendants", true);
        if (Firebase.Firestore.runQuery(&fbdo, FIRE_PROJECT_ID, "" , documentPathBeforcollectionId , &query )){
            String data = fbdo.payload();
            Serial.println(data);
            return data;
        }
        else{
            Serial.println(fbdo.errorReason());
            return "-1";
        }
    }
    else{
        Serial.println("Firebase Not Initialized Properly \n");
        return "-2";
    }
}
