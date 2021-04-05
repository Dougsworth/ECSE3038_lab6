from flask import Flask, request, jsonify, json
from flask_pymongo import PyMongo
from marshmallow import Schema, fields, ValidationError
from bson.json_util import dumps
from json import loads
from datetime import datetime



uri_update1 = "mongodb+srv://dougy:<password>@cluster0.vm12q.mongodb.net/myFirstDatabase?retryWrites=true&w=majority".format(
    upass, upass)


app = Flask(__name__)
app.config["MONGO_URI"] = uri_update1
mongo = PyMongo(app)

ClientData = {
    "tank_id": "t1",
    "percentage_full": 12
}


class Levels(Schema):
    tank_id = fields.String(required=True)
    percentage_full = fields.Integer(required=True)


def percent(x, in_min, in_max, out_min, out_max):
    return int((x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min)

# POST /data


@app.route("/tank", methods=["POST"])
def data_post():

    W_Levels = (request.json["water_Levels"])
    P_full = percent(W_Levels, 10, 200, 0, 100)
    ClientData["tank_id"] = request.json["tank_id"]
    ClientData["percentage_full"] = P_full
    try:
        C_Data = Levels().load(ClientData)
        clientUP = mongo.db.Levelss.insert_one(C_Data).inserted_id
        clientDN = mongo.db.Levelss.find_one(clientUP)
        
        now = datetime.now()
        dt = now.strftime("%d/%m/%Y %H:%M:%S")
        return {
            "success": True,
            "msg": dt,
            "date": "<datetime of respsonse>",
        }
    except ValidationError as ve:
        return ve.messages, 400


if __name__ == "__main__":
    app.run(debug=True)
