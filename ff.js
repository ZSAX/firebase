var firebaseConfig = {
    apiKey: "AIzaSyAhbKZiDt7JbdvJboUoFQRsmiyWXBJo99g",
    authDomain: "sg001-353df.firebaseapp.com",
    databaseURL: "https://sg001-353df.firebaseio.com",
    projectId: "sg001-353df",
    storageBucket: "sg001-353df.appspot.com",
    messagingSenderId: "1078764135313",
    appId: "1:1078764135313:web:22c0381fffabd0a3"
  };
  firebase.initializeApp(firebaseConfig);
  
var db = firebase.database();
var db1 = firebase.database();
var ref1 = db.ref("ESP32_motor");

FormData();



function FormData(){
//-------------------------------------------------------------------------------------------溫溼度 	
    const preObject1 = document.getElementById('Humidity');

    const dbRefObject1 = firebase.database().ref("ESP32_Test").child('Stream/dth');

    dbRefObject1.on('value', snap => console.log(snap.val()));
	dbRefObject1.on('value', snap => {
		preObject1.innerText = JSON.stringify(snap.val(),null,3).replace(/[,{}/"]/g, "");});
//-------------------------------------------------------------------------------------------土壤 	 	
	const preObject2 = document.getElementById('soil');

    const dbRefObject2 = firebase.database().ref("ESP32_Test").child('Stream/soil');

    dbRefObject2.on('value', snap => console.log(snap.val()));
	dbRefObject2.on('value', snap => {
		preObject2.innerText = JSON.stringify(snap.val(),null,3).replace(/[,{}/"]/g, "");;});	
//-------------------------------------------------------------------------------------------水位
	const preObject3 = document.getElementById('water');

    const dbRefObject3 = firebase.database().ref("ESP32_Test").child('Stream/water sensor');

    dbRefObject3.on('value', snap => console.log(snap.val()));
	dbRefObject3.on('value', snap => {
		preObject3.innerText = JSON.stringify(snap.val(),null,3).replace(/[,{}/"]/g, "");});		
		
}

function motor(){
	var StreamRef = ref1.child("water");
	StreamRef.set({  
    motor1: "ON",
});
}

