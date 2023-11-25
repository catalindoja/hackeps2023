import serial
import json
import firebase_admin
from firebase_admin import credentials
from firebase_admin import firestore


cred = credentials.Certificate('./weedcobot-firebase_Creds.json')
app = firebase_admin.initialize_app(cred)

db = firestore.client()


ser = serial.Serial('COM5', 9600)

while True:
    if ser.in_waiting > 0:
        try:
            payload = ser.readline().decode('utf-8').strip()
            data = json.loads(payload)
            print(data)
            document_id = "P_01_EPS"
            doc_ref = db.collection("plantes").document(document_id)
            doc_ref.set(data)
        except UnicodeDecodeError as e:
            print(f"UnicodeDecodeError: {e}")