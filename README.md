
**ofxTwilio**  
A openFrameworks & POCO only client for sending SMS messages using Twilio.

Created by Andreas Borg, 2017  
[crea.tion.to](http://crea.tion.to)

**Usage**

```
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
```
 

**License**  
Whatever [Twilio](https://www.twilio.com) C++ SDK license is under.
