#ifndef FIREBASE_H
#define FIREBASE_H

#include <Arduino.h>

void firebaseInit();
void createDocument(String documentPath);
void updateDocument(String documentPath, String fieldName, float newVal);
String readDocument(String documentPathBeforcollectionId , String collectionId,  String fieldName);

#endif
