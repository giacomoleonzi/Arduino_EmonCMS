
/*
Copyright (c) 2015 Giacomo Leonzi. All right reserved.

  ArduinoEmoncms - Library to pubblish data on Emoncsm.org

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/


#include "ArduinoEmoncms.h"


ArduinoEmoncms::ArduinoEmoncms(String host, int port, String APIKEY)	{
	_host=host;
	_port=port;
	_APIKEY=APIKEY;
	_jsonString ="";
}

/*************************************************************************************
* addValue - function to build the string json format to comunicate with emoncms.org*
* you need to give a name value colled key and it's value in a int variable				 *
************************************************************************************/

void ArduinoEmoncms::addValue(String key, int value)  {

	if(_jsonString!="")_jsonString +=",";//add the comma only when is not the first or only data added
	_jsonString += key;
	_jsonString += ":";
	_jsonString += value;
}

/*************************************************************************************
* pubblish - function to pubblish on emoncms.org the data measured                  *
* this function build the string to send, open the comunication through the server  *
* and send all the data.
************************************************************************************/

String ArduinoEmoncms::pubblish()  {

	String response;
	//begin to build the string to send
	String _url="GET /api/post?json={";
	_url+=_jsonString;
	_url+="}&apikey=";
	_url+=String(_APIKEY);
	_url+=" HTTP/1.1\r\nHost: emoncms.org\r\nConnection: keep-alive\r\nAccept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\nUpgrade-Insecure-Requests: 1\r\nUser-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/44.0.2403.157 Safari/537.36\r\nAccept-Encoding: gzip, deflate, sdch\r\nAccept-Language: it-IT,it;q=0.8,en-US;q=0.6,en;q=0.4\r\nCookie: PHPSESSID=j6ef0j34cn3pjnhgma4ha2sic3\r\n\r\n";
	//ended to build the string to send
	_jsonString=""; //clear the string with data ready for the next lecture

	_host.toCharArray(_host2, _host.length()+1); //client.connect function need a char* address
	/*Serial.print("_host:");
	Serial.print(_host);
	Serial.print("_host:");
	Serial.print(_host.length());
	Serial.print("-host2:");
	Serial.print(_host2);
	Serial.println("-");*/
	if (_client.connect(_host2, _port)) {
		_client.println(_url);
		Serial.print("Data sent");
		unsigned long timeToRead = millis();
		while (millis() - timeToRead < 1000) {
			while (_client.available()) {
				response = _client.readStringUntil('\r');
			}
		}
	}
	else Serial.print("Connection failed!");
	return response;
}
