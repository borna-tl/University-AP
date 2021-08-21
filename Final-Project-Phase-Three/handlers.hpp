#ifndef _MY_HANDLERS_
#define _MY_HANDLERS_

#include "server/server.hpp"
#include "Application.hpp"
#include <iostream>

class SignupForm : public RequestHandler {
public:
	SignupForm(Application* utrip, Status* status_, std::map <std::string, User*>* sessions_){
        app = utrip;
		status = status_;
		sessions = sessions_;
    }
	Response *callback(Request *req);
private:
	Application* app;
	Status* status;
	std::map <std::string, User*>* sessions;
};

class ShowDynamicHome : public RequestHandler {
public:
	ShowDynamicHome(Application* utrip, Status* status_, std::map <std::string, User*>* sessions_){
        app = utrip;
		status = status_;
		sessions = sessions_;
    }
	Response *callback(Request *req);
private:
	Application* app;
	Status* status;
	std::map <std::string, User*>* sessions;
};

class CheckSignup : public RequestHandler {
public:
	CheckSignup(Application* utrip, Status* status_, std::map <std::string, User*>* sessions_){
        app = utrip;
		status = status_;
		sessions = sessions_;
    }
	Response *callback(Request *req);
private:
	Application* app;
	Status* status;
	std::map <std::string, User*>* sessions;
};

class ShowLoggedinHome : public RequestHandler {
public:
	ShowLoggedinHome(Application* utrip, Status* status_, std::map <std::string, User*>* sessions_){
        app = utrip;
		status = status_;
		sessions = sessions_;
    }
	Response *callback(Request *req);
private:
	Application* app;
	Status* status;
	std::map <std::string, User*>* sessions;
};
class ShowLoginForm : public RequestHandler {
public:
	ShowLoginForm(Application* utrip, Status* status_, std::map <std::string, User*>* sessions_){
        app = utrip;
		status = status_;
		sessions = sessions_;
    }
	Response *callback(Request *req);
private:
	Application* app;
	Status* status;
	std::map <std::string, User*>* sessions;
};
class CheckLogin : public RequestHandler {
public:
	CheckLogin(Application* utrip, Status* status_, std::map <std::string, User*>* sessions_){
        app = utrip;
		status = status_;
		sessions = sessions_;
    }
	Response *callback(Request *req);
private:
	Application* app;
	Status* status;
	std::map <std::string, User*>* sessions;
};
class CheckLogout : public RequestHandler {
public:
	CheckLogout(Application* utrip, Status* status_, std::map <std::string, User*>* sessions_){
        app = utrip;
		status = status_;
		sessions = sessions_;
    }
	Response *callback(Request *req);
private:
	Application* app;
	Status* status;
	std::map <std::string, User*>* sessions;
};
class ShowWallet : public RequestHandler {
public:
	ShowWallet(Application* utrip, Status* status_, std::map <std::string, User*>* sessions_){
        app = utrip;
		status = status_;
		sessions = sessions_;
    }
	Response *callback(Request *req);
private:
	Application* app;
	Status* status;
	std::map <std::string, User*>* sessions;
};
class ShowHotel : public RequestHandler {
public:
	ShowHotel(Application* utrip, Status* status_, std::map <std::string, User*>* sessions_){
        app = utrip;
		status = status_;
		sessions = sessions_;
    }
	Response *callback(Request *req);
private:
	Application* app;
	Status* status;
	std::map <std::string, User*>* sessions;
};
class CheckWallet : public RequestHandler {
public:
	CheckWallet(Application* utrip, Status* status_, std::map <std::string, User*>* sessions_){
        app = utrip;
		status = status_;
		sessions = sessions_;
    }
	Response *callback(Request *req);
private:
	Application* app;
	Status* status;
	std::map <std::string, User*>* sessions;
};

#endif
