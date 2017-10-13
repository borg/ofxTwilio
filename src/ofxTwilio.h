// =============================================================================
//
// ofxTwilio.h
// Twilio client using POCO
//
// Created by Andreas Borg on 10/2/17
//
// Copyright (c) 2015-2017 Andreas Borg <http://crea.tion.to>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// =============================================================================


/*
    Usage example
    Copy ssl folder to data folder.
    This is required to be able to make POST calls over SSL with POCO.
    
    
    ofxTwilio twilio;

    twilio.setCredentials("xxxxx","yyyyyy");
    twilio.addMsg("Hola Mr Borg");
    twilio.setFrom("+1203478xx");
    twilio.setTo("+1345345xx");
    addMediaURL("http://thatimage.com");
    ofxJSON reply =  twilio.send();
    cout<<reply<<endl;

*/


#ifndef _ofxTwilio
#define _ofxTwilio

#include "ofMain.h"

#include "Poco/Exception.h"
#include "Poco/SharedPtr.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/KeyConsoleHandler.h"


#include "Poco/Net/HTTPSession.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPSClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"
#include "Poco/Path.h"
#include "Poco/URI.h"
#include "Poco/Exception.h"
#include "Poco/URIStreamOpener.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/Net/HTTPSStreamFactory.h"

#include "Poco/Net/HTTPBasicCredentials.h"
#include "Poco/Net/SSLManager.h"
#include "Poco/Net/KeyConsoleHandler.h"
#include "Poco/Net/ConsoleCertificateHandler.h"


//Twilio response comes back in JSON
#include "ofxJSON.h"

using namespace Poco::Net;
using namespace Poco;


class SSLInitializer {
public:
    SSLInitializer() { Poco::Net::initializeSSL(); }

    ~SSLInitializer() { Poco::Net::uninitializeSSL(); }
};




class ofxTwilio {
	
  public:
	
	ofxTwilio();
    ~ofxTwilio();
	
    string twilioHost = "api.twilio.com";

    string twilioURL = "https://api.twilio.com";
    string fromNumber = "+XXXXXXX";
    // Twilio Account Sid
    string ACCOUNT_SID = "XXXX";
    // Twilio Auth Token
    string ACCOUNT_TOKEN = "XXXX";
    
    string API_VERSION = "2010-04-01";
    
    string message = "";
    string from = "";
    string to = "";
    string mediaURL = "";
    
	void setCredentials(string SID, string TOKEN);
	void beginSMS();
	void setTo(string toNumber);
    void setFrom(string fromNumber);
	void addMsg(string msg);
    void addMediaURL(string file);
    ofxJSON send();
    void reset();
};

#endif
