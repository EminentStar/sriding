var express = require('express');
var app = express();
var fs = require('fs');
var bodyParser = require('body-parser');

/**** DBMS setting ****/
var mongoose = require('mongoose');
mongoose.connect('mongodb://localhost:27017/test');
var db = mongoose.connection;
db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function callback() {
	console.log('mongo db connection OK.');
});


/* 자전거 주행  정보 테이블 스키마  */
var ridingInfoSchema = mongoose.Schema({
	email: String,	//facebook id
	ridingStartTime: String,	
	ridingStopTime: String,
	ridingTime: String,
	ridingBreakTime: String,
	entireRidingTime: String,
	entireRidingDistance: String,
	startingLocationName: String,
	startingLocationLatitude: String,
	startingLocationLongitude: String,
	destinationName: String,
	destinationLatitude: String,
	destinationLongitude: String,
	consumedCal: String,
	averageSpeed: String,
	maxSpeed: String,
	instantSpeed: String,
	instantHeight: String
});

ridingInfoSchema.methods.speak = function(){
	console.log("email: %s, ridingStartTime: %s, ridingStopTime: %s, ridingTime: %s, ridingBreakTime: %s, entireRidingTime: %s, entireRidingDistance: %s, startingLocationName: %s, startingLocationLatitude: %s, startingLocationLongitude: %s, destinationName: %s, destinationLatitude: %s, destinationLongitude: %s, consumedCal: %s , averageSpeed: %s, maxSpeed: %s, instantSpeed: %s, instantHeight: %s  ",this.email, this.ridingStartTime, this.ridingStopTime, this.ridingTime, this.ridingBreakTime, this.entireRidingTime, this.entireRidingDistance, this.startingLocationName, this.startingLocationLatitude, this.startingLocationLongitude, this.destinationName, this.destinationLatitude, this.destinationLongitude, this.consumedCal, this.averageSpeed, this.maxSpeed, this.instantSpeed, this.instantHeight);
}

var RidingInfo = mongoose.model("RidingInfo", ridingInfoSchema);


/**** server application ****/

app.use(bodyParser.urlencoded());
app.use(bodyParser.json());

app.get('/', function(req, res){
	console.log("GET '/' requested");
})

app.post('/ridingInfo', function(req,res){
	var jsonContent = req.body;
	
	var RInfoIns = new RidingInfo({ email: jsonContent.email, ridingStartTime: jsonContent.ridingStartTime, ridingStopTime: jsonContent.ridingStopTime, ridingTime: jsonContent.ridingTime, ridingBreakTime: jsonContent.ridingBreakTime, entireRidingTime: jsonContent.entireRidingTime, entireRidingDistance: jsonContent.entireRidingDistance, startingLocationName: jsonContent.startingLocationName, startingLocationLatitude: jsonContent.startingLocationLatitude, startingLocationLongitude: jsonContent.startingLocationLongitude, destinationName: jsonContent.destinationName, destinationLatitude: jsonContent.destinationLatitude, destinationLongitude: jsonContent.destinationLongitude, consumedCal: jsonContent.consumedCal, averageSpeed: jsonContent.averageSpeed, maxSpeed: jsonContent.maxSpeed, instantSpeed: jsonContent.instantSpeed, instantHeight: jsonContent.instantHeight});

	RInfoIns.save(function(err, RInfoIns){
		if(err) return console.error(err);
		RInfoIns.speak();
	});
	
	console.log("POST '/ridingInfo' requested.");
})


//response to client for sending riding information requested
app.post('/record', function(req, res){
	var jsonContent = req.body;
	var str = jsonContent.facebookId;
	var facebookId = Number(str);
	
	console.log("log : facebookId : ", facebookId);

	var result = "{"
	SRidingTest.find({_id:facebookId}, function(err, docs){
		if(err){
			return console.error.bind(console, 'finding error:');
		}
		for(var i = 0 , size = docs.length; i < size; i++){
			if(i != 0) result = result + ", ";
			var id = docs[i]._id;
			var startingLocation = docs[i].startingLocation;
			result = result + "{\'id\' : "+ id + ", \'startingLocation\' : " + startingLocation + "}";
		}
		
		result = result + "}";

		res.end(result);
	});

	console.log("POST '/record requested.'");
})


var server = app.listen(8081, function(){
	var host = server.address().address
	var port = server.address().port

	console.log('Example app listening at http://%s:%s', host, port);
})

