// =============================================================================
//
// ofxTwilio.cpp
// TJXMachine
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



#include "ofxTwilio.h"

//------------------------------------------------------------------
ofxTwilio::ofxTwilio(){


};


//------------------------------------------------------------------
ofxTwilio::~ofxTwilio(){


};

void ofxTwilio::setCredentials(string SID, string TOKEN){
    ACCOUNT_SID = SID;
    ACCOUNT_TOKEN = TOKEN;
};


void ofxTwilio::beginSMS(){};


void ofxTwilio::setTo(string toNumber){
    to = toNumber;
};


void ofxTwilio::setFrom(string fromNumber){
    from = fromNumber;
};


void ofxTwilio::addMsg(string msg){
    message = msg;
};

/*
Needs to be hosted online
*/
void ofxTwilio::addMediaURL(string file){
    mediaURL = file;
};


/*
curl 'https://api.twilio.com/2010-04-01/Accounts/AC6e585b2bffb50a5c60399d5efd3fb11c/Messages.json' -X POST \
--data-urlencode 'To=+13478816615' \
--data-urlencode 'From=+12019497899' \
--data-urlencode 'Body=Hey there' \
-u AC6e585b2bffb50a5c60399d5efd3fb11c:8f747163e1c9a65c11f5aff1086fd4b8




TJX
SID
SKc2bcc59aef6b67077bcb777afd415193
KEY TYPE
Standard
SECRET
1pxyXHJ5l7yP5Ha6wThayWewFRcLwSd5


*/


ofxJSON ofxTwilio::send(){
    ofxJSON jsonReply;
    
    try {
        
        SSLInitializer sslInitializer;
        
        SharedPtr<InvalidCertificateHandler> ptrCert = new ConsoleCertificateHandler(false);
        Context::Ptr ptrContext = new Context(Context::CLIENT_USE, "", "", ofToDataPath("ssl/cacert.pem"), Context::VERIFY_STRICT, 9, false, "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
        SSLManager::instance().initializeClient(0, ptrCert, ptrContext);



        HTTPSClientSession session(twilioHost);
        session.setKeepAlive(true);
        
        string url =   "/2010-04-01/Accounts/" + ACCOUNT_SID + "/Messages.json";
        
        cout<<url<<endl;
        
        HTTPRequest req(HTTPRequest::HTTP_POST, url, HTTPMessage::HTTP_1_1);
        
        
        HTTPBasicCredentials cred(ACCOUNT_SID, ACCOUNT_TOKEN);
        cred.authenticate(req);
        
        
        req.setContentType("application/x-www-form-urlencoded");
        //req.setKeepAlive(true); // notice setKeepAlive is also called on session (above)



        string reqBody = "";
        
        reqBody += "Body="+message;
        reqBody += "&From="+from;
        reqBody += "&To="+to;
        if(mediaURL != ""){
            reqBody += "&MediaUrl="+mediaURL;
        }
        
        
        string encoded;
        Poco::URI::encode(reqBody,"",encoded);
        reqBody = encoded;
        cout<<reqBody<<endl;
        
        
        req.setContentLength( reqBody.length() );

        ostream& myOStream = session.sendRequest(req); // sends request, returns open stream
        myOStream << reqBody;  // sends the body

        req.write(cout);

        HTTPResponse res;
        //cout << res.getStatus() << " " << res.getReason() << endl;
        istream& iStr = session.receiveResponse(res);  // get the response from server
        //cout << iStr.rdbuf();  // dump server response so you can view it
        
        stringstream ss;
        ss << iStr.rdbuf();
        
        string str = ss.str();
        
        string decoded;
        Poco::URI::decode(str,decoded);
        //cout<<decoded<<endl;
        
        jsonReply.parse(decoded);
        
        reset();
    }
    catch (Exception &ex){
        cerr << ex.displayText() << endl;
    }
    
    
    return jsonReply;
};

void ofxTwilio::reset(){
    mediaURL = "";
    message = "";
    from = "";
    to = "";
};
